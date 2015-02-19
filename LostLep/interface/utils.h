#include <vector>
#include "TLorentzVector.h"
#include "TVector2.h"
#include <string>

// Collection of geometry-related helper functions.
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
namespace utils {
  // Return delta-phi between -Pi and Pi
  float deltaPhi(float phi1, float phi2) {
    return TVector2::Phi_mpi_pi(phi1-phi2);
  }

  // Return delta-R
  float deltaR(float eta1, float eta2, float phi1, float phi2) {
    float dphi = deltaPhi(phi1,phi2);
    float deta = eta1 - eta2;

    return sqrt( deta*deta + dphi*dphi );
  }


  double mt(double pt, double phi, double met, double metPhi) {
    const double dPhi = deltaPhi(phi,metPhi);                                
    return sqrt( 2.*pt*met*(1.-cos(dPhi)) );                                       
  }   






}
