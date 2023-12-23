#include <iostream>
#include "initialization_funcs.h"

int main() 
{
    SimulationParameters params;
    SimulationsVectors vectors;
    
    if (readParameters("parameters.in", params)) 
    {
        callInitializationFuncs(params, vectors);
    } 
    else 
    {
        std::cerr << "Failed to read parameters!" << std::endl;
    }

    return 0;
}