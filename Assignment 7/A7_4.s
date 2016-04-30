.pos 0x0
                 ld   $0x1028, r5                       #loading the address of the stack       
                 ld   $0xfffffff4, r0                   #adding frames to the stack
                 add  r0, r5                            #adding frames to the stack
                 ld   $0x200, r0                        #loading address of c 
                 ld   0x0(r0), r0                       #loading c[0]
                 st   r0, 0x0(r5)                       #storing c[0]
                 ld   $0x204, r0                        #loading c[1]
                 ld   0x0(r0), r0                       #storing c[1]
                 st   r0, 0x4(r5)                       #loading c[2]
                 ld   $0x208, r0                        #storing c[2]
                 ld   0x0(r0), r0                       
                 st   r0, 0x8(r5)                       
                 gpc  $6, r6                            #save return address           
                 j    0x300                     
                 ld   $0x20c, r1                        #jumping to foo
                 st   r0, 0x0(r1)                       #taking the return and saving it to c[3]
                 halt                     
.pos 0x200
                 .long 0                                #c[]
                 .long 0        
                 .long 0         
                 .long 0         
.pos 0x300
                 ld   0x0(r5), r0                       #taking the arguments form the stack
                 ld   0x4(r5), r1         
                 ld   0x8(r5), r2         
                 ld   $0xfffffff6, r3                   #loading -10 
                 add  r3, r0                            #c[0] -10 
                 mov  r0, r3                             #moving between registers       
                 not  r3                                #negating
                 inc  r3                  
                 bgt  r3, L6                            #see if c[0] is bigger than or equal to 10 
                 mov  r0, r3              
                 ld   $0xfffffff8, r4                   #load 8 
                 add  r4, r3              
                 bgt  r3, L6                            #see if c[0] is smaller or equal to 18 
                 ld   $0x400, r3          
                 j    *(r3, r0, 4)                      #go to the jump table if 10<= c[0] <=18
.pos 0x330
                 add  r1, r2                            #if c[0] = 10 
                 br   L7                                #go to l7
                 not  r2                                #if c[0] = 11 
                 inc  r2                  
                 add  r1, r2                            #-c[2] + c[1]
                 br   L7                                #go to l7
                 not  r2                                
                 inc  r2                  
                 add  r1, r2              
                 bgt  r2, L0              
                 ld   $0x0, r2            
                 br   L1                  
L0:              ld   $0x1, r2                          #r2 = 1    
L1:              br   L7                                #go to l7 
                 not  r1                  
                 inc  r1                  
                 add  r2, r1              
                 bgt  r1, L2              
                 ld   $0x0, r2            
                 br   L3                  
L2:              ld   $0x1, r2            
L3:              br   L7                        
                 not  r2                                #if(-c[2]+c[1] == 0 )
                 inc  r2                  
                 add  r1, r2              
                 beq  r2, L4              
                 ld   $0x0, r2                          #return 0 
                 br   L5                  
L4:              ld   $0x1, r2                          #return 1
L5:              br   L7                  
L6:              ld   $0x0, r2                          #return 0 
                 br   L7                  
L7:              mov  r2, r0                            #return r2 
                 j    0x0(r6)             
.pos 0x400
                 .long 0x00000330                       #jump table
                 .long 0x00000384         
                 .long 0x00000334         
                 .long 0x00000384         
                 .long 0x0000033c         
                 .long 0x00000384         
                 .long 0x00000354         
                 .long 0x00000384         
                 .long 0x0000036c         
.pos 0x1000     
                 .long 0x00000000                       #stack
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
