in

jmp main

fib:

pop bx
push bx
push bx
push 0
ja checkRet1
pop bx
push 0
ret

checkRet1:
pop bx
push bx
push bx
push 1
jne prev
ret1:
pop bx
push 1
ret

prev:

pop bx
push bx
push bx
push -1
add
call fib

pop cx
pop bx
push cx

push bx
push -2
add
call fib

add
ret

main:

call fib

out
hlt