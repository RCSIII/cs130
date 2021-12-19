// Robert Schenck
// Lab 3
// 9/13/2019
// Professor Marz
// Manipulates bits using bitwise operators
#include <cstdio>
#include <string>

using namespace std;

class Bitset{
	unsigned long m_value;
public:
	Bitset();
	Bitset(unsigned long initial_value);
	bool test(int bit) const;
	void set (int bit);
	void clear(int bit);
	void reset();
	void print() const;
};

// This Constructor does nothing
Bitset::Bitset(){
}

// Sets private variable m_value to the given value
Bitset::Bitset(unsigned long initial_value){
	m_value = initial_value;
}

// Test to see if the given bit is a 1 or 0, if 1 returns true. If bit is out of bounds returns false
bool Bitset::test(int bit) const{
	if(bit > 64){
		return false;
	}
	return ((m_value >> bit ) & 1) == 1;
};

// Sets given bit to 1
void Bitset::set(int bit){
	m_value = m_value | (static_cast<long>(1) << bit);
};

// Clears given bit, does not change bit if already 0
void Bitset::clear(int bit){
	m_value = m_value & ~(static_cast<long>(1) << bit);
};

// Resets bit
void Bitset::reset(){
	m_value = m_value & 0;
};

// Prints out the entire bit
void Bitset::print() const{
	int count = 0;
	string ret;
	for(int i = 63; i >= 0; i--){
		// Prints underscores inbetween each 4 bits
		if(count == 4){
			ret += "_";
			count = 0;
			i++;
		}else{
			// If bit is tested true adds a 1 to be printed
			if(1 == test(i)){
				ret += "1";
				count++;
			// If bit is tested to be false adds a 0 to be printed
			}else{
				ret += "0";
				count++;
			}
		}
	}
	// Prints ret as a c-style string
	printf(ret.c_str());
};

int main(){

	Bitset mybs {0b00011100111UL};

	mybs.print();
	printf("\n");

	mybs.set(44);
	mybs.set(45);
	mybs.clear(1);
	mybs.set(13);
	mybs.clear(14);
	mybs.print();
	printf("\n");

	mybs.reset();
	mybs.print();
	printf("\n");

	return 0;
}
