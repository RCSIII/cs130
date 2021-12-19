# cs130

# **Assignment**
In this lab, you will be reading, manipulating, and writing binary, bitmap files. You must use C-style files for both reading and writing Bitmap files.

# **Bitmap File Structure**
A 24-bit bitmap contains two headers that describe significant details about a picture, such as where to locate the pixel data, its width and height, and so forth. Each pixel contains three color values and is stored using 24-bits. Each color is stored in 1 byte (8 bits). They are stored in the order: blue, green, red and may contain values from 0 (no color) to 255 (full color). For example B=255, G=255, R=255 would be white, B=0, G=0, R=0 would be black, and B=10,G=10,R=255 would be a mostly red color.

The following structures do not contain padding, and are therefore known as "packed". C++ by default adds padding, so you need to turn it off by writing the following:
```
#pragma pack(push, 2)
struct BitmapFileHeader {
    // Members go here.
};
struct BitmapInfoHeader {
    // Members go here.
};
#pragma pack(pop)
```
**File header (starts at offset 0)**

The very top of a bitmap is what is called a file header. This header contains five fields and is 14 bytes total:

2 bytes - type (the type of the file, this will be Windows bitmap BM)
4 bytes - size (the entire size of the file, including headers)
2 bytes - reserved (reserved for future expansion)
2 bytes - reserved (reserved for future expansion too)
4 bytes - offset (this tells you the offset from the top of the file where the pixel data is stored)

**Info header (starts at offset 14)**

Right after the file header is the "info" header which describes the picture itself. It is 40 bytes total:

4 bytes - size (the size of the info header [should be 40])
4 bytes - width (the width of the picture in pixels)
4 bytes - height (the height of the picture in pixels)
2 bytes - planes (the number of layers, this should always be 1 for the test pictures)
2 bytes - bitcount (The number of bits per pixel, should be 24)
4 bytes - compression (the compression used, there is none, so this should be zero)
4 bytes - imagesize (the size of the image. May be zero for you to figure out!)
4 bytes - x_pixels_per_meter (the number of pixels per meter horizontally)
4 bytes - y_pixels_per_meter (the number of pixels per meter vertically)
4 bytes - color_used (the color index used, this should be 0 since we're not using indexed color)
4 bytes - color_important (again, should be 0)

**Pixel data (starts at offset specified by file header [typically 54])**

The pixel data starts at file_header->offset, but it is usually directly after the info header at offset 54 (14+40). The pixels are arranged with three channels BGR (blue, green, and red). Each color is 1 byte (8 bits).

There are width * height pixels, but there is something weird about bitmaps. Each row is "padded" to a multiple of 4 bytes. That means the number of bytes per row % 4 must be 0. For example, if I had a width of 3 and each pixel is 3 bytes, then my row takes 9 bytes. However, 9 % 4 = 1. Therefore, I must add 0s, 1 byte at a time, to the end of the row until the x % 4 = 0. In the previous example, 9 % 4 = 1, so lets add a "padded zero" which gives us 10 % 4 = 2, add another, 11 % 4 = 3, and another, 12 % 4 = 0. Ah, there we go. So, for a width of 3 using 3 bytes per pixel, each row is 12 bytes long. The pixel data itself only takes 9 bytes, then there are 3 zeros to give us a total of 12 bytes for the row.

**NOTE:** It is extremely inefficient to keep calculating the amount of padding per row. However, if you think about it, you know the size of a pixel and the width of a row, so you will only calculate the amount of padding once! Furthermore, you may notice that the padding is either 0, 1, 2, or 3 bytes. Therefore, it is possible for a pixel row to already be a multiple of 4. If that's the case, no padding is added.

Do NOT hardcode size values. Instead, judiciously use sizeof().

Lastly, pixel rows are stored in inverted order (upside down). This won't matter for this lab because you will be flipping around the Y axis (horizontally), but it is nice to know.

# **Reading / Writing binary files**
1. Download the test files: lab.bmp and ut.bmp. You will write all of your code in C++.

2. In this step, you will check to make sure you understand how to read a bitmap file. Write a program whose first command line argument is the input bitmap file and the second command line argument is the output bitmap file.

3. Create a structure called "Pixel" that stores the pixel color channels. [See bitmap file structure for details on how to construct a pixel]

4. Pixel, BitmapFileHeader, and BitmapInfoHeader are the ONLY structures you may use in this lab. Pixel must have a size of 3 bytes.

5. For the input file, read the offset (from file header), width, and height (from info header) from the file by seeking to the appropriate location.

6. Create a pixel array on the heap to store all of the pixels in memory. You must use a pointer of data type Pixel *.

7. Read in all of the pixels into memory using your pixel pointer. DO NOT FORGET to skip the padding after each row. This means you must read row-by-row rather than the entire pixel array all at once. You must use file seeking to skip the padding and move the file location to the next row. You must determine the amount of padding using the row size.

8. Now, using an output file, write the exact same file and info header to the output file.

9. Write the pixel data. Do not forget to include the extra padding after each row (if applicable).

The images may be different but it might not be easily apparent. To test if image files are the same, use the following command: diff lab.bmp test.bmp

If the files are the same, you will not get any output. If the files differ, diff will say so.

# **Inverting**
1. Now you will need to add a step before you write the pixels to invert them in place. Remember that there are width * height pixels. Inversions mean that you take the maximum color intensity per channel (for blue, green, and red) and subtract from that the actual color intensity.

2. Re-compile and re-test your code.

3. The colors should now be inverted (blues should be reddish/brown and reds should be blackish/blue).

# **Flipping**
1. Now, either before or after step 2 (inverting the colors), add code that flips the image horizontally (around the Y axis) in place.

2. Since the pointer is a large array of pixels, you cannot directly index a row and a column (it isn't a 2D array). We know that pixel_array[0] is the bottom, left pixel and pixel_array[1] is the bottom, left+1 pixel. Therefore, pixel_array[width-1] would describe the rightmost pixel on the bottom array. Use this to determine how to index a row and column.

3. Re-compile and re-test your code.

4. Not only should the colors be inverted still, the image should be flipped around. That is, it should look like a mirror image.

# **Verifying**
1. If your input file is lab.bmp, the output should look like lab_final.bmp  Download lab_final.bmp. If your input file is ut.bmp, the output should look like ut_final.bmp  Download ut_final.bmp.  You should use the diff command to check your output matches these images.

2. You must have a Pixel structure and use it for your pixel array. You must have a BitmapFileHeader structure and a BitmapInfoHeader structure as well.

3. You must allocate using the heap using the new and delete operators. Do not use malloc or free or vectors.

# **Examples**
```
hydra3: ~> /home/cosc130/labs/lab5
```
# **Submission**
Compile your code using the following command line, fix your errors, and submit to Canvas:
```
g++ -std=c++11 -Wall -Werror -o mylab mylab.cpp
```
Replace mylab with the name of your lab.
