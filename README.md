# MyVirtualMachine
Это проект эмуляции процессора, чтобы **понять устройство**, собственно, процессоров.
## Что конкретно содержит проект?
# Компилятор
  - Я написал собственно свой компилятор для ассемблера (напоминающего `x86`). Компилятор создает бинарное представление кода(`asm` -> `bin`), которое выполняется значительно быстрее, чем парсинг `asm` кода в `Runtime`.
    
    ![image](https://github.com/quqveik1/MyVirtualMachine/assets/64206443/90d8bcbc-843e-4e75-8e17-c178fd206064)

  - Также может быть создан файл листинга для удобства последующей отладки:
    ```
    File listing Pass #3: Final Machine Code
  
    000 | #3 | 00000 | eb 01 00 00 00 00 0c 03 00 00 00 00   | jmp main
    001 | #3 | 0000c |                                       | 
    002 | #3 | 0000c |                                       | convertPixelsToRadians:
    003 | #3 | 0000c | 06 02 00 00 00 00 01 00 00 00 00 00   | 	push bx
    004 | #3 | 00018 | f7 00 00 00                           | 	div
    005 | #3 | 0001c | 06 02 00 00 00 00 00 00 00 00 00 00   | 	push ax
    006 | #3 | 00028 | f6 00 00 00                           | 	mul
    007 | #3 | 0002c | c2 00 00 00                           | 	ret
    ```
  - Этапы компиляции.

    `Code` -> `Intermediate Representation` -> `Machine code` -> `Final Machine Code (with label linking)`
    Создание промежуточного [представления](https://github.com/quqveik1/MyVirtualMachine/blob/main/TextToNumConverter/IR/CommandIR.h) делает компилятор похожим на `LLVM`.

  - Компилятор поддерживает Unicode.

# Логика и устройство ассемблера
  - Все операции выполняются на стеке. Ниже пример как перевести код `C++` на мой ассемблер:
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
    Тоесть, например, чтобы сложить два числа, их надо положить на стек.
  - Виртуальная машина и ассемблер поддерживают хранение данных в стеке, регистре (`ax`, `bx`, `cx`, `dx`), оперативной памяти (`[3]` - обращение к 4 ячейке по порядку).

  - Есть поддержка нескольких операций в одну строку:
    ```asm
    push 10
    pop ax
    push 57
    pop [ax + 5] ; [15] = 57
    ```

  - Поддерживается графика. Программа может быть запущена с графическим окном.
    Простейший пример, в котором ставиться точка красного цвета по X: 179, Y: 57
    ```asm
    push 179
    push 57
    push 255
    push 0
    push 0
    setpxl
    ```
    
    [Более сложный пример:](https://github.com/quqveik1/MyVirtualMachine/blob/main/AsmCode/Sinus.asm)
    
    <img src="https://github.com/quqveik1/MyVirtualMachine/assets/64206443/0ce4ae08-fa9b-4811-8b60-2382b66e5d2c" width="200">
    
    Тут рисуется синус при помощи рядов Тейлора, которые явно считаются в виртуальной машине.
    
    Графика реализована на основе [`SFML`](https://www.sfml-dev.org/).
    

    
    
    
    

