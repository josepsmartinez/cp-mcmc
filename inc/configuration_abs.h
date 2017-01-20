#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

#include "indexes.h"

class MonteCarloConfiguration {
	protected:
		float temperature;
		long int energy;
		int size;
	
		virtual void load_energy() = 0;
		virtual short int read_spin(SpinIndex index) = 0;
		virtual short int flip_energy(SpinIndex index) = 0;

		double flip_prob(short int energy_diff){ return exp(-energy_diff/temperature); };
		virtual void try_flip(SpinIndex index) = 0;
	
	public:
		MonteCarloConfiguration(int configuration_size): size(configuration_size) {};
		
		void set_temperature(float temp){ temperature = temp; };
		long int get_energy(){  return energy; };
		int get_size() { return size; };
		static short int spin_value(bool spin) { return ((int) spin) * 2 - 1; };
		
		
		virtual void markov_step() = 0;
		virtual float by_size(float value) = 0; // describe computed value by its dimension (U -> U/N or U/(N*N))
	
		virtual void test() = 0;
		
}; 