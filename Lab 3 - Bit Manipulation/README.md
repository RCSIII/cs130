# cs130

# Updated
Use a counter to determine where the _ goes. Do not use the % operator. Furthermore, use your test() function to determine whether you print a 1 or 0.

# Overview
The goal of this lab is to manipulate individual bits in a number.

# Assignment
Write a class called ```Bitset``` that looks like the following:

```
class Bitset {
    unsigned long m_value;
public:
    Bitset();
    Bitset(unsigned long initial_value);
    bool test(int bit) const;
    void set(int bit);
    void clear(int bit);
    void reset();
    void print() const;
};
```
# Bitset::Bitset()
This constructor will do absolutely nothing.

# Bitset::Bitset(unsigned long initial_value)
This constructor will set the private variable ```m_value``` to the given value.

# bool Bitset::test(int bit) const
This member function will test ```m_value``` to see if the given bit is a 1 or 0. If it is a 1, it returns ```true```, otherwise it returns ```false```.

Bit Indices
Bit values start with 0 from the right and move left.

For example, given ```0b1100```:

```test(0)``` would return ```false```. ```test(1)``` would return ```false```. ```test(2)``` would return ```true```. ```test(3)``` would return ```true```.

# **BE CAREFUL**
Any shifting you do must be done carefully. For example ```1 << 63``` looks valid for the data type of ```m_value```, but remember, ```1``` in this case is a 32-bit integer literal.


# **Out-of-bounds bit indices**
We will not test out of bounds values, but should an out-of-bounds bit index be specified, return ```false```. Remember that out of bounds is the number of bits in the value! (Hint: check the data type of ```m_value```).

# void Bitset::set(int bit)
This member function will set the given bit in ```m_value``` to 1 and leave all other bits unchanged.

For example, given ```m_value = 0b1100```

```set(0)``` would set ```m_value``` to ```0b1101```, and a subsequent call to ```set(1)``` would set m_value to ```0b1111```.

If the given bit is already 1, this function will just overwrite the bit to 1. In other words, do not test the bit first.

If the bit index is out of bounds, this function does nothing.

# void Bitset::clear(int bit)
This member function will clear the given bit in ```m_value``` to 0 and leave all other bits unchanged.

For example, given ```m_value = 0b1100```

```clear(0)``` would set ```m_value``` to ```0b1100``` (unchanged), and a subsequent call to ```clear(3)``` would set ```m_value``` to ```0b0100```.

Just like with ```void Bitset::set(int bit)```, if a bit is already cleared, overwrite that bit with 0. In other words, do not test the bit first.

If the bit index is out of bounds, this function does nothing.

# void Bitset::reset()
This function clears the entire bitset to ```0```. You must perform this using only a single operation.

# void Bitset::print() const
This function will use ```printf``` to print out all 64, 0s and 1s in the bitset. Furthermore, it will separate groups of 4 bits with underscores ```_```. For example, if ```m_value = 0b11101001```, then ```print()``` will output the following:

```0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_1110_1001```
Do not output a newline character after printing.

Use a counter to determine where the _ goes. Do not use the % operator. Furthermore, use your ```test()``` function to determine whether you print a 1 or 0.

# Examples
You can test your code with the following examples and see if you get the same output.
```
#include <cstdio>
// Bitset goes here
int main()
{
        Bitset mybs { 0b00011100111UL };

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
```
Running the example above will produce the following output given Bitset is implemented correctly:
```
0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_1110_0111
0000_0000_0000_0000_0011_0000_0000_0000_0000_0000_0000_0000_0010_0000_1110_0101
0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
```
# **Submission**
Before submitting your lab, use the following command and correct all errors:
```
g++ -Wall -Werror -std=c++11 -o mylab mylab.cpp
```
Replace mylab with the name of your lab.
