#include "configuration_1d.h"

MonteCarloConfiguration1D::MonteCarloConfiguration1D(int configuration_size) :
	MonteCarloConfiguration(configuration_size, 2)
{
	configuration = (bool*) malloc(size * sizeof(bool));
	for(int i=0; i < size; i++)
		configuration[i] = true;
	
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
	
	for(int i=0; i < size-1; i++) {
		energy -= spin_value( !(configuration[i] ^ configuration[i+1]));
	}
	
	cout << "First Energy: " << energy << '\n';
}


int MonteCarloConfiguration1D::available_spins() {
	return size;
}



short int MonteCarloConfiguration1D::flip_energy(SpinIndex index) {
	long int diff = 0;
	int i = index[0];

	if (i < size-1) diff += 2 * spin_value( !(configuration[i] ^ configuration[i+1]));
	if (i > 0) diff += 2 * spin_value( !(configuration[i] ^ configuration[i-1]));
	
	return diff;
}

SpinIndex MonteCarloConfiguration1D::random_spin() {
	SpinIndex index(1);
	index[0] = rand() % size;
	
	return index;
	
}


void MonteCarloConfiguration1D::try_flip(SpinIndex index) {
	int i;
	short int e_diff = flip_energy(index);
	double r = (double) rand() / RAND_MAX;
	double q = flip_prob(e_diff);

	
	if (q > r) {
		i = index[0];
		energy += e_diff;
		configuration[i] = !configuration[i];
	}
}

void MonteCarloConfiguration1D::accumulate() {
	accumulators[0] += energy;
	accumulators[1] += energy*energy;
}

vector<float> MonteCarloConfiguration1D::realize(int samples){
	vector<float> results(2);
	results[0] = by_size(accumulators[0] / (float) samples); // U_MC
	results[1] = by_size(pow(1/temperature, 2) * ((accumulators[1] / (float) samples) - pow(accumulators[0] / (float) samples, 2))); // C_MC
	
	return results;
	
}

void MonteCarloConfiguration1D::print_realization(vector<float> results, ostream& stream){
	stream << fixed << setprecision(4);
	stream << "Energy: " <<  results[0] << " | ";
	stream << "Specific Heat: " << results[1] << "\n";

}


void MonteCarloConfiguration1D::test() {
	srand(time(NULL));
	
	for (int i=0; i < size; i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}