.pos 0x1000

ld $0, r0			#r0 = 0
ld $i, r1 			#r1 = address of i 
st r0,(r1)			#i = 0 
ld $a, r1			#r1 = address of a 
ld $s, r2			#r2 = address of s 
ld (r2), r2			#r2 = value of s
loop : 
ld $5, r3			#r3 = 5
not r3				#negating r3 
inc r3  			#negating 5 
add r0, r3 			#r3 = i-5
bgt r3, end			#if r3 greater than 0 go to end 
beq r3, end			#if r3 = 0 then go to end		
ld (r1,r0,4), r4	#r4 = a[i]
inc r0				# i ++
bgt r4, true		#if a[i] is negative go back to loop 
br loop 			#go back to loop 
true:
add r4, r2			# r2 = s+ a[i]
br loop 			#go back to lop 
end: 				#bginning of end 
ld $i, r7 			#r7 = address of i 
ld $s, r6 			#r6 = address of s
st r0, 0x0(r7) 		#i = r0
st r2, 0x0(r6)		#storing the value back into s
halt				#stops




.pos 0x2000
s:	.long 0 		#s 
i: 	.long 0xa		#i
a:	.long 0xa		#a[1]
	.long 0xfff 	#a[2]
	.long 0xfffff4	#a[3]
	.long 4			#a[4]
	.long 8 		#a[5]


