;file.asm
.586
.model flat, C
.code
mas_func proc mas:dword,n:dword
mov eax, n
add eax, mas
mov n, eax
ret
mas_func endp
end
