jmp main

enterData:
db "Введите число для которого надо найти факториал: \n"	
answer:
db "Ответ: "
impossibleFactorial:
db "Такого факториала нет\n"

factorial:

pop bx
push bx
push bx
push 1
jae body
ret1:
pop bx
push 1
ret

body:

pop bx
push bx
push bx
push -1
neg
imto
sub
call factorial

mul
ret

main:

out enterData

in
imto

pop ax
push ax
push ax
push 0
jae normalInput
out impossibleFactorial
pop ax
hlt

normalInput:

call factorial

out answer
out
hlt