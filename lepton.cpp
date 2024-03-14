#include <iostream>
#include <cmath>
#include <iomanip>
#include "lepton.h"

// Default constructor
lepton::lepton() : particle_type("Unknown"), rest_mass(0), charge(0), check_particle(false), four_momentum(new std::vector<double>(4, 0))
{
}
// Parameterized constructor
lepton::lepton(const std::string& type, double mass, bool particle, double e, double px, double py, double pz):
  particle_type(type), rest_mass(mass), charge((particle) ? -1 : 1), check_particle(particle),four_momentum(new std::vector<double>{e, px, py, pz})
  {
    // Validation can be added here
    if(e < 0)
    {
      std::cerr << "Invalid energy value. It has been set to the rest mass energy equivalent." << std::endl;
      e = rest_mass * c;
    }
  }
// Destructor
lepton::~lepton()
{
  delete four_momentum;
  std::cout<<"Destroying lepton: "<<particle_type<<std::endl;
}

// Setters
void lepton::set_energy(double energy)
{
  if(energy >= 0)
  {
    (*four_momentum)[0] = energy;
  }
  else
  {
    std::cerr<<"Invalid energy value. It must be non-negative. It will be set to rest_mass energy"<<std::endl;
    // Keep the energy value within valid bounds
    (*four_momentum)[0] = rest_mass * c;
  }
}
void lepton::set_momentum_px(double px)
{
  (*four_momentum)[1] = px;
  double new_energy = sqrt(rest_mass * rest_mass + ((*four_momentum)[1]*(*four_momentum)[1] + (*four_momentum)[1]*(*four_momentum)[2] + (*four_momentum)[1]*(*four_momentum)[3]));
  if(new_energy >= 0)
  {
    (*four_momentum)[0] = new_energy;
  }
  else
  {
    std::cerr<<"Invalid energy value. It must be non-negative and less than the rest mass energy equivalent."<<std::endl;
    // Keep the energy value within valid bounds
    (*four_momentum)[0] = rest_mass * c;
  }
}
void lepton::set_momentum_py(double py)
{
  (*four_momentum)[2] = py;
  double new_energy = sqrt(rest_mass * rest_mass + ((*four_momentum)[1]*(*four_momentum)[1] + (*four_momentum)[1]*(*four_momentum)[2] + (*four_momentum)[1]*(*four_momentum)[3]));
  if(new_energy >= 0)
  {
    (*four_momentum)[0] = new_energy;
  }
  else
  {
    std::cerr<<"Invalid energy value. It must be non-negative and less than the rest mass energy equivalent."<<std::endl;
    // Keep the energy value within valid bounds
    (*four_momentum)[0] = rest_mass * c;
  }
}
void lepton::set_momentum_pz(double pz)
{
  (*four_momentum)[3] = pz;
  double new_energy = sqrt(rest_mass * rest_mass + ((*four_momentum)[1]*(*four_momentum)[1] + (*four_momentum)[1]*(*four_momentum)[2] + (*four_momentum)[1]*(*four_momentum)[3]));
  if(new_energy >= 0)
  {
    (*four_momentum)[0] = new_energy;
  }
  else
  {
    std::cerr<<"Invalid energy value. It must be non-negative and less than the rest mass energy equivalent."<<std::endl;
    // Keep the energy value within valid bounds
    (*four_momentum)[0] = rest_mass * c;
  }
}
void lepton::set_particle_type(const std::string& type)
{
  if(type != "electron" && type != "muon")
  {
    std::cout<<"Invalid type of particle. (electron or muon)"<<std::endl;
  }
  particle_type = type;
}
void lepton::set_rest_mass(double mass)
{
  rest_mass = mass;
  std::cout<<"Rest mass of the particle now set to "<<mass<<" MeV"<<std::endl;
}
void lepton::set_check_particle(bool particle)
{
  check_particle = particle;
  charge = (particle) ? -1 : +1;
  std::cout<<"The particle is now a "<<particle_type<<((particle) ? " particle" : " antiparticle")<<" with charge: "<<charge<<std::endl;
}
void lepton::set_charge(int c)
{
  charge = c;
  if(check_particle == true && charge == +1)
  {
    std::cout<<"Charge set does not align with the particle type, particle will be set to it's antiparticle"<<std::endl;
    check_particle = false;
  }
  else if(check_particle == false && charge == -1)
  {
    std::cout<<"Charge set does not align with the particle type, particle will be set to it's particle"<<std::endl;
    check_particle = true;
  }
  else if(check_particle == true && charge == -1)
  {
    std::cout<<"The particle now have charge of "<<charge<<std::endl;
  }
  else if(check_particle == false && charge == 1)
  {
    std::cout<<"The antiparticle now have charge of "<<charge<<std::endl;
  }
  else
  {
    std::cout<<"Charge set does not align with the particle properties"<<std::endl;
  }
}


// Getters
std::string lepton::get_particle_type() const
{
  return particle_type;
}
double lepton::get_rest_mass() const
{
  return rest_mass;
}
bool lepton::get_check_particle() const
{
  return check_particle;
}
double lepton::get_energy() const {
    return (*four_momentum)[0];
}
double lepton::get_momentum_px() const
{
  return (*four_momentum)[1];
}
double lepton::get_momentum_py() const
{
  return (*four_momentum)[2];
}
double lepton::get_momentum_pz() const
{
  return (*four_momentum)[3];
}
int lepton::get_charge() const
{
  return charge;
}

// Print particle data
void lepton::print_particle_data() const
{
  if(four_momentum != nullptr)
  {
    std::cout<<"-------------"<<std::endl;
    std::cout<<"Particle type: "<<particle_type<<" "<<(check_particle ? "particle" : "antiparticle")<<" | ";
    std::cout<<"Rest mass (MeV): "<<rest_mass<<" | "<<"Charge: "<<charge<<" | ";
    std::cout<<"Four-momentum (MeV/c): ("<<(*four_momentum)[0]<<", "<<(*four_momentum)[1]<<", "<<(*four_momentum)[2]<<", "<<(*four_momentum)[3]<<")"<<std::endl;
    std::cout<<"-------------"<<std::endl;
  }
  else
  {
    std::cout<<"The particle has been moved from and its data no longer exists."<<std::endl;
  }
}

// Dot product member function
double lepton::dot_product(const lepton& other) const
{
  // Assuming metric signature (1, -1, -1, -1)
  return (*four_momentum)[0] * other.four_momentum->at(0) - 
          ((*four_momentum)[1] * other.four_momentum->at(1) +
          (*four_momentum)[2] * other.four_momentum->at(2) +
          (*four_momentum)[3] * other.four_momentum->at(3));
}
// Overloaded sum operator
lepton lepton::operator+(const lepton& other) const
{
  return lepton(particle_type, rest_mass, check_particle, 
            (*four_momentum)[0] + other.four_momentum->at(0),
            (*four_momentum)[1] + other.four_momentum->at(1),
            (*four_momentum)[2] + other.four_momentum->at(2),
            (*four_momentum)[3] + other.four_momentum->at(3));
}

// Assignment operator (Copy assignemnt operator)
// Start a new vector and put four momentum in
lepton& lepton::operator=(const lepton& other)
{
  std::cout<<"Calling Copy Assignment for lepton"<<std::endl;
  if(this != &other)
  { 
    // Check for self-assignment
    particle_type = other.particle_type;
    rest_mass = other.rest_mass;
    charge = other.charge;
    check_particle = other.check_particle;
    std::vector<double>* new_four_momentum = new std::vector<double>(*other.four_momentum);
    delete four_momentum;
    four_momentum = new_four_momentum;
  }
  return *this;
}

// Copy Constructor - Modify to add print statement
lepton::lepton(const lepton& other):
  particle_type(other.particle_type), rest_mass(other.rest_mass), charge(other.charge), check_particle(other.check_particle), four_momentum(new std::vector<double>(*other.four_momentum))
  {
    std::cout<<"Calling Copy Constructor for lepton"<<std::endl;
  }

// Move Constructor
lepton::lepton(lepton&& other) noexcept:
  particle_type(std::move(other.particle_type)), rest_mass(other.rest_mass), charge(other.charge), check_particle(other.check_particle), four_momentum(other.four_momentum)
  {
    std::cout<<"Calling Move Constructor for lepton"<<std::endl;
    other.four_momentum = nullptr;
  }

// Move Assignment Operator
// Change four momentum (start a new one and replace it)
lepton& lepton::operator=(lepton&& other) noexcept
{
  std::cout<<"Calling Move Assignment for lepton"<<std::endl;
  if(this != &other)
  {
    delete four_momentum;
    particle_type = std::move(other.particle_type);
    rest_mass = other.rest_mass;
    charge = other.charge;
    check_particle = other.check_particle;
    four_momentum = other.four_momentum;
    other.four_momentum = nullptr;
  }
  return *this;
}
