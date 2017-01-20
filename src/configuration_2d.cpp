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
	SpinIndex index(2, 0);
	SpinIndex index_next(2, 0);
	
	// HORIZONTAL
	for(int i=0; i < size-1; i++) {
		index[0] = i;
		index_next[0] = i+1;
		
		for(int j=0; j < size; j++){
			index[1] = j;
			index_next[1] = j;

			energy -= read_spin(index) * read_spin(index_next);
		}
	}
	
	// VERTICAL
	for(int i=0; i < size; i++) {
		index[0] = i;
		index_next[0] = i;

		for(int j=0; j < size-1; j++){
			index[1] = j;
			index_next[1] = j+1;
			
			energy -= read_spin(index) * read_spin(index_next);
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
	
	SpinIndex nextv(2,0), nexth(2,0), prevv(2,0), prevh(2,0);
	nexth[0] = i+1; nexth[1] = j;
	prevh[0] = i-1; prevh[1] = j;
	nextv[0] = i; nextv[1] = j+1;
	prevv[0] = i; prevv[1] = j-1;
	
	diff += 2 * read_spin(index)  * (read_spin(nexth) + read_spin(prevh) + read_spin(nextv) + read_spin(prevv));
	
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
	
	for (int i=0; i < size; i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}