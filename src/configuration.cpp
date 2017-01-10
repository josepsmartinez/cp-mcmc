#include "configuration.h"

using namespace std;

MonteCarloConfiguration::MonteCarloConfiguration(int configuration_size) :
	size(configuration_size)
{
	configuration = (bool*) malloc(size * sizeof(bool));
	
	load_energy();
}

short int MonteCarloConfiguration::read_spin(int index) {
	if (configuration[index]) return 1;
	else return -1;
}

void MonteCarloConfiguration::load_energy() {
	energy = 0;
	for(int i=0; i < size-1; i++) {
		energy -= read_spin(i) * read_spin(i+1);
	}
	
	//cout << "First Energy: " << energy << '\n';
}


short int MonteCarloConfiguration::flip_energy(int index) {
	long int diff = 0;
	if (index == 0) {
		diff += 2 * read_spin(0) * read_spin(1); // + 0~1 - -0~1
	}
	else if (index == size-1) {
		diff += 2 * read_spin(size-2) * read_spin(size-1);
	}
	else {
		diff += 2 * read_spin(index)  * (read_spin(index-1) + read_spin(index+1));
	}
	
	return diff;
}

double MonteCarloConfiguration::flip_prob(int index) {
	double beta = 1 / temperature;
	long int energy_diff = flip_energy(index);
	
	return exp(-beta * energy_diff);
}

void MonteCarloConfiguration::try_flip(int index) {
	double r = (double) rand() / RAND_MAX;
	double q = flip_prob(index);
	//printf("q: %f r: %f  %i \n", q, r, q>r);
	
	
	if (q > r) {
		energy += flip_energy(index);
		configuration[index] = !configuration[index];
	}
}

void MonteCarloConfiguration::markov_step() {
	for (int i=0, r; i < size; i++) {
		r = rand() % size;
		try_flip(r);
		//try_flip(i);
	}
}

void MonteCarloConfiguration::test() {
	srand(time(NULL));
	
	for (int i=0; i < size; i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}