jmp main

parabola:
push [0]
sub
pop bx
push 1
pop cx

circleParabola:
push bx
push bx
mul
pop dx
push cx
push 1
sub
pop cx
push cx
push 0
ja circleParabola

push dx
neg
rdsys vsizey
add
ret

main:

rdsys vsizex
push 2
sub 
pop [0]

push 0
pop ax

circle:
push ax
push ax
call parabola
push 255
push 255
push 255
setpxl
push ax+1
pop ax
push ax
push 100
jb circle

in

hlt