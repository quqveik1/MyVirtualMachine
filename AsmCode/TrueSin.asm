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
push 0
pop [0]

push 1
pop [1]

push 1
pop [2]

push 10
pop [3]

pop [4]
push [4]
push [4]
mul
pop [5]

push 0
pop [6]

	sinFor:

	push 2
	push [6]
	mul 
	push 1
	add
	pop [7]

	push [1]
	push [4]
	mul
	push [2]
	div 
	push [0]
	add
	pop [0]

	push [7]
	push 1
	add
	push [2]
	mul
	pop [2]
	push [7]
	push 1
	add
	push [2]
	mul
	pop [2]

	push [4]
	push [5]
	mul
	pop [4]

	push [1]
	neg
	pop [1]

	push [6]
	push 1
	add
	pop [6]
	push [6]
	push [3]
	jb sinFor

push [0]
ret	


main:

push 3.14159265
pop ax
push 31.4159265
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