#ifndef MCC_ABSTRACT
	#define MCC_ABSTRACT
	#include "configuration_abs.h"
#endif

class MonteCarloConfiguration2D: public MonteCarloConfiguration {
		bool** configuration; // spins implementation
		long int magnetization; // M_mc measurement
	
	
		short int read_spin(SpinIndex index);
		void load_energy();
		short int flip_energy(SpinIndex index);
		short int flip_magnetization(SpinIndex index);

		SpinIndex random_spin();
		void try_flip(SpinIndex index);
	
	public:
		MonteCarloConfiguration2D(int configuration_size);
		~MonteCarloConfiguration2D() {};
		
		void accumulate();
		vector<float> realize(long int samples);
				
		int available_spins();
	
		void print_header(ostream& stream);
		void print_theory(ostream& stream);
		void print_realization(vector<float> results, ostream& stream);	
			
		void test();
		
}; 