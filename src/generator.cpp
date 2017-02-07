#include "generator.h"
#include "configuration_1d.h"

using namespace std;

void MonteCarloSampleGenerator::experiment(float temp, long int samples) {
	temperature = temp;
	configuration->set_temperature(temperature);
	float beta = 1 / temperature;

// THEORY
	float u_theory = -tanh(beta); // 1D
	float c_theory = pow(beta / cosh(beta), 2); // 1D
	double m_theory;
	if(temperature < (2 / log(1 + sqrt(2)))) m_theory = pow(1 - pow(sinh(2*beta), -4), 1/8); 
	else m_theory = 0;
	
	printf("Theory Energy: %.3f | Theory Specific Heat: %.3f | Theory Magnetization: %.3f | Beta: %.3f  | Temperature: %.2f  | ", u_theory, c_theory, m_theory, beta, temperature);
	
// SAMPLING
	long int relax = samples / 10;
	for (int i=0; i < relax; i++) configuration->markov_step(relax=true);
	
	configuration->clear();
	for (int i=0; i < samples; i++) {
		configuration->markov_step();
	}

// REALIZATION AND OUTPUTTING	
	vector<float> results = configuration->realize(samples);	
	configuration->print_realization(results, std::cout);
	
	
}

void MonteCarloSampleGenerator::test() {
	for (float f=0.2f; f < 4.2f; f+=0.2f) {
		srand(time(NULL));
		experiment(f, Nsamples);
	}
}