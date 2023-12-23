#include <iostream>
#include "initialization_funcs.h"

int main() 
{
    SimulationParameters params;
    SimulationsVectors vectors;
    
    if (readParameters("parameters.in", params)) 
    {
        printParameters(params);
        rescaleParameters(params);
        calculateParameters(params);
        printParameters(params, true);
        allocateVectors(vectors, params);
    } 
    else 
    {
        std::cerr << "Failed to read parameters!" << std::endl;
    }

    return 0;
}