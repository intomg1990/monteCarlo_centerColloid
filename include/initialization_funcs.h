#ifndef INITIALIZATION_FUNCS_H
#define INITIALIZATION_FUNCS_H

bool readParameters(const std::string& filename, int& mc_steps, double& molar_conc, double& lambda_bje, double& box_size,
                    double& charge_anion, double& charge_cation);
void printParameters(int mc_steps, double molar_conc, double lambda_bje, double box_size, double charge_anion,
                     double charge_cation);

#endif // INITIALIZATION_FUNCS_H