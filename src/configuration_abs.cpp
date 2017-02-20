#include "configuration_abs.h"

MonteCarloConfiguration::MonteCarloConfiguration(int configuration_size, int n_accumulators): 
	size(configuration_size), 
	accumulators(n_accumulators) 
{}

void MonteCarloConfiguration::set_temperature(float temp){ temperature = temp; }
		
int MonteCarloConfiguration::get_size() { return size; }

float MonteCarloConfiguration::get_acc(int index) { return accumulators[index]; }


double MonteCarloConfiguration::flip_prob(short int energy_diff){ 
	return exp(-energy_diff/temperature); 
}



static short int MonteCarloConfiguration::spin_value(bool spin) { 
	return ((int) spin) * 2 - 1; 
}

void MonteCarloConfiguration::clear() { 
	for(unsigned int i=0; i < accumulators.size(); i++) accumulators[i] = 0; 
}
		


void MonteCarloConfiguration::markov_step(bool relax=false) {
	for (int i=0; i < available_spins(); i++) {
		try_flip(random_spin());
	}
	if(!relax) accumulate();
}

float MonteCarloConfiguration::by_size(float value) {
	return value / available_spins();
}