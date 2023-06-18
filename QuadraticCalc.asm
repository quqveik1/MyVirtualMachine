in
in
in
pop cx
pop bx
pop ax

push ax
push 0
jne 00080

push 0
push cx
sub
push bx
push 0
jne 0006c
hlt
push bx
div

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
jb 001a4

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
je 001a4
push [4]
out

hlt