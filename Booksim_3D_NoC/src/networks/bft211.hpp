// bft header file file 
#ifndef _BFT211_HPP_
#define _BFT211_HPP_

#include "network.hpp"

class Bft211 : public Network {

  int _k;
  int _n;

  void _ComputeSize( const Configuration &config );
   void _BuildNet( const Configuration &config );
  Router*& _Router( int depth, int pos );

  int _OutChannel( int stage, int addr, int port ) const;
  int _InChannel( int stage, int addr, int port ) const;
 
public:
  Bft211( const Configuration &config, const string & name );
  static void RegisterRoutingFunctions() ;

  int GetN( ) const;
  int GetK( ) const;
 // static void RegisterRoutingFunctions(){};
  //double Capacity( ) const;
};

#endif 
