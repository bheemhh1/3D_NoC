

#include "booksim.hpp"
#include <vector>
#include <sstream>
#include <cmath>

#include "bft23.hpp"
#include "misc_utils.hpp"


Bft23::Bft23( const Configuration& config, const string & name )
: Network ( config, name )
{
  _ComputeSize( config );
  _Alloc( );
  _BuildNet( config );
}

void Bft23::_ComputeSize( const Configuration& config )
{
  
 _k = config.GetInt( "k" );
  _n = config.GetInt( "n" );
_k=4; _n=3;
_nodes = pow( _k, _n );
int i,levels;
levels=(log10(_nodes)/log10(4)); 
for ( i=1;i<=levels;i++)
{
 _size=_size+(_nodes/pow(2,i+1));
	 
}
_size=30;
// cout<<_size<<_nodes<<_k<<_n<<levels;
  gK = _k; int gN = _n;
_channels = 2*56;
  

  // n stages of k^(n-1) k x k switches
  //_size     = _n*powi( _k, _n-1 );

  // n-1 sets of wiring between the stages
           // Connectivity of Middle Routers
}

void Bft23::RegisterRoutingFunctions(){

}

void Bft23::_BuildNet( const Configuration& config )
{
cout<<"BFat Tree"<<endl;
  cout<<" k = "<<_k <<" levels = "<<_n<<endl;
  //cout << " each switch - total radix =  "<< 2*_k << endl;
  cout<< " # of switches = "<<  _size << endl;
  cout<< " # of channels = "<<  _channels << endl;
  cout<< " # of nodes ( size of network ) = " << _nodes << endl;
 

  //
  // Allocate Routers
  //
  ostringstream name;
  int h, pos, nPos, degree, id;
id=0;
  for ( h = 0; h < _n; h++ ) {
    nPos = (4 >> h) * powi( _k, h );
        if(h == 0)
        {
        	nPos=6;
        }
        cout<<"number of nodes:"<<nPos<<endl;

    for ( pos = 0; pos < nPos; ++pos) {
      if ( h == 0 ) 
		{ 
	 degree = 4;
		}
      else if ( h == 1 ) 
		degree = 5;
      else 
	degree = 6;
      
      name.str("");
      name << "router_" << h << "_" << pos;
	cout<< "router_" << h << "_" << pos<<"ID:"<<id<<"degree"<<degree<<endl;      
      
      
      Router * r = Router::NewRouter( config, this, name.str( ),
				      id, degree, degree );
      _Router( h, pos ) = r;
      
      _timed_modules.push_back(r);
      id++;
    }
  }  

  //
  // Connect Channels to Routers
  //
  int pp, pc;
  //
  // Connection Rule: Output Ports 0:3 Move DOWN Network
  //                  Output Ports 4:7 Move UP Network
  //
  
  // Injection & Ejection Channels
   nPos=_nodes/powi(2,_n-1);
  cout<<"npos"<<nPos<<endl;

  for ( pos = 0 ; pos < nPos ; ++pos ) {
    for ( int port = 0 ; port < _k ; ++port ) {
      
      
      _Router( _n-1, pos)->AddInputChannel( _inject[_k*pos+port],
					    _inject_cred[_k*pos+port]);
      

      _inject[_k*pos+port]->SetLatency( 1 );
      _inject_cred[_k*pos+port]->SetLatency( 1 );

      _Router( _n-1, pos)->AddOutputChannel( _eject[_k*pos+port],
					     _eject_cred[_k*pos+port]);

      _eject[_k*pos+port]->SetLatency( 1 );
      _eject_cred[_k*pos+port]->SetLatency( 1 );

      cout<<"added inject and eject at router pos"<<pos<<"\t"<<port<<"\t"<<"inject port"<<_k*pos+port<<endl;
    }
  }
  
int l0=0;
  int l1=1;
  int nPosl0,nPosl1;

  int c = 0;
  // Connections between h = 1 and h = 2 Levels
  l1=1;
  int l2=2,L=1;
  int nPosl2;
   nPosl1=_nodes/powi(2,4-l1);
   nPosl2=_nodes/powi(2,4-l2);
 
  

   nPosl1=_nodes/powi(2,4-l1);
   nPosl2=_nodes/powi(2,4-l2);
       cout<<nPosl1<<"\t"<<nPosl2<<endl;

  for ( pos = 0; pos < nPosl1; ++pos ) {
    for ( int port = 0; port < 4; ++port ) {
      int L=17; //because remaining links 1 to 2 have short lenght
      pp = pos;
      pc = _k * ( pos / 2 ) + port;
      
	if(( (pp==0 || pp==1) && (pc==0 || pc==2)) || ( (pp==2 || pp==3) && (pc==5 || pc==7)) || ((pp==4 || pp==5) && (pc==8 || pc==10)) || ((pp==6 || pp==7) && (pc==13 || pc==15)))
      {
	L=17;
      }
      else
      {
	L=17;
      }
      
      cout << "connecting (1,"<<pp<<") <-> (2,"<<pc<<")"<<"With Latency="<<L<<"clock cycle"<<endl;

      _Router( 1, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );
      _Router( 2, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      

      _chan[c]->SetLatency( L );
      _chan_cred[c]->SetLatency( L);

      c++;

      _Router(1, pp)->AddInputChannel( _chan[c], _chan_cred[c] );
      _Router(2, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
      
      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency(L);
      _chan_cred[c]->SetLatency( L);

      c++;
    }
  }
 
 cout<<"Channels"<<c<<endl;
  // Connections between h = 0 and h = 1 Levels

  	 L=19;
     cout << "connecting (0,"<<0<<") <-> (1,"<<0<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 0)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 0)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 0)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 0)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
         cout << "connecting (0,"<<0<<") <-> (1,"<<1<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 0)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 1)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 0)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 1)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
  
     cout << "connecting (0,"<<1<<") <-> (1,"<<2<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 1)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 2)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 1)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 2)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
     cout << "connecting (0,"<<1<<") <-> (1,"<<3<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 1)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 3)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 1)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 3)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
   
     cout << "connecting (0,"<<2<<") <-> (1,"<<4<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 2)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 4)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 2)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 4)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
     cout << "connecting (0,"<<2<<") <-> (1,"<<5<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 2)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 5)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 2)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 5)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
cout << "connecting (0,"<<3<<") <-> (1,"<<6<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 3)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 6)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 3)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 6)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
     cout << "connecting (0,"<<3<<") <-> (1,"<<7<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
	_Router( 0, 3)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, 7)->AddInputChannel(  _chan[c], _chan_cred[c] );
	_chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
	  c++;
	_Router(0, 3)->AddInputChannel( _chan[c], _chan_cred[c] );
	_Router(1, 7)->AddOutputChannel( _chan[c], _chan_cred[c] );
	 _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
   c++;



   cout << "connecting (0,"<<0<<") <-> (0,"<<2<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 0)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 2)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( 1 );
    _chan_cred[c]->SetLatency( 1 );
    c++;
  _Router(0, 0)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 2)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( 1);
    _chan_cred[c]->SetLatency( 1 );
    c++;
     cout << "connecting (0,"<<1<<") <-> (0,"<<3<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;
  _Router( 0, 1)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 3)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( 1 );
    _chan_cred[c]->SetLatency( 1 );
    c++;
  _Router(0, 1)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 3)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( 1);
    _chan_cred[c]->SetLatency( 1 );
    c++;

     cout << "connecting (0,"<<0<<") <-> (0,"<<4<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 0)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 4)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
       cout<<"Channels"<<c<<endl;

    c++;
  _Router(0, 0)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 4)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L);
    c++;

     cout << "connecting (0,"<<1<<") <-> (0,"<<4<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 1)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 4)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
    c++;
  _Router(0, 1)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 4)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
     cout << "connecting (0,"<<2<<") <-> (0,"<<5<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 2)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 5)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L );
    c++;
  _Router(0, 2)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 5)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( L);
    _chan_cred[c]->SetLatency( L );
    c++;
     cout << "connecting (0,"<<3<<") <-> (0,"<<5<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 3)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 5)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( L );
    _chan_cred[c]->SetLatency( L);
    c++;
  _Router(0, 3)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 5)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( 1);
    _chan_cred[c]->SetLatency( 1 );
    c++;
        cout << "connecting (0,"<<4<<") <-> (0,"<<5<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 4)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 5)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( 1 );
    _chan_cred[c]->SetLatency( 1 );
    c++;
  _Router(0, 4)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 5)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( 1);
    _chan_cred[c]->SetLatency( 1 );
    c++;

    cout << "connecting (0,"<<4<<") <-> (0,"<<5<<")"<<"With Latency=<<1<<clcok cycle"<<endl;
  _Router( 0, 4)->AddOutputChannel( _chan[c], _chan_cred[c] );  
  _Router( 0, 5)->AddInputChannel(  _chan[c], _chan_cred[c] );
  _chan[c]->SetLatency( 1 );
    _chan_cred[c]->SetLatency( 1 );
    c++;
  _Router(0, 4)->AddInputChannel( _chan[c], _chan_cred[c] );
  _Router(0, 5)->AddOutputChannel( _chan[c], _chan_cred[c] );
   _chan[c]->SetLatency( 1);
    _chan_cred[c]->SetLatency( 1 );
    c++;

  /*
   nPosl0=_nodes/powi(2,4-l0);
   nPosl1=_nodes/powi(2,4-l1);
    cout<<nPosl0<<"\t"<<nPosl1<<endl;
//  for ( pos  = 0; pos < nPosl0; ++pos ) {
  //  for ( int port = 0; port < nPosl1; ++port ) {
     
      pp = pos;
      pc = port;
      int L=1;
//      //updating actual latency which  are derived from floorplan ...
 //      if (pos%2==0 && port%2==0){
	  pp =pos;
	  pc=port;
	        cout << "connecting (0,"<<pp<<") <-> (1,"<<pc<<")"<<"With Latency="<<L<<"clcok cycle"<<endl;

		
	_Router( 0, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 1, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );
	 //_chan[c]->SetLatency( L );
	 //_chan_cred[c]->SetLatency( L );
       // _Router( _n, pc)->Display1();
        _chan[c]->SetLatency( L );
        _chan_cred[c]->SetLatency( L );

	  c++;

	_Router(0, pp)->AddInputChannel( _chan[c], _chan_cred[c] );

	_Router(1, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
  //    cout<<"next\n";
     

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency( L);
      _chan_cred[c]->SetLatency( L );

	
	//cout << "Used " << c << " of " << _channels << " channels" << endl;

	
	//}
	//if(pos%2==1 && port%2==1){
	pp =pos;
	pc=port;
	cout << "connecting (0,"<<pp<<") <-> (1,"<<pc<<")"<<"With Latenc="<<L<<"clock cycle"<<endl;

	_Router( 0, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );
	_Router( 1, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );

      _chan[c]->SetLatency( L );
      _chan_cred[c]->SetLatency( L );
	
	c++;

      _Router(0, pp)->AddInputChannel( _chan[c], _chan_cred[c] );
      _Router(1, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
      
      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency( L);
      _chan_cred[c]->SetLatency( L );
//cout << "Used " << c << " of " << _channels << " channels" << endl;
	c++;
    
	
 // cout << "Used " << c-1<<endl;
  
 */

  
}
Router*& Bft23::_Router( int height, int pos )
{
  assert( height < _n );
  int pos1=0;
  //assert( pos < (4 >> height) * powi( _k, height) );
if(height==0)
{
pos1=pos;

}
else if(height==1)
{
	pos1=pos+6;
}
else if(height==2)
{
pos1=pos+14;	
}
 
 /* int i = 0;
  for ( int h = 0; h < height; ++h )
    i += (4 >> h) * powi( _k, h );
cout<<i+pos<<endl;
  */
 cout<<pos1<<endl;
  return _routers[pos1];

}
  /*
int Bft23::_WireLatency( int height1, int pos1, int height2, int pos2 )
{
  int heightChild, heightParent, posChild, posParent;

  int L;

  if (height1 < height2) {
    heightChild  = height2;
    posChild     = pos2;
    heightParent = height1;
    posParent    = pos1;
  } else {
    heightChild  = height1;
    posChild     = pos1;
    heightParent = height2;
    posParent    = pos2;
  }

  int _length_d2_d1   = 2 ;
  int _length_d1_d0_0 = 2 ;
  int _length_d1_d0_1 = 2 ;
  int _length_d1_d0_2 = 6 ;
  int _length_d1_d0_3 = 6 ;

  assert( heightChild == heightParent+1 );

  // We must decrement the delays by one to account for how the 
  //  simulator interprets the specified delay (with 0 indicating one
  //  cycle of delay).

  if ( heightChild == 2 ) 
    L = _length_d2_d1;
  else {
       if ( posChild == 0 || posChild == 6 )
      switch ( posParent ) {
      case 0: L =_length_d1_d0_0; break;
      case 1: L =_length_d1_d0_1; break;
      case 2: L =_length_d1_d0_2; break;
      case 3: L =_length_d1_d0_3; break;
      }
    if ( posChild == 1 || posChild == 7 )
      switch ( posParent ) {
      case 0: L =_length_d1_d0_3; break;
      case 1: L =_length_d1_d0_2; break;
      case 2: L =_length_d1_d0_1; break;
      case 3: L =_length_d1_d0_0; break;
      }
    if ( posChild == 2 || posChild == 4 )
      switch ( posParent ) {
      case 0: L = _length_d1_d0_0; break;
      case 1: L = _length_d1_d0_1; break;
      case 2: L = _length_d1_d0_2; break;
      case 3: L = _length_d1_d0_3; break;
      }
    if ( posChild == 3|| posChild == 5 )
      switch ( posParent ) {
      case 0: L =_length_d1_d0_3; break;
      case 1: L =_length_d1_d0_2; break;
      case 2: L =_length_d1_d0_1; break;
      case 3: L =_length_d1_d0_0; break;
      }
  }
  return L;
}
*/
