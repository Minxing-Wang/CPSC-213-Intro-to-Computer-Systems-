.pos 0x1000 

#translating: a[i] = a[i+1] + b[i+2];
	ld $a, r0        # r0 = address of a
   	ld $b, r1        # r1 = address of b
    ld $i, r2        # r2 = address ofi
   	ld 0(r2), r2     # r2 = value of i
   	mov r2, r3       # r3 = i
   	inc r2           # r2 = i + 1
   	ld (r0,r2,4), r4 # r4 = a[i+1]
    inc r2           # r2 = i + 2
    ld (r1,r2,4), r2 # r2 = b[i+2]
    add r4, r2       # r2 = a[i+1] + b[i+2]
    st r2, (r0,r3,4) # a[i] = a[i+1] + b[i+2]

#translating: d[i] = a[i] + b[i]
    ld $i, r0        # r0 = address of i
    ld 0(r0), r0     # r0 = value of i
    ld $a, r1        # r1 = address of a
    ld (r1,r0,4), r1 # r1 = a[i]
    ld $b, r2        # r2 = address of b
    ld (r2,r0,4), r2 # r2 = b[i]
    add r2, r1       # r1 = a[i] + b[i]
    ld $d, r2        # r2 = address of d
    ld 0(r2), r2     # r2 = d
    st r1, (r2,r0,4) # d[i] = a[i] + b[i]

#translating: d[i] = a[b[i]] + b[a[i]]
    ld $i, r0        # r0 = address of i
    ld 0(r0), r0     # r0 = i
    ld $a, r1        # r1 = address of a
    ld $b, r2        # r2 = address of b
    ld (r1,r0,4), r3 # r3 = a[i]
    ld (r2,r0,4), r4 # r4 = b[i]
    ld (r1,r4,4), r4 # r4 = a[b[i]]
    ld (r2,r3,4), r3 # r3 = b[a[i]]
    add r4, r3       # r3 = a[b[i]] + b[a[i]]
    ld $d, r1        # r1 = address of d
    ld 0(r1), r1     # r1 = d
    st r3, (r1,r0,4) # d[i] = a[b[i]] + b[a[i]]

#translating: d[b[i]] = b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i];
    ld $i, r0        # r0 = address of i
    ld 0(r0), r0     # r0 = i
    ld $3, r1        # r1 = 3
    mov r1, r6       # r6 = 3
    and r0, r1       # r1 = i & 3
    ld $a, r2        # r2 = address a
    ld $b, r3        # r3 = address of b
    ld (r2,r1,4), r4 # r4 = a[i & 3]
    ld (r3,r1,4), r5 # r5 = b[i & 3]
    and r6, r4       # r4 = a[i & 3] & 3
    and r6, r5       # r5 = b[i & 3] & 3
    ld (r3,r4,4), r4 # r4 = b[a[i & 3] & 3]
    ld (r2,r5,4), r5 # r5 = a[b[i & 3] & 3]
    not r5           # r5 = ~a[b[i & 3] & 3]
    inc r5           # r5 = -a[b[i & 3] & 3]
    add r5, r4       # r4 = b[a[i & 3] & 3] - a[b[i & 3] & 3]
    ld $d, r1        # r1 = address of d
    ld 0(r1), r1     # r1 = d
    ld (r1,r0,4), r2 # r2 = d[i]
    add r2, r4       # r4 = b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i]
    ld (r3,r0,4), r2 # r2 = b[i]
    st r4, (r1,r2,4) # d[b[i]] = b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i]

# end
    halt


#memory
.pos 0x2000
a:  .long 0          # a[0]
    .long 0 		 # a[1]
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0          # a[7]
b:  .long 0          # b[0]
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0          # b[7]
c:  .long 0          # c[0]
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0          # b[7]
i:  .long 0
d:  .long c
