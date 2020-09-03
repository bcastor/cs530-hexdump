/************************************************************* Name: Brandon Castor
username: cssc1960
Project: Assignment 1
File: dbx.c
Notes: This program emulates the xxd program on edoras, it reads data from a file
 and outputs the hex or binary code of that file as well as its ascii representation.
*************************************************************/
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[]) {
    //buffer for binary
    char buff[6] = "";
    //buffer for hex
    char buffr[16]  = "";
    int read, address = 0, i;
    int j;



    //open the file and take the third argument for the file name if a format is provided
    //if not then take the second argument if the format isnt provided
    FILE *fptr = argc > 2 ? fopen(argv[2], "rb") : fopen(argv[1], "rb");

    char str[] = "-b";

    int res = strcmp(str,argv[1]);//checks if the format is -b



    if (!fptr) {
        perror("Not file found");
        return 1;
    }

   if(res == 0)

       // Binary format
       while ((read = fread(buff, 1, sizeof buff, fptr)) > 0) {
           //print address
           printf("%08x: ", address);
           address += 6;

           for (i = 0; i < 7; i++)

               if (i >= read || buff[i] == 0)
                   printf("         ");//moves the last row of the ascii into place to align it

               else {//prints the binary representation
                   for (j = 7; j >= 0; j--) {
                       printf(buff[i] & (1 << j) ? "1" : "0");//perform bitwise operation to get the binary code
                   }
                   printf(" ");//separates the digits every 8 digits
               }


           //print ascii value
           for (i = 0; i < 6; i++)
               if (i >= read || buff[i] == 0)
                   break;//break if it has reached the end of the file
               else
                   printf("%c", ((buff[i]) >= ' ' && buff[i] <= '~') ? buff[i] : '.');//

           putchar('\n');

       }

        //hex format
        else{
            while ((read = fread(buffr, 1, sizeof buffr, fptr)) > 0) {

                printf("%08x: ", address);
                address += 16;

                //print hex values
                for (i = 0; i < 16; i++)

                    if (i >= read || buffr[i] == 0)
                        printf("   ");
                    else//prints hex values with separation every 2 digits
                        (i % 2 == 0) ? printf(" %02hhx", (unsigned char) buffr[i]) : printf("%02hhx",
                                                                                           (unsigned char) buffr[i]);
                printf("  ");
                //prints the ascii values
                for (i = 0; i < 16; i++)
                    if (i >= read || buffr[i] == 0)
                        break;//stop once it reaches the end of the file
                    else
                        printf("%c", ((buffr[i]) >= ' ' && buffr[i] <= '~') ? buffr[i] : '.');

                putchar('\n');


            }
            if (fptr != stdin)
            fclose(fptr);//closes the file
        }
}
