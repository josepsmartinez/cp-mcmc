#include "configuration_1d.h"

MonteCarloConfiguration1D::MonteCarloConfiguration1D(int configuration_size) :
	MonteCarloConfiguration(configuration_size, 2)
{
	srand(time(NULL));
	configuration = (bool*) malloc(size * sizeof(bool));
	
	for(int i=0; i < size; i++)
		configuration[i] = (bool) (rand()%2);
		//configuration[i] = true;
	
	for (int j=0; j < size; j++) cout << configuration[j] << " ";
	
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

vector<float> MonteCarloConfiguration1D::realize(long int samples){
	vector<float> results(2);
	float beta = 1 / temperature;
	float u_mc = accumulators[0] / (float) samples;
	
	results[0] = by_size(u_mc); // U
	results[1] = by_size( beta * beta * ((accumulators[1]/samples - u_mc*u_mc) ) ); // C
	//results[1] = beta*beta * (by_size(accumulators[1]/samples - accumulators[0]*accumulators[0]/samples/samples));			

	
	return results;
	
}

void MonteCarloConfiguration1D::print_header(ostream& stream) {
	stream << left;
	stream << setw(column_w) << "T";
	stream << setw(column_w) << "beta";
	stream << setw(column_w) << "U_theory";
	stream << setw(column_w) << "C_theory";
	stream << setw(column_w) << "U_mc";
	stream << setw(column_w) << "C_mc";
	stream << endl << endl;
}

void MonteCarloConfiguration1D::print_theory(ostream& stream) {
	float beta = 1 / temperature;
	float u_theory = -tanh(beta); // 1D
	float c_theory = pow(beta / cosh(beta), 2); // 1D
	
	stream << fixed << setprecision(4);
	
	stream << setw(column_w) << temperature;
	stream << setw(column_w) << beta;
	stream << setw(column_w) << u_theory;
	stream << setw(column_w) << c_theory;
}

void MonteCarloConfiguration1D::print_realization(vector<float> results, ostream& stream){
	stream << fixed << setprecision(4);
	
	stream << setw(column_w) << results[0];
	stream << setw(column_w) << setprecision(6) << results[1];
	stream << endl;
}


void MonteCarloConfiguration1D::test() {
	for (int i=0; i < size; i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}