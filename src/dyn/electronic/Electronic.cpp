#include "Electronic.h"


namespace libdyn{
namespace libelectronic{

using namespace libmmath;

void Electronic::rnd_phase(double& x, double& y, double nrm){ 
// x^2 + y^2 = nrm^2

  double phi = rnd_obj->uniform(0.0,1.0);
  x = std::sqrt(nrm) * std::cos(M_PI*phi); 
  y = std::sqrt(nrm) * std::sin(M_PI*phi); 
}

void Electronic::init(int n_,int st){
  // This function allocates memory for time-dependent wfc with n_ stationary states
  // Then it initializes the overall multiconfigurational wfc
  // to be a 1-configurational, with the weight 1 set to basis state with index st
  // and with a random phase
  rnd_obj = new Random();

  if(st>=n_){ std::cout<<"Error in Electronic::init - st("<<st<<") must be smaller than n_("<<n_<<")\n"; exit(0); }

  nstates = n_;
  q = std::vector<double>(n_,0.0);
  p = std::vector<double>(n_,0.0); 

  istate = st;
  rnd_phase(q[istate],p[istate],1.0);   // populate only istate-th state

}

//
// Overloaded version
//
void Electronic::init(int n_){ init(n_,0); }  


//
// Constructors
//
Electronic::Electronic(int n_,int st){  init(n_,st); }
Electronic::Electronic(int n_){  init(n_,0); }
Electronic::Electronic(){  init(1,0); }


//
// Destructor
//
Electronic::~Electronic(){  delete rnd_obj; q.clear(); p.clear(); }



std::complex<double> Electronic::c(int i){
// return amplitude in the complex format: c_i = q_i + i*p_i

  return complex<double>(q[i],p[i]);

}

std::complex<double> Electronic::rho(int i, int j){
// return the density matrix element: rho_ij = c^*_i * c_j

  return complex<double>((q[i]*q[j] + p[i]*p[j]), (q[i]*p[j]-p[i]*q[j]));

}



}//namespace libelectronic
}// namespace libdyn

