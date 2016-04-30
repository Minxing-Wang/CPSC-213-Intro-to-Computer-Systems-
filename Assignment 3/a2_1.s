#code
.pos 0x1000 
#translating: c = 5 
ld $c, r0 			# r0 = address of c 	
ls $5, r1 			# r1 = 5 
st r1, 0(r0)		# c = 5

#translating: b = c + 10
ld $c, r0 			# r0 = address of c 
ld 0(r0), r0 		# r0 = value of c 
ld $10, r1 			# r1 = 10 
add r1, r0 			# r0 = c + 10 
ld $b, r1 			# r1 = address of b 
st r0, 0(r1)  		# b = c + 10 

#translating: a[8] = 8 
ld $a, r0   		# r0 = address of a 
ld $8, r1 			# r1 = 8 
st r1, 32(r0) 		# or st r1, (r0,r1,4)

#translating: a[4] = a[4] + 4
ld $a, r0 			# r0 = address of a or a[0]
ld $4, r1 			# r1 = 4 	
ld 16(r0), r2 		# r0 = a[4]	 	OR use ld (r0,r1,4),r2
add r1, r2 			# a[4] + 4
st r1, 16(r0)		# a[4] = a[4] + 4, OR use st r2, (r0,r1,4)

#translating: a[c] = a[8] + b + a[b & 0x7]
ld $a, r0        # r0 = address of a 
ld $8, r1        # r1 = 8
ld (r0,r1,4), r2 # r2 = a[8]
ld $b, r3        # r3 = address of b 
ld 0(r3), r3     # r3 = b
add r3, r2       # r2 = a[8] + b
ld $7, r1        # r1 = 7
and r3, r1       # r1 = b & 7
ld (r0,r1,4), r1 # r1 = a[b & 7]
add r1, r2       # r2 = a[8] + b + a[b & 7]
ld $c, r1        # r1 = address of c
ld 0(r1), r1     # r1 = c
st r2, (r0,r1,4) # a[c] = a[8] + b + a[b & 7]

#memory
.pos 0x5000
b: .long 0
c: .long 0 
a: .long 0           # a[0]
   .long 0           # a[1]
   .long 0 			 # a[2]
   .long 0 			 # a[3]
   .long 0 			 # a[4]
   .long 0  		 # a[5] 
   .long 0 			 # a[6]
   .long 0 			 # a[7] 
   .long 0           # a[8]
   .long 0           # a[9]

