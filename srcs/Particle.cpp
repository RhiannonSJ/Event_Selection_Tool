#include <string>
#include <vector>
#include <cmath>
#include "TVector3.h"
#include "../include/Particle.h"

namespace selection{

  Particle::Particle(const int mc_id, const int pdg, const float mass, const float energy, const TVector3 &vertex, const TVector3 &end, const TVector3 &momentum) : 
    m_mc_id(mc_id), 
    m_pdg(pdg), 
    m_mass(mass),
    m_energy(energy),
    m_has_calorimetry(true),
    m_from_reco_track(false),
    m_vertex(vertex),
    m_end(end),
    m_momentum(momentum){
      m_length = sqrt(pow(end[0] - vertex[0], 2) + pow(end[1] - vertex[1], 2) + pow(end[0] - vertex[0], 2));
  }

  //------------------------------------------------------------------------------------------ 
  
  Particle::Particle(const int mc_id_charge, const int mc_id_energy, const int mc_id_hits, const int pdg, const float kinetic_energy, const float length, const TVector3 &vertex, const TVector3 &end) :
    m_mc_id_charge(mc_id_charge),
    m_mc_id_energy(mc_id_energy),
    m_mc_id_hits(mc_id_hits),
    m_pdg(pdg),
    m_length(length),
    m_has_calorimetry(true),
    m_from_reco_track(true),
    m_vertex(vertex),
    m_end(end){
      // Set member variables
      m_mass            = this->GetMassFromPdg(pdg);
      m_energy          = m_mass + kinetic_energy/1000.;
      
      // Get the magnitude of the momentum
      double momentum_magnitude = sqrt(pow(m_energy,2) - pow(m_mass,2));
      m_momentum = momentum_magnitude * (m_end - m_vertex)*(1/double((m_end-m_vertex).Mag()));
    }

  //------------------------------------------------------------------------------------------ 

  Particle::Particle(const int pdg, const TVector3 &vertex, const TVector3 &end) :
    m_pdg(pdg),
    m_mass(this->GetMassFromPdg(pdg)),
    m_has_calorimetry(false),
    m_from_reco_track(false),
    m_vertex(vertex),
    m_end(end){
      m_length = sqrt(pow(end[0] - vertex[0], 2) + pow(end[1] - vertex[1], 2) + pow(end[0] - vertex[0], 2));
    }

  
  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetMassFromPdg(const int pdg) const{
    switch(abs(pdg)){ 
      case 211: 
        return 0.1395701; 
      case 111:
        return 0.1349766;
      case 13:
        return 0.1056583;
      case 2212:
        return 0.9382720;
      case 321:
        return 0.4936770;
      default:
        throw 2;
    }
  }

  //------------------------------------------------------------------------------------------ 
  
  int Particle::GetPdgCode() const{return m_pdg;}

  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetMass() const{return m_mass;}

  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetEnergy() const{
    if(!m_has_calorimetry) throw 1;
    return m_energy;
  }

  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetKineticEnergy() const{
    if(!m_has_calorimetry) throw 1;
    return m_energy-m_mass;
  }
  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetLength() const{return m_length;}

  //------------------------------------------------------------------------------------------ 
  
  TVector3 Particle::GetVertex() const{return m_vertex;}

  //------------------------------------------------------------------------------------------ 
  
  TVector3 Particle::GetEnd() const{return m_end;}

  //------------------------------------------------------------------------------------------ 
  
  TVector3 Particle::GetMomentum() const{
    if(!m_has_calorimetry) throw 1;
    return m_momentum;
  }

  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetModulusMomentum() const{
    if(!m_has_calorimetry) throw 1;
    return m_momentum.Mag();
  }

  //------------------------------------------------------------------------------------------ 

  int Particle::GetMCId() const{ 
    if(m_has_calorimetry && !m_from_reco_track){
      return m_mc_id;
    }
    
    std::cout << "GetMCId" << std::endl;

    throw 5;
  }

  //------------------------------------------------------------------------------------------ 

  int Particle::GetMCParticleIdCharge() const{
    // Check that the particle has been made using reconstructed tracks
    if(m_has_calorimetry && m_from_reco_track){
      return m_mc_id_charge;
    }
    
    std::cout << "GetMCIdCharge" << std::endl;

    throw 6;
  }

  //------------------------------------------------------------------------------------------ 

  int Particle::GetMCParticleIdEnergy() const{
    // Check that the particle has been made using reconstructed tracks
    if(m_has_calorimetry && m_from_reco_track){
      return m_mc_id_energy;
    }
    
    std::cout << "GetMCIdEnergy" << std::endl;

    throw 6;
  }

  //------------------------------------------------------------------------------------------ 

  int Particle::GetMCParticleIdHits() const{
    // Check that the particle has been made using reconstructed tracks
    if(m_has_calorimetry && m_from_reco_track){
      return m_mc_id_hits;
    }
    
    std::cout << "GetMCIdHits" << std::endl;

    throw 6;
  }

  //------------------------------------------------------------------------------------------ 
  
  bool Particle::GetHasCalorimetry() const{return m_has_calorimetry;}

  //------------------------------------------------------------------------------------------ 
  
  bool Particle::GetFromRecoTrack() const{return m_from_reco_track;}
  
  //------------------------------------------------------------------------------------------ 
  
  float Particle::GetCosTheta() const{
    TVector3 u_z(0,0,1);
    return (m_end - m_vertex).Dot( u_z )/((m_end - m_vertex).Mag());
  }
  
  //------------------------------------------------------------------------------------------ 

} // Selection
