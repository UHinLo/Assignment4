#ifndef LEPTON_H
#define LEPTON_H
#include <string>
#include <vector>

class lepton
{
  private:
    std::string particle_type;
    double rest_mass;
    int charge;
    bool check_particle;
    // Pointer to a dynamically allocated vector for four-momentum (E/c, px, py, pz)
    std::vector<double>* four_momentum;
    static constexpr double c = 2.99792458e8;
    static constexpr double c_squared = c * c;

  public:
    lepton();
    lepton(const std::string& type, double mass, bool particle, double energy, double px, double py, double pz);
    ~lepton();

    // Setters for four-momentum using a vector
    void set_energy(double e);
    void set_momentum_px(double px);
    void set_momentum_py(double py);
    void set_momentum_pz(double pz);

    // Getters for four-momentum components
    double get_energy() const;
    double get_momentum_px() const;
    double get_momentum_py() const;
    double get_momentum_pz() const;

    void set_particle_type(const std::string& type);
    void set_rest_mass(double mass);
    void set_check_particle(bool particle);
    void set_charge(int c);
    std::string get_particle_type() const;
    double get_rest_mass() const;
    bool get_check_particle() const;
    int get_charge() const;
    void print_particle_data() const;

    // Member function for dot product
    double dot_product(const lepton& other) const;
    // Overloaded operator for sum
    lepton operator+(const lepton& other) const;
    // Copy constructor
    lepton(const lepton& other);
    // Move constructor
    lepton(lepton&& other) noexcept;
    // Move assignment operator
    lepton& operator=(lepton&& other) noexcept;
    // Assignment operator (Copy assignment operator)
    lepton& operator=(const lepton& other);
};

#endif
