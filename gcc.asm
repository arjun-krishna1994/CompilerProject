.model tiny
.data
a1  db  0
b1  db  0
c1  db  0
d1  db  0
.code
.startup
mov bx,2
mov ax,5
mul bx
mov cx,ax
mov bx,1
mov ax,7
mul bx
add cx,ax
mov bx,3
mov ax,6
mul bx
add cx,ax
mov ax,cx
mov bx,8
mov cx,7
mov dx,bx
add dx,cx
lea di,a1
mov [di],ax
lea di,b1
mov [di],bx
lea di,c1
mov [di],cx
lea di,d1
mov [di],dx
.exit
end
