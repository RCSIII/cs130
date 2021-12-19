// Robert Schenck
// Lab 4
// 9/17/2019
// Dr. Marz
//  Caclulator using bitwise operators
#include <cstdio>

using namespace std;

void add(bool left, bool right, bool cin, bool &cout, bool &sum){
	cout = left & right & cin;
	sum = left ^ right ^ cin;
}

// Takes two numbers and adds them togethers, finds the sum of the two numbers using XOR and finds the carry using AND, sums the sum and carry and finds the carry for that sum until the carry is equal to 0
int add(int left, int right){
	int carry;
	int new_carry;
	int sum;

	carry = left & right;
	sum = left ^ right;
	while(carry > 0){
		carry <<= 1;
		new_carry = sum & carry;
		sum = sum ^ carry;
		carry = new_carry;
	}
	return sum;
}

// Finds the twos complements of a value, inverts the value and adds 1
int twos(int value){
	value = ~(value);
	value = add(value, 1);
	return value;
}

// Subtracts two numbers by finding the twos complement of the second number (right) and then adding
int sub(int left, int right){
	int sum;

	right = twos(right);
	sum = add(left, right);
	return sum;
}
 
// Multiplies the two numbers
int mul(int left, int right){
	unsigned int top;
	unsigned int bottom;
	short result;
	bool result_is_negative = false;
	if(((left << 7) & 1) == 1){
		top = add(~left, 1);
		result_is_negative = !result_is_negative;
	}else{
		top = left;
	}

	if(((right << 7) & 1) == 1){
		bottom = add(~right, 1);
		result_is_negative = !result_is_negative;
	}else{
		bottom = right;
	}

	while(bottom != 0){
		if(bottom & 1){
			result = add(result, top);
		}
		bottom >>= 1;
		top <<= 1;
	}
	if(result_is_negative){
		result = add(~result, 1);
	}
	return result;
}

int main(){
	int l, r;
	printf("Enter two values: ");
	scanf("%d %d", &l, &r);
	printf("%d + %d = %d\n", l, r, add(l, r));
	printf("%d - %d = %d\n", l, r, sub(l, r));
	printf("%d * %d = %d\n", l, r, mul(l, r));
	return 0;
}
