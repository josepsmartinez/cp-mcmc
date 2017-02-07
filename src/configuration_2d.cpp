#include "configuration_2d.h"

MonteCarloConfiguration2D::MonteCarloConfiguration2D(int configuration_size) :
	MonteCarloConfiguration(configuration_size, 3)
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
	energy_diag = 0;
	
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
	
	// DIAGONAL
	for(int i=0; i < size; i++) {
		energy_diag += spin_value(configuration[i][i]);
	}
	
	cout << "First Energy: " << energy << '\n';
}

int MonteCarloConfiguration2D::available_spins() {
	return size*size;
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

short int MonteCarloConfiguration2D::flip_energy_diag(SpinIndex index) {
	int i = index[0];
	int j = index[1];
	
	if(i == j and i < size-1)
		return -2 * read_spin(index);
	else
		return 0;
}

SpinIndex MonteCarloConfiguration2D::random_spin() {
	SpinIndex index(2);
	index[0] = rand() % size;
	index[1] = rand() % size;
	
	return index;
	
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
		energy_diag += flip_energy_diag(index);
		configuration[i][j] = !configuration[i][j];
	}
}

void MonteCarloConfiguration2D::accumulate() {
	accumulators[0] += energy;
	accumulators[1] += energy*energy;
	accumulators[2] += energy_diag;
}

vector<float> MonteCarloConfiguration2D::realize(int samples){
	vector<float> results(3);
	results[0] = by_size(accumulators[0] / (float) samples); // U_MC
	results[1] = by_size(pow(1/temperature, 2) * ((accumulators[1] / (float) samples) - pow(accumulators[0] / (float) samples, 2))); // C_MC
	results[2] = by_size(accumulators[2] / (float) samples); // M_MC
	
	return results;
	
}

void MonteCarloConfiguration2D::print_realization(vector<float> results, ostream& stream){
	stream << fixed << setprecision(4);
	stream << "Energy: " << results[0] << " | ";
	stream << "Specific Heat: " << results[1] << " | ";
	stream << "Magnetization: " << results[2] << "\n";

}

void MonteCarloConfiguration2D::test() {
	srand(time(NULL));
	
	for (int i=0; i < pow(size,2); i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}