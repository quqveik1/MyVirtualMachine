jmp programmStart
intro:
db "Данная программа решает квадратные уравнения в виде ax^2 + bx + c"
inputA:
db "\nВведите a: "
inputB:
db "\nВведите b: "
inputC:
db "\nВведите c: "
noSolutions:
db "\nУравнение не имеет решений\n"
oneSolution:
db "\nУравнение имеет одно решение: \n"
twoSolutions:
db "\nУравнение имеет два решения: \n"
programmStart:
out intro
out inputA
in
out inputB
in
out inputC
in
pop cx
pop bx
pop ax

push ax
push 0
jne quadratic

push 0
push cx
sub
push bx
push 0
jne linear
out noSolutions
hlt

linear:
push bx
div

out oneSolution
out

hlt

quadratic:
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
jae positiveD
out noSolutions
hlt

positiveD:
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
jne endProgamm
push [4]
out

endProgamm:
hlt