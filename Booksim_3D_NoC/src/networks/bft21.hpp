// bft header file file 
#ifndef _BFT21_HPP_
#define _BFT21_HPP_

#include "network.hpp"

class Bft21 : public Network {

  int _k;
  int _n;

  void _ComputeSize( const Configuration &config );
   void _BuildNet( const Configuration &config );
  Router*& _Router( int depth, int pos );

  int _OutChannel( int stage, int addr, int port ) const;
  int _InChannel( int stage, int addr, int port ) const;
 
public:
  Bft21( const Configuration &config, const string & name );
  static void RegisterRoutingFunctions() ;

  int GetN( ) const;
  int GetK( ) const;
 // static void RegisterRoutingFunctions(){};
  //double Capacity( ) const;
};

#endif 
