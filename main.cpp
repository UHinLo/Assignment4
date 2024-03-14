// Assignment 4
// Program of creating electrons, muons and their anti particles and put them in different special defined functions.
// Program is run by the following command
// g++ -std=c++17 -o assignment4 main.cpp lepton.cpp
// .\assignment4
// U Hin Lo, 10916069, 14/03/2024

#include <iostream>
#include <vector>
#include <random>
#include "lepton.h"

// Generate random number
double random_number()
{
  std::random_device random_d;
  std::mt19937 eng(random_d());
  std::uniform_real_distribution<double> distr(0.0, 3.0e8);
  return distr(eng);
}

int main()
{
  std::vector<lepton> particles;
  particles.reserve(8);

  // Emplace back particle objects directly into the vector
  // Two electrons, four muons, one antielectron, one antimuon
  particles.emplace_back("electron", 0.511, true, 5, 1, 1, 1);
  particles.emplace_back("electron", 0.511, true, random_number(), random_number(), random_number(), random_number());
  particles.emplace_back("muon", 105.658, true, random_number(), random_number(), random_number(), random_number());
  particles.emplace_back("muon", 105.658, true, random_number(), random_number(), random_number(), random_number());
  particles.emplace_back("muon", 105.658, true, random_number(), random_number(), random_number(), random_number());
  particles.emplace_back("muon", 105.658, true, random_number(), random_number(), random_number(), random_number());
  particles.emplace_back("electron", 0.511, false, random_number(), random_number(), random_number(), random_number());
  particles.emplace_back("muon", 105.658, false, random_number(), random_number(), random_number(), random_number());

  // Print information about particles in the vector
  for(const auto& particle : particles)
  {
    particle.print_particle_data();
  }


  // Part 3
  std::cout<<"---"<<std::endl;
  lepton sum_of_electrons = particles[0] + particles[1];
  std::cout<<"Sum of electrons' four momentum: ( "<<sum_of_electrons.get_energy();
  std::cout<<" , "<<sum_of_electrons.get_momentum_px()<<" , "<<sum_of_electrons.get_momentum_py()<<" , "<<sum_of_electrons.get_momentum_pz()<<" )"<<std::endl;

  // Dot product
  double dot_product_of_muons = particles[2].dot_product(particles[3]);
  std::cout<<"Dot product of two muons: "<<dot_product_of_muons<<std::endl;

  std::cout<<"---"<<std::endl;
  lepton new_electron;
  // Using the copy assignment operator to copy the first electron
  new_electron = particles[0];
  new_electron.print_particle_data();
  particles[0].print_particle_data();
  std::cout<<"---"<<std::endl;

  // Using the copy constructor to create a new muon from the first one
  std::cout<<"---"<<std::endl;
  lepton new_muon(particles[2]);
  new_muon.print_particle_data();
  particles[2].print_particle_data();
  std::cout<<"---"<<std::endl;

  // Move the old antielectron into a new antielectron object using the move constructor
  std::cout<<"---"<<std::endl;
  lepton antielectron(std::move(particles[6]));
  antielectron.print_particle_data();
  particles[6].print_particle_data();
  std::cout<<"---"<<std::endl;

  std::cout<<"---"<<std::endl;
  // Create a new lepton object for the new antimuon
  lepton new_antimuon;
  // Move assign the antimuon to the new antimuon using the move assignment operator
  new_antimuon = std::move(particles[7]);
  new_antimuon.print_particle_data();
  particles[7].print_particle_data();
  std::cout<<"---"<<std::endl;

  std::cout<<"---End of program---"<<std::endl;
  return 0;
}
