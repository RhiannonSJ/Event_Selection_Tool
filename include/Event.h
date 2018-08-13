#ifndef EVENT_H
#define EVENT_H

#include "Particle.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "TH1.h"
#include "TF1.h"

namespace selection{
  
  // Typedef for the map
  typedef std::map< std::vector< int >, int > TopologyMap;
  typedef std::vector<Particle> ParticleList;
  typedef std::vector< vector<double> > ParticleMatrix;

  /**
   * @brief  Event class
   */
  class Event{

    public :
    

      /**
       * @brief  Constructor
       *
       * @param  mc_particles list of the MC particle objects in the event
       * @param  reco_particles list of the reconstructed particle objects in the event
       * @param  nuance the nuance code corresponding to the event
       * @param  is_cc is this a charged or neutral current event
       * @param  mc_vertex Monte Carlo neutrino vertex 
       * @param  reco_vertex reconstructed neutrino vertex
       */
      Event(const ParticleList &mc_particles, const ParticleList &reco_particles, const unsigned int nuance, const int neutrino_pdg, const unsigned int charged_pi, const unsigned int neutral_pi, const bool is_cc, const TVector3 &mc_vertex, const TVector3 &reco_vertex, const float neutrino_energy);

      /**
       * @brief  CountMCParticlesWithPdg
       *
       * @param  pdg pdg code to count
       *
       * @return number of Monte Carlo particles with the given pdg code
       */
      unsigned int CountMCParticlesWithPdg(const int pdg) const;

      /**
       * @brief  CountRecoParticlesWithPdg
       *
       * @param  pdg pdg code to count
       *
       * @return number of reconstructed partices with the given pdg code
       */
      unsigned int CountRecoParticlesWithPdg(const int pdg) const;

      /**
       * @brief  CheckMCTopology
       *
       * @param  topology map of the chosen topology which holds the number of each chosen type of particle to look for
       *
       * @return boolean as to whether the event has the desired Monte Carlo topology
       */
      bool CheckMCTopology(const TopologyMap &topology) const;

      /**
       * @brief  CheckRecoTopology
       *
       * @param  topology map of the chosen topology which holds the number of each chosen type of particle to look for
       *
       * @return boolean as to whether the event has the desired reconstructed topology
       */
      bool CheckRecoTopology(const TopologyMap &topology) const;

      /**
       * @brief  Get the list of MC particls for this event
       */
      ParticleList GetMCParticleList() const;

      /**
       * @brief  Get the list of reconstructed particls for this event
       */
      ParticleList GetRecoParticleList() const;
      
      /**
       * @brief  Get the nuance code - interaction of the event
       */
      int GetNuanceCode() const;

      /**
       * @brief  Get the neutrino pdg code in the event
       */
      int GetNeutrinoPdgCode() const;

      /**
       * @brief  Get the number of charged pions
       */
      int GetNChargedPions() const;
      
      /**
       * @brief  Get the number of neutral pions
       */
      int GetNNeutralPions() const;
      
      /**
       * @brief  Get whether the true neutrino interaction happened within the SBND fiducial 
       *         volume
       */
      bool IsSBNDTrueFiducial() const;
      
      /**
       * @brief  Get whether all the reconstructed tracks in an event are contained
       */
      bool AllContained() const;
      
      /**
       * @brief  Get the physical process
       */
      int GetPhysicalProcess() const;
      
      /**
       * @brief  Get if the event is CC or NC
       */
      bool GetIsCC() const;

      /**
       * @brief  Get the Monte Carlo neutrino vertex position
       */
      TVector3 GetMCNuVertex() const;

      /**
       * @brief  Get the reconstructed neutrino vertex position
       */
      TVector3 GetRecoNuVertex() const;
      
      /**
       * @brief  Get the true neutrino energy
       */
      float GetTrueNuEnergy() const;
      
      /**
       * @brief  Get the most energetic reconstructed particle
       *
       * @return Particle most energetic reco
       */
      Particle GetMostEnergeticRecoParticle() const;

      /**
       * @brief  Get the most energetic true particle
       *
       * @return Particle most energetic true
       */
      Particle GetMostEnergeticTrueParticle() const;

      /**
       * @brief  Get the minimum x,y,z positions of the SBND fiducial volume
       *
       * @return Vector of lowest x,y,z positions
       */
      TVector3 GetMinimumFiducialDimensions() const;

      /**
       * @brief  Get the maximum x,y,z positions of the SBND fiducial volume
       *
       * @return Vector of highest x,y,z positions
       */
      TVector3 GetMaximumFiducialDimensions() const;

    private : 

      /**
       * @brief  CountParticlesWithPdg
       *
       * @param  pdg pdg code to count
       *
       * @return number of partices with the given pdg code
       */
      unsigned int CountParticlesWithPdg(const int pdg, const ParticleList &particle_list) const;
      
      /**
       * @brief  CheckTopology
       *
       * @param  topology map of the chosen topology which holds the number of each chosen type of particle to look for
       *
       * @return boolean as to whether the event has the desired topology
       */
      bool CheckTopology(const TopologyMap &topology, const ParticleList &particle_list) const;

      /**
       * @brief  Get the most energetic particle
       *
       * @return Particle most energetic
       */
      Particle GetMostEnergeticParticle(const ParticleList &particle_list) const;

      // Member variables
      ParticleList       m_mc_particles;       ///< vector of Monte Carlo particles
      ParticleList       m_reco_particles;     ///< vector of reconstructed particles
      unsigned int       m_nuance;             ///< Nuance code/interaction of the event
      int                m_nu_pdg;             ///< Neutrino pdg code of the event
      unsigned int       m_charged_pi;         ///< Number of charged pions in the event
      unsigned int       m_neutral_pi;         ///< Number of neutral pions in the event
      bool               m_is_cc;              ///< whether the event contains and CC or NC interaction
      TVector3           m_reco_vertex;        ///< reconstructed neutrino vertex
      TVector3           m_mc_vertex;          ///< reconstructed neutrino vertex
      float              m_neutrino_energy;    ///< true neutrino energy
      float              m_sbnd_border_x;      ///< fiducial border in x for the sbnd detector
      float              m_sbnd_border_y;      ///< fiducial border in y for the sbnd detector
      float              m_sbnd_border_z;      ///< fiducial border in z for the sbnd detector
      float              m_sbnd_offset_x;      ///< offset in x for the sbnd detector
      float              m_sbnd_offset_y;      ///< offset in y for the sbnd detector
      float              m_sbnd_offset_z;      ///< offset in z for the sbnd detector
      float              m_sbnd_half_length_x; ///< detector half length in x
      float              m_sbnd_half_length_y; ///< detector half length in y
      float              m_sbnd_half_length_z; ///< detector half length in z
                                                                               

  }; // Event
} // selection

#endif
