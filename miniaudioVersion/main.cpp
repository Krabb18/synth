#include <iostream>

#include "AudioManager.h"

double MakeNoise(double dTime)
{
    double dOutput = 0.5 * sin(440.0 * 2 * 3.14159 * dTime);
    return dOutput;
}

int main(int argc, char** argv)
{
    AudioManager audioManager;
    audioManager.SetUserFunction(MakeNoise);
    

    getchar();

    audioManager.Clear();

    return 0;
}
