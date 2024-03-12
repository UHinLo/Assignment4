#include <iostream>
#include "detector.h"

// Default constructor
detector::detector():
  detector_type("tracker"), status(false), detector_particles_number(0)
  {
  }

// Parameterized constructor
detector::detector(const std::string& type):
  detector_type(type), status(false), detector_particles_number(0)
  {
  }

// Destructor
detector::~detector()
{
  std::cout<<"Destroying "<<detector_type<<std::endl;
}

// Setters
// Setters for number of particles detected doesn't make sense so there's no setter for it
void detector::set_detector_type(const std::string& type)
{
  if(type != "tracker" && type != "calorimeter" && type != "muon chamber" && type != "muonchamber" && type != "muon_chamber")
  {
    std::cout<<"Invalid type of detector. (tracker, calorimeter or muon_chamber)"<<std::endl;
  }
  detector_type = type;
}

// Getters
std::string detector::get_detector_type() const
{
  return detector_type;
}
bool detector::get_status() const
{
  return status;
}
int detector::get_detector_particles_number() const
{
  return detector_particles_number;
}

// Turn on function
void detector::turn_on()
{
  status = true;
  std::cout<<"Turning on "<<detector_type<<std::endl;
}

// Turn off function
void detector::turn_off()
{
  status = false;
  std::cout<<"Shutting down "<<detector_type<<std::endl;
}

// Detection
int detector::detect(const lepton& particle)
{
  if(!status)
  {
    std::cout<<"Trying to detect with "<<detector_type<<" turned off.\n";
    return 0;
  }
  else
  {
    bool detected = false;
    if((detector_type == "tracker" && particle.get_particle_type() == "electron") || (detector_type == "tracker" && particle.get_particle_type() == "muon"))
    {
    detected = true;
    }
    else if(detector_type == "calorimeter" && particle.get_particle_type() == "electron")
    {
    detected = true;
    }
    else if((detector_type == "muon chamber" && particle.get_particle_type() == "muon") || (detector_type == "muonchamber" && particle.get_particle_type() == "muon") || (detector_type == "muon_chamber" && particle.get_particle_type() == "muon"))
    {
    detected = true;
    }
    if(detected)
    {
    std::cout << particle.get_particle_type() << (particle.get_check_particle() ? "" : " antiparticle") << " was detected." << std::endl;
    detector_particles_number++;
    return 1;
    }

    // Particle type not detected
    return 0;
  }
}

// Print detector status
void detector::print_status() const
{
  std::cout<<"Detector Type: "<<detector_type<<" - Status: "<<(status ? "On" : "Off")<<std::endl;
}

// Print number of particles detected
void detector::print_detected() const
{
  std::cout<<detector_particles_number<<" particles detected"<<std::endl;
}
