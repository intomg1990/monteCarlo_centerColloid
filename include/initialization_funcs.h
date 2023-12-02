#ifndef INITIALIZATION_FUNCS_H
#define INITIALIZATION_FUNCS_H

bool readParameters(const std::string& filename, int& mc_steps, double& molar_conc, double& lambda_bje, double& box_size,
                    double& charge_anion, double& charge_cation, double& charge_colloid, double& charge_counterion,
                    double& radius_anion, double& radius_cation, double& radius_colloid, double& radius_counterion);

void printParameters(int mc_steps, double molar_conc, double lambda_bje, double box_size, 
                     double charge_anion, double charge_cation, double charge_colloid, double charge_counterion,
                     double radius_anion, double radius_cation, double radius_colloid, double radius_counterion,
                     int number_cations, int number_anions);

void calculateParameters(const double& molar_conc, int& number_cations, int& number_anions, double& box_size);

#endif // INITIALIZATION_FUNCS_H