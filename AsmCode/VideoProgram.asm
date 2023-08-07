push 0
push 0
push 255
push 255
push 255
pixel 
push 0
pop ax

circle:
push ax
push ax
mul
pop bx
push ax+1
pop ax
push 100
push ax
ja circle
hlt