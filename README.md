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

# Логика и устройство ассемблера и виртуальной машины
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
  - В виртульной машине все числа одного размера в памяти, поэтому нецелые цисла храняться в формате с фиксированным числом занков после запятой. [Тут](https://github.com/quqveik1/MyVirtualMachine/blob/main/Converter/FloatConvert.h) просиходит конвертация туда и обратно.

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
  - У каждого скомпилированного файла есть [заголовок](https://github.com/quqveik1/MyVirtualMachine/blob/main/FileHeader/FileHeader.h) с версией программы и хэш суммой файла для проверки при исполнении его сохранности. 
  - Подробнее про команды процессора [тут](https://github.com/quqveik1/MyVirtualMachine/blob/main/Constants/CommandConstants.h)
    
# Отладчик
  - Мой отладчик очень схож с `lldb` (названия всех комманд совпадает с ним)
  - Прерывание из кода можно устроить с помощью команды `into`, также поддерживается добавление точек останова из отладчика.
  - Если в программе возникает ошибка вызывается отладчик.
  - В отладчик встроен декомпилятор.
     <details>
       <summary>Пример вывода отладчика с декомпилятором</summary>
       
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
   
  - Подробнее про команды отладчика [тут](https://github.com/quqveik1/MyVirtualMachine/blob/main/InteractiveMode/InteractiveModeConstants.h)


# Запуск
  - Скачайте репозиторий. Во папке `x64` -> `Release`. Скопируйте пусть к компилатору(`TextToNumConverter.exe`) и к машине(`MyVirtualMachine.exe`).
  - Вызовите из командной строки компилятор и укажите путь к компилируемому файлу, далее в качестве параметра можно передать нужен ли вам файл листинга(по умолачнию да)
  - Затем вызовите машину с параметром пути к скомпилированому файлу и укажите какого размера(x, y) экран следует создать(0 0 если вам графика не нужна)

----
- [EN](https://github.com/quqveik1/MyVirtualMachine/blob/main/README_EN.md)
- [DE](https://github.com/quqveik1/MyVirtualMachine/blob/main/README_DE.md)
    
    

