#include <vector>

class SpinIndex: public std::vector<int> {
	using std::vector<int>::vector; // copies constructor
	//using std::vector<int>::operator[];
	
	public:
		SpinIndex operator + (const SpinIndex& v) {
			if (this->size() != v.size())
				return *this;
			else{
				for (int i=0; i < (int) this->size(); i++){
					this[i] = this[i] + (&v)[i];
				}
			}
		};
		
		
};

