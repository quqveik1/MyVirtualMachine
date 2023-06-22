db "Данная программа решает квадратные уравнения в виде ax^2 + bx + c"
db "\nВведите a: "
db "\nВведите b: "
db "\nВведите c: "
db "\nУравнение не имеет решений\n"
db "\nУравнение имеет одно решение: \n"
db "\nУравнение имеет два решения: \n"
out 8
out 94
in
out 000b6
in
out 000d8
in
pop cx
pop bx
pop ax

push ax
push 0
jne 00276

push 0
push cx
sub
push bx
push 0
jne 0025a
out 000fa
hlt
push bx
div

out 0013c
out

hlt

push bx
push bx
mul
push 4
push ax
mul 
push cx
mul
sub
pop dx

push dx
push 0
ja 002d6

out 000fa

push dx
sqrt

pop dx

push 0
push bx
sub
pop [1]
push [1]

push dx
add
push 2
push ax
mul
pop [2]
push [2]
div
pop [3]

push [1]
push dx
sub
push [2]
div
pop [4]

push [3]
out
push dx
push 0
jne 003a2
push [4]
out

hlt