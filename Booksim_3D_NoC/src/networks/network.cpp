// $Id$

/*
 Copyright (c) 2007-2012, Trustees of The Leland Stanford Junior University
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this 
 list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this
 list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*network.cpp
 *
 *This class is the basis of the entire network, it contains, all the routers
 *channels in the network, and is extended by all the network topologies
 *
 */

#include <cassert>
#include <sstream>
//Orion Power Support
#include <fstream>

#include "booksim.hpp"
#include "network.hpp"
#include "trafficmanager.hpp"
#include "kncube.hpp"
#include "fly.hpp"
#include "cmesh.hpp"
#include "flatfly_onchip.hpp"
#include "qtree.hpp"
#include "tree4.hpp"
#include "fattree.hpp"
#include "anynet.hpp"
#include "dragonfly.hpp"
#include "trace.hpp"
#include "bft1.hpp"
#include "bft2.hpp"
#include "bft21.hpp"
#include "bft211.hpp" 
#include "bft22.hpp"
#include "bft23.hpp"
#include "bft3.hpp"
Network::Network( const Configuration &config, const string & name ) :
  TimedModule( 0, name )
{
  _size     = -1; 
  _nodes    = -1; 
  _channels = -1;
  _classes  = config.GetInt("classes");
  _TPtrace1 =  config.GetInt( "Temp_series_data");
}

Network::~Network( )
{
  for ( int r = 0; r < _size; ++r ) {
    if ( _routers[r] ) delete _routers[r];
  }
  for ( int s = 0; s < _nodes; ++s ) {
    if ( _inject[s] ) delete _inject[s];
    if ( _inject_cred[s] ) delete _inject_cred[s];
  }
  for ( int d = 0; d < _nodes; ++d ) {
    if ( _eject[d] ) delete _eject[d];
    if ( _eject_cred[d] ) delete _eject_cred[d];
  }
  for ( int c = 0; c < _channels; ++c ) {
    if ( _chan[c] ) delete _chan[c];
    if ( _chan_cred[c] ) delete _chan_cred[c];
  }
}

Network * Network::New(const Configuration & config, const string & name)
{
  const string topo = config.GetStr( "topology" );
  Network * n = NULL;
  if ( topo == "torus" ) {
    KNCube::RegisterRoutingFunctions() ;
    n = new KNCube( config, name, false );
  } else if ( topo == "mesh" ) {
    KNCube::RegisterRoutingFunctions() ;
    n = new KNCube( config, name, true );
    topon=3;
  } else if ( topo == "cmesh" ) {
    CMesh::RegisterRoutingFunctions() ;
    n = new CMesh( config, name );
  } else if ( topo == "fly" ) {
    KNFly::RegisterRoutingFunctions() ;
    n = new KNFly( config, name );
  } else if ( topo == "qtree" ) {
    QTree::RegisterRoutingFunctions() ;
    n = new QTree( config, name );
  } else if ( topo == "tree4" ) {
    Tree4::RegisterRoutingFunctions() ;
    n = new Tree4( config, name );
  } else if ( topo == "fattree" ) {
    FatTree::RegisterRoutingFunctions() ;
    n = new FatTree( config, name );
  } 
  else if ( topo == "bft1"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft1(config, name);
    topon=0;// 4 layer bft
  }
  else if ( topo == "bft2"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft2(config, name);
    topon=1; // 2d with acc length
  }
    else if ( topo == "bft3"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft3(config, name);
    topon=2; // 2d with acc length
  }
  else if ( topo == "bft21"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft21(config, name);
    topon=111; // 2d with acc length
  }
  else if ( topo == "bft211"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft211(config, name);
    topon=111; // 2d with acc length
  }
  else if ( topo == "bft23"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft23(config, name);
    topon=11; // 2d with acc length
  }
  else if ( topo == "bft22"){
    //Bft1::RegisterRoutingFunctions() ;
    n = new Bft22(config, name);
    topon=111; // 2d with acc length
  }
  else if ( topo == "flatfly" ) {
    FlatFlyOnChip::RegisterRoutingFunctions() ;
    n = new FlatFlyOnChip( config, name );
  } else if ( topo == "anynet"){
    AnyNet::RegisterRoutingFunctions() ;
    n = new AnyNet(config, name);
  } else if ( topo == "dragonflynew"){
    DragonFlyNew::RegisterRoutingFunctions() ;
    n = new DragonFlyNew(config, name);
  } else {
    cerr << "Unknown topology: " << topo << endl;
  }
  
  /*legacy code that insert random faults in the networks
   *not sure how to use this
   */
  if ( n && ( config.GetInt( "link_failures" ) > 0 ) ) {
    n->InsertRandomFaults( config );
  }
  return n;
}

void Network::_Alloc( )
{
  assert( ( _size != -1 ) && 
	  ( _nodes != -1 ) && 
	  ( _channels != -1 ) );

  _routers.resize(_size);
  gNodes = _nodes;
  Nsize =_nodes;
  Nport =6;
  
  /*booksim used arrays of flits as the channels which makes have capacity of
   *one. To simulate channel latency, flitchannel class has been added
   *which are fifos with depth = channel latency and each cycle the channel
   *shifts by one
   *credit channels are the necessary counter part
   */
  _inject.resize(_nodes);
  _inject_cred.resize(_nodes);
  for ( int s = 0; s < _nodes; ++s ) {
    ostringstream name;
    name << Name() << "_fchan_ingress" << s;
    _inject[s] = new FlitChannel(this, name.str(), _classes);
    _inject[s]->SetSource(NULL, s);
    _timed_modules.push_back(_inject[s]);
    name.str("");
    name << Name() << "_cchan_ingress" << s;
    _inject_cred[s] = new CreditChannel(this, name.str());
    _timed_modules.push_back(_inject_cred[s]);
  }
  _eject.resize(_nodes);
  _eject_cred.resize(_nodes);
  for ( int d = 0; d < _nodes; ++d ) {
    ostringstream name;
    name << Name() << "_fchan_egress" << d;
    _eject[d] = new FlitChannel(this, name.str(), _classes);
    _eject[d]->SetSink(NULL, d);
    _timed_modules.push_back(_eject[d]);
    name.str("");
    name << Name() << "_cchan_egress" << d;
    _eject_cred[d] = new CreditChannel(this, name.str());
    _timed_modules.push_back(_eject_cred[d]);
  }
  _chan.resize(_channels);
  _chan_cred.resize(_channels);
  for ( int c = 0; c < _channels; ++c ) {
    ostringstream name;
    name << Name() << "_fchan_" << c;
    _chan[c] = new FlitChannel(this, name.str(), _classes);
    _timed_modules.push_back(_chan[c]);
    name.str("");
    name << Name() << "_cchan_" << c;
    _chan_cred[c] = new CreditChannel(this, name.str());
    _timed_modules.push_back(_chan_cred[c]);
  }
}

void Network::ReadInputs( )
{
  for(deque<TimedModule *>::const_iterator iter = _timed_modules.begin();
      iter != _timed_modules.end();
      ++iter) {
    (*iter)->ReadInputs( );
  }
}

void Network::Evaluate( )
{
  for(deque<TimedModule *>::const_iterator iter = _timed_modules.begin();
      iter != _timed_modules.end();
      ++iter) {
    (*iter)->Evaluate( );
  }
}

void Network::WriteOutputs( )
{
  for(deque<TimedModule *>::const_iterator iter = _timed_modules.begin();
      iter != _timed_modules.end();
      ++iter) {
    (*iter)->WriteOutputs( );
  }
}

void Network::WriteFlit( Flit *f, int source )
{
  assert( ( source >= 0 ) && ( source < _nodes ) );
  _inject[source]->Send(f);
}

Flit *Network::ReadFlit( int dest )
{
  assert( ( dest >= 0 ) && ( dest < _nodes ) );
  return _eject[dest]->Receive();
}

void Network::WriteCredit( Credit *c, int dest )
{
  assert( ( dest >= 0 ) && ( dest < _nodes ) );
  _eject_cred[dest]->Send(c);
}

Credit *Network::ReadCredit( int source )
{
  assert( ( source >= 0 ) && ( source < _nodes ) );
  return _inject_cred[source]->Receive();
}

void Network::InsertRandomFaults( const Configuration &config )
{
  Error( "InsertRandomFaults not implemented for this topology!" );
}

void Network::OutChannelFault( int r, int c, bool fault )
{
  assert( ( r >= 0 ) && ( r < _size ) );
  _routers[r]->OutChannelFault( c, fault );
}

double Network::Capacity( ) const
{
  return 1.0;
}

/* this function can be heavily modified to display any information
 * neceesary of the network, by default, call display on each router
 * and display the channel utilization rate
 */
void Network::Display( ostream & os ) const
{
  for ( int r = 0; r < _size; ++r ) {
    _routers[r]->Display( os );
  }
}

void Network::DumpChannelMap( ostream & os, string const & prefix ) const
{
  os << prefix << "source_router,source_port,dest_router,dest_port" << endl;
  for(int c = 0; c < _nodes; ++c)
    os << prefix
       << "-1," 
       << _inject[c]->GetSourcePort() << ',' 
       << _inject[c]->GetSink()->GetID() << ',' 
       << _inject[c]->GetSinkPort() << endl;
  for(int c = 0; c < _channels; ++c)
    os << prefix
       << _chan[c]->GetSource()->GetID() << ',' 
       << _chan[c]->GetSourcePort() << ',' 
       << _chan[c]->GetSink()->GetID() << ',' 
       << _chan[c]->GetSinkPort() << endl;
  for(int c = 0; c < _nodes; ++c)
    os << prefix
       << _eject[c]->GetSource()->GetID() << ',' 
       << _eject[c]->GetSourcePort() << ',' 
       << "-1," 
       << _eject[c]->GetSinkPort() << endl;
}

void Network::DumpNodeMap( ostream & os, string const & prefix ) const
{
  os << prefix << "source_router,dest_router" << endl;
  for(int s = 0; s < _nodes; ++s)
    os << prefix
       << _eject[s]->GetSource()->GetID() << ','
       << _inject[s]->GetSink()->GetID() << endl;
}

// MoRi
void Network::_PowerReports(int report_mode, string fileout, long power_time)
{
  

  ofstream PowerOut,PowerOut1;
  string Ptrace_file1="ptrace.txt";
  PowerOut.open(fileout.c_str(), std::ofstream::app);
  //string Ptrace_file1 = config.GetStr( "Ptrace_file" );
  PowerOut1.open(Ptrace_file1.c_str(), std::ofstream::app);
  PowerOut1 <<"power time \n ======================= " <<power_time<<endl;
  double total_power_crossbar   = 0.0;
  double total_power_buffer     = 0.0;
  double total_power_link       = 0.0;
  double total_power_SW_arbiter = 0.0;
  double total_power_VC_arbiter = 0.0;
  double total_power_routing = 0.0;
  
  double static_power_crossbar   = 0.0;
  double static_power_buffer     = 0.0;
  double static_power_link       = 0.0;
  double static_power_SW_arbiter = 0.0;
  double static_power_VC_arbiter = 0.0;
  double static_power_routing    = 0.0;
  
  double total_power_CSRegister = 0.0;
  int    total_number_of_crossed_flits=0;
  int    total_number_of_crossed_headerFlits=0;
  int    total_number_of_calls_of_power_functions=0;

  if (report_mode == 0)
  {
     double router_power_s =  _routers[0]->_orion_router_power.I_crossbar_static * Vdd * SCALE_S  * bitwidth64x + _routers[0]->_orion_router_power.I_buf_static * Vdd * SCALE_S * bitwidth64x/2.0 + _routers[0]->_orion_router_power.I_sw_arbiter_static * Vdd * SCALE_S + _routers[0]->_orion_router_power.I_vc_arbiter_static * Vdd * SCALE_S;
    for(int r = 0; r < _size; r++ )
    {

     total_number_of_crossed_flits += _routers[r]->_number_of_crossed_flits;
     total_number_of_crossed_headerFlits += _routers[r]->_number_of_crossed_headerFlits;
     total_number_of_calls_of_power_functions += _routers[r]->_number_of_calls_of_power_functions;

      //double SIM_crossbar_report(SIM_crossbar_t *crsbar)
      total_power_crossbar += SIM_crossbar_report(&(_routers[r]->_orion_router_power.crossbar));

      //double SIM_array_power_report(SIM_array_info_t *info, SIM_array_t *arr );
      total_power_buffer += SIM_array_power_report(&(_routers[r]->_orion_router_info.in_buf_info),&(_routers[r]->_orion_router_power.in_buf));
      //double SIM_link_power_report(Router * current_router );
      total_power_link += SIM_link_power_report(_routers[r]);
      static_power_link += SIM_link_power_report_static(_routers[r]);
      //double SIM_arbiter_report(SIM_arbiter_t *arb);
      total_power_SW_arbiter += SIM_arbiter_report(&(_routers[r]->_orion_router_power.sw_out_arb));
      if(!(PARM_v_channel < 2 && PARM_v_class < 2))
	total_power_VC_arbiter += SIM_arbiter_report(&(_routers[r]->_orion_router_power.vc_out_arb));
     //individual router Power
   if((_TPtrace1==1))
        {
      double router_power=SIM_crossbar_report(&(_routers[r]->_orion_router_power.crossbar))+SIM_array_power_report(&(_routers[r]->_orion_router_info.in_buf_info),&(_routers[r]->_orion_router_power.in_buf))+SIM_arbiter_report(&(_routers[r]->_orion_router_power.sw_out_arb))+SIM_arbiter_report(&(_routers[r]->_orion_router_power.sw_out_arb));
       double link_p=SIM_link_power_report(_routers[r])+SIM_link_power_report_static(_routers[r]);
      double router_power_d=router_power*bitwidth64x*(PARM_Freq/power_time);
      router_power=router_power_d+router_power_s+link_p;      
      PowerOut1 <<"Router-"<<r<<"="<< router_power_s <<"+"<<router_power_d<<"+"<<link_p<<"="<<router_power<<endl;
       }
     }
      double link_lenght1 = 0.001;
      double total_link_power1= 0.0;
      double HZ_link_power= 0.0;
      double TSVlink_power= 0.0;
      double TSVlink_power1= 0.0;
      //double total_Tlink_power2= 0.0;
      //double total_Tlink_power1= 0.0;
      double leakage_link_power= 0.0;
      double total_link_power2= 0.0;
      double Pleakage= 0.0;
    //  double link_power1= 0.0, slink_power1=0.0;
//     cout<<"bitwidth64x"<<bitwidth64x<<"PARM_flit_width"<<PARM_flit_width<<endl;
    if (topon==0)
     {
        double link_l1 = 0.0093,link_l2= 0.0089,link_l3= 0.0044,link_l4= 0.004,link_l5= 0.0001;
      double  pl11 =0.00, pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00;
       
        pl11 = (LinkDynamicEnergyPerBitPerMeter(link_l1, PARM_Vdd)) * link_l1 * PARM_flit_width / 2 * l1 * bitwidth64x * PARM_Freq / power_time;
        pl12 = (LinkDynamicEnergyPerBitPerMeter(link_l2, PARM_Vdd)) * link_l2 * PARM_flit_width / 2 * l2 * bitwidth64x * PARM_Freq / power_time;
        pl13 = (LinkDynamicEnergyPerBitPerMeter(link_l3, PARM_Vdd)) * link_l3 * PARM_flit_width / 2 * l3 * bitwidth64x * PARM_Freq / power_time;
        pl14 = (LinkDynamicEnergyPerBitPerMeter(link_l4, PARM_Vdd)) * link_l4 * PARM_flit_width / 2 * l4 * bitwidth64x * PARM_Freq / power_time;
        pl15 = (LinkDynamicEnergyPerBitPerMeter(link_l5, PARM_Vdd)) * link_l5 * PARM_flit_width / 2 * l5 * bitwidth64x * PARM_Freq / power_time;
       
      
       HZ_link_power=pl11+pl12+pl13+pl14+pl15;
       
       
       
      pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00; 
      pl11 = (LinkLeakagePowerPerMeter(link_l1, Vdd)) * link_l1 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl12 = (LinkLeakagePowerPerMeter(link_l2, Vdd)) * link_l2 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl13 = (LinkLeakagePowerPerMeter(link_l3, Vdd)) * link_l3 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl14 = (LinkLeakagePowerPerMeter(link_l4, Vdd)) * link_l4 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl15 = (LinkLeakagePowerPerMeter(link_l5, Vdd)) * link_l5 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      Pleakage=+pl11+pl12+pl13+pl14+pl15;
      cout << "Horizntal Links in 2D BFT links and link usage" <<endl<<" L1 = "<<link_l1 <<" L2 = "<<link_l2 <<" L3 =  "<<link_l3 <<" L4 = "<<link_l4 <<" L5  =  "<<link_l5<<endl;
      cout <<" L1 =  "<<l1 <<" L2 = "<<l2 <<" L3 = "<<l3 <<" L4 =  "<<l4 <<" L5 = "<<l5<<endl;
      
    //  cout << "VL Link count = " <<lt1<<endl;

      //TSVlink_power =  0.0000042 * lt1 * PARM_flit_width  * bitwidth64x / power_time;
       total_link_power1=HZ_link_power ;//+ TSVlink_power;
     //  cout << "TSV Link power = " << TSVlink_power<<endl;
       cout << "HZ Link power = " <<HZ_link_power<<endl;
       
      //total_link_power1 /=_time;

      cout << "DT Link power = " << total_link_power1<<endl;
      
        
        
    }
    else if (topon==1)
    {
     double link_l11 = 0.0001,link_l1 = 0.0001,link_l2= 0.0036,link_l3= 0.004,link_l4= 0.0076,link_l5= 0.007;
     double pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00;
        pl1 = (LinkDynamicEnergyPerBitPerMeter(link_l11, PARM_Vdd)) * link_l11 * PARM_flit_width / 2 * ll1 * bitwidth64x * PARM_Freq / power_time;
        pl11 = (LinkDynamicEnergyPerBitPerMeter(link_l1, PARM_Vdd)) * link_l1 * PARM_flit_width / 2 * l1 * bitwidth64x * PARM_Freq / power_time;
        pl12 = (LinkDynamicEnergyPerBitPerMeter(link_l2, PARM_Vdd)) * link_l2 * PARM_flit_width / 2 * l2 * bitwidth64x * PARM_Freq / power_time;
        pl13 = (LinkDynamicEnergyPerBitPerMeter(link_l3, PARM_Vdd)) * link_l3 * PARM_flit_width / 2 * l3 * bitwidth64x * PARM_Freq / power_time;
        pl14 = (LinkDynamicEnergyPerBitPerMeter(link_l4, PARM_Vdd)) * link_l4 * PARM_flit_width / 2 * l4 * bitwidth64x * PARM_Freq / power_time;
        pl15 = (LinkDynamicEnergyPerBitPerMeter(link_l5, PARM_Vdd)) * link_l5 * PARM_flit_width / 2 * l5 * bitwidth64x * PARM_Freq / power_time;
       
      
       HZ_link_power=pl1+pl11+pl12+pl13+pl14+pl15;
       
      pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00; 
      pl1 = (LinkLeakagePowerPerMeter(link_l11, Vdd)) * link_l11 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl11 = (LinkLeakagePowerPerMeter(link_l1, Vdd)) * link_l1 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl12 = (LinkLeakagePowerPerMeter(link_l2, Vdd)) * link_l2 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl13 = (LinkLeakagePowerPerMeter(link_l3, Vdd)) * link_l3 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl14 = (LinkLeakagePowerPerMeter(link_l4, Vdd)) * link_l4 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl15 = (LinkLeakagePowerPerMeter(link_l5, Vdd)) * link_l5 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      Pleakage=pl1+pl11+pl12+pl13+pl14+pl15;
      cout << "Horizntal Links in 3D BFT 2 layer links and link usage" <<endl<<" L0 = "<<link_l11 <<" L1 = "<<link_l1 <<" L2 = "<<link_l2 <<" L3 =  "<<link_l3 <<" L4 = "<<link_l4 <<" L5  =  "<<link_l5<<endl;
      cout <<"  L0 = "<<ll1 <<" L1 =  "<<l1 <<" L2 = "<<l2 <<" L3 = "<<l3 <<" L4 =  "<<l4 <<" L5 = "<<l5<<endl;
      
      cout << "VL Link count = " <<lt1<<endl;

      TSVlink_power =  0.0000042 * lt1 * PARM_flit_width  * bitwidth64x / power_time;
       total_link_power1=HZ_link_power + TSVlink_power;
       cout << "TSV Link power = " << TSVlink_power<<endl;
       cout << "HZ Link power = " <<HZ_link_power<<endl;
      //total_link_power1 /=_time;

      cout << "DT Link power = " << total_link_power1<<endl;
      
        
    }
    else if (topon==2)
    {
      double link_l11 = 0.004;
     double pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00;
        pl1 = (LinkDynamicEnergyPerBitPerMeter(link_l11, PARM_Vdd)) * link_lenght1 * PARM_flit_width / 2 * ll1 * bitwidth64x * PARM_Freq / power_time;
     
      
       HZ_link_power=pl1;
       
      pl1 =0.00;
      pl1 = (LinkLeakagePowerPerMeter(link_l11, Vdd)) * link_lenght1 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      Pleakage=pl1;
      cout << "Horizntal Links in 3D BFT 2 layer links and link usage" <<endl<<" L0 = "<<link_l11 <<endl;
      
      cout <<"L0 = "<<ll1<<endl;
      
      cout << "VL Link count(1 tsv) = " <<lt1<<endl;
      cout << "VL Link count (2 tsv)= " <<lt2<<endl;

      TSVlink_power =  0.0000042 * lt1 * PARM_flit_width  * bitwidth64x / power_time;
      TSVlink_power1 = 2 * 0.0000042 * lt2 * PARM_flit_width  * bitwidth64x / power_time;
       total_link_power1=HZ_link_power + TSVlink_power+TSVlink_power1;
       cout << "TSV Link power = " << TSVlink_power<<endl;
       cout << "TSV (2) Link power = " << TSVlink_power1<<endl;
       cout << "HZ Link power = " <<HZ_link_power<<endl;
      //total_link_power1 /=_time;

      cout << "DT Link power = " << total_link_power1<<endl;
      
        
   
    }
    else if (topon==111)
    {
     double link_l1= 0.0039,link_l2= 0.0041;
     double pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00;
        pl1 = (LinkDynamicEnergyPerBitPerMeter(link_l1, PARM_Vdd)) * link_l1 * PARM_flit_width / 2 * ll1 * bitwidth64x * PARM_Freq / power_time;
        pl11 = (LinkDynamicEnergyPerBitPerMeter(link_l2, PARM_Vdd)) * link_l2 * PARM_flit_width / 2 * l1 * bitwidth64x * PARM_Freq / power_time;
       
       
      
       HZ_link_power=pl1+pl11;
       
      pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00; 
      pl1 = (LinkLeakagePowerPerMeter(link_l1, Vdd)) * link_l1 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl11 = (LinkLeakagePowerPerMeter(link_l2, Vdd)) * link_l2 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      Pleakage=pl1+pl11;
      cout << "Horizntal Links in Modified 3D BFT 2 layer links and link usage" <<endl<<" L0 = "<<link_l1 <<" L1 = "<<link_l2 <<endl;
      cout <<"  L0 = "<<ll1 <<" L1 =  "<<l1<<endl;
      
      cout << "VL Link count = " <<lt1<<endl;

      TSVlink_power =  0.000028 * lt1 * PARM_flit_width  * bitwidth64x / power_time;
       total_link_power1=HZ_link_power + TSVlink_power;
       cout << "TSV Link power = " << TSVlink_power<<endl;
       cout << "HZ Link power = " <<HZ_link_power<<endl;
      //total_link_power1 /=_time;

      cout << "DT Link power = " << total_link_power1<<endl;
      
        
    }
     else if (topon==11)
    {
     double link_l1= 0.0039,link_l2= 0.0041;
     double pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00;
        pl1 = (LinkDynamicEnergyPerBitPerMeter(link_l1, PARM_Vdd)) * link_l1 * PARM_flit_width / 2 * ll1 * bitwidth64x * PARM_Freq / power_time;
        pl11 = (LinkDynamicEnergyPerBitPerMeter(link_l2, PARM_Vdd)) * link_l2 * PARM_flit_width / 2 * l1 * bitwidth64x * PARM_Freq / power_time;
       
       
      
       HZ_link_power=pl1+pl11;
       
      pl1 =0.00, pl11 =0.00,pl12 =0.00,pl13 =0.00,pl14 =0.00,pl15 =0.00; 
      pl1 = (LinkLeakagePowerPerMeter(link_l1, Vdd)) * link_l1 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      pl11 = (LinkLeakagePowerPerMeter(link_l2, Vdd)) * link_l2 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      Pleakage=pl1+pl11;
      cout << "Horizntal Links in Modified 3D BFT 2 layer links and link usage" <<endl<<" L0 = "<<link_l1 <<" L1 = "<<link_l2 <<endl;
      cout <<"  L0 = "<<ll1 <<" L1 =  "<<l1<<endl;
      
      cout << "VL Link count = " <<lt1<<endl;

      TSVlink_power =  0.000028 * lt1 * PARM_flit_width  * bitwidth64x / power_time;
       total_link_power1=HZ_link_power + TSVlink_power;
       cout << "TSV Link power = " << TSVlink_power<<endl;
       cout << "HZ Link power = " <<HZ_link_power<<endl;
      //total_link_power1 /=_time;

      cout << "DT Link power = " << total_link_power1<<endl;
      
        
    }
    else 
    {
              
    cout << "Router HR links" << ll1<<endl;
    //cout << "Router HR links" << ll2<<endl;
    //cout << "Router HR links" << ll3<<endl;
     cout << "Router VR links" << lt1<<endl;
  //cout << "Router VR links" << lt2<<endl;
  //
  //cout << "sT Link power " << Pleakage<<endl;
     //horizontal link power
      HZ_link_power = (LinkDynamicEnergyPerBitPerMeter(link_lenght1, PARM_Vdd)) * link_lenght1 * PARM_flit_width / 2;
      HZ_link_power  = HZ_link_power * ll1 ;
      HZ_link_power *= bitwidth64x;
      HZ_link_power  = HZ_link_power * PARM_Freq / power_time;
      leakage_link_power = LinkLeakagePowerPerMeter(link_lenght1, PARM_Vdd) * link_lenght1;
      Pleakage = (LinkLeakagePowerPerMeter(link_lenght1, Vdd)) * link_lenght1 * Nsize * Nport *PARM_flit_width * bitwidth64x;
      cout << "HZ Link power = " <<HZ_link_power<<endl;
      if(gN==3)
      {
       TSVlink_power =  0.0000042 * lt1 * PARM_flit_width  * bitwidth64x / power_time;
       total_link_power1=HZ_link_power + TSVlink_power;
       cout << "TSV Link power = " << TSVlink_power<<endl;
      }
      //total_link_power1 /=_time;

      cout << "DT Link power = " << total_link_power1<<endl;
      }
      
      
      
     //slink_power1 = LinkLeakagePowerPerMeter(link_lenght1, PARM_Vdd);
      
     


   
 
    
     

    
    total_power_crossbar *= bitwidth64x;
    total_power_buffer *= bitwidth64x;
    total_power_link *= bitwidth64x;
    //cout<<"\nLink_power"<<total_power_link<<endl;

    total_power_crossbar *= (PARM_Freq/power_time);
    total_power_buffer *= (PARM_Freq/power_time);
    total_power_link *= (PARM_Freq/power_time);
    total_power_SW_arbiter *= (PARM_Freq/power_time);
    total_power_VC_arbiter *=(PARM_Freq/power_time);

    //  cout << "Total Link power = " << total_power_link<<endl;

    static_power_crossbar	= _size * _routers[0]->_orion_router_power.I_crossbar_static * Vdd * SCALE_S  * bitwidth64x;//* Period;// * power_time;
    static_power_buffer 	= _size * _routers[0]->_orion_router_power.I_buf_static * Vdd * SCALE_S * bitwidth64x/2.0;//* Period;// * power_time;
    static_power_SW_arbiter	= _size * _routers[0]->_orion_router_power.I_sw_arbiter_static * Vdd * SCALE_S;// * Period;// * power_time;//* bitwidth64x;
    static_power_VC_arbiter     = _size * _routers[0]->_orion_router_power.I_vc_arbiter_static * Vdd * SCALE_S;// * Period;// * power_time;//* bitwidth64x;
    static_power_link           *=  bitwidth64x;
    cout<<"\n==Sp= "<<static_power_link<<endl;
/*    cout<<"\n==i static= "<<_routers[0]->_orion_router_power.I_crossbar_static<<endl;
    cout<<"\n==vdd= "<<Vdd<<endl;
    cout<<"\n==SCALE_S= "<<SCALE_S<<endl;
    cout<<"\n==tg= "<<Period<<endl;
    cout<<"\n==time= "<<power_time<<endl;*/

    
    cout<<"\n==i static= "<<_routers[0]->_orion_router_power.I_crossbar_static<<endl;
    cout<<"\n==vdd= "<<Vdd<<endl;
    cout<<"\n==SCALE_S= "<<SCALE_S<<endl;
    cout<<"\n==tg= "<<Period<<endl;
    cout<<"\n==tlink= "<<tlink<<endl;
    cout<<"\n==time= "<<power_time<<endl;
    total_power_link=total_link_power1;
    total_power_routing = total_power_VC_arbiter;
    
    total_power_CSRegister = (((double)g_total_cs_register_writes)*(677e-11));
    
    PowerOut << "Crossbar Power  :: Dynamic: " << total_power_crossbar << "  Static: "<<static_power_crossbar<<"  Total: "<<static_power_crossbar+total_power_crossbar <<"\n";
    PowerOut << "Buffer Power    :: Dynamic: " << total_power_buffer << "  Static: "<<static_power_buffer<<"  Total: "<<static_power_buffer+total_power_buffer <<"\n";
    PowerOut << "SW_arbiter Power:: Dynamic: " << total_power_SW_arbiter << "  Static: "<<static_power_SW_arbiter<<"  Total: "<<static_power_SW_arbiter+total_power_SW_arbiter <<"\n";
    PowerOut << "VC_arbiter Power:: Dynamic: " << total_power_VC_arbiter << "  Static: "<<static_power_VC_arbiter<<"  Total: "<<static_power_VC_arbiter+total_power_VC_arbiter <<"\n";
    PowerOut << "Link Power      :: Dynamic: " << total_power_link << "  Static: "<<static_power_link<<"  Total: "<<static_power_VC_arbiter+total_power_link <<"\n";
  //PowerOut << "Total Routing     Energy Consumption:   \t" << total_power_routing << "\n";
    PowerOut << "Circuit-switching Power (CS mode only):\t" << total_power_CSRegister << "\n";
   
 //PowerOut1 << "Crossbar Power  :: Dynamic: " << total_power_crossbar << "  Static: "<<static_power_crossbar<<"  Total: "<<static_power_crossbar+total_power_crossbar <<"\n";
   // PowerOut1 << "Buffer Power    :: Dynamic: " << total_power_buffer << "  Static: "<<static_power_buffer<<"  Total: "<<static_power_buffer+total_power_buffer <<"\n";
   // PowerOut1 << "SW_arbiter Power:: Dynamic: " << total_power_SW_arbiter << "  Static: "<<static_power_SW_arbiter<<"  Total: "<<static_power_SW_arbiter+total_power_SW_arbiter <<"\n";
   // PowerOut1 << "VC_arbiter Power:: Dynamic: " << total_power_VC_arbiter << "  Static: "<<static_power_VC_arbiter<<"  Total: "<<static_power_VC_arbiter+total_power_VC_arbiter <<"\n";
   /// PowerOut1 << "Link Power      :: Dynamic: " << total_power_link << "  Static: "<<static_power_link<<"  Total: "<<static_power_VC_arbiter+total_power_link <<"\n";
  //PowerOut << "Total Routing     Energy Consumption:   \t" << total_power_routing << "\n";
   // PowerOut1 << "Circuit-switching Power (CS mode only):\t" << total_power_CSRegister << "\n";
   

        cout << "Crossbar Power  :: Dynamic: " << total_power_crossbar << "  Static: "<<static_power_crossbar<<"  Total: "<<static_power_crossbar+total_power_crossbar <<"\n";
    cout << "Buffer Power    :: Dynamic: " << total_power_buffer << "  Static: "<<static_power_buffer<<"  Total: "<<static_power_buffer+total_power_buffer <<"\n";
    cout << "SW_arbiter Power:: Dynamic: " << total_power_SW_arbiter << "  Static: "<<static_power_SW_arbiter<<"  Total: "<<static_power_SW_arbiter+total_power_SW_arbiter <<"\n";
    cout << "VC_arbiter Power:: Dynamic: " << total_power_VC_arbiter << "  Static: "<<static_power_VC_arbiter<<"  Total: "<<static_power_VC_arbiter+total_power_VC_arbiter <<"\n";
    cout << "Link Power      :: Dynamic: " << total_power_link << "  Static: "<<static_power_link<<"  Total: "<<static_power_VC_arbiter+total_power_link <<"\n";
    cout << "Total Routing     Energy Consumption:   \t" << total_power_routing << "\n";
    cout << "Circuit-switching Power (CS mode only):\t" << total_power_CSRegister << "\n";
    

    double total_power = total_power_crossbar+total_power_buffer+total_power_link+total_power_SW_arbiter+total_power_VC_arbiter+total_power_routing+total_power_CSRegister;
    double static_power= static_power_crossbar+ static_power_buffer+static_power_link+static_power_SW_arbiter+static_power_VC_arbiter;
   
    cout << "\nTotal Average Power Consumption (W)    =\t" << total_power << endl;
    cout << "Total Average Energy per Flit =\t" << (double) ( (total_power * Period * power_time)/g_number_of_retired_flits) << "\n\n";
    cout<<"g_number_of_retired_flits ="<<g_number_of_retired_flits<<endl;
    total_power+=static_power;
       
    PowerOut << "\nTotal Average Power Consumption (W)    =\t" << total_power << endl;
    PowerOut << "Total Average Energy per Flit =\t" << (double) ( (total_power * Period * power_time)/g_number_of_retired_flits) << "\n\n";
    PowerOut << "\nTotal g_number_of_retired_flits =\t" << g_number_of_retired_flits << endl;

    PowerOut << "Power Breakdown:\n" << "\tCrossbars:\t" << (double) (total_power_crossbar+static_power_crossbar)/total_power*100 << " %\n"
				  << "\tBuffers:\t" << (double) (total_power_buffer+static_power_buffer)/total_power*100 << " %\n"
				  << "\tLinks:\t\t" << (double) (total_power_link+static_power_link)/total_power*100 << " %\n"
				  << "\tSW_arbiters:\t" << (double) (total_power_SW_arbiter+static_power_SW_arbiter)/total_power*100 << " %\n"
				  << "\tVC_arbiters:\t" << (double) (total_power_VC_arbiter+static_power_VC_arbiter)/total_power*100 << " %\n";
				  //<< "\tRouting:\t" << (double) total_power_routing/total_power*100 << " %\n";
//	PowerOut1 << "\nTotal Average Power Consumption (W)    =\t" << total_power << endl;
 //   PowerOut1 << "Total Average Energy per Flit =\t" << (double) ( (total_power * Period * power_time)/g_number_of_retired_flits) << "\n\n";
  //  PowerOut1 << "\nTotal g_number_of_retired_flits =\t" << g_number_of_retired_flits << endl;

   /// PowerOut1 << "Power Breakdown:\n" << "\tCrossbars:\t" << (double) (total_power_crossbar+static_power_crossbar)/total_power*100 << " %\n"
          //<< "\tBuffers:\t" << (double) (total_power_buffer+static_power_buffer)/total_power*100 << " %\n"
          //<< "\tLinks:\t\t" << (double) (total_power_link+static_power_link)/total_power*100 << " %\n"
          //<< "\tSW_arbiters:\t" << (double) (total_power_SW_arbiter+static_power_SW_arbiter)/total_power*100 << " %\n"
          //<< "\tVC_arbiters:\t" << (double) (total_power_VC_arbiter+static_power_VC_arbiter)/total_power*100 << " %\n";
          //<< "\tRouting:\t" << (double) total_power_routing/total_power*100 << " %\n";
    	




      cout << "Power Breakdown:\n" << "\tCrossbars:\t" << (double) (total_power_crossbar+static_power_crossbar)/total_power*100 << " %\n"
          << "\tBuffers:\t" << (double) (total_power_buffer+static_power_buffer)/total_power*100 << " %\n"
          << "\tLinks:\t\t" << (double) (total_power_link+static_power_link)/total_power*100 << " %\n"
          << "\tSW_arbiters:\t" << (double) (total_power_SW_arbiter+static_power_SW_arbiter)/total_power*100 << " %\n"
          << "\tVC_arbiters:\t" << (double) (total_power_VC_arbiter+static_power_VC_arbiter)/total_power*100 << " %\n";
          //<< "\tRouting:\t" << (double) total_power_routing/total_power*100 << " %\n";
		  

    PowerOut << "\nInternal Reports:\nTotal Number of Detected Flits:\t\t" << total_number_of_crossed_flits << " ( Header: " << total_number_of_crossed_headerFlits << " )" << endl;
    PowerOut << "Total Number of Orion Function Calls:\t" << total_number_of_calls_of_power_functions << endl;

    PowerOut1 << "\nInternal Reports:\nTotal Number of Detected Flits:\t\t" << total_number_of_crossed_flits << " ( Header: " << total_number_of_crossed_headerFlits << " )" << endl;
    //PowerOut1 << "Total Number of Orion Function Calls:\t" << total_number_of_calls_of_power_functions << endl;
  }
  else
  {
    PowerOut << "Power Consumption for :\n";
    for(int r = 0; r < _size; r++ ){
      PowerOut << "Router "<< r << " :\n\tCrossbar:\t" << SIM_crossbar_report(&(_routers[r]->_orion_router_power.crossbar))
			    << "\n\tBuffers:\t"    << SIM_array_power_report(&(_routers[r]->_orion_router_info.in_buf_info),&(_routers[r]->_orion_router_power.in_buf))
			    << "\n\tLinks:\t" 	   << SIM_link_power_report(_routers[r])
			    << "\n\tSW_arbiter:\t" << SIM_arbiter_report(&(_routers[r]->_orion_router_power.sw_out_arb))
			    << "\n\tVC_arbiter:\t" << SIM_arbiter_report(&(_routers[r]->_orion_router_power.vc_out_arb)) << "\n";
    }
  }
  
  PowerOut.close();
}

