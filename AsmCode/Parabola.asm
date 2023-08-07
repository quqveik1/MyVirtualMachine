jmp main

parabola:
push 50
sub
pop bx
push bx
push bx
mul
neg
si vsizey
add
ret

main:

push 0
pop ax

circle:
push ax
push ax
call parabola
push 255
push 255
push 255
pixel
push ax+1
pop ax
push ax
push 100
jb circle

in

hlt