jmp main

convertPixelsToRadians:
push bx
div
push ax
mul
ret


convertSinToPixels:
push dx
mul
neg
push dx
add
ret

sinus:


main:

push 3.145
pop ax
push 31.45
pop bx
rdsys vsizey
push 2
div
pop dx

push 0
pop cx

drawCircle:

push cx
call convertPixelsToRadians
call sinus
pop [0]
push cx
push [0]
call convertSinToPixels
push 255
push 255
push 255
setpxl

push cx+1
pop cx
push cx
push 100
jb drawCircle 

in

hlt