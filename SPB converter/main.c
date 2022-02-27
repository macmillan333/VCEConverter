#include <stdio.h>
#include <stdlib.h>

void xxor(unsigned  char key, FILE* infile);

FILE *infile;
int main(int argc, char *argv[])
{
    int argcindex=1;
    long size;
    char a;

    unsigned char stringg[100];

    if (argc == 1) {	//no parameter, print help
        printf("no param");

        return -1;

    } else { //parse params

        while (argcindex<argc) {

            infile = fopen (argv[argcindex],"rb+");
            if (infile==NULL) {
                printf("Error opening file %s\n",argv[argcindex]);
                return -1;
            } else {    //check format
                printf("Opened %s \n",argv[argcindex]);

                fseek(infile, 0L, SEEK_END);
                size = ftell(infile);
                fflush(infile);
                rewind(infile);
                fflush(infile);
                fputs("BM",infile);
                //printf("%d",size);
                fwrite(&size,sizeof (long),1,infile);
                fflush(infile);
                fseek(infile, 10L, SEEK_SET);
                //fputc('F',infile);


                xxor(0xFE,infile);
                xxor(0x56,infile);
                fseek(infile, 0x12, SEEK_SET);
                xxor(0x31,infile);
                xxor(0x08,infile);
                fseek(infile, 0x16, SEEK_SET);
                xxor(0x19,infile);
                xxor(0x10,infile);
                fseek(infile, 0x1c, SEEK_SET);
                xxor(0x20,infile);
                xxor(0x11,infile);

            }
            fflush(infile);
            fclose(infile);

            argcindex++;
        }
    }

    return 0;
}

void xxor(unsigned char key, FILE* infile) {
                char a;

                a=fgetc(infile);
                a^=key;
                fseek(infile, -1L, SEEK_CUR);
                fputc(a,infile);
                fflush(infile);
}
