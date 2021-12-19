// Robert Schenck
// 8/23/2019
// Lab 1
// Converts command line arguments into numerical data types1
#include <cstdio>
#include <string>

using namespace std;

int main(int argc, char **argv){
	// Usage Message if not enough command line arguments were specified
	if(argc != 2){
		printf("Usage: ./lab1 [number])\n");
		return 1;
	}


	
	// Variable Declarations
	int num1;
	float num2;
	unsigned int num3;
	double num4;

	// Converts and prints argv into 32-bit integer
	sscanf(argv[1], "%d\n", &num1);
	if(sscanf(argv[1], "%d\n", &num1) == 0){
		printf("Unable to convert %s into 32-bit integer.\n", argv[1]);
		return 1;
	}
	printf("Integer:          %-8d\n", num1);
	// Converts and prints argv into 32-bit float
	sscanf(argv[1], "%f\n", &num2);
	printf("Float:            %7.3f\n", num2);
	// Converts and prints argv into 64-bit unsigned integer
	sscanf(argv[1], "%u\n", &num3);
	printf("Unsigned Integer: %05u\n", num3);
	// Converts and prints argv into 64-bit double
	sscanf(argv[1], "%lf\n", &num4);
	printf("Double:           %-6.5e\n", num4);

};

