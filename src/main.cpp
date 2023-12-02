#include <iostream>
#include "initialization_funcs.h"

int main ()
{
    int mc_steps;
    double molar_conc, lambda_bje, box_size;
    double charge_anion, charge_cation, charge_colloid, charge_counterion;
    double radius_anion, radius_cation, radius_colloid, radius_counterion;
    int number_cations, number_anions;

    // Read parameters from file
    if (!readParameters("parameters.in", mc_steps, molar_conc, lambda_bje, box_size, charge_anion, charge_cation,
                        charge_colloid, charge_counterion, radius_anion, radius_cation, radius_colloid, radius_counterion)) 
    {
        std::cerr << "Error reading parameters." << std::endl;
        return 1;
    }
    
    calculateParameters(molar_conc, number_cations, number_anions, box_size);

    // Print parameters
    printParameters(mc_steps, molar_conc, lambda_bje, box_size, charge_anion, charge_cation, charge_colloid, charge_counterion,
                    radius_anion, radius_cation, radius_colloid, radius_counterion, number_cations, number_anions);


    return 0;
}