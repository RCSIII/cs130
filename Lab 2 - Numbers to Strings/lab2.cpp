/*
 Robert Schenck
 8/30/2019
 Lab 2
 Converts decimal number into Base 10, Base 2, and Base 16 numbers
*/
#include <cstdio>
#include <string>
using namespace std;

// Converts the number given by the user into a base 10 number
string base10(unsigned int val){
	string ret;
	do{
		// c is equal to the remainder of val divided by 10
		char c = val % 10;
		// adds char 0 as a value offset
		c += '0';
		// adds c to the end of the string that will be returned
		ret = c + ret;
		// divides the value by 10 to move the places down and starts the loop over again with new number
		val /= 10;
	}while(val != 0);
	// returns converted number
	return ret;
}

// Converts number given by the user into a binary number
string base2(unsigned int val){
	string ret;
	do{
		// c is equal to the remainder of val divided by 2
		char c = val % 2;
		// adds char 0 as a value offset
		c += '0';
		// adds c to the end of the string that will be returned
		ret = c + ret;
		// divides the value by 2 to move the places down and starts the loop over again with new number
		val /= 2;
	}while(val != 0);
	// returns converted number
	return ret;
}

// Converts number given by the user into a hexdecimal number
string base16(unsigned int val){
	string ret;
	do{
		// c is equal to the remainder of val divided by 16
		char c = val % 16;
		// If c is 10 or above, the value offset is changed to reflect that base 16 only has 0-9 numbers and A-F letters
		if(c + '0'> '9'){
			c += 'a' - 10;
		}else{
			// If c is below 10, the offset stays as char 0
			c += '0';
		}
		// adds c to the end of the string that will be returned
		ret = c + ret;
		// divides the value by 16 to move the palces down and starts the loop over again with new number
		val /= 16;
	}while(val != 0);
	// returns converted number
	return ret;
}


int main(){

	unsigned int value;

	// User is prompted for a decimal number
	printf("Enter a decimal number: ");
	scanf("%u", &value);
	
	// Prints output
	printf("Base  2 = 0b%s\n", base2(value).c_str());
	printf("Base 10 = %s\n", base10(value).c_str());
	printf("Base 16 = 0x%s\n", base16(value).c_str());

	return 0;
}
