#ifndef MCC_ABSTRACT
	#define MCC_ABSTRACT
	#include "configuration_abs.h"
#endif

class MonteCarloSampleGenerator {
		MonteCarloConfiguration* configuration;
		float temperature;
		int size;
	
		
		int Nsamples;
	
	public:
		MonteCarloSampleGenerator(MonteCarloConfiguration* config, int n_samples):
				configuration(config),
				Nsamples(n_samples)
		{}
 
		
		void experiment(float temp, long int samples);
	
		void test();
		
}; 