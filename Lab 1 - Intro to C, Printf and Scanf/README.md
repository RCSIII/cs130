# cs130

# **Overview**
The purpose of this lab is to get familiar with the Canvas system, lab machines, and how to submit assignments. All software should be downloaded, including Logisim (Links to an external site.), Mars  Download Mars, and MobaXterm (for Windows) (Links to an external site.) -- Linux, Windows, and Mac have a built-in terminal and doesn't required additional software. Your TA will show you where and how to install these programs. For Windows, if you don't want MobaXterm, you can use the command prompt or powershell. However, MobaXterm is graphical and could make it easier to upload and download your labs from the lab machines.

Practice using MobaXterm or Terminal. The important part is to see how to upload and download files from the Hydra machines to your personal laptop so you can submit your assignment.

The second part of this lab is to get familiar with C-style console functions printf and scanf. Notes regarding the subject matter of this lab can be found under Pages > Printf/Scanf.

# **Assignment**
Write a program that inputs a value with sscanf, and then prints the same value using printf. Your program will be given the following data types via the command line arguments. You must print a "usage" message if not enough command line arguments were specified.

User command line arguments:

1. a 32-bit integer
2. a 32-bit floating point
3. a 64-bit unsigned integer
4. a 64-bit floating point
Use sscanf to convert these from a command line argument (c-style string) into the given data type. If the user doesn't specify a parameter that can be converted, print an error message, such as "unable to convert 'xyz' into a 32-bit integer".

1. Output the 32-bit integer in a left-justified field, 8 characters wide.
2. Output the 32-bit floating point in a right-justified field, 7 characters wide, with 3 digits of precision in fixed notation.
3. Output the 64-bit unsigned integer in a right-justified field, 5 characters wide, insert zeros '0' instead of spaces.
4. Output the 64-bit floating point in a left-justified field, 6 characters wide in scientific notation with 5 digits of precision.
# **Examples**
```
hydra3: ~> /home/cosc130/labs/lab1
```
# **Submission**
Use the following command line before submitting your assignment. Your lab must compile using the following command on the Hydra machines, otherwise it will be graded 0.
```
g++ -std=c++11 -Wall -Wextra -Werror -o mylab mylab.cpp
```
Replace mylab with the name of your lab.

Submit your .cpp file.

# **Printf and Scanf**
Include File
You must include ```cstdio``` or ```stdio.h``` to use ```printf```. When using either of these, you do not need the ```using namespace std```; unless you use a C++ header, such as ```<string>``` or ```<vector>```.
```
#include <cstdio>
```
# **Formatters**
```
printf("%s %d %ld %c %f %lf\n",
       "A c-style string",
       123,
       1234L,
       'c',
       7.89F,
       7.89
       );
```
In the example above, an interpolated value is prefixed by a ```%```. If you actually want to print a ```%```, you would use two ```%%```. The percent sign is a special character that tells ```printf``` that a formatter is coming next.

The formatters have these meanings:

                      Printf/Scanf Formatters
Formatter	Data Type	                            Description
%s	Prints a C-style string	                    0-terminated character array
%d	Prints a 32-bit integer	                    int
%ld	Prints a 64-bit integer	                    long
%c	Prints a single character	                  char 
%f	Prints a 32-bit float	                      float
%lf	Prints a 64-bit float	                      double
%e	Prints a 32-bit float in scinot	            float
%le	Prints a 64-bit float in scinot	            double
%u	Prints a 32-bit unsigned integer	          unsigned int
%lu	Prints a 64-bit unsigned integer	          unsigned long
%x	Prints a 32-bit integer as a hex value	    int/unsigned int
%lx	Prints a 64-bit integer as a hex value	    long/unsigned long
%%	Prints %	                                  N/A

Printing a short uses ```%d``` or ```%u```. C++ will automatically promote it to an integer.

Manipulating Formatters
In C++, you used ```iomanip``` to specify field widths and precision. Using ```printf```, you need to specify these between the ```%``` and the formatter.

Precision
Precision was set by the ```setprecision()``` manipulator. However, with ```printf```, you will need to use a special formatter. For example,
```
printf("%.2lf", 17.212345);
```
produces the following output:
```
17.21
```
In other words, the ```.2``` specifies the precision.

Field Widths
Field widths were set by the ```setw()``` manipulator. With ```printf```, these can be specified by a number in the formatter string. This number can be positive for right justfied strings, or negative for left justified strings.

For example,
```
printf("%10s B\n", "A");
```
... will print:
```
         A B
```
```
printf("%-10s B\n", "A");
```
... will print:
```
A          B
```
# Combining Precision/Width
The precision is specified after the decimal point, whereas the width is specified (either positive or negative) before the decimal point:
```
printf("HELLO %-15.2lf WORLD\n", 77.12345);
```
... will print:
```
HELLO 77.12           WORLD
```
# Zero Fill
You can set the fill to a 0 by adding a 0 in front of the field width:
```
printf("%010d B\n", 21)
```
... will print:
```
0021 B
```
This is especially useful when writing out binary numbers where ```0b10``` would be ```0b00000010``` if put into a ```char```.

# Closing Notes
Unlike ```iomanip```, none of these are stateful. Meaning, if you set ```.2``` as a precision, it is only that precision for that particular formatter.

You cannot print C++ style strings using ```printf```. Instead, you can only print C-style strings. However, this is fairly easy to do using the ```.c_str()``` member function of any string.

# Examples
```
string your_name = "Stephen";
int num_email_unread = 100;
printf("Hello %s, you have %d unread email messages.\n", your_name.c_str(), num_email_unread);
```
# Scan Formatted
```scanf``` is much like ```cin``` in that it will scan for input from the console.

However, there is also ```sscanf```, which stands for string scan formatted. Instead of reading from the console, ```sscanf``` takes an additional parameter, a c-style string to scan from.

The format string looks the same as with ```printf```. However, the format list is a list of variables you'd like the scan to put the value into.

Scan Include File
Just like ```printf```, you must include ```cstdio``` or ```stdio.h``` to use it.
```
#include <cstdio>
```
# Scan Return Value
```scanf``` and ```sscanf``` will return the number of arguments in the list it was successfully able to put a value into.

A great way to check to see if ```scanf``` or ```sscanf``` worked properly is to check its return value and compare it to the number of values you're extracting. For example,
```
int val1, val2;
int num_vals;
num_vals = scanf("%d %d", &val1, &val2);
if (num_vals != 2) {
    printf("Error reading from input: ");
    printf("expected 2 values, got %d.\n", num_vals);
}
```
# Scan Examples
The following code example will read a 32-bit integer from the console and store it into ```&myint```. The ```&``` is necessary because scanf doesn't store into the variable directly. Instead, it stores into the memory location where the variable is located. Remember pointers?
```
int myint;
scanf("%d", &myint);
```
The following code will read a c-style string up to 50 characters and store it into ```buffer```. We need 51 characters for the buffer since ```scanf``` will automatically add the null terminator \0.
```
char buffer[51];
scanf("%50s\n", buffer);
```
# String Scan Example
The following code will convert the first user supplied command line argument into a float called ```myfloat```. This is how you will convert command line arguments instead of using a string stream.
```
int main(int argc, char *argv[]) {
    float myfloat;
    sscanf(argv[1], "%f", &myfloat);
}
```
For more information visit: Using scanf (Links to an external site.).
