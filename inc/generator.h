#include "configuration.h"

class MonteCarloSampleGenerator {
		float temperature;
		int size;
		MonteCarloConfiguration configuration;
	
	public:
		MonteCarloSampleGenerator(int configuration_size);
		
		void experiment(float temp, long int samples);
	
		void test();
		
}; 