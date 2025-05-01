/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   uiSrc = uiSrc << (32 - uiNumBits - uiSrcStartBit);
   uiSrc = uiSrc >> (32 - uiNumBits);
   uiSrc = uiSrc << uiDestStartBit;
   *puiDest = *puiDest | uiSrc;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   /* Your code here */
   unsigned int uiInstr;
   unsigned int uiOPCode = 0x294;

   /* Base Instruction Code */
   uiInstr = 0x10000000;
   /* 01*/
   setField(uiOPCode, 0, &uiInstr, 21, 11);
   setField(uiReg, 0, &uiInstr, 0, 5);
   setField(iImmed, 0, &uiInstr, 5, 16);
   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
                               unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
                                unsigned int uiToReg)
{
   unsigned int uiInstr;
   unsigned int uiOPCode = 0xe4;

   /* Base Instruction Code */
   uiInstr = 0x10000000;
   setField(uiOPCode, 0, &uiInstr, 22, 10);
   setField(uiFromReg, 0, &uiInstr, 0, 5);
   setField(uiToReg, 0, &uiInstr, 5, 5);
   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
                             unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiOPCode = 0x5;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);
   uiDisp = uiDisp >> 2;
   setField(uiDisp, 0, &uiInstr, 0, 26);
   setField(uiOPCode, 0, &uiInstr, 26, 6);
   return uiInstr;
}
