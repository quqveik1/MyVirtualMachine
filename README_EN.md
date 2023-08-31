# MyVirtualMachine
This is a processor emulation project aimed at **understanding the inner workings** of processors.

## What Does the Project Specifically Contain?
# Compiler
  - I've written my own compiler for an assembler similar to `x86`. The compiler creates a binary representation of the code (`asm` -> `bin`), which executes significantly faster than parsing `asm` code at `Runtime`.
    
    ![image](https://github.com/quqveik1/MyVirtualMachine/assets/64206443/90d8bcbc-843e-4e75-8e17-c178fd206064)

  - A listing file can also be created for easier debugging later on:
    ```
    File listing Pass #3: Final Machine Code
  
    000 | #3 | 00000 | eb 01 00 00 00 00 0c 03 00 00 00 00   | jmp main
    ```
  - Compilation stages.

    `Code` -> `Intermediate Representation` -> `Machine code` -> `Final Machine Code (with label linking)`
    The creation of an intermediate [representation](https://github.com/quqveik1/MyVirtualMachine/blob/main/TextToNumConverter/IR/CommandIR.h) makes the compiler similar to `LLVM`.

  - The compiler supports Unicode.

# Logic and Structure of the Assembler and Virtual Machine
  - All operations are carried out on the stack. Below is an example of translating `C++` code to my assembler:
    ```cpp
    int a = 0;
    int b = 4, c = 8;
    a = sqrt(b) + c * c;
    std::cout << a << std::endl;
    ```
    ```asm
    push 0
    pop ax
    push 4
    pop bx
    push 8
    pop cx
    push bx
    sqrt
    push cx
    push cx
    mul
    push ax
    add
    out
    ```
  - The virtual machine and assembler support storing data in the stack, registers (`ax`, `bx`, `cx`, `dx`), and RAM (`[3]` - refers to the 4th cell in the sequence).

  - Support for multiple operations in one line:
    ```asm
    push 10
    pop ax
    push 57
    pop [ax + 5] ; [15] = 57
    ```
  - All numbers in the virtual machine have a fixed size in memory, so floating-point numbers are stored in fixed-point format. [Here](https://github.com/quqveik1/MyVirtualMachine/blob/main/Converter/FloatConvert.h) is the conversion process.

  - Graphics are supported. The program can be launched with a graphical window. A simple example to plot a red pixel at X: 179, Y: 57:
    ```asm
    push 179
    push 57
    push 255
    push 0
    push 0
    setpxl
    ```
    [More complex example:](https://github.com/quqveik1/MyVirtualMachine/blob/main/AsmCode/Sinus.asm)
    
    <img src="https://github.com/quqveik1/MyVirtualMachine/assets/64206443/0ce4ae08-fa9b-4811-8b60-2382b66e5d2c" width="200">
    
    Here, sine is drawn using Taylor series, which are explicitly calculated on the virtual machine.
    
    Graphics are based on [`SFML`](https://www.sfml-dev.org/).
  - Every compiled file comes with a [header](https://github.com/quqveik1/MyVirtualMachine/blob/main/FileHeader/FileHeader.h) that contains the version of the program and a file hash for integrity checking during execution.
  - More details about processor commands can be found [here](https://github.com/quqveik1/MyVirtualMachine/blob/main/Constants/CommandConstants.h).
    
# Debugger
  - My debugger is very similar to `lldb` (all command names are the same).
  - Interruption in the code can be done using the `into` command; breakpoint setting from the debugger is also supported.
  - If an error occurs in the program, the debugger is invoked.
  - The debugger has a built-in decompiler.
     <details>
       <summary>Example output from debugger with decompiler</summary>
       
        -----Interactive mode launched-----
  
        Last 32 fully executed commands:
        000 | 00360 | 07 02 00 00 00 00 03 00 00 00 00 00   | pop dx
        001 | 0036c | 06 01 00 00 00 00 00 00 00 00 00 00   | push 0
        002 | 00378 | 07 02 00 00 00 00 02 00 00 00 00 00   | pop cx
        003 | 00384 | 06 02 00 00 00 00 02 00 00 00 00 00   | push cx
        004 | 00390 | e8 01 00 00 00 00 0c 00               | call c
        005 | 0000c | 06 02 00 00 00 00 01 00 00 00 00 00   | push bx
        006 | 00018 | f7 00 00 00                           | div
        007 | 0001c | 06 02 00 00 00 00 00 00 00 00 00 00   | push ax
        008 | 00028 | f6 00 00 00                           | mul
        009 | 0002c | c2 00 00 00                           | ret
        010 | 0039c | 18 00 00 00                           | sin
        011 | 003a0 | 07 05 00 00 00 00 39 00 00 00 00 00   | pop [57]
        012 | 003ac | 06 02 00 00 00 00 02 00 00 00 00 00   | push cx
        013 | 003b8 | 06 05 00 00 00 00 39 00 00 00 00 00   | push [57]
        014 | 003c4 | e8 01 00 00 00 00 30 00               | call 30
        015 | 00030 | 06 02 00 00 00 00 03 00 00 00 00 00   | push dx
        016 | 0003c | f6 00 00 00                           | mul
        017 | 00040 | f8 00 00 00                           | neg
        018 | 00044 | 06 02 00 00 00 00 03 00 00 00 00 00   | push dx
        019 | 00050 | 06 01 00 00 00 00 ff ff ff ff ff ff   | push -1
        020 | 0005c | 00 00 00 00                           | add
        021 | 00060 | 00 00 00 00                           | add
        022 | 00064 | c2 00 00 00                           | ret
        023 | 003d0 | 06 01 00 00 00 00 ff 00 00 00 00 00   | push 255
        024 | 003dc | 06 01 00 00 00 00 ff 00 00 00 00 00   | push 255
        025 | 003e8 | 06 01 00 00 00 00 ff 00 00 00 00 00   | push 255
        026 | 003f4 | 25 00 00 00                           | setpxl
        027 | 003f8 | 06 03 00 00 00 00 01 00 00 00 00 00 + | push 1 + ax
                    | 00 00 02 00 00 00 00 00               |
        028 | 0040c | 07 02 00 00 00 00 02 00 00 00 00 00   | pop cx
        029 | 00418 | 06 02 00 00 00 00 02 00 00 00 00 00   | push cx
        030 | 00424 | 27 00 00 00 00 00 00 00               | rdsys vsizex
        031 | 0042c | ce 00 00 00                           | into
        
        Stack from start to end:
        00000: 1
        00001: 500
        End of stack
        
        Call stack is empty
        
        Register printout:
        ax: 3.14499
        bx: 166.667
        cx: 1
        dx: 250
        End of register printout
     </details>
  
  - More details about debugger commands can be found [here](https://github.com/quqveik1/MyVirtualMachine/blob/main/InteractiveMode/InteractiveModeConstants.h).


# Launch Instructions
  - Download the repository. In the `x64` folder, go to `Release`. Copy the path to the compiler (`TextToNumConverter.exe`) and the machine (`MyVirtualMachine.exe`).
  - Open the command line and call the compiler, specifying the path to the file you wish to compile. Optionally, you can indicate whether you need a listing file (enabled by default).
  - Then, call the machine with the compiled file's path as an argument, and specify the screen size(x, y) you want to create (use 0 0 if you don't need graphics).

----
- [RU](https://github.com/quqveik1/MyVirtualMachine/blob/main/README.md)
- [DE](https://github.com/quqveik1/MyVirtualMachine/blob/main/README_DE.md)

