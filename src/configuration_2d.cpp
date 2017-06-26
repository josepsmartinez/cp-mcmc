#include "configuration_2d.h"

MonteCarloConfiguration2D::MonteCarloConfiguration2D(int configuration_size) :
	MonteCarloConfiguration(configuration_size, 3)
{
	srand(time(NULL));
	configuration = (bool**) malloc(size * sizeof(bool*));
	
	for(int i=0; i < size; i++){
		configuration[i] = (bool*) malloc(size * sizeof(bool));
		for (int j=0; j < size; j++)
			configuration[i][j] = (bool) (rand()%2);
			//configuration[i][j] = true;
		
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
	magnetization = 0;
	
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
	for(int i=0; i < size; i++) 
		for (int j=0; j < size; j++)
		magnetization += spin_value(configuration[i][j]);
	
	
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
	//if (i < size-1) diff += 2 * spin_value( !(configuration[i][j]^ configuration[i+1][j]));
	//if (i > 0) diff += 2 * spin_value( !(configuration[i][j] ^ configuration[i-1][j]));
	if (i < size-1) diff+= 2 * spin_value(configuration[i][j]) * spin_value(configuration[i+1][j]);
	if (i > 0) diff+= 2 * spin_value(configuration[i][j]) * spin_value(configuration[i-1][j]);
	
	
	// VERTICAL
	//if (j < size-1) diff += 2 * spin_value( !(configuration[i][j] ^ configuration[i][j+1]));
	//if (j > 0) diff += 2 * spin_value( !(configuration[i][j] ^ configuration[i][j-1]));
	if (j < size-1) diff+= 2 * spin_value(configuration[i][j]) * spin_value(configuration[i][j+1]);
	if (j > 0) diff+= 2 * spin_value(configuration[i][j]) * spin_value(configuration[i][j-1]);
	
	return diff;
}

short int MonteCarloConfiguration2D::flip_magnetization(SpinIndex index) {
	int i = index[0];
	int j = index[1];
	

	return -2 * read_spin(index);
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
		magnetization += flip_magnetization(index);
		configuration[i][j] = !configuration[i][j];
	}
}

void MonteCarloConfiguration2D::accumulate() {
	accumulators[0] += energy;
	accumulators[1] += energy * energy;
	accumulators[2] += magnetization;
	
}

vector<float> MonteCarloConfiguration2D::realize(long int samples){
	vector<float> results(3);
	double beta = 1/temperature;
	float u_mc = accumulators[0] / (float) samples;
	
	
	results[0] = by_size(u_mc); 														// U
	results[1] = by_size( beta * beta * ((accumulators[1]/(float)(samples) - u_mc*u_mc )) ); // C
	results[2] = by_size(accumulators[2] / (float) samples); 														// M
	
	return results;
	
}

void MonteCarloConfiguration2D::print_header(ostream& stream) {

	stream << left;
	stream << setw(column_w) 			<< "T";
	stream << setw(column_w) 			<< "beta";
	stream << setw(column_w) 			<< "M_theory";
	stream << setw(column_w) 			<< "M_mc";
	stream << setw(column_w) 			<< "U_mc";
	stream << setw(column_w) 			<< "C_mc";
	stream 							<< endl << endl;



}

void MonteCarloConfiguration2D::print_theory(ostream& stream) {
	float beta = 1 / temperature;
	double m_theory;
		if(temperature < (2 / log(1 + sqrt(2)))) m_theory = pow(1 - pow(sinh(2*beta), -4), 1/8.0); 
		else m_theory = 0;
	
	
	stream << fixed << setprecision(4);
	

	stream << setw(column_w) << temperature;
	stream << setw(column_w) << beta;
	stream << setw(column_w) << m_theory;

	
}

void MonteCarloConfiguration2D::print_realization(vector<float> results, ostream& stream){
	stream << fixed << setprecision(4);
	

	stream << setw(column_w) << results[2]; 			// M
	stream << setw(column_w) << results[0]; 			// U
	stream << setw(column_w) << setprecision(8) << results[1]; 	// C
	stream << endl;

	
}

void MonteCarloConfiguration2D::test() {
	srand(time(NULL));
	
	for (int i=0; i < pow(size,2); i++) {
		markov_step();
		cout << "Energy: " << energy << '\n';
	}
}
