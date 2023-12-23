#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <cmath>
#include <tuple>
#include <vector>
#include "initialization_funcs.h"

bool readParameters(const std::string& filename, SimulationParameters& params) 
{
    std::ifstream file(filename);
    
    if (!file.is_open()) 
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        
        return false;
    }

    // Map keys to double pointers referring to the input parameters
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
        
        // Skip empty lines
        if (!(iss >> key)) 
        {
            continue;
        } 

        // Serach for key in input text file
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



template <typename T>
void printParameter(const std::string& name, const T& value, const std::string& unit) 
{
    const int name_width = 30; 
    const int value_width = 15;

    // Set color codes for output
    const std::string color = "\033[31m";
    const std::string reset = "\033[0m"; 
    
    std::cout << std::left; 
    std::cout << std::setw(name_width) << name << std::setw(value_width) << value << color << unit << reset << std::endl;
}



void printParameters(const SimulationParameters& params, bool is_calculated) 
{
    std::string header_message, footer_message;
    std::vector<std::tuple<std::string, double, std::string>> parameters_double;
    std::vector<std::tuple<std::string, int, std::string>> parameters_int;

    if (!is_calculated)
    {
        header_message = "Input Parameters List";
        footer_message = "End of Input Parameters List";

        parameters_double = {
        {"Bjerrum Length:", params.lambda_bjerrum, "Å"},
        {"Molar Concentration:", params.molar_conc, "mol/L"},
        {"Box Length:", params.box_length, "Å"},
        {"Anion Radius:", params.radius_anion, "Å"},
        {"Cation Radius:", params.radius_cation, "Å"},
        {"Colloid Radius:", params.radius_colloid, "Å"},
        {"Counterion Radius:", params.radius_counterion, "Å"},
        {"Cutoff Radius:", params.radius_cutoff, "Å"}
        };

        parameters_int = {
        {"Anion Charge:", params.charge_anion, "e"},
        {"Cation Charge:", params.charge_cation, "e"},
        {"Colloid Charge:", params.charge_colloid, "e"},
        {"Counterion Charge:", params.charge_counterion, "e"},
        {"Fourier Max:", params.k_fourier_max, ""},
        {"Ewald Kappa:", params.kappa_ewald, ""},
        {"Monte Carlo Steps:", params.mc_steps, ""}
        };
    }
    else
    {
        header_message = "Calculated Parameters List";
        footer_message = "End of Calculated Parameters List";

        parameters_double = {
        {"Number of Anions:", params.num_anions, ""},
        {"Number of Cations:", params.num_cations, ""},
        {"Number of Counterions:", params.num_counterions, ""},
        {"Number of Particles:", params.num_particles, ""},
        };
    }

    std::cout << header_message << std::endl;
    std::cout << std::string(60, '-') << std::endl;


    for (const auto& [name, value, unit] : parameters_double) 
    {
        printParameter(name, value, unit);
    }

    for (const auto& [name, value, unit] : parameters_int) 
    {
        printParameter(name, value, unit);
    }

    std::cout << std::string(60, '-') << std::endl; 
    std::cout << footer_message << std::endl;

    std::cout << std::endl;
}



void rescaleParameters(SimulationParameters& params) 
{
    params.box_length /= params.lambda_bjerrum;

    params.radius_anion /= params.lambda_bjerrum;
    params.radius_cation /= params.lambda_bjerrum;
    params.radius_colloid /= params.lambda_bjerrum;
    params.radius_counterion /= params.lambda_bjerrum;
    
    params.radius_cutoff /= params.lambda_bjerrum;

    params.kappa_ewald = params.kappa_ewald / params.box_length;
    params.radius_cutoff = params.radius_cutoff * params.box_length;

    // Concentration in simulation units
    params.molar_conc *= 1e-27 * std::pow(params.lambda_bjerrum, 3);
}



void calculateParameters(SimulationParameters& params) 
{
    params.volume = params.box_length * params.box_length * params.box_length;
    
    params.num_anions = static_cast<int>(std::round(6.0221e23 * params.molar_conc * params.volume));
    params.num_cations = params.num_anions;
    params.num_counterions = static_cast<int>(std::fabs(params.charge_colloid / params.charge_counterion));
    params.num_particles = params.num_anions + params.num_cations + params.num_counterions + 1;

    params.radius_cutoff_sq = params.radius_cutoff * params.radius_cutoff;
}



bool check_overlap(const SimulationParameters& params, const SimulationsVectors& vectors, int i) 
{

    for (int j = 0; j < i; ++j) 
    {
        double dx = vectors.positions[i][0] - vectors.positions[j][0];
        double dy = vectors.positions[i][1] - vectors.positions[j][1];
        double dz = vectors.positions[i][2] - vectors.positions[j][2];

        dx -= params.box_length * std::round(dx / params.box_length);
        dy -= params.box_length * std::round(dy / params.box_length);
        dz -= params.box_length * std::round(dz / params.box_length);

        double dist = std::sqrt(dx * dx + dy * dy + dz * dz);

        if (dist < vectors.radii[i] + vectors.radii[j]) 
        {
            return true;
        }
    }

    return false;
}



void setInitialPositions(SimulationsVectors& vectors, const SimulationParameters& params) 
{
    vectors.positions.resize(params.num_particles);
    for (auto& position : vectors.positions) 
    {
        position.resize(3);
    }

    vectors.positions[0] = {0.0, 0.0, 0.0};

    for (int i = 1; i < params.num_particles; ++i) 
    {
        
        while (true) 
        {
            vectors.positions[i][0] = (2.0 * std::rand() / RAND_MAX - 1.0) * params.box_length / 2.0;
            vectors.positions[i][1] = (2.0 * std::rand() / RAND_MAX - 1.0) * params.box_length / 2.0;
            vectors.positions[i][2] = (2.0 * std::rand() / RAND_MAX - 1.0) * params.box_length / 2.0;

            
            if (!check_overlap(params, vectors, i)) 
            {
                break;
            }
        }

    }

    std::cout << "Initial positions set!\n" << std::endl;

}

    

void allocateVectors(SimulationsVectors& vectors, const SimulationParameters& params) 
{
    vectors.charges.resize(params.num_particles);
    vectors.radii.resize(params.num_particles);
    
    for (int i = 0; i < params.num_particles; ++i) 
    {
        if (i == 0) 
        {
            vectors.charges[i] = params.charge_colloid;
            vectors.radii[i] = params.radius_colloid;
        } 
        else if (i <= params.num_anions) 
        {
            vectors.charges[i] = params.charge_anion;
            vectors.radii[i] = params.radius_anion;
        } 
        else if (i <= params.num_anions + params.num_cations) 
        {
            vectors.charges[i] = params.charge_cation;
            vectors.radii[i] = params.radius_cation;
        } 
        else 
        {
            vectors.charges[i] = params.charge_counterion;
            vectors.radii[i] = params.radius_counterion;
        }
    }

    setInitialPositions(vectors, params);

}