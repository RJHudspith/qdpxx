// $Id: t_blas_g5_3.cc,v 1.1 2005-05-18 13:42:51 bjoo Exp $

#include <iostream>
#include <cstdio>

// Ensure that the template matches don't get used
#include "qdp.h"


#include "scalarsite_generic/generic_blas_g5.h"
 
using namespace QDP;

int main(int argc, char *argv[])
{
  // Put the machine into a known state
  QDP_initialize(&argc, &argv);

  // Setup the layout
  const int foo[] = {8,8,8,8};
  multi1d<int> nrow(Nd);
  nrow = foo;  // Use only Nd elements
  Layout::setLattSize(nrow);
  Layout::create();

  
  Real a=Real(1.5);
  Real b=Real(2.0);
  
  LatticeFermion x;
  LatticeFermion y;
  LatticeFermion z1;
  LatticeFermion z2;
  LatticeFermion tmp;
  int G5=Ns*Ns-1;

  gaussian(x);
  gaussian(y);




  REAL* Out;
  REAL* scalep;
  REAL* scalep2;
  REAL* InScale;
  REAL* Add;

  int n_4vec = all.end()-all.start()+1;
  Double norm_diff;

  gaussian(x);
  tmp=Gamma(G5)*x;
  z1 = a*tmp;

  Out = (REAL *)&(z2.elem(0).elem(0).elem(0).real());
  scalep = (REAL *)&(a.elem().elem().elem().elem());
  InScale = (REAL *)&(x.elem(0).elem(0).elem(0).real());

  // z2 = a*g5*x
  z2=a*(GammaConst<Ns,Ns*Ns-1>()*x);

  norm_diff=norm2(z1-z2);
 
  {
    QDPIO::cout << "ag5x diff=" << sqrt(norm_diff) << endl;
    StopWatch swatch;
    double time=0;
    int iter=1;
    while( time < 1.0 ) { 
      iter *=2;
      QDPIO::cout << "Calling " << iter << " times " << endl;
      swatch.reset();
      swatch.start();
      for(int i=0; i < iter; i++) {
	tmp=Gamma(G5)*x;
	z1 = a*tmp;	
      }
      swatch.stop();
      time = swatch.getTimeInSeconds();
      Internal::broadcast(time);
    }
    
    QDPIO::cout << "Timing with " << iter << " iters" << endl;
    swatch.reset();
    swatch.start();
    for(int i=0; i < iter; i++) {
	tmp=Gamma(G5)*x;
	z1 = a*tmp;	
    }
    swatch.stop();
    time = swatch.getTimeInMicroseconds();
    Internal::broadcast(time);
    
    double Nflops = (double)(2*Nc*Ns*Layout::sitesOnNode()*iter);
    QDPIO::cout << "Time taken: " << time << "(us) Perf: " << Nflops/time << " Mflop/s per node" << endl;
  }

  {
    StopWatch swatch;
    double time=0;
    int iter=1;
    while( time < 1.0 ) { 
      iter *=2;
      QDPIO::cout << "Calling " << iter << " times " << endl;
      swatch.reset();
      swatch.start();
      for(int i=0; i < iter; i++) {
	z2=a*(GammaConst<Ns,Ns*Ns-1>()*x);
      }
      swatch.stop();
      time = swatch.getTimeInSeconds();
      Internal::broadcast(time);
    }
    
    QDPIO::cout << "Timing with " << iter << " iters" << endl;
    swatch.reset();
    swatch.start();
    for(int i=0; i < iter; i++) {
      z2=a*(GammaConst<Ns,Ns*Ns-1>()*x);
    }
    swatch.stop();
    time = swatch.getTimeInMicroseconds();
    Internal::broadcast(time);
    
    double Nflops = (double)(2*Nc*Ns*Layout::sitesOnNode()*iter);
    QDPIO::cout << "Time taken: " << time << "(us) Perf: " << Nflops/time << " MFlops/node" << endl;
  }


  // ax + bg5y
  gaussian(x);
  gaussian(y);
  tmp=Gamma(G5)*x;
  z1 = b*y + a*tmp;
  z2=b*y + a*(GammaConst<Ns,Ns*Ns-1>()*x);  
  norm_diff=norm2(z1-z2); 
  {
    QDPIO::cout << "ax + bg5y diff=" << sqrt(norm_diff) << endl;
    StopWatch swatch;
    double time=0;
    int iter=1;
    while( time < 1.0 ) { 
      iter *=2;
      QDPIO::cout << "Calling " << iter << " times " << endl;
      swatch.reset();
      swatch.start();
      for(int i=0; i < iter; i++) {
	tmp=Gamma(G5)*x;
	z1 = b*y + a*tmp;	
      }
      swatch.stop();
      time = swatch.getTimeInSeconds();
      Internal::broadcast(time);
    }
    
    QDPIO::cout << "Timing with " << iter << " iters" << endl;
    swatch.reset();
    swatch.start();
    for(int i=0; i < iter; i++) {
	tmp=Gamma(G5)*x;
	z1 = b*y + a*tmp;	

    }
    swatch.stop();
    time = swatch.getTimeInMicroseconds();
    Internal::broadcast(time);
    
    double Nflops = (double)(6*Nc*Ns*Layout::sitesOnNode()*iter);
    QDPIO::cout << "Time taken: " << time << "(us) Perf: " << Nflops/time << " Mflop/s per node" << endl;
  }

  {
    StopWatch swatch;
    double time=0;
    int iter=1;
    while( time < 1.0 ) { 
      iter *=2;
      QDPIO::cout << "Calling " << iter << " times " << endl;
      swatch.reset();
      swatch.start();
      for(int i=0; i < iter; i++) {
	z2=a*y + b*(GammaConst<Ns,Ns*Ns-1>()*x);  
      }
      swatch.stop();
      time = swatch.getTimeInSeconds();
      Internal::broadcast(time);
    }
    
    QDPIO::cout << "Timing with " << iter << " iters" << endl;
    swatch.reset();
    swatch.start();
    for(int i=0; i < iter; i++) {
      z2=a*y + b*(GammaConst<Ns,Ns*Ns-1>()*x);  
    }
    swatch.stop();
    time = swatch.getTimeInMicroseconds();
    Internal::broadcast(time);
    
    double Nflops = (double)(6*Nc*Ns*Layout::sitesOnNode()*iter);
    QDPIO::cout << "Time taken: " << time << "(us) Perf: " << Nflops/time << " MFlops/node" << endl;
  }


  // x - ag5y
  gaussian(x);
  gaussian(y);
  tmp=Gamma(G5)*x;
  z1 = y - a*tmp;
  
  z2 = y - a*(GammaConst<Ns,Ns*Ns-1>()*x);

  norm_diff=norm2(z1-z2);
 
  {
    QDPIO::cout << "x - a g5 y diff=" << sqrt(norm_diff) << endl;
    StopWatch swatch;
    double time=0;
    int iter=1;
    while( time < 1.0 ) { 
      iter *=2;
      QDPIO::cout << "Calling " << iter << " times " << endl;
      swatch.reset();
      swatch.start();
      for(int i=0; i < iter; i++) {
	tmp=Gamma(G5)*x;
	z1 = y - a*tmp;	
      }
      swatch.stop();
      time = swatch.getTimeInSeconds();
      Internal::broadcast(time);
    }
    
    QDPIO::cout << "Timing with " << iter << " iters" << endl;
    swatch.reset();
    swatch.start();
    for(int i=0; i < iter; i++) {
	tmp=Gamma(G5)*x;
	z1 = y - a*tmp;	
    }
    swatch.stop();
    time = swatch.getTimeInMicroseconds();
    Internal::broadcast(time);
    
    double Nflops = (double)(4*Nc*Ns*Layout::sitesOnNode()*iter);
    QDPIO::cout << "Time taken: " << time << "(us) Perf: " << Nflops/time << " Mflop/s per node" << endl;
  }

  {
    StopWatch swatch;
    double time=0;
    int iter=1;
    while( time < 1.0 ) { 
      iter *=2;
      QDPIO::cout << "Calling " << iter << " times " << endl;
      swatch.reset();
      swatch.start();
      for(int i=0; i < iter; i++) {
	z2 = y - a*(GammaConst<Ns,Ns*Ns-1>()*x);
  
      }
      swatch.stop();
      time = swatch.getTimeInSeconds();
      Internal::broadcast(time);
    }
    
    QDPIO::cout << "Timing with " << iter << " iters" << endl;
    swatch.reset();
    swatch.start();
    for(int i=0; i < iter; i++) {
      z2 = y - a*(GammaConst<Ns,Ns*Ns-1>()*x);
  
    }
    swatch.stop();
    time = swatch.getTimeInMicroseconds();
    Internal::broadcast(time);
    
    double Nflops = (double)(4*Nc*Ns*Layout::sitesOnNode()*iter);
    QDPIO::cout << "Time taken: " << time << "(us) Perf: " << Nflops/time << " MFlops/node" << endl;
  }



  // Time to bolt
  QDP_finalize();

  exit(0);
}
  
