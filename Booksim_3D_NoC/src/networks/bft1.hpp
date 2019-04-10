// bft header file file 
#ifndef _BFT1_HPP_
#define _BFT1_HPP_

#include "network.hpp"

class Bft1 : public Network {

  int _k;
  int _n;

  void _ComputeSize( const Configuration &config );
   void _BuildNet( const Configuration &config );
  Router*& _Router( int depth, int pos );

  int _OutChannel( int stage, int addr, int port ) const;
  int _InChannel( int stage, int addr, int port ) const;
 
public:
  Bft1( const Configuration &config, const string & name );
  static void RegisterRoutingFunctions() ;

  int GetN( ) const;
  int GetK( ) const;
 // static void RegisterRoutingFunctions(){};
  //double Capacity( ) const;
};

#endif 
