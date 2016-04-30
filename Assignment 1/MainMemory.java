package arch.sm213.machine.student;

import machine.AbstractMainMemory;

/**
 * Main Memory of Simple CPU.
 *
 * Provides an abstraction of main memory (DRAM).
 */

public class MainMemory extends AbstractMainMemory {
  private byte [] mem;
  
  /**
   * Allocate memory.
   * @param byteCapacity size of memory in bytes.
   */
  public MainMemory (int byteCapacity) {
    //TODO
    mem = new byte [byteCapacity];
  }
  
  /**
   * Determine whether an address is aligned to specified length.
   * @param address memory address.
   * @param length byte length.
   * @return true iff address is aligned to length.
   */
  @Override protected boolean isAccessAligned (int address, int length) {
    //TODO
    if((address % length) == 0 ){
      return true;
    }
    return false;
  }
  
  /**
   * Convert an sequence of four bytes into a Big Endian integer.
   * @param byteAtAddrPlus0 value of byte with lowest memory address (base address).
   * @param byteAtAddrPlus1 value of byte at base address plus 1.
   * @param byteAtAddrPlus2 value of byte at base address plus 2.
   * @param byteAtAddrPlus3 value of byte at base address plus 3 (highest memory address).
   * @return Big Endian integer formed by these four bytes.
   */
  @Override public int bytesToInteger (byte byteAtAddrPlus0, byte byteAtAddrPlus1, byte byteAtAddrPlus2, byte byteAtAddrPlus3) {
    //TODO
    int a = byteAtAddrPlus0 << 24;
    int b = byteAtAddrPlus1 << 16;
    int c = byteAtAddrPlus2 << 8;
    int d = byteAtAddrPlus3;

    return (a | b | c | d);
  }
  
  /**
   * Convert a Big Endian integer into an array of 4 bytes organized by memory address.
   * @param  i an Big Endian integer.
   * @return an array of byte where [0] is value of low-address byte of the number etc.
   */
  @Override public byte[] integerToBytes (int i) {
    //TODO
    byte[] bytes = new byte[4];

    int part1 = i & 0xff000000;
    int part2 = i & 0x00ff0000;
    int part3 = i & 0x0000ff00;
    int part4 = i & 0x000000ff;

    bytes[0] = (byte)(part1 >> 24);
    bytes[1] = (byte)(part2 >> 16);
    bytes[2] = (byte)(part3 >> 8);
    bytes[3] = (byte)(part4);

    return bytes;
  }
  
  /**
   * Fetch a sequence of bytes from memory.
   * @param address address of the first byte to fetch.
   * @param length  number of bytes to fetch.
   * @throws InvalidAddressException  if any address in the range address to address+length-1 is invalid.
   * @return an array of byte where [0] is memory value at address, [1] is memory value at address+1 etc.
   */
  @Override protected byte[] get (int address, int length) throws InvalidAddressException {
    //TODO
    byte[] bytes;
    if(((address + length)-1) > length()){
      throw new InvalidAddressException();
    }
    else{
      bytes = new byte[(length - address)];
      int bytespos = 0 ;
      for(int  k = address; k > (address + length) -1 ; k ++ ){
          bytes[bytespos] = mem[k];
          bytespos++;
      }
    }
    return bytes;
  }
  
  /**
   * Store a sequence of bytes into memory.
   * @param  address                  address of the first byte in memory to recieve the specified value.
   * @param  value                    an array of byte values to store in memory at the specified address.
   * @throws InvalidAddressException  if any address in the range address to address+value.length-1 is invalid.
   */
  @Override protected void set (int address, byte[] value) throws InvalidAddressException {
    //TODO
    if((address+value.length)-1 > mem.length){
      throw new InvalidAddressException();
    }else {
      int valuepos = 0;
      for (int m = address; m > (address + value.length) -1 ; m++){
        mem[m] = value[valuepos];
      }
    }
  }
  
  /**
   * Determine the size of memory.
   * @return the number of bytes allocated to this memory.
   */
  @Override public int length () {
    return mem.length;
  }
}