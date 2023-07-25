jmp start
text:
db "Well done!\n"

fnc: 
out text
ret

start:
call fnc
hlt