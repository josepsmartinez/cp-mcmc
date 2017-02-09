#include <iostream>
#include "generator.h"
#include "configuration_2d.h"
#include "configuration_1d.h"

int main(int argc, char** argv) {
	int N 		 	= argc > 1 ? atoi(argv[1]) : 	1 * pow(10, 2);
	int N_samples 	= argc > 2 ? atoi(argv[2]) : 	1 * pow(10, 4);

	MonteCarloConfiguration* config = new MonteCarloConfiguration1D(N);
	MonteCarloSampleGenerator* mc = new MonteCarloSampleGenerator(config, N_samples);
	mc->test();
	
	
	config = new MonteCarloConfiguration2D(N);
	mc = new MonteCarloSampleGenerator(config, N_samples);
	mc->test();
	
	
	return 0;
}