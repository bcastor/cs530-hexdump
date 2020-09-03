dbx.o: dbx.c
    gcc -o Assignment dbx.c\
dbx: dbx.o
    gcc dbx.o -o dbx