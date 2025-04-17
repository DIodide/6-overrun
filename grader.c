#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

enum {BUFSIZE = 48};

char grade = 'D';
char name[BUFSIZE];

/* Stack Memory Map: */
/* read string on top 
   get name below that 
   main below that */

void readString(void)
{
   char buf[BUFSIZE];
   int i = 0; 
   int c;

   for (;;)
   {
      c = fgetc(stdin);
      if ((c == EOF) || (c == '\n')) 
         break;
      buf[i] = c;
      i++;
   }
   buf[i] = '\0';

   for (i = 0; i < BUFSIZE; i++) 
      name[i] = buf[i];
}

void getName(void)
{
   /* In the getName function we call the readString function */
   printf("What is your name?\n");
   /* This branches to readString, we set x30 to be where we left off
      in getName. */
   readString();
}

int main(void)
{
   mprotect((void*)((unsigned long)name & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE | PROT_EXEC);

   getName(); /* When we call getName, x30 becomes where we left off in
    main */

   if (strcmp(name, "Andrew Appel") == 0) 
      grade = 'B';

   printf("%c is your grade.\n", grade);
   printf("Thank you, %s.\n", name);

   return 0;
}
