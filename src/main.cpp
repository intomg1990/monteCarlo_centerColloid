#include <iostream>
#include "initialization_funcs.h"

int main ()
{
    int mc_steps;
    double molar_conc, lambda_bje, box_size;
    double charge_anion, charge_cation;

    if (!readParameters("parameters.in", mc_steps, molar_conc, lambda_bje, box_size, charge_anion, charge_cation)) 
    {
        std::cerr << "Error reading parameters." << std::endl;
        return 1;
    }
    else 
    {
        printParameters(mc_steps, molar_conc, lambda_bje, box_size, charge_anion, charge_cation);
    }

    return 0;
}