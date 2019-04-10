#include "booksim.hpp"
#include <vector>
#include <sstream>

#include "bft.hpp"
#include "misc_utils.hpp"

#define DEBUG_BFFLY 
#include<math.h>
#include <sstream>
#include <limits>
#include <cmath>
#include "flatfly_onchip.hpp"
#include "random_utils.hpp"
#include "misc_utils.hpp"
#include "globals.hpp"

Bft::Bft( const Configuration &config, const string & name ) : Network( config, name )
{
  _ComputeSize( config );
  _Alloc( );
  _BuildNet( config );
} 
void Bft::_ComputeSize( const Configuration &config )
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
// cout<<_size<<_nodes<<_k<<_n<<levels;
  gK = _k; int gN = _n;
_channels = 2*48;
  

  // n stages of k^(n-1) k x k switches
  //_size     = _n*powi( _k, _n-1 );

  // n-1 sets of wiring between the stages
 
}

//void Bft::RegisterRoutingFunctions() {}
void Bft::_BuildNet( const Configuration& config )
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
  int level,nPos, pos, id, degree, port,cc;
  id=0;
  for ( level = _n ; level >=1 ; level-- ) {
     // Number of router positions at each depth of the network
    nPos = _nodes/pow(2,level+1);
        for ( pos = 0 ; pos < nPos ; ++pos ) {
     
      if ( level == _n ) //top routers is zero
	degree = 4;
      else
	degree = 6;

      //id = (cc) * nPos + pos;
//   cout<<id<<endl;
      name.str(""); //check router id
      
      Router * r = Router::NewRouter( config, this, name.str( ), id,
				      degree, degree );
      
      _Router( level, pos ) = r;
      _timed_modules.push_back(r);
      int id1=r->GetID(),in=r->NumInputs(),ou=r->NumInputs();
    //  cout<<id1<<in<<ou<<endl;
          cout<<"level:"<<level<<"switch:"<<nPos<<"-"<<"position:"<<pos<<"-"<<"node ID:"<<id1<<in<<ou<<"=="<<endl;
         id++;
 }
    //cc++;
  }
  
   nPos = powi( _k, _n - 1 );
   _k=4;
   
  
  //connectionof channels lower to uppper level 3 to level 2
 // level 3 to leve 1 i.e router 0 1 2 3 to 4 5 6 7 8 9 10 11 
   int pp, pc;
  int pos1, _k=4;
    int c = 0;
  nPos =( _nodes/pow(2,4));
  int nnPos=( _nodes/pow(2,3));
  cout<<nPos<<nnPos<<endl;
  for ( pos = 0; pos < nPos; ++pos ) {
     // for ( int port = 0; port < 4; ++port ) {
    port=0;
    for( pos1=0;pos1<nnPos;++pos1){
      if (pos%2==0 && pos1%2==0){
	pp =pos;
	pc=pos1;
	cout << "connecting (3,"<<pp<<") <-> (2,"<<pc<<")"<<endl;	
	_Router( 2, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );	
	_Router( 3, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );
	 //_chan[c]->SetLatency( L );
	 //_chan_cred[c]->SetLatency( L );
       // _Router( _n, pc)->Display1();
        _chan[c]->SetLatency( 1 );
        _chan_cred[c]->SetLatency( 1 );
 // cout<<"next\n";
  //cout << "Used " << c << " of " << _channels << " channels" << endl;
      c++;

      _Router(2, pp)->AddInputChannel( _chan[c], _chan_cred[c] );
  //  cout<<"next\n";
     _Router(3, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
  //    cout<<"next\n";
     

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );


port++;
    c++;
}
if(pos%2!=0 && pos1%2!=0)
{
   pp =pos;
pc=pos1;
      cout << "connecting (3,"<<pp<<") <-> (2,"<<pc<<")"<<endl;

      _Router( _n, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );
      _Router( _n-1, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );

      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );
cout << "Used " << c << " of " << _channels << " channels" << endl;
      c++;

      _Router(_n, pp)->AddInputChannel( _chan[c], _chan_cred[c] );
      _Router(_n-1, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
      
      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );

port++;
    c++;
    
}

}

}
cout<<c++;

}

   /*   _Router( 1, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );
      _Router( 2, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );

      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );

      c++;

      _Router(1, pp)->AddInputChannel( _chan[c], _chan_cred[c] );
      _Router(2, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
      
      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );

  

  
}
*/

  // Connect Channels to Routers
  //

  //
  // Router Connection Rule: Output Ports <gK Move DOWN Network
  //                         Output Ports >=gK Move UP Network
  //                         Input Ports <gK from DOWN Network
  //                         Input Ports >=gK  from up Network
  /*
int pp ,c,pc;
  // Connecting  Injection & Ejection Channels  
  for ( pos = 0; pos < (_channels/2); ++pos ) {
    for ( int port = 0; port < 4; ++port ) {

      pp = pos;
      pc = _k * ( pos / 2 ) + port;
      
      cout << "connecting (1,"<<pp<<") <-> (2,"<<pc<<")"<<endl;

      _Router( 1, pp)->AddOutputChannel( _chan[c], _chan_cred[c] );
      _Router( 2, pc)->AddInputChannel(  _chan[c], _chan_cred[c] );

      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );

      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );

      c++;

      _Router(1, pp)->AddInputChannel( _chan[c], _chan_cred[c] );
      _Router(2, pc)->AddOutputChannel( _chan[c], _chan_cred[c] );
      
      //_chan[c]->SetLatency( L );
      //_chan_cred[c]->SetLatency( L );
      _chan[c]->SetLatency( 1 );
      _chan_cred[c]->SetLatency( 1 );

      c++;
    }
  }
}
*/
  
Router*& Bft::_Router( int height, int pos )
{
  assert( height <= _n );
  //assert( pos < (4 >> height) * powi( _k, height) );

  int i = 0;
  for ( int h = 0; h < height; ++h )
    i += (4 >> h) * powi( _k, h );
  return _routers[i+pos];

}
  
/*
  for ( pos = 0 ; pos < nPos ; ++pos ) {
    for(int index = 0; index<_k; index++){
      int link = pos*_k + index;
      cout<<"pos="<<pos<<"link:no"<<link<<endl;
      
      _Router( _n-1, pos)->AddInputChannel( _inject[link],
					    _inject_cred[link]);
      _Router( _n-1, pos)->AddOutputChannel( _eject[link],
					     _eject_cred[link]);
      _inject[link]->SetLatency( 1 );
      _inject_cred[link]->SetLatency( 1 );
      _eject[link]->SetLatency( 1 );
      _eject_cred[link]->SetLatency( 1 );
    }
  }

#ifdef FATTREE_DEBUG
  cout<<"\nAssigning output\n";
#endif

  //channels are numbered sequentially from an output channel perspective
  int chan_per_direction = (_k * powi( _k , _n-1 )); //up or down
  int chan_per_level = 2*(_k * powi( _k , _n-1 )); //up+down

  //connect all down output channels
  //level n-1's down channel are injection channels
  for (level = 0; level<_n-1; level++){
    for ( pos = 0; pos < nPos; ++pos ) {
      for ( port = 0; port < _k; ++port ) {
	int link = (level*chan_per_level) + pos*_k + port;
	_Router(level, pos)->AddOutputChannel( _chan[link],
						_chan_cred[link] );
	_chan[link]->SetLatency( 1 );
	_chan_cred[link]->SetLatency( 1 ); 
#ifdef FATTREE_DEBUG
	cout<<_Router(level, pos)->Name()<<" "
	    <<"down output "<<port<<" "
	    <<"channel_id "<<link<<endl;
#endif

      }
    }
  }
  //connect all up output channels
  //level 0 has no up chnanels
  for (level = 1; level<_n; level++){
    for ( pos = 0; pos < nPos; ++pos ) {
      for ( port = 0; port < _k; ++port ) {
	int link = (level*chan_per_level - chan_per_direction) + pos*_k + port ;
	_Router(level, pos)->AddOutputChannel( _chan[link],
						_chan_cred[link] );
	_chan[link]->SetLatency( 1 );
	_chan_cred[link]->SetLatency( 1 ); 
#ifdef FATTREE_DEBUG
	cout<<_Router(level, pos)->Name()<<" "
	    <<"up output "<<port<<" "
	    <<"channel_id "<<link<<endl;
#endif
      }
    }
  }

#ifdef FATTREE_DEBUG
  cout<<"\nAssigning Input\n";
#endif

  //connect all down input channels
  for (level = 0; level<_n-1; level++){
    //input channel are numbered interleavely, the interleaev depends on level
    int routers_per_neighborhood = powi(_k,_n-1-(level)); 
    int routers_per_branch = powi(_k,_n-1-(level+1)); 
    int level_offset = routers_per_neighborhood*_k;
    for ( pos = 0; pos < nPos; ++pos ) {
      int neighborhood = pos/routers_per_neighborhood;
      int neighborhood_pos = pos%routers_per_neighborhood;
      for ( port = 0; port < _k; ++port ) {
	int link = 
	  ((level+1)*chan_per_level - chan_per_direction)  //which levellevel
	  +neighborhood*level_offset   //region in level
	  +port*routers_per_branch*gK  //sub region in region
	  +(neighborhood_pos)%routers_per_branch*gK  //router in subregion
	  +(neighborhood_pos)/routers_per_branch; //port on router

	_Router(level, pos)->AddInputChannel( _chan[link],
					      _chan_cred[link] );
#ifdef FATTREE_DEBUG
	cout<<_Router(level, pos)->Name()<<" "
	    <<"down input "<<port<<" "
	    <<"channel_id "<<link<<endl;
#endif
      }
    }
  }


 //connect all up input channels
  for (level = 1; level<_n; level++){
    //input channel are numbered interleavely, the interleaev depends on level
    int routers_per_neighborhood = powi(_k,_n-1-(level-1)); 
    int routers_per_branch = powi(_k,_n-1-(level)); 
    int level_offset = routers_per_neighborhood*_k;
    for ( pos = 0; pos < nPos; ++pos ) {
      int neighborhood = pos/routers_per_neighborhood;
      int neighborhood_pos = pos%routers_per_neighborhood;
      for ( port = 0; port < _k; ++port ) {
	int link = 
	  ((level-1)*chan_per_level) //which levellevel
	  +neighborhood*level_offset   //region in level
	  +port*routers_per_branch*gK  //sub region in region
	  +(neighborhood_pos)%routers_per_branch*gK //router in subregion
	  +(neighborhood_pos)/routers_per_branch; //port on router

	_Router(level, pos)->AddInputChannel( _chan[link],
					      _chan_cred[link] );
#ifdef FATTREE_DEBUG
	cout<<_Router(level, pos)->Name()<<" "
	    <<"up input "<<port<<" "
	    <<"channel_id "<<link<<endl;
#endif
      }
    }
  }
#ifdef FATTREE_DEBUG
  cout<<"\nChannel assigned\n";
#endif
}

Router*& Bft::_Router( int depth, int pos ) 
{
  assert( depth < _n && pos < powi( _k, _n-1) );
  return _routers[depth * powi( _k, _n-1) + pos];
}
*/
