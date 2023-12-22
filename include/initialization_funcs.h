#ifndef INITIALIZATION_FUNCS_H
#define INITIALIZATION_FUNCS_H

struct SimulationParameters {
    double lambda_bjerrum;
    double molar_conc;
    double box_length;
    int charge_anion;
    int charge_cation;
    int charge_colloid;
    int charge_counterion;
    double radius_anion;
    double radius_cation;
    int kappa_ewald;
    double radius_cutoff;
    int k_fourier_max;
    int mc_steps;
};

bool readParameters(const std::string& filename,
                    SimulationParameters& params);
void printParameters(const SimulationParameters& params);

#endif // INITIALIZATION_FUNCS_H