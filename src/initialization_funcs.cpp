#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <iomanip>

bool readParameters(const std::string& filename, 
                    int& mc_steps, 
                    double& molar_conc, 
                    double& lambda_bje, 
                    double& box_size,
                    double& charge_anion,
                    double& charge_cation) 
{
    // Open file
    std::ifstream file(filename);
    
    // Check if file is open
    if (!file.is_open()) 
    {
        std::cerr << "Error openings file: " << filename << std::endl;
        return false;
    }

    // Create map of keys and values
    // The key is a string and the value is a function that takes a string as an argument and returns void
    std::unordered_map<std::string, std::function<void(const std::string&)>> map;
    map["mc_steps"] = [&](const std::string& val) { mc_steps = std::stoi(val); };
    map["molar_conc"] = [&](const std::string& val) { molar_conc = std::stod(val); };
    map["lambda_bje"] = [&](const std::string& val) { lambda_bje = std::stod(val); };
    map["box_size"] = [&](const std::string& val) { box_size = std::stod(val); };
    map["charge_anion"] = [&](const std::string& val) { charge_anion = std::stod(val); };
    map["charge_cation"] = [&](const std::string& val) { charge_cation = std::stod(val); };

    // Read file line by line
    std::string line;
    
    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string key, value;
        
        // Split line into key and value
        if (std::getline(iss, key, ':') && std::getline(iss, value)) 
        {
            if (map.find(key) != map.end()) 
            {
                map[key](value);
            }
        }
    }

    file.close();
    
    return true;
}


void printParameters(int mc_steps, 
                     double molar_conc, 
                     double lambda_bje, 
                     double box_size,
                     double charge_anion,
                     double charge_cation) 
{
    int width = 48; // adjust as needed

    std::cout << std::left << std::setw(width) << "Parameter" << "Value" << '\n';
    std::cout << std::string(56, '-') << '\n'; // print a line of dashes

    std::cout << std::setw(width) << "MC Steps:" << mc_steps << '\n';
    std::cout << std::setw(width) << "Molar Concentration:" << std::fixed << std::setprecision(2) << molar_conc << '\n';
    std::cout << std::setw(width) << "Lambda BJE:" << lambda_bje << '\n';
    std::cout << std::setw(width) << "Box Size:" << box_size << '\n';
    std::cout << std::setw(width) << "Charge Anion:" << charge_anion << '\n';
    std::cout << std::setw(width) << "Charge Cation:" << charge_cation << '\n';
}
