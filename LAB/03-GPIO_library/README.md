# Lab 3: User library for GPIO control

### Learning objectives

The purpose of this laboratory exercise is to learn how to create your own library in C. Specifically, it will be a library for controlling GPIO (General Purpose Input/Output) pins.

## Preparation tasks (done before the lab at home)

Fill in the following table and enter the number of bits and numeric range for the selected data types defined by C.

| **Data type** | **Number of bits** | **Range** | **Description** |
| :-: | :-: | :-: | :-- | 
| `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
| `int8_t`   | 8 | -128, +127 | Signed 8-bit integer |
| `uint16_t` | 16 | 0, 1, …, 65535 | Unsigned 16-bit integer |
| `int16_t`  | 16 | -32768, + 32767 | Signed 16-bit integer |
| `float`    | 32 | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |



Void pointer size varies system to system. If the system is 16-bit, size of void pointer is 2 bytes. If the system is 32-bit, size of void pointer is 4 bytes. If the system is 64-bit, size of void pointer is 8 bytes.

Here is an example of how to find the size of the void pointer in the C language:
#include <stdio.h>
int main() {
	void *ptr;

printf("Pointer size value is: %d", sizeof(ptr));
return 0;
}

Output:
“Pointer size value is: 8”


* Completed source code from the example.

2. GPIO library. Submit:
    * Listing of library source file `gpio.c`,
    * C code of the application `main.c`,
    * In your words, describe the difference between the declaration and the definition of the function in C. Give an example.

