// Assignment 4 - lab go bruh
// Program of creating electrons, muons and their anti particles and put them into detectors.
// Program is run by the following command
// g++ -std=c++17 -o assignment4 main.cpp lepton.cpp detector.cpp
// .\assignment4
// U Hin Lo, 10916069, 12/03/2024

#include <iostream>
#include <vector>
#include <random>
#include "lepton.h"
#include "detector.h"

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
  particles.emplace_back("electron", 0.511, true, random_number(), random_number(), random_number(), random_number());
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

  // Instantiate the three types of detectors
  detector tracker("tracker"), calorimeter("calorimeter"), muon_chamber("muon_chamber");

  // Array of pointers to detectors for easier iteration
  std::vector<detector*> detectors = {&tracker, &calorimeter, &muon_chamber};

  // Operate the detectors using iterators
  for(auto detector_iterator = detectors.begin(); detector_iterator != detectors.end(); ++detector_iterator)
  {
    detector* detector_using = *detector_iterator;
    detector_using->turn_on();
    for(auto particle_iterator = particles.begin(); particle_iterator != particles.end(); ++particle_iterator)
    {
      const lepton& particle = *particle_iterator;
      detector_using->detect(particle);
    }
    detector_using->print_detected();
    detector_using->turn_off();
    // Attempt to detect the first particle with the detector off
    detector_using->detect(particles.front());
    std::cout<<"--------------------------"<<std::endl;
  }

  // Part 3
  // Assuming `particles` is a vector of lepton objects and contains at least two electrons
  lepton sum_of_electrons = particles[0] + particles[1];
  // Assuming `particles` contains at least two muons, following the two electrons
  double dot_product_of_muons = particles[2].dot_product(particles[3]);
  // Assuming there is at least one electron in `particles`
  lepton new_electron;
  // Using the assignment operator to copy the first electron
  new_electron = particles[0];
  // Assuming there is at least one muon in `particles`, following the electrons
  // Using the copy constructor to create a new muon from the first one
  lepton new_muon(particles[2]);
  // Assuming there is at least one antielectron in `particles`
  // Move the last particle (assumed to be an antielectron) into a new antielectron object
  lepton antielectron(std::move(particles[6]));
  // Create a new lepton object for the new antimuon
  lepton new_antimuon;
  // Move assign the antimuon to the new antimuon using the move assignment operator
  new_antimuon = std::move(particles[7]);

  std::cout<<"---End of program---"<<std::endl;
  return 0;
}
