jmp main

sinus:

push 6.28
fmod

push 0
pop [0]

push 1
pop [1]

push 1
pop [2]

push 7
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

push [0]
ret

main:

push 0
call sinus
out
push 1.5
call sinus
out
push 3
call sinus
out

push 6.28
call sinus
out

hlt