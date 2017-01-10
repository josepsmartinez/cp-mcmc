#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


class MonteCarloConfiguration {
		float temperature;
		long int energy;
		int size;
		bool* configuration;
	
		short int read_spin(int index);
		void load_energy();
		short int flip_energy(int index);

		double flip_prob(int index);
		void try_flip(int index);
	
	public:
		MonteCarloConfiguration(int configuration_size);
	
		void set_temperature(float temp){ temperature = temp; };
		long int get_energy(){  return energy; };
		void markov_step();
	
		void test();
		
}; 