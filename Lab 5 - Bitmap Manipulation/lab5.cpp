// Robert Schenck
// Lab 5 10/3/19
// Dr. Marz CS130
// Replicate a bitmap image and the proceed to invert it and flip it across the Y axis

#include <cstdio>
#include <cstdint>
#include <cstring>

#pragma pack(push, 2)
// Structure for the File Header of a Bitmap Image
struct BitmapFileHeader{

	uint16_t type;
	uint32_t size;
	uint16_t reserved_1;
	uint16_t reserved_2;
	uint32_t offset;
};

// Structure for the Info Header of a Bitmap Image
struct BitmapInfoHeader{

	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bit_count;
	uint32_t compression;
	uint32_t image_size;
	uint32_t x_pixels_per_meter;
	uint32_t y_pixels_per_meter;
	uint32_t color_indexed;
	uint32_t color_important;

};
#pragma pack(pop)

// Structure for a pixel, contains variables for the RGB values of a pixel
struct Pixel{

	uint8_t blue;
	uint8_t green;
	uint8_t red;

};

int main(int argc, char *argv[]){
	
	// Checks how many arguments are given and if to many/to little, give an error
	if(argc > 3){
		perror("Improper usage, please enter a input file and a output file only.");
	}else if(argc == 0){
		perror("Improper usage, please enter a input file and a output file only.");
	}

	FILE *fin;
	FILE *fout;
	BitmapFileHeader bfh;
	BitmapInfoHeader bih;
	// Opens up the given bitmap image for reading only and makes sure it that is open, if not the program exits
	fin = fopen(argv[1], "rb");
	if(nullptr == fin){
		perror(argv[1]);
		return -1;
	}
	// Reads the File header of the Bitmap image
	if(sizeof(BitmapFileHeader) != fread(&bfh, 1, sizeof(bfh), fin)){
			printf("Unable to read bitmap file header.\n");
			return -2;
	}
	// Reads the Info Header of the Bitmap image
	if(sizeof(BitmapInfoHeader) != fread(&bih, 1, sizeof(bih), fin)){
			printf("Unable to read bitmap info header.\n");
			return -2;
	}
	// Calculates the padding of the image by mutliplying the width of the image by 3 to get the amount of bytes per row. We then % that number by 4
	// to determine the remainder, and then subtract the remainder by 4. So if a row is 9 bytes long and we modulo that number by 4, we get 1, so we have to have 3
	// padded bytes at the end of the row. So we subtract the remainder from 4 to get 3 bytes of padding. In the case that the the remainder is 0 and my equation would have
	// padding equal to 4, I added an if statement to set it to 0
	// Creates an array of padding length will values 0x00
	uint32_t padding = 4 - ((bih.width * 3) % 4);
	if(padding == 4){
		padding = 0;
	}
	uint32_t int_pad = 0x00;
	// Declares two pixel arrays on the heap, 1 for the initial reading and a second one for inverting the pixels colors
	Pixel *pixel_array = new Pixel[bih.width * bih.height];
	Pixel *inverted_pixel_array = new Pixel[bih.width * bih.height];
	// fseek goes to the pixels data starting past the offset which is read in from the file header portion on the bitmap image
	fseek(fin, bfh.offset, SEEK_SET);
	// This for loop should loop through all of the pixels in the bitmap image, reading in 1 pixel at a time.
	// Since I'm not using a 2d array i * bih.width theroetically should keep track of how many pixels I have read in
	// So for example, if I have read in 1 row already then i will be 1 meaning i * bih.width will be 1 * bih.width
	// This is to prevent reading in the same row of pixels over and over again
	// and at the end of every row (bih.width) it should skip the padding using fseek(fin, padding, SEEK_CUR)
	// This should jump us ahead of the padding so that the padding isn't read into any of our pixels
	for(uint32_t i = 0; i < bih.height; i++){
		for(uint32_t j = 0; j < bih.width; j++){
			fread(&pixel_array[j + (i * bih.width)], 1, 3, fin);
			// Debugging that I may have forgot to remove
			printf("Pixel: %u R: %u G: %u B: %u\n", j + (i + bih.width), pixel_array[j].red, pixel_array[j].green, pixel_array[j].blue);
		}
		fseek(fin, padding, SEEK_CUR);
	}
	
	// Close the file stream because I should be done with it
	fclose(fin);
	// This for loop should loop through all of the pixels in my pixel array and subtract the value of each color channel from 255
	// and then store that value into the inverted pixels array
	for(uint32_t i = 0; i < sizeof(pixel_array); i++){
		inverted_pixel_array[i].red = 255 - pixel_array[i].red;
		inverted_pixel_array[i].green = 255 - pixel_array[i].green;
		inverted_pixel_array[i].blue = 255 - pixel_array[i].blue;
	}
	
	// Deletes the pixel array as it is not needed anymore
	delete [] pixel_array;

	// This for loop should loop through all of the pixels in the pixels array (attempting to split them into rows and columns by looping through height and width)
	// I have a temporary Pixel variable that is assigned to have the same value as the pixel at the current width and height
	// Then the pixel at the current index is assigned the value of the pixel at the end of the row minus the current index
	// Lastly the pixel at the end of the row minus the current index is assigned the value of the temp pixel variable
	for(uint32_t i = 0; i < bih.height; i++){
		for(uint32_t j = 0; j < bih.width / 2; j++){
			Pixel temp = inverted_pixel_array[j + (i * bih.width)];
			inverted_pixel_array[j + (i * bih.width)] = inverted_pixel_array[bih.width - (j + 1)];
			inverted_pixel_array[bih.width - (j + 1)] = temp;
		}
	}

	// Opens/Creates the output for writing, if it unable to open the file then the program exits
	fout = fopen(argv[2], "wb");
	if(nullptr == fout){
		perror(argv[2]);
		return -1;
	}

	// Writes the file header and info header to the output file using fwrite
	fwrite(&bfh, sizeof(bfh), 1, fout);
	fwrite(&bih, sizeof(bih), 1, fout);
	
	// This for loop should write the inverted pixel array to the file in the pixel format and writing the padding to the array after each row
	for(uint32_t i = 0; i < bih.height; i++){
		for(uint32_t j = 0; j < bih.width; j++){
			fwrite(&inverted_pixel_array[j + (i * bih.width)], 1, 3, fout);
		}
		fwrite(&int_pad, sizeof(uint32_t), sizeof(padding), fout);
	}
	
	// Closes the file stream for the output file
	fclose(fout);
	// Deletes the inverted pixel array
	delete [] inverted_pixel_array;
	return 0;
}
