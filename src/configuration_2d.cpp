#include "configuration_2d.h"

using namespace std;


MonteCarloConfiguration2D::MonteCarloConfiguration2D(int configuration_size) :
	MonteCarloConfiguration(configuration_size)
{
	
	configuration = (bool**) malloc(size * sizeof(bool*));
	for(int i=0; i < size; i++){
		configuration[i] = (bool*) malloc(size * sizeof(bool));
		for (int j=0; j < size; j++)
			configuration[i][j] = true;
	}
	
	load_energy();
	
}

short int MonteCarloConfiguration2D::read_spin(SpinIndex index) {
	int i = index[0];
	int j = index[1];
	
	if (i >= 0 && i < size && j >= 0 && j < size) {
		return(spin_value(configuration[i][j]));
	}
	else return 0;
}

void MonteCarloConfiguration2D::load_energy() {
	energy = 0;
	
	// HORIZONTAL
	for(int i=0; i < size-1; i++) {
		for(int j=0; j < size; j++){
			energy -= spin_value( !(configuration[i][j] ^ configuration[i+1][j]));
		}
	}
	
	// VERTICAL
	for(int i=0; i < size; i++) {
		for(int j=0; j < size-1; j++){
			energy -= spin_value( !(configuration[i][j] ^ configuration[i][j+1]));
		}
	}
	
	cout << "First Energy: " << energy << '\n';
}

float MonteCarloConfiguration2D::by_size(float value) {
	return (value / (float) pow(size,2));
}

short int MonteCarloConfiguration2D::flip_energy(SpinIndex index) {
	long int diff = 0;
	int i = index[0];
	int j = index[1];
	
	// HORIZONTAL
	if (i < size-1) diff += 2 * spin_value( !(configuration[i][j]^ configuration[i+1][j]));
	if (i > 0) diff += 2 * spin_value( !(configuration[i][j] ^ configuration[i-1][j]));
	
	// VERTICAL
	if (j < size-1) diff += 2 * spin_value( !(configuration[i][j] ^ configuration[i][j+1]));
	if (j > 0) diff += 2 * spin_value( !(configuration[i][j] ^ configuration[i][j-1]));
	
	return diff;
}

void MonteCarloConfiguration2D::try_flip(SpinIndex index) {
	int i, j;
	short int e_diff = flip_energy(index);
	double q = flip_prob(e_diff);
	double r = (double) rand() / RAND_MAX;
	
	if (q > r) {
		i = index[0];
		j = index[1];
		
		energy += e_diff;
		configuration[i][j] = !configuration[i][j];
	}
}

void MonteCarloConfiguration2D::markov_step() {
	SpinIndex index(2,0);
	for (int i=0; i < pow(size,2); i++) {
		index[0] = rand() % size;
		index[1] = rand() % size;
		
		try_flip(index);
	}
}

void MonteCarloConfiguration2D::test() {
	srand(time(NULL));
	
	for (int i=0; i < pow(size,2); i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}