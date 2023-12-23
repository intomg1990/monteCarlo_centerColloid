#ifndef INITIALIZATION_FUNCS_H
#define INITIALIZATION_FUNCS_H

struct SimulationParameters {
    // Input parameters
    double lambda_bjerrum;
    double molar_conc;
    double box_length;
    double radius_cutoff;

    int charge_anion;
    int charge_cation;
    int charge_colloid;
    int charge_counterion;
    
    double radius_anion;
    double radius_cation;
    double radius_colloid;
    double radius_counterion;
    
    int kappa_ewald;
    int k_fourier_max;
    
    int mc_steps;

    // Calculated parameters
    double volume;
    
    double num_anions;
    double num_cations;
    double num_counterions;
    double num_particles;
};

bool readParameters(const std::string& filename,
                    SimulationParameters& params);
void printParameters(const SimulationParameters& params);
void rescaleParameters(SimulationParameters& params);
void calculateParameters(SimulationParameters& params);

template <typename T>
void printParameter(const std::string& name, const T& value, const std::string& unit);

#endif // INITIALIZATION_FUNCS_H