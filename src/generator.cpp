#include "generator.h"
#include "configuration_1d.h"

using namespace std;

void MonteCarloSampleGenerator::experiment(float temp) {
	temperature = temp;
	configuration->set_temperature(temperature);

// THEORY
	configuration->print_theory(cout);
	
// SAMPLING
	long int relax = Nsamples / 10;
	for (int i=0; i < relax; i++) configuration->markov_step(relax=true);
	
	configuration->clear();
	for (int i=0; i < Nsamples; i++) {
		configuration->markov_step();
	}

// REALIZATION AND OUTPUTTING	
	vector<float> results = configuration->realize(Nsamples);	
	configuration->print_realization(results, cout);
	
}

void MonteCarloSampleGenerator::test() {
	cout << "N: " << configuration->get_size() << " N_samples: " << Nsamples << "\n";
	
	configuration->print_header(cout);
	for (float f=4.f; f > 0.f; f-=0.2f) 
	//for (float f=0.2f; f < 4.2f; f+=0.2f)
		experiment(f);
}