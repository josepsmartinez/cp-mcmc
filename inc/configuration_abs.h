#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <iomanip>

#include <math.h>
#include <time.h>

#include "indexes.h"

using namespace std;
class MonteCarloConfiguration {
	protected:
		// configuration/sampling parameters
		float temperature;
		long int energy;
		int size;
		
		vector<float> accumulators; // abstraction for accumulating values in between markov steps
	
		virtual void load_energy() = 0; // computes the configuration energy from scratch
		virtual short int read_spin(SpinIndex index) = 0; // reads the spin physical value {-1, 1}
		virtual short int flip_energy(SpinIndex index) = 0; // change of energy upon flipping a spin

		double flip_prob(short int energy_diff);
		
		virtual SpinIndex random_spin() = 0;
		virtual void try_flip(SpinIndex index) = 0;
	
	public:
		MonteCarloConfiguration(int configuration_size, int n_accumulators);
		
		void set_temperature(float temp);
		long int get_energy(); // prob will fall out
		
		static short int spin_value(bool spin);
		
		
		virtual int available_spins() = 0; // (N or N*N)
		float by_size(float value); // describes computed value by its dimension (U -> U/N or U/(N*N))
	
		virtual void accumulate() = 0; // accepts current configuration
		void markov_step(bool relax=false); // generates a new configuration | relax: whether the new configuration should be discarded
		virtual std::vector<float> realize(int samples) = 0; // computes the final simulation values, assuming <samples> accumulations have ocurred
		
		
		
		void clear(); // clear accumulated values
		
		// READABILITY
		int get_size();
		float get_acc(int index);
		
		// OUTPUT
		virtual void print_realization(vector<float> results, ostream& stream) = 0;
	
		virtual void test() = 0;
		
}; 