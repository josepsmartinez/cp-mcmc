#include "generator.h"

using namespace std;

MonteCarloSampleGenerator::MonteCarloSampleGenerator(int configuration_size):
	size(configuration_size),
	configuration(MonteCarloConfiguration(configuration_size))
{
}
 
void MonteCarloSampleGenerator::experiment(float temp, long int samples) {
	temperature = temp;
	configuration.set_temperature(temperature);
	float beta = 1 / temperature;

// THEORY
	float u_theory = -tanh(beta);
	float c_theory = pow(beta / cosh(beta), 2);
	
	printf("Theory Average Energy: %.3f | Theory Specific Heat: %.3f | Beta: %.3f  | Temperature: %.2f  | ", u_theory, c_theory, beta, temperature);
	
// SAMPLING
	long int relax = samples / 10;
	for (int i=0; i < relax; i++) configuration.markov_step();
	
	float u_mc = 0;
	float c_mc = 0;
	for (int i=0; i < samples; i++) {
		configuration.markov_step();
		u_mc += configuration.get_energy();
		c_mc += configuration.get_energy() * configuration.get_energy();
	}

	u_mc = u_mc / (float) (samples);	
	c_mc = pow(beta, 2) * ((c_mc / (float) (samples)) - pow(u_mc, 2)) ;
	
	printf("Average Energy: %.3f | ", u_mc / (float) (size));
	printf("Average Specific Heat: %.3f  \n", c_mc / (float) (size));
	
}

void MonteCarloSampleGenerator::test() {
	for (float f=4.f; f > 0.f; f-=0.2f) {
		srand(time(NULL));
		experiment(f, 10000);
	}
}