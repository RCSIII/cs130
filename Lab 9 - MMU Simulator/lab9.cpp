// Robert Schenck
// Lab 9 11/19/2019
// Professor Marz
// Converts a virtual address into a physical address

#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){

	// Checks for improper usage
	if(argc > 2){
		perror("Improper usage, please enter a input file only");
	}else if(argc < 2){
		perror("Improper usage, please enter a input file");
	}

	// Numerous variable declarations
	FILE* fin;
	unsigned int virtualAddress = 0;
	unsigned long long physicalAddress;
	unsigned long fileSize;
	unsigned int SATP;
	unsigned long PPN0;
	unsigned long PPN1;
	unsigned long VPN1;
	unsigned long VPN0;
	unsigned long entry;
	unsigned long pageOffset;
	char userInput[11] = {};


	// Checks to see if given file can be opened
	fin = fopen(argv[1], "rb");
	if(nullptr == fin){
		perror("Cannot open file.");
		return -1;
	}
	
	// Read the elements of the file into an array
	fseek(fin, -4, SEEK_END);
	fileSize = ftell(fin);
	char *mmuTable = new char [fileSize];
	fseek(fin, 0, SEEK_SET);
	fread(mmuTable, fileSize, 1, fin);
	fread(&SATP, sizeof(unsigned int), 1, fin);
	fclose(fin);	

	// Continues to ask for virtual addresses unless the user enters in 'done'
	while(1){
		printf("Enter virtual address (or 'done' to quit): ");
		scanf("%10s", userInput);
		sscanf(userInput, "%x", &virtualAddress);

		// Checks to see if the user entered 'done' if so breaks out of loop and program ends
		if(userInput[0] == 'd'){
			if(userInput[1] == 'o'){
				if(userInput[2] == 'n'){
					if(userInput[3] == 'e'){
						break;
					}
				}
			}
		}
		// Checks to see if the user entered a hexadecimal number, if not, asks for another input
		if(sscanf(userInput, "%x", &virtualAddress) != 1){
			printf("Please enter a hexadecimal number.\n");
			continue;
		}

		// Checks to see if MMU is turned on, if not the physical address is the virtual address
		if(((SATP >> 31) & 1) == 0){
			physicalAddress = virtualAddress;
			printf("%#011llx\n", physicalAddress);
			continue;
		}
		// Gets the VPN0, VPN1, and pageOffset from virtual address
		VPN1 = (virtualAddress >> 22) & 0x3ff;
		VPN0 = (virtualAddress >> 12) & 0x3ff;
		pageOffset =  virtualAddress & 0xfff;

		// Get the first entry in the level 1 page table
		PPN1 = (SATP & 0x3ff) << 12;
		// Dereference the address to get a 32-bit page table entry
		entry = *(unsigned int*)(&mmuTable[PPN1 + (4 * VPN1)]);
		// Checks if the first entry if valid, 0 = not valid, so page fault. 1 = continues with the program
		if((entry & 1) == 0){
			printf("Page fault!\n");
			continue;
		}
		// Checks to see if any RWX bits are not 0, if they are all zero we go to table 0, otherwise we create the physical address 
		if((entry & 0xe) == 0){
			// Gets the first entry in the level 0 page table
			PPN0 = (entry << 2) & ~0xfff;
			// Derefernce the address to get a 32-bit page table entry
			entry = *(unsigned int*)(&mmuTable[PPN0 + (4 * VPN0)]);
			// Checks if the first entry is valid
			if((entry & 1) == 0){
				printf("Page fault!\n");
				continue;
			}
			// If RWX are all 0 on this level as well then we page fault, otherwise we create the physical address
			if((entry & 0xe) == 0){
				printf("Page fault!\n");
				continue;
			}
			physicalAddress = ((entry << 2) & ~0xff) | pageOffset;
			printf("%#011llx\n", physicalAddress);
			continue;
		}
		entry = ((entry << 2) & ~0x3fffff);
		entry |= VPN0 << 12;
		physicalAddress = entry | pageOffset;
		printf("%#011llx\n", physicalAddress);
		continue;
	
	}
	// Deletes the allocated memory
	delete [] mmuTable;
	return 0;	
}

