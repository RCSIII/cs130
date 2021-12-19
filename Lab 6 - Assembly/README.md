# cs130

# **Overview**
This lab will introduce you to assembly programming, including functions and loops.

# **Assignment**
You will be implementing the random number formula ```rand() % (max-min+1) + min``` in MIPS assembly. MARS has a random number generator within a range system call. You are **NOT** permitted to use this system call (number 42).

You need to ask the user to ```"Enter min: "```, and then wait for the user to input an integer (see ```$v0 = 5``` under System Calls below).

You need to then ask the user to ```"Enter max: "```, and then wait for the user to input another integer.

Finally, ask the user to ```"Enter fill: "```, and then wait for the user to input a third integer. This integer will be used to determine how many random numbers will be generated to fill an array.

The min value must be less than the max value. If this is NOT the case, ask the user for another min and max. Keep repeating this until the user provides a min that is less than the max. The number of elements to fill is unbounded.

Now that you have the min and max, write a C++ function prototyped below that will return a number between the minimum and maximum:

```
int get_random(int min, int max);
```
After you've written (and tested) this function, create another function called fill_array as prototyped below:

```
short fill_array(short array[], int size, int min, int max);
```
This function will take the min and max that the user gave you in your prompts, and it will generate a random number to fill into the array. The array is specified as the first parameter, the number of elements to fill is the second parameter, the minimum random number is in min, and the maximum random number is in max. Finally, this function returns the average of the numbers that were filled into array[]. NOTE: The testing code does not use the average, however you should always test your code! Also, do not assume anything about the array. For example, it may contain a value other than 0 or it might be 0.

Write another function prototyped below:
```
void print_array(short array[], int size);
```
This function will print the number of elements provided by size inside of array in the following format:
```
[0] = -3
[1] = 22
[2] = 12
[3] = 4
[4] = -2
```
Write the last function prototyped below:
```
void sort_array(short array[], int size);
```
This will use any sorting algorithm (bubble, selection, or insertion) to sort the given array that contains the number of elements given by size in ascending order.

For example, the array above would be sorted to be:
```
[0] = -3
[1] = -2
[2] = 4
[3] = 12
[4] = 22
```
Now, write your main function that will put these functions together. Main will perform the following operations: (1) read min, (2) read max, (3) error check min/max, (4) read fill, (5) fill array with random numbers using fill_array, (6) sort array in ascending order using sort_array, (7) print array using print_array. All of these must be made using proper function calls!

MARS will properly end your program when there are no more instructions to execute. The best way is to create a label called "exit" (or something similar) that is the last line of your .asm file. Then, whenever you want to "quit" your program, you would j exit.

Remember, when you make these system and function calls, you cannot expect ```$a0``` to have the proper values, therefore, it must be saved. You MUST save all entered values onto the stack. Remember, the stack is pointed to by the stack pointer register, ```$sp```. Also, remember, if you use the saved registers $sX, they must be returned the same way you found them.

You must comment and format all of your assembly code!

Do not try to write the functions all at once! Instead, write one, test it, test it, and test it again. Then move onto the next and repeat!

Allocating a dynamically sized array will be performed on the stack. Remember, you can allocate a given number of bytes by simply subtracting that from the stack pointer ($sp). Furthermore, remember the restrictions when subtracting from $sp. For example, addi $sp, $sp, -16 will allocate 4 integers contiguously on the stack 0($sp), 4($sp), 8($sp), and 12($sp). An array is simply one integer after another in a contiguous chunk of memory.

There is a system call that can be used for allocating on the heap, but it won't be necessary for this lab. Instead, use the stack when allocating memory. The, pass this memory location as your array[].

# **System Calls**
System calls are function calls that will request that the fake operating system (runtime) do some work. Typically, Windows, Mac, or Linux will be the runtime, but for this simulator, MARS simulates these system calls.

You will need to make a few system calls for the following operations:

```
$v0	Description	Parameters	Result
1	Print integer	$a0 - integer to print	N/A
4	Print string	$a0 - null terminated address of string	N/A
5	Read integer	None	$v0
41	Generate random number	None	$a0
```
To make a system call, you save all registers, put the number into $v0, and then issue the instruction syscall.

Print integer example
 ```
.text
    li $v0, 1
    li $a0, 1234
    syscall
```
The system call above will print the following:

```
1234
```
# Print string example
```
.data
output: .asciiz "This is an example of output\n"
.text
    li $v0, 4
    la $a0, output
    syscall
```
The system call above will print the following:
```
This is an example of output
```

# Read integer example
```
.data
input: .asciiz "Enter integer: "

.text
    # Issue the prompt "Enter integer: "
    li $v0, 4
    la $a0, input
    syscall

    # Get input from user
    li $v0, 5
    syscall

    # $v0 contains the integer given, move it to $a0 for print integer
    move $a0, $v0

    # Now, print the integer given
    li $v0, 1
    syscall
```
The code above will prompt the user, wait for input, and the print out the integer it input:

```
Enter integer: 12345678
12345678
```
# Generate random number example
```
.text
   li $v0, 41
   syscall

   # Random number is put into the register $a0

   # Now, print out $a0 by using print integer ($v0 = 1)
   li $v0, 1
   syscall
```
The code above will generate a random number and then print the random number:

```
71838129
```
```
2918271
```
```
4412912
```
# **Example**
If your lab works properly, you will see the following:

```
Enter min: 100
Enter max: 103
Enter fill: 5
[0] = 100
[1] = 100
[2] = 100
[3] = 102
[4] = 103
```
Remember, the number is random, so you might get different results. However, no matter what, the number must be between [100..103] if that's what the user provided and in ascending order.

# **Assembling**
You must use the MARS (Mips Assembler and Runtime Simulator) to test your MIPS assembly program. This is a Java program, and it requires a Java runtime.

You can assemble your code by clicking ```Run > Assemble```. Then, to run your program, click ```Run > Go```
