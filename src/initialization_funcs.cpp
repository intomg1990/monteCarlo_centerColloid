#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <cmath>
#include "initialization_funcs.h"

bool readParameters(const std::string& filename, SimulationParameters& params) 
{
    std::ifstream file(filename);
    
    if (!file.is_open()) 
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        
        return false;
    }

    std::unordered_map<std::string, double*> param_map = {
        {"lambda_bjerrum", &params.lambda_bjerrum},
        {"molar_conc", &params.molar_conc},
        {"box_length", &params.box_length},
        {"radius_anion", &params.radius_anion},
        {"radius_cation", &params.radius_cation},
        {"radius_colloid", &params.radius_colloid},
        {"radius_counterion", &params.radius_counterion},
        {"radius_cutoff", &params.radius_cutoff}
    };

    std::unordered_map<std::string, int*> int_param_map = {
        {"charge_anion", &params.charge_anion},
        {"charge_cation", &params.charge_cation},
        {"charge_colloid", &params.charge_colloid},
        {"charge_counterion", &params.charge_counterion},
        {"k_fourier_max", &params.k_fourier_max},
        {"kappa_ewald", &params.kappa_ewald},
        {"mc_steps", &params.mc_steps}
    };

    std::string line, key;
    
    while (getline(file, line)) 
    {
        std::istringstream iss(line);
        
        if (!(iss >> key)) 
        {
            continue;
        } 

        if (param_map.find(key) != param_map.end()) 
        {
            iss >> *param_map[key];
        } 
        else if (int_param_map.find(key) != int_param_map.end()) 
        {
            iss >> *int_param_map[key];
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
    const int name_width = 30; 
    const int value_width = 15;

    const std::string red = "\033[31m";
    const std::string reset = "\033[0m"; 

    std::cout << "Simulation Input Parameters:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    std::cout << std::left; 

    std::cout << std::setw(name_width) << "Bjerrum Length:" << std::setw(value_width) << params.lambda_bjerrum << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Molar Concentration:" << std::setw(value_width) << params.molar_conc << red << "mol/L" << reset << std::endl;
    std::cout << std::setw(name_width) << "Box Length:" << std::setw(value_width) << params.box_length << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Anion Charge:" << std::setw(value_width) << params.charge_anion << red << "e" << reset << std::endl;
    std::cout << std::setw(name_width) << "Cation Charge:" << std::setw(value_width) << params.charge_cation << red << "e" << reset << std::endl;
    std::cout << std::setw(name_width) << "Colloid Charge:" << std::setw(value_width) << params.charge_colloid << red << "e" << reset << std::endl;
    std::cout << std::setw(name_width) << "Counterion Charge:" << std::setw(value_width) << params.charge_counterion << red << "e" << reset << std::endl;
    std::cout << std::setw(name_width) << "Anion Radius:" << std::setw(value_width) << params.radius_anion << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Cation Radius:" << std::setw(value_width) << params.radius_cation << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Colloid Radius:" << std::setw(value_width) << params.radius_colloid << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Counterion Radius:" << std::setw(value_width) << params.radius_counterion << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Ewald Kappa:" << std::setw(value_width) << params.kappa_ewald << red << "Å⁻¹" << reset << std::endl;
    std::cout << std::setw(name_width) << "Cutoff Radius:" << std::setw(value_width) << params.radius_cutoff << red << "Å" << reset << std::endl;
    std::cout << std::setw(name_width) << "Fourier K Max:" << std::setw(value_width) << params.k_fourier_max << red << "Å⁻¹" << reset << std::endl;
    std::cout << std::setw(name_width) << "Monte Carlo Steps:" << std::setw(value_width) << params.mc_steps << red << "steps" << reset << std::endl;

    std::cout << std::string(60, '-') << std::endl; 
    std::cout << "End of input parameters list" << std::endl;

    std::cout << std::endl;
}

void rescaleParameters(SimulationParameters& params) {
    
    if (params.lambda_bjerrum == 0) 
    {
        std::cerr << "Bjerrum length cannot be zero for rescaling." << std::endl;
        return;
    }

    params.box_length /= params.lambda_bjerrum;
    params.radius_anion /= params.lambda_bjerrum;
    params.radius_cation /= params.lambda_bjerrum;
    params.radius_colloid /= params.lambda_bjerrum;
    params.radius_counterion /= params.lambda_bjerrum;
    params.radius_cutoff /= params.lambda_bjerrum;

    params.molar_conc *= 1e-27 * std::pow(params.lambda_bjerrum, 3);
}

void calculateParameters(SimulationParameters& params) 
{
    params.volume = params.box_length * params.box_length * params.box_length;
    
    params.num_anions = static_cast<int>(std::round(6.0221e23 * params.molar_conc * params.volume));
    params.num_cations = params.num_anions;
}