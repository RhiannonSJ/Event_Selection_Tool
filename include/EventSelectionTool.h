#ifndef EVENT_SELECTION_TOOL_H
#define EVENT_SELECTION_TOOL_H

#include <string>
#include <vector>
#include <utility>
#include "TTree.h"
#include "TFile.h"
#include "TVector3.h"
#include "Event.h"
#include "Particle.h"

namespace selection{
 
  /**
   * @brief  EventSelectionTool helper class
   */
  class EventSelectionTool {

    private : 
      class Track;
      class Shower;

    public : 

      typedef std::vector<std::pair<int,int> > UniqueEventIdList;
      typedef std::vector<Particle>            ParticleList;
      typedef std::vector<Event>               EventList;
      typedef std::vector<Track>               TrackList;
      typedef std::vector<Shower>              ShowerList;

      /**
       * @brief  load the list of events to analyse from the root file
       *
       * @param  file_name name of the root file to access
       * @param  event_list vector of events to fill
       *
       */
      static void LoadEventList(const std::string &file_name, EventList &event_list);

    private : 

      /**
       * @brief  get a list of event IDs which are entirely unique
       *
       * @param  event_tree the event tree from the root file
       * @param  unique_event_list list of unique events to fill
       *
       */
      static void GetUniqueEventList(TTree *event_tree, UniqueEventIdList &unique_event_list);

      /**
       * @brief  get the list of track objects
       *
       * @param  track_tree tree to take track information from
       * @param  unique_event_list list of unique events to take track information from
       * @param  track_list vector of tracks to fill
       *
       */
      static void GetTrackList(unsigned int start, TTree *track_tree, const std::pair<int, int> &unique_event, TrackList &track_list);

      /**
       * @brief  get the list of shower objects
       *
       * @param  shower_tree tree to take shower information from
       * @param  unique_event_list list of unique events to take shower information from
       * @param  shower_list vector of showers to fill
       *
       */
      static void GetShowerList(unsigned int start, TTree *shower_tree, const std::pair<int, int> &unique_event, ShowerList &shower_list);
      
      /**
       * @brief  get the list of mc particle objects
       *
       * @param  mc particle_tree tree to take mc particle information from
       * @param  unique_event_list list of unique events to take mc particle information from
       * @param  mc particle_list vector of mc particles to fill
       *
       */
      static void GetMCParticleList(unsigned int start, TTree *mcparticle_tree, const std::pair<int, int> &unique_event, ParticleList &mcparticle_list);

      /**
       * @brief  get a list of reconstructed particles from track objects
       *
       * @param  track_list list of tracks in the event
       * @param  recoparticle_list particle list to fill
       *
       */
      static void GetRecoParticleFromTrack(const TrackList &track_list, ParticleList &recoparticle_list);
 
      /**
       * @brief  get a list of reconstructed particles from track objects using original method
       *
       * @param  track_list list of tracks in the event
       * @param  recoparticle_list particle list to fill
       *
       */
      static void GetRecoParticleFromShower(const ShowerList &shower_list, const TVector3 &reco_vertex, ParticleList &recoparticle_list);

      /**
       * @brief  get the particle id based on its chi2 value
       *
       * @param  track the track to find the pdg of
       *
       * @return pdg
       *
       */
      static int GetPdgByChi2(const Track &track);
      
      /**
       * @brief  get the particle id based on its PIDA value
       *
       * @param  track the track to find the pdg of
       *
       * @return pdg
       *
       */
      static int GetPdgByPIDA(const Track &track);
      
      /**
       * @brief  get the particle id based on its PIDA value with strict limits
       *
       * @param  track the track to find the pdg of
       *
       * @return pdg
       *
       */
      static int GetPdgByPIDAStrict(const Track &track);
      
      /**
       * @brief  Track class 
       */
      class Track{
      
        public : 
          
        /**
         * @brief  Constructor
         *
         * @param  pida pida value
         * @param  chi2_mu chi squared value for the muon fit of the reconstructed dEdx to the expected distribution
         * @param  chi2_pi chi squared value for the pion fit of the reconstructed dEdx to the expected distribution
         * @param  chi2_pr chi squared value for the proton fit of the reconstructed dEdx to the expected distribution
         * @param  chi2_ka chi squared value for the kaon fit of the reconstructed dEdx to the expected distribution
         * @param  length track length
         * @param  kinetic_energy track kinetic energy
         * @param  vertex vertex of the track
         * @param  end end point of the track
         *
         */
          Track(const float &pida, const float &chi2_mu, const float &chi2_pi, const float &chi2_pr, const float &chi_ka, const float &length, const float &kinetic_energy, const TVector3 &vertex, const TVector3 &end);

          // Member variables
          float    m_pida;           ///< pida value
          float    m_chi2_mu;        ///< chi squared fit to the muon expected dEdx
          float    m_chi2_pi;        ///< chi squared fit to the pion expected dEdx
          float    m_chi2_pr;        ///< chi squared fit to the proton expected dEdx 
          float    m_chi2_ka;        ///< chi squared fit to the kaon expected dEdx
          float    m_length;         ///< length of the track
          float    m_kinetic_energy; ///< kinetic energy of the track
          TVector3 m_vertex;         ///< vertex of the track         
          TVector3 m_end;            ///< end of the track 
      
      }; // Track
      
      /**
       * @brief  Shower class 
       */
      class Shower{
      
        public : 
          
          /**
           * @brief  Constructor
           *
           * @param  vertex vertex of the shower
           * @param  direction direction of the shower
           * @param  open_angle opening angle at the vertex of the shower
           * @param  length length of the shower
           *
           */
          Shower(const TVector3 &vertex, const TVector3 &direction, const float &open_angle, const float &length);

          // Member variables
          TVector3 m_vertex;     ///< vertex of the shower 
          TVector3 m_direction;  ///< direction of the shower
          float    m_open_angle; ///< opening angle at the vertex of the shower
          float    m_length;     ///< length of the shower

      }; // Shower

      /*
       *
      // Construct event from defined variables above and fill event list
      Event e();
      event_list.push_back(e);
      *
      */

  }; // EventSelectionTool
} // namespace: selection
#endif
