# cs130

# **Assignment**
You will create a manual calculator using bitwise operators to support binary arithmetic.

Write the following functions:

```
void add(bool left, bool right, bool cin, bool &cout, bool &sum);
int twos(int value);
int add(int left, int right);
int sub(int left, int right);
int mul(int left, int right);
```

# **Notes and Restrictions**
1. The first add function adds only a single bit. The other functions need to use this to add bit-by-bit. Do not use any arithmetic operators (except for in loops).
  1. My add() function is exactly two lines: one for sum and one for carry. If you find you're exceeding two, start rethinking your strategy. You must only use bitwise operators for the add() function. Do not use any arithmetic or Boolean operators.
2. The twos() function will take a value and return the two's complement of that value.
3. The second add() function will take two values (left and right) and add them together using your bitwise add function.
4. The sub() function will take two values (left and right) and take the difference. This is another function that is a single line. So, if you find that you're writing multiple lines, think if there is another function or functions you could reuse to accomplish this function.
5. The mul() function will take two values (left and right) and multiply them together. You will need to use loops and comparison operators.
  1. Remember to convert negative numbers to positive before multiplying and then deciding the sign afterward.
  2. Do not use arithmetic operators for any of the multiplication. Instead, use bit shifting and your add() function where applicable.
  3. You must use the multiplication algorithm we covered in class (shift left operand left by 1, shift right operand right by 1 for each iteration of the loop).
6. Again, the point of this lab is binary arithmetic. Therefore, do not use arithmetic or Boolean operators (+, /, -, *, %, &&, ||, !) except for loops. Instead, use logical, bitwise operators.

Use the following as a template for your code and add comments where necessary:
```
#include <cstdio>

void add(bool left, bool right, bool cin, bool &cout, bool &sum);
int twos(int value);
int add(int left, int right);
int sub(int left, int right);
int mul(int left, int right);

int main()
{
   int l, r;
   printf("Enter two values: ");
   scanf("%d %d", &l, &r);
   printf("%d + %d = %d\n", l, r, add(l, r));
   printf("%d - %d = %d\n", l, r, sub(l, r));
   printf("%d * %d = %d\n", l, r, mul(l, r));
   return 0;
}
```
# **Examples**
```
hydra3: ~> /home/cosc130/labs/lab4
Enter two values: 55 100
55 + 100 = 155
55 - 100 = -45
55 * 100 = 5500

hydra3: ~> /home/cosc130/labs/lab4
Enter two values: -10 -20
-10 + -20 = -30
-10 - -20 = 10
-10 * -20 = 200

hydra3: ~> /home/cosc130/labs/lab4
Enter two values: 0 0
0 + 0 = 0
0 - 0 = 0
0 * 0 = 0

hydra3: ~> /home/cosc130/labs/lab4
Enter two values: -7 11
-7 + 11 = 4
-7 - 11 = -18
-7 * 11 = -77
```
# **Submission**
Compile your code using the following command, fix the errors, and submit to Canvas.
```
g++ -std=c++11 -Wall -Werror -o mylab mylab.cpp
```
Replace mylab with the name of your lab.
