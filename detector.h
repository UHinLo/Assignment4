#ifndef DETECTOR_H
#define DETECTOR_H

#include <string>
#include "lepton.h"

class detector
{
  private:
    std::string detector_type;
    bool status;
    int detector_particles_number;

  public:
    detector();
    detector(const std::string& type);
    ~detector();
    void set_detector_type(const std::string& type);
    std::string get_detector_type() const;
    bool get_status() const;
    int get_detector_particles_number() const;
    void turn_on();
    void turn_off();
    int detect(const lepton& particle);
    void print_status() const;
    void print_detected() const;

    // Special member functions
    // Copy constructor
    detector(const detector& other);
    // Assignment operator (Copy assignment operator)
    detector& operator=(const detector& other);
    // Move constructor
    detector(detector&& other) noexcept;
    // Move assignment operator
    detector& operator=(detector&& other) noexcept;
};

#endif
