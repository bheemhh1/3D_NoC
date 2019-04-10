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

/*router.cpp
 *
 *The base class of either iq router or event router
 *contains a list of channels and other router configuration variables
 *
 *The older version of the simulator uses an array of flits and credit to 
 *simulate the channels. Newer version ueses flitchannel and credit channel
 *which can better model channel delay
 *
 *The older version of the simulator also uses vc_router and chaos router
 *which are replaced by iq rotuer and event router in the present form
 */

#include "booksim.hpp"
#include <iostream>
#include <cassert>
#include "router.hpp"

//////////////////Sub router types//////////////////////
#include "iq_router.hpp"
#include "event_router.hpp"
#include "chaos_router.hpp"
///////////////////////////////////////////////////////

int const Router::STALL_BUFFER_BUSY = -2;
int const Router::STALL_BUFFER_CONFLICT = -3;
int const Router::STALL_BUFFER_FULL = -4;
int const Router::STALL_BUFFER_RESERVED = -5;
int const Router::STALL_CROSSBAR_CONFLICT = -6;

Router::Router( const Configuration& config,
		Module *parent, const string & name, int id,
		int inputs, int outputs ) :
TimedModule( parent, name ), _id( id ), _inputs( inputs ), _outputs( outputs ),
   _partial_internal_cycles(0.0)
{
  _crossbar_delay   = ( config.GetInt( "st_prepare_delay" ) + 
			config.GetInt( "st_final_delay" ) );
  _credit_delay     = config.GetInt( "credit_delay" );
  _input_speedup    = config.GetInt( "input_speedup" );
  _output_speedup   = config.GetInt( "output_speedup" );
  _internal_speedup = config.GetFloat( "internal_speedup" );
  _classes          = config.GetInt( "classes" );

// Orion Power Support

   int _vcs = config.GetInt( "num_vcs" );

   /* added by [a.mazloumi and modarressi] due to add power calculating from Orion */
    //link power
    _orion_link_length = new double [_outputs-1];
    _orion_link_output_counters = new int [_outputs-1];
    for(int i = 0; i < _outputs-1; i++)
    {
	_orion_link_output_counters[i] = 0;
	_orion_link_length[i] = 1e-3; 
    }

   // switch arbiter power
    _orion_last_sw_request = new unsigned int [_inputs*_input_speedup];
    _orion_last_sw_grant = new int [_inputs*_input_speedup];
    for(int i = 0 ; i < _inputs*_input_speedup; i++){
      _orion_last_sw_request[i] = 0;
      _orion_last_sw_grant[i] = 0;
    }

   //VC arbiter power
    _orion_last_vc_reguest = new unsigned int [_inputs*_vcs];
    _orion_last_vc_grant = new int [_inputs*_vcs];
    for(int i = 0 ; i < _inputs*_vcs; i++){
      _orion_last_vc_reguest[i] = 0;
      _orion_last_vc_grant[i] = 0;
    }

   //crossbar power
    _orion_crosbar_last_match = new int [_outputs*_output_speedup];
    for (int i = 0 ; i < _outputs*_output_speedup ; i++){
      _orion_crosbar_last_match[i] = 0;
    }
    _number_of_calls_of_power_functions = 0;
    _number_of_crossed_flits = 0;
    _number_of_crossed_headerFlits = 0;
 
 
/*
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  Orion XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
NOTE: Orion 3 just provides power relations. 
we added these relations to Record and Report functions of Orion 2
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
*/
    cout<<"\n-- Orion 3 just provides power relations.\n";
    Flexus_Orion_init(config);
    SIM_router_init(&_orion_router_info, &_orion_router_power, NULL);
    cout<<"\n--power initilized in router<< -------------------------\n";
  
   /*LastCxbarIn= new int[_outputs];
   link_power= new double[_outputs];
   for(int mg=0;mg<_outputs;mg++)
   {
	LastCxbarIn[mg]=-1;
	link_power[mg]=0;
   }
   link_len=1e-3;
   LinkEnergy=LinkDynamicEnergyPerBitPerMeter(link_len, 1.2) * link_len;//per bit 
   LinkStatic=LinkLeakagePowerPerMeter(link_len, 1.2)* link_len;//Watt for 1 bit
   //cout<<"  "<<LinkDynamicEnergyPerBitPerMeter(1e-6, 1.2); int k; cin>>k;
   */


#ifdef TRACK_FLOWS
  _received_flits.resize(_classes, vector<int>(_inputs, 0));
  _stored_flits.resize(_classes);
  _sent_flits.resize(_classes, vector<int>(_outputs, 0));
  _active_packets.resize(_classes);
  _outstanding_credits.resize(_classes, vector<int>(_outputs, 0));
#endif

#ifdef TRACK_STALLS
  _buffer_busy_stalls.resize(_classes, 0);
  _buffer_conflict_stalls.resize(_classes, 0);
  _buffer_full_stalls.resize(_classes, 0);
  _buffer_reserved_stalls.resize(_classes, 0);
  _crossbar_conflict_stalls.resize(_classes, 0);
#endif

}

// Orion Power Support
Router::~Router()
{
  delete [] _orion_crosbar_last_match;
  delete [] _orion_last_sw_request;
  delete [] _orion_last_sw_grant;
  delete [] _orion_last_vc_reguest;
  delete [] _orion_last_vc_grant;
  delete [] _orion_link_length;
  delete [] _orion_link_output_counters;
}

void Router::AddInputChannel( FlitChannel *channel, CreditChannel *backchannel )
{
  _input_channels.push_back( channel );
  _input_credits.push_back( backchannel );
  channel->SetSink( this, _input_channels.size() - 1 ) ;
}

void Router::AddOutputChannel( FlitChannel *channel, CreditChannel *backchannel )
{
  _output_channels.push_back( channel );
  _output_credits.push_back( backchannel );
  _channel_faults.push_back( false );
  channel->SetSource( this, _output_channels.size() - 1 ) ;
}

void Router::Evaluate( )
{
  _partial_internal_cycles += _internal_speedup;
  while( _partial_internal_cycles >= 1.0 ) {
    _InternalStep( );
    _partial_internal_cycles -= 1.0;
  }
}

void Router::OutChannelFault( int c, bool fault )
{
  assert( ( c >= 0 ) && ( (size_t)c < _channel_faults.size( ) ) );

  _channel_faults[c] = fault;
}

bool Router::IsFaultyOutput( int c ) const
{
  assert( ( c >= 0 ) && ( (size_t)c < _channel_faults.size( ) ) );

  return _channel_faults[c];
}

/*Router constructor*/
Router *Router::NewRouter( const Configuration& config,
			   Module *parent, const string & name, int id,
			   int inputs, int outputs )
{
  const string type = config.GetStr( "router" );
  Router *r = NULL;
  if ( type == "iq" ) {
    r = new IQRouter( config, parent, name, id, inputs, outputs );
  } else if ( type == "event" ) {
    r = new EventRouter( config, parent, name, id, inputs, outputs );
  } else if ( type == "chaos" ) {
    r = new ChaosRouter( config, parent, name, id, inputs, outputs );
  } else {
    cerr << "Unknown router type: " << type << endl;
  }
  /*For additional router, add another else if statement*/
  /*Original booksim specifies the router using "flow_control"
   *we now simply call these types. 
   */

  return r;
}





