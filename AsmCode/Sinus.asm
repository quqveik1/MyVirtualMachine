jmp main

convertPixelsToRadians:
push bx
into
div
into
push ax
mul
ret


convertSinToPixels:
push dx
mul
neg
push dx
push -1
add
add
ret

sinus:

pop [8]
push 100
pop [9]
	testCircle:

	push [8]

	push ax
	push 2
	mul
	fmod

	push 0
	pop [0]

	push 1
	pop [1]

	push 1
	pop [2]

	push 8
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
		pop [7]
		push [7]
		push [2]
		mul
		pop [2]
		push [7]
		push 1
		add
		pop [7]
		push [7]
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
push [9]
push 1
sub
pop [9]
push [9]
push 0
ja testCircle

push [0]
ret

sinTest:
pop [8]
push 100
pop [9]
	origSinusTest:
	push [8]
	sin
	pop [0]
	push [9]
	push 1
	sub
	pop [9]
	push [9]
	push 0
	ja origSinusTest

push [0]
ret
 

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
pop [57]
push cx
push [57]
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

hlt