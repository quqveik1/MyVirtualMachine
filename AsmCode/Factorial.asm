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
jae prev
ret1:
pop bx
push 1
ret

prev:

pop bx
push bx
push bx
push -1
neg
sub
call factorial

mul
ret

main:

out enterData

in

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