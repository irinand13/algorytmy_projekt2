#include <iostream>
#include "Runner.h"
#include <ctime>
using namespace std;
int main(int argc, char* argv[]) {
    srand(std::time(nullptr));

    if (Parameters::readParameters(argc - 1, argv + 1) !=0) {
        std::cerr << "Blad podczas parsowania parametrow wywolania!" << std::endl;
        return 1;
    }

    Runner runner;
    runner.run();

    return 0;
}


