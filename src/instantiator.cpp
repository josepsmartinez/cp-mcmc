#include <iostream>
#include "generator.h"
#include "configuration_2d.h"
#include "configuration_1d.h"

int main() {
	int N = pow(10, 2);
	int N_samples = pow(10, 2);
	MonteCarloConfiguration* config = new MonteCarloConfiguration1D(N);
	
	MonteCarloSampleGenerator mc(config, N_samples);
	
	mc.test();
	
	
	return 0;
}