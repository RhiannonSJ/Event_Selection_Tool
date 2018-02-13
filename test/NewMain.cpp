#include "../include/EventSelectionTool.h"
#include "../include/Event.h"
#include <iostream>
#include <sstream>
#include <numeric>
#include <time.h>
#include "TVector3.h"

using namespace selection;

int MainTest(){
  
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Start: Local time and date:  " << asctime(timeinfo) << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Running all files " << std::endl;
  
  // Counters
  unsigned int correctly_reconstructed_cc  = 0;
  unsigned int true_topology_cc            = 0;
  unsigned int reco_topology_cc            = 0;

  unsigned int correctly_reconstructed_nc  = 0;
  unsigned int true_topology_nc            = 0;
  unsigned int reco_topology_nc            = 0;

  unsigned int correctly_reconstructed_0pi = 0;
  unsigned int true_topology_0pi           = 0;
  unsigned int reco_topology_0pi           = 0;
  unsigned int protons_cc0pi               = 0;
  unsigned int true_protons_cc0pi          = 0;

  unsigned int correctly_reconstructed_1pi = 0;
  unsigned int true_topology_1pi           = 0;
  unsigned int reco_topology_1pi           = 0;
  unsigned int protons_cc1pi               = 0;
  unsigned int true_protons_cc1pi          = 0;

  unsigned int correctly_reconstructed_pi0 = 0;
  unsigned int true_topology_pi0           = 0;
  unsigned int reco_topology_pi0           = 0;

  // Initialise event list and the topology maps
  EventSelectionTool::EventList events;
  
  TopologyMap cc_signal_map;
  TopologyMap nc_signal_map;
  TopologyMap cc0pi_signal_map;
  TopologyMap cc1pi_signal_map;
  TopologyMap ccpi0_signal_map;
 
  std::vector< int > mu;
  std::vector< int > pi;
  std::vector< int > pi0;
  
  mu.push_back( 13 );
  pi.push_back( 211 );
  pi.push_back(-211 );
  pi0.push_back( 111 );
  
  cc_signal_map.insert( std::make_pair( mu,  1 ) );
  nc_signal_map.insert( std::make_pair( mu,  0 ) );
  
  cc0pi_signal_map.insert( std::make_pair( mu,  1 ) );
  cc0pi_signal_map.insert( std::make_pair( pi,  0 ) );
  cc0pi_signal_map.insert( std::make_pair( pi0, 0 ) );

  cc1pi_signal_map.insert( std::make_pair( mu,  1 ) );
  cc1pi_signal_map.insert( std::make_pair( pi,  1 ) );
  
  ccpi0_signal_map.insert( std::make_pair( mu,  1 ) );
  ccpi0_signal_map.insert( std::make_pair( pi0, 1 ) );
  
  for( unsigned int i = 0; i < 398; ++i ){
  
    // Get the filename for each 2D histogram
    std::stringstream ss;
    ss.clear();
    
    std::string name;
    name.clear();
    
    char file_name[1024];
    
    ss << "/hepstore/rjones/Samples/FNAL/analysis_trees/all/3486578_" << i <<"/output_file.root";
    name = ss.str();
            
    strcpy( file_name, name.c_str() );
      
    EventSelectionTool::LoadEventList(file_name, events);
  }

  std::cout << " Events : " << events.size() << std::endl;
  
  for(unsigned int i = 0; i < events.size(); ++i){

    // Do analysis
    Event &e(events[i]);

    if(e.CheckMCTopology(cc_signal_map) && e.CheckRecoTopology(cc_signal_map)) correctly_reconstructed_cc++;
    if(e.CheckMCTopology(cc_signal_map)) true_topology_cc++;
    if(e.CheckRecoTopology(cc_signal_map)) reco_topology_cc++;

    if(e.CheckMCTopology(nc_signal_map) && e.CheckRecoTopology(nc_signal_map)) correctly_reconstructed_nc++;
    if(e.CheckMCTopology(nc_signal_map)) true_topology_nc++;
    if(e.CheckRecoTopology(nc_signal_map)) reco_topology_nc++;
    
    if(e.CheckMCTopology(cc0pi_signal_map) && e.CheckRecoTopology(cc0pi_signal_map)) correctly_reconstructed_0pi++;
    if(e.CheckMCTopology(cc0pi_signal_map)) true_topology_0pi++;
    if(e.CheckRecoTopology(cc0pi_signal_map)) {
      reco_topology_0pi++;
      if( e.CountRecoParticlesWithPdg(2212) > 0) protons_cc0pi++;
      if( e.CountMCParticlesWithPdg(2212) > 0)   true_protons_cc0pi++;
    }
    
    if(e.CheckMCTopology(cc1pi_signal_map) && e.CheckRecoTopology(cc1pi_signal_map)) correctly_reconstructed_1pi++;
    if(e.CheckMCTopology(cc1pi_signal_map)) true_topology_1pi++;
    if(e.CheckRecoTopology(cc1pi_signal_map)) {
      reco_topology_1pi++;
      if( e.CountRecoParticlesWithPdg(2212) > 0) protons_cc1pi++;
      if( e.CountMCParticlesWithPdg(2212) > 0)   true_protons_cc1pi++;
    }
    
    if(e.CheckMCTopology(ccpi0_signal_map) && e.CheckRecoTopology(ccpi0_signal_map)) correctly_reconstructed_pi0++;
    if(e.CheckMCTopology(ccpi0_signal_map)) true_topology_pi0++;
    if(e.CheckRecoTopology(ccpi0_signal_map)) reco_topology_pi0++;
  }

  std::cout << "===========================================================" << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Percentage of correctly reconstructed NC events     : " << correctly_reconstructed_nc/double(true_topology_nc) * 100                         << std::endl;
  std::cout << " Impurity of reconstructed NC events                 : " << (reco_topology_nc - correctly_reconstructed_nc)/double(reco_topology_nc) * 100    << std::endl; 
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Percentage of correctly reconstructed CC events     : " << correctly_reconstructed_cc/double(true_topology_cc) * 100                         << std::endl;
  std::cout << " Impurity of reconstructed CC events                 : " << (reco_topology_cc - correctly_reconstructed_cc)/double(reco_topology_cc) * 100    << std::endl; 
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Percentage of correctly reconstructed CC 0Pi events : " << correctly_reconstructed_0pi/double(true_topology_0pi) * 100                       << std::endl;
  std::cout << " Impurity of reconstructed CC 0Pi events             : " << (reco_topology_0pi - correctly_reconstructed_0pi)/double(reco_topology_0pi) * 100 << std::endl; 
  std::cout << " Reco Protons                                        : " << protons_cc0pi      << std::endl;
  std::cout << " True Protons                                        : " << true_protons_cc0pi << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Percentage of correctly reconstructed CC 1Pi events : " << correctly_reconstructed_1pi/double(true_topology_1pi) * 100                       << std::endl;
  std::cout << " Impurity of reconstructed CC 1Pi events             : " << (reco_topology_1pi - correctly_reconstructed_1pi)/double(reco_topology_1pi) * 100 << std::endl; 
  std::cout << " Reco Protons                                        : " << protons_cc1pi << std::endl;
  std::cout << " True Protons                                        : " << true_protons_cc1pi << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Percentage of correctly reconstructed CC Pi0 events : " << correctly_reconstructed_pi0/double(true_topology_pi0) * 100                       << std::endl;
  std::cout << " Impurity of reconstructed CC Pi0 events             : " << (reco_topology_pi0 - correctly_reconstructed_pi0)/double(reco_topology_pi0) * 100 << std::endl; 
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << "===========================================================" << std::endl;

  time_t rawtime_end;
  struct tm * timeinfo_end;
  time (&rawtime_end);
  timeinfo_end = localtime (&rawtime_end);
  std::cout << " End: Local time and date:  " << asctime(timeinfo_end) << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

  return 0;

} // MainTest()
