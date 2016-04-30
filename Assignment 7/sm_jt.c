#include <stdio.h>

int           reg[8];
unsigned char mem[40*4];
int           pc;
unsigned char insOpCode;
unsigned char insOp0;
unsigned char insOp1;
unsigned char insOp2;
char          insOpImm;
int           insOpExt;


void fetch() {

  insOpCode = mem [pc] >> 4;
  insOp0    = mem [pc] & 0xf;
  insOp1    = mem [pc+1] >> 4;
  insOp2    = mem [pc+1] & 0xf;
  insOpImm  = mem [pc+1];
  pc += 2;
  switch (insOpCode) {
      case 0x0:
      case 0xb:
        insOpExt = mem [pc] << 24 | mem [pc+1] << 16 | mem [pc+2] << 8 | mem [pc+3];
        pc += 4;
        break;
      default:
        ;
  }
}

int exec() {
 
  int cont = 1;
  int addr, val;
  static const void* jumpTable[] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&ca, &&cb, &&cc, &&cd, &&ce, &&cf, &&DEFAULT};

  if(insOpCode<0 || insOpCode > 15){ goto DEFAULT;} 
  goto *jumpTable[insOpCode];
  c0: 
    reg [insOp0] = insOpExt;
    goto CON; 

  c1: 
    addr = (insOp0 << 2) + reg [insOp1];
    reg [insOp2] = mem [addr] << 24 | mem [addr+1] << 16 | mem [addr+2] << 8 | mem [addr+3];
    goto CON;

  c2:
    addr = reg [insOp0] + (reg [insOp1] << 2);
    reg [insOp2] = mem [addr] << 24 | mem [addr+1] << 16 | mem [addr+2] << 8 | mem [addr+3];
    goto CON; 

  c3: 
    addr = (insOp1 << 2) + reg [insOp2];
    val  = reg [insOp0];
    mem [addr]   = val >> 24 & 0xff;
    mem [addr+1] = val >> 16 & 0xff;
    mem [addr+2] = val >>  8 & 0xff;
    mem [addr+3] = val       & 0xff;
    goto CON; 

  c4: 
    addr = reg [insOp1] + (reg [insOp2] << 2);
    val  = reg [insOp0];
    mem [addr]   = val >> 24 & 0xff;
    mem [addr+1] = val >> 16 & 0xff;
    mem [addr+2] = val >>  8 & 0xff;
    mem [addr+3] = val       & 0xff;
    goto CON; 

  c5: goto DEFAULT; 

  c6: {
    static const void* jumpTable2[] = {&&c60, &&c61, &&c62, &&c63, &&c64, &&c65, &&c66, &&c67, &&c68, &&c69, &&c6a, &&c6b, &&c6c, &&c6d, &&c6e, &&c6f, &&DEFAULT6};
    if(insOp0<0 || insOp0 > 15){ goto DEFAULT6;}
    goto *jumpTable2[insOp0];

    c60: 
      reg [insOp2] = reg [insOp1];
      goto CON; 

    c61: 
      reg [insOp2] = reg [insOp1] + reg [insOp2];
      goto CON; 

    c62: 
      reg [insOp2] = reg [insOp1] & reg [insOp2];
      goto CON; 

    c63: 
      reg [insOp2] = reg [insOp2] + 1;
      goto CON; 

    c64: 
      reg [insOp2] = reg [insOp2] + 4;
      goto CON; 

    c65: 
      reg [insOp2] = reg [insOp2] - 1;
      goto CON; 

    c66: 
      reg [insOp2] = reg [insOp2] -4;
      goto CON; 

    c67: 
      reg [insOp2] = ~ reg [insOp2];
      goto CON; 

    c68: 
      goto DEFAULT6;

    c69: 
      goto DEFAULT6;

    c6a: 
      goto DEFAULT6;

    c6b: 
      goto DEFAULT6;

    c6c: 
      goto DEFAULT6;

    c6d: 
      goto DEFAULT6;

    c6e: 
      goto DEFAULT6;

    c6f: 
      reg [insOp2] = pc + (insOp1 << 1);
      goto CON; 


    DEFAULT6: 
    printf ("Illegal ALU instruction: pc=0x%x fun=0x%x\n", pc, insOp0);
    goto CON; }


  c7: 
    if (insOpImm > 0)
          reg [insOp0] = reg [insOp0] << insOpImm;
        else
          reg [insOp0] = reg [insOp0] >> -insOpImm;
    goto CON; 

  c8:
    pc += insOpImm << 1;
    goto CON; 

  c9: 
    if (reg [insOp0] == 0)
        pc += insOpImm << 1;
    goto CON; 

  ca: 
    if (reg [insOp0] > 0)
        pc += insOpImm << 1;
    goto CON; 

  cb: 
    pc = insOpExt;
    goto CON; 

  cc: 
    pc = (((unsigned short) insOpImm) << 1) + reg [insOp0];
    goto CON;

  cd: 
    //NYI 
    goto CON; 

  ce: // NYI  
    goto CON; 

  cf: 
    if (insOp0 == 0)
        cont = 0; 
    goto CON; 


  DEFAULT: 
  printf ("Illegal  instruction: pc=0x%x opCode=0x%x\n", pc, insOpCode);
  goto CON; 

  CON: 
  return cont;
}

void load2 (unsigned short v) {
  mem [pc]   = v >> 8;
  mem [pc+1] = v & 0xff;
  pc += 2;
}

void load4 (unsigned int v) {
  mem [pc]   = v >> 24 & 0xff;
  mem [pc+1] = v >> 16 & 0xff;
  mem [pc+2] = v >> 8  & 0xff;
  mem [pc+3] = v       & 0xff;
  pc += 4;
}

void loadMax () {
  pc = 0;
  load4 (-1);    // max
  load4 (0);     // i
  load4 (0x2);   // a[0]
  load4 (0x28);  // a[1]
  load4 (0x6);   // a[2]
  load4 (0x50);  // a[3]
  load4 (0xa);   // a[4]
  load4 (0x78);  // a[5]
  load4 (0xe);   // a[6]
  load4 (0x10);  // a[7]
  load4 (0x12);  // a[8]
  load4 (0x14);  // a[9]
  pc = 0x50;
  load2 (0x0000); load4 (0x00000000);
  load2 (0x0100); load4 (0xfffffff6);
  load2 (0x0200); load4 (0x00000000);
  load2 (0x1023);
  load2 (0x0400); load4 (0x00000008);
  load2 (0x6005);
  load2 (0x6115);
  load2 (0x9509);
  load2 (0x2405);
  load2 (0x6057);
  load2 (0x6707);
  load2 (0x6307);
  load2 (0x6137);
  load2 (0xa701);
  load2 (0x6053);
  load2 (0x6300);
  load2 (0x80f4);
  load2 (0x3302);
  load2 (0x0100); load4 (0x00000004);
  load2 (0x3001);
  load2 (0xf000);
  pc = 0x50;
}

void loadTest() {
  pc = 0x0;
  load2 (0x0200); load4 (0x00000030);
  load2 (0x1001);
  load2 (0x2001);
  load2 (0x3100);
  load2 (0x4100);
  load2 (0x6001);
  load2 (0x6101);
  load2 (0x6201);
  load2 (0x6301);
  load2 (0x6401);
  load2 (0x6501);
  load2 (0x6601);
  load2 (0x6701);
  load2 (0x6f01);
  load2 (0x7100);
  load2 (0x8000);
  load2 (0x9000);
  load2 (0xa000);
  load2 (0xb000); load4 (0x0000002e);
  load2 (0xc200);
  load2 (0xf000);
  pc = 0x0;
}

void showMem (int start, int count) {
  int i;
  for (i=start; i<count; i+=4)
    printf ("0x%08x: %02x %02x %02x %02x\n", i, mem [i], mem [i+1], mem [i+2], mem [i+3]);
}

void compute (void (*loader)(), int showStart, int showCount) {
  int cont = 0;
  
  loader();
  
  do {
    fetch();
    cont = exec();
  } while (cont);
  
  showMem (showStart, showCount);
}

int main (int argc, char** argv) {
  compute (loadMax,  0, 4);
}