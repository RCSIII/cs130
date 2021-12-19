# cs130

# **Assignment**
Write a program that converts numbers into strings.

*Do NOT use bitwise operators (if you know what they are) to solve this problem. Instead, take this mechanically with how numbers work. Think about how to get the ones place of a number depending on the base, and then how to move the 10s place or the 16s place to the ones place.

Write the following functions to perform the base conversion:
```
string base2(unsigned int value);
string base10(unsigned int value);
string base16(unsigned int value);
```
These functions all take an integer and convert it into the given string.

Use the following as your int main():
```
int main()
{
    unsigned int value;

    printf("Enter a decimal number: ");
    scanf("%u", &value);

    printf("Base  2 = 0b%s\n", base2(value).c_str());
    printf("Base 10 = %s\n", base10(value).c_str());
    printf("Base 16 = 0x%s\n", base16(value).c_str());

    return 0;
}
```
# **Examples**
```
hydra3: ~> /home/cosc130/labs/lab2
Enter a decimal number: 255
Base  2 = 0b11111111
Base 10 = 255
Base 16 = 0xff

hydra3: ~> /home/cosc130/labs/lab2
Enter a decimal number: 0
Base  2 = 0b0
Base 10 = 0
Base 16 = 0x0
```
Make sure you test boundary cases to make sure your code functions properly.

# **Submission**
Compile using the following command, fix your errors, and submit to Canvas.
```
g++ -std=c++11 -Wall -Werror -o mylab mylab.cpp
```
Replace mylab with the name of your lab.

# **Numbers**
The mod operator gives the remainder after division. So, if I divide any number by 10, then whatever is in the ones place will be returned (0 through 9). For example, take the decimal number 1234. 1234 % 10 = 4. Then 1234 / 10 = 123. 123 % 10 = 3. 123 / 10 = 12, and so on. Essentially, one operator returns the one's digit and the other moves all places down and removes the current one's digit.

As you can see, I'm not only getting the value of the ones digit, but I'm also moving all other places down one place. NOTICE: this will store the values backwards (ones digit comes first); however, the string needs to store the numbers in the correct order.

You will need to continue to extract the ones place until there are no more places above the ones place. If you choose the wrong loop, you might get an empty string since 0 is a possible value. Always make sure that you observe the number at least once.

# **Characters and Numbers**
Strings are simply array of characters. For this program, you'll need to convert between integer values and character values. Luckily 0, 1, 2, 3, ..., 9 are all in order where character 0 is actually integer value 48. So, if I have integer 0 and add 48, I now have character 0 and can add it to the string. Unfortunately, a, b, c (for hex) do not follow 9, so you'll need to make a check when converting hexadecimal numbers to see if the value is a number or a letter.
