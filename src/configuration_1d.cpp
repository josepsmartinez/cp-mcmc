#include "configuration_1d.h"

using namespace std;


MonteCarloConfiguration1D::MonteCarloConfiguration1D(int configuration_size) :
	MonteCarloConfiguration(configuration_size)
{
	cout << "OQUE" ;
	configuration = (bool*) malloc(size * sizeof(bool));
	for(int i=0; i < size; i++)
		configuration[i] = true;
	
	cout << "adasdsd";
	load_energy();
	
}


short int MonteCarloConfiguration1D::read_spin(SpinIndex index) {
	int i = index[0];
	if (i >= 0 && i < size) {
		return(spin_value(configuration[i]));
	}
	else return 0;
}

void MonteCarloConfiguration1D::load_energy() {
	energy = 0;
	SpinIndex index(1,0), index_next(1,0);
	
	cout << "AAAAAAAAAAAAAAAa piru";
	for(int i=0; i < size-1; i++) {
		index[0] = i;
		index_next[0] = i+1;
		
		energy -= read_spin(index) * read_spin(index_next);
	}
	
	cout << "First Energy: " << energy << '\n';
}

float MonteCarloConfiguration1D::by_size(float value) {
	return value / (float) size;
}


short int MonteCarloConfiguration1D::flip_energy(SpinIndex index) {
	long int diff = 0;
	int i = index[0];

	diff += 2 * read_spin(SpinIndex(1, i))  * (read_spin(SpinIndex(1, i-1)) + read_spin(SpinIndex(1, i+1)));
	
	
	return diff;
}



void MonteCarloConfiguration1D::try_flip(SpinIndex index) {
	//int i;
	//short int e_diff = flip_energy(index);
	//double r = (double) rand() / RAND_MAX;
	//double q = flip_prob(e_diff);

	
	//if (q > r) {
		//i = index[0];
		//energy += e_diff;
		//cout << i;
		//configuration[i] = !configuration[i];
	//}
}

void MonteCarloConfiguration1D::markov_step() {
	return;
	//for (int i=0, r; i < size; i++) {
		//r = rand() % size;
		//try_flip(SpinIndex(1, r));
		//try_flip(i);
	//}
}

void MonteCarloConfiguration1D::test() {
	srand(time(NULL));
	
	for (int i=0; i < size; i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}