#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "initialization_funcs.h"

bool readParameters(const std::string& filename, SimulationParameters& params) 
{
    std::ifstream file(filename);
    
    if (!file.is_open()) 
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        
        return false;
    }

    std::string line;

    while (getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string key;

        if (!(iss >> key)) 
        {
            continue;
        } 

        if (key == "lambda_bjerrum")
        {
            iss >> params.lambda_bjerrum;
        }
        else if (key == "molar_conc")
        {
            iss >> params.molar_conc;
        }
        else if (key == "box_length")
        {
            iss >> params.box_length;
        }
        else if (key == "charge_anion")
        {
            iss >> params.charge_anion;
        }
        else if (key == "charge_cation")
        {
            iss >> params.charge_cation;
        }
        else if (key == "charge_colloid")
        {
            iss >> params.charge_colloid;
        }
        else if (key == "charge_counterion")
        {
            iss >> params.charge_counterion;
        }
        else if (key == "radius_anion")
        {
            iss >> params.radius_anion;
        }
        else if (key == "radius_cation")
        {
            iss >> params.radius_cation;
        }
        else if (key == "kappa_ewald")
        {
            iss >> params.kappa_ewald;
        }
        else if (key == "radius_cutoff")
        {
            iss >> params.radius_cutoff;
        }
        else if (key == "k_fourier_max")
        {
            iss >> params.k_fourier_max;
        }
        else if (key == "mc_steps")
        {
            iss >> params.mc_steps;
        }
        else 
        {
            std::cerr << "Unknown parameter: " << key << std::endl;
        }

    }

    file.close();

    return true;
}


void printParameters(const SimulationParameters& params) 
{
    const int nameWidth = 30; 
    const int valueWidth = 15;

    const std::string red = "\033[31m";
    const std::string reset = "\033[0m"; 

    std::cout << "Simulation Parameters:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    std::cout << std::left; 

    std::cout << std::setw(nameWidth) << "Bjerrum Length:" << std::setw(valueWidth) << params.lambda_bjerrum << red << "Å" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Molar Concentration:" << std::setw(valueWidth) << params.molar_conc << red << "mol/L" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Box Length:" << std::setw(valueWidth) << params.box_length << red << "Å" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Anion Charge:" << std::setw(valueWidth) << params.charge_anion << red << "e" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Cation Charge:" << std::setw(valueWidth) << params.charge_cation << red << "e" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Colloid Charge:" << std::setw(valueWidth) << params.charge_colloid << red << "e" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Counterion Charge:" << std::setw(valueWidth) << params.charge_counterion << red << "e" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Anion Radius:" << std::setw(valueWidth) << params.radius_anion << red << "Å" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Cation Radius:" << std::setw(valueWidth) << params.radius_cation << red << "Å" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Ewald Kappa:" << std::setw(valueWidth) << params.kappa_ewald << red << "Å⁻¹" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Cutoff Radius:" << std::setw(valueWidth) << params.radius_cutoff << red << "Å" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Fourier K Max:" << std::setw(valueWidth) << params.k_fourier_max << red << "Å⁻¹" << reset << std::endl;
    std::cout << std::setw(nameWidth) << "Monte Carlo Steps:" << std::setw(valueWidth) << params.mc_steps << red << "steps" << reset << std::endl;

    std::cout << std::string(60, '-') << std::endl; 
    std::cout << "End of parameters list" << std::endl;
}