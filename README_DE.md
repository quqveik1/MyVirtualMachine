# MyVirtualMachine
Dies ist ein Prozessoremulationprojekt, um das **Gerät** von Prozessoren **zu verstehen**.
## Was enthält das Projekt konkret?
# Compiler
  - Ich habe meinen eigenen Assembler-Compiler geschrieben (ähnlich wie `x86`). Der Compiler erstellt eine binäre Darstellung des Codes (`asm` -> `bin`), die viel schneller ausgeführt wird als das Parsen des `asm`-Codes zur Laufzeit.
    
    ![Bild](https://github.com/quqveik1/MyVirtualMachine/assets/64206443/90d8bcbc-843e-4e75-8e17-c178fd206064)

  - Es kann auch eine Listing-Datei für die spätere Debugging-Erleichterung erstellt werden:
    ```
    Dateilisting Pass #3: Finaler Maschinencode
  
    000 | #3 | 00000 | eb 01 00 00 00 00 0c 03 00 00 00 00   | jmp main
    001 | #3 | 0000c |                                       | 
    002 | #3 | 0000c |                                       | convertPixelsToRadians:
    003 | #3 | 0000c | 06 02 00 00 00 00 01 00 00 00 00 00   | 	push bx
    004 | #3 | 00018 | f7 00 00 00                           | 	div
    005 | #3 | 0001c | 06 02 00 00 00 00 00 00 00 00 00 00   | 	push ax
    006 | #3 | 00028 | f6 00 00 00                           | 	mul
    007 | #3 | 0002c | c2 00 00 00                           | 	ret
    ```
  - Kompilierungsphasen.

    `Code` -> `Zwischendarstellung` -> `Maschinencode` -> `Endgültiger Maschinencode (mit Label-Verknüpfung)`
    Die Erstellung der Zwischendarstellung macht den Compiler ähnlich wie `LLVM`.

  - Der Compiler unterstützt Unicode.

# Logik und Struktur des Assemblers und der virtuellen Maschine
  - Alle Operationen werden auf dem Stapel ausgeführt. Unten ist ein Beispiel, wie man den Code `C++` in meinen Assembler übersetzt:
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
    Das heißt, um zwei Zahlen zu addieren, müssen sie auf den Stapel gelegt werden.
  - Die virtuelle Maschine und der Assembler unterstützen die Datenspeicherung im Stapel, Register (`ax`, `bx`, `cx`, `dx`), Arbeitsspeicher (`[3]` - Zugriff auf die 4. Zelle in der Reihenfolge).

  - Es wird die Unterstützung für mehrere Operationen in einer Zeile unterstützt:
    ```asm
    push 10
    pop ax
    push 57
    pop [ax + 5] ; [15] = 57
    ```
  - In der virtuellen Maschine haben alle Zahlen die gleiche Größe im Speicher, daher werden nicht ganzzahlige Zahlen im Format mit fester Anzahl von Nachkommastellen gespeichert. Die [Konvertierung](https://github.com/quqveik1/MyVirtualMachine/blob/main/Converter/FloatConvert.h) erfolgt hin und zurück.

  - Grafik wird unterstützt. Das Programm kann mit einem Grafikfenster gestartet werden.
    Einfachstes Beispiel, in dem ein roter Punkt bei X: 179, Y: 57 gesetzt wird
    ```asm
    push 179
    push 57
    push 255
    push 0
    push 0
    setpxl
    ```
    
    [Ein komplexeres Beispiel:](https://github.com/quqveik1/MyVirtualMachine/blob/main/AsmCode/Sinus.asm)
    
    <img src="https://github.com/quqveik1/MyVirtualMachine/assets/64206443/0ce4ae08-fa9b-4811-8b60-2382b66e5d2c" width="200">
    
    Hier wird der Sinus mit Hilfe der Taylor-Reihen gezeichnet, die explizit in der virtuellen Maschine berechnet werden.
    
    Die Grafik basiert auf [`SFML`](https://www.sfml-dev.org/).
  - Jede kompilierte Datei hat einen [Header](https://github.com/quqveik1/MyVirtualMachine/blob/main/FileHeader/FileHeader.h) mit der Programmversion und der Hash-Summe der Datei zur Überprüfung ihrer Unversehrtheit während der Ausführung.
  - Weitere Informationen zu den Prozessorbefehlen finden Sie [hier](https://github.com/quqveik1/MyVirtualMachine/blob/main/Constants/CommandConstants.h).
    
# Debugger
  - Mein Debugger ähnelt stark `lldb` (die Namen aller Befehle stimmen mit ihm überein).
  - Ein Unterbrechung aus dem Code kann mit dem Befehl `into` eingeleitet werden, auch das Hinzufügen von Haltepunkten aus dem Debugger wird unterstützt.
  - Wenn im Programm ein Fehler auftritt, wird der Debugger aufgerufen.
  - In den Debugger ist ein Dekompil
    <details>
       <summary>Debuggerbeispiel</summary>
       
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
   
  - Mehr ueber Debugger [тут](https://github.com/quqveik1/MyVirtualMachine/blob/main/InteractiveMode/InteractiveModeConstants.h)
    
# Starten
  - Laden Sie das Repository herunter. Im Ordner `x64` -> `Release`. Kopieren Sie den Pfad zum Compiler (`TextToNumConverter.exe`) und zur Maschine (`MyVirtualMachine.exe`).
  - Rufen Sie den Compiler über die Befehlszeile auf und geben Sie den Pfad zur zu kompilierenden Datei an. Dann können Sie als Parameter angeben, ob Sie eine Listing-Datei benötigen (standardmäßig ja).
  - Rufen Sie dann die Maschine mit dem Parameterpfad zur kompilierten Datei auf und geben Sie die Größe (x, y) des zu erstellenden Bildschirms an (0 0, wenn Sie keine Grafik benötigen).
