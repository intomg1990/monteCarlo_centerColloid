#include <iostream>
#include "initialization_funcs.h"

int main() 
{
    SimulationParameters params;
    
    if (readParameters("parameters.in", params)) 
    {
        printParameters(params);
    } 
    else 
    {
        std::cerr << "Failed to read parameters!" << std::endl;
    }

    return 0;
}