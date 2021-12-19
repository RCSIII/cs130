# cs130

# **Overview**
You will be writing an MMU simulator. You will be given MMU tables as binary files with a starting address.

3 **Documents**
The RISC-V privileged specification is available at: https://riscv.org/specifications/privileged-isa/ (Links to an external site.)

Chapter 4.3 of this specification documents the Sv32 system, which contains the following data structures:
![mmu_sv32](https://user-images.githubusercontent.com/89229416/146666664-906816bb-8f38-4c34-9076-fad0589258c1.png)

The SATP register is depicted as:
![mmu_sv32_satp](https://user-images.githubusercontent.com/89229416/146666673-c7223edf-5a3b-4830-ac0e-c57e640c99e8.png)

# **Assignment**
Your program will perform the following steps:

1. read a binary MMU file given by the first user command line argument.
2. grab the virtual memory address in 32-bit hex by asking the user.
3. translate the address to a physical address.
4. output "Page fault!" or the physical address in hex using 9 digits and preceded by 0x.
5. if the user enters any non-hex value or any other error occurs,  give the user an error message and prompt them again.
6. Keep asking for virtual memory addresses until the user types "quit".
7. Use C-style functions for console interaction and files, such as printf/scanf and fopen/fread/fclose.

# **Examples**
```
hydra10: ~> ./mylab /home/cosc130/progs/test1.mmu
Enter virtual address (or "done" to quit): 0x1000
Page fault!
Enter virtual address (or "done" to quit): 0x100002cf
0x02dc002cf
Enter virtual address (or "done" to quit): done
hydra10: ~> 
```
```
hydra10: ~> ./mylab /home/cosc130/progs/test4.mmu
Enter virtual address (or "done" to quit): 0x12dcd123
0x071942123
Enter virtual address (or "done" to quit): 0x70f217f2
0x1f7f217f2
Enter virtual address (or "done" to quit): done
hydra10: ~>
```

# **MMU File Format**
The MMU files have the following format:

1. The last 4 bytes are the SATP register.
2. Bytes 0 through (size - 4 - 1) contain the page tables starting at memory address 0x0.

# **Testing**
Compile your lab using the following command:
```
g++ -Wall -Werror -pedantic -std=c++11 -o mylab mylab.cpp
```
