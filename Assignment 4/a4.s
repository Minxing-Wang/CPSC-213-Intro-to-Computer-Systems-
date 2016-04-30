.pos 0x1000
code: 		#translating: v = s.x[i];
			ld $s, r0 	   		#r0 = address of s 
			ld $i, r1 			#r1 = address of i 
			ld 0(r1), r1		#r1 = value of i 
			ld (r0,r1,4), r3 	#r3 = s.x[i]
			ld $v, r2			#r2 = address of v 
			st r3, 0x0(r2) 		#v = s.x[i];
			#translating: v = s.y[i];		
			ld 0x8(r0), r3 		#r3 = adress of y[0]
			ld (r3,r1,4), r4	#r4 = s.y[i]
			st r4, 0x0(r2) 		#v = s.y[i];
			#translating: v = s.z->x[i];
			ld 12(r0), r3		#r3 = value of z = address of the nested struct 
			ld (r3,r1,4), r3 	#r3 = s.z->x[i]
			st r3, 0(r2)		#v = s.z->x[i]
			halt 


.pos 0x2000
static:

i: 			.long 0 			
v:			.long 0 
s: 			.long 0  			#x1 
			.long 0 			#x2
			.long 0 	 		#y
			.long 0 			#z


.pos 0x3000
heap0:	 	.long 0 			# y0
			.long 0 			# y1
				 
			     

heap1: 		.long 0 			#z.x1 
			.long 0 			#z.x2
			.long 0 			#z.y
			.long 0 			#z.z
