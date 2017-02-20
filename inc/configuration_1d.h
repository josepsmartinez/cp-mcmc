#ifndef MCC_ABSTRACT
	#define MCC_ABSTRACT
	#include "configuration_abs.h"
#endif

class MonteCarloConfiguration1D: public MonteCarloConfiguration {
		bool* configuration; // spins implementation

	
		short int read_spin(SpinIndex index);
		void load_energy();
		short int flip_energy(SpinIndex index);

		SpinIndex random_spin();
		void try_flip(SpinIndex index);
	
	public:
		MonteCarloConfiguration1D(int configuration_size);
		~MonteCarloConfiguration1D() {};
		
		void accumulate();
		vector<float> realize(long int samples);
			
		int available_spins();
	
		void print_header(ostream& stream);
		void print_theory(ostream& stream);
		void print_realization(vector<float> results, ostream& stream);	
			
		void test();
		
}; 