#include <iostream>
#include "generator.h"
#include "configuration_2d.h"
#include "configuration_1d.h"

#define RUN1D 	1
#define RUN2D 	2
#define RUNBOTH 0

int main(int argc, char** argv) {
	int N 		 	= argc > 1 ? atoi(argv[1]) : 	1 * pow(10, 2);
	long int N_samples 	= argc > 2 ? atoi(argv[2]) : 	1 * pow(10, 4);
	int dimension		= argc > 3 ? atoi(argv[3]) :	RUNBOTH;

	MonteCarloConfiguration* config;
	MonteCarloSampleGenerator* mc;

	if(dimension == RUNBOTH or dimension == RUN1D) {
		config = new MonteCarloConfiguration1D(N);
		mc = new MonteCarloSampleGenerator(config, N_samples);
		mc->test();
	}
	
	if(dimension == RUNBOTH or dimension == RUN2D) {
		config = new MonteCarloConfiguration2D(N);
		mc = new MonteCarloSampleGenerator(config, N_samples);
		mc->test();
	}
	
	
	
	return 0;
}
