// vce-de.cpp : de-encryptor for djmax's vce, vci and vcq files.
// Generic xor (un)masker with header preserve
// Input: files to decrypt or encrypt
// Output: it remplaces the same input file.
//
// Made by ADHSoft ( fdbf11@gmail.com )

#include <stdio.h>
//#include "string.h"

#define KEY_LENGTH 256
const unsigned char key[] = {
	247 ,77 ,219 ,74 ,220 ,102 ,240 ,83 ,197 ,127 ,233 ,28 ,138 ,48 ,166 ,5 ,147 ,41 ,191 ,46 ,184 ,2 ,148 ,55 ,161 ,27 ,141 ,0 ,150 ,44 ,186 ,25 ,143 ,53 ,163 ,50 ,164 ,30 ,136 ,43 ,189 ,7 ,145 ,100 ,242 ,72 ,222 ,125 ,235 ,81 ,
	199 ,86 ,192 ,122 ,236 ,79 ,217 ,99 ,245 ,200 ,94 ,228 ,114 ,209 ,71 ,253 ,107 ,250 ,108 ,214 ,64 ,227 ,117 ,207 ,89 ,172 ,58 ,128 ,22 ,181 ,35 ,153 ,15 ,158 ,8 ,178 ,36 ,135 ,17 ,171 ,61 ,144 ,6 ,188 ,42 ,137 ,31 ,165 ,51 ,162 ,
	52 ,142 ,24 ,187 ,45 ,151 ,1 ,244 ,98 ,216 ,78 ,237 ,123 ,193 ,87 ,198 ,80 ,234 ,124 ,223 ,73 ,243 ,101 ,88 ,206 ,116 ,226 ,65 ,215 ,109 ,251 ,106 ,252 ,70 ,208 ,115 ,229 ,95 ,201 ,60 ,170 ,16 ,134 ,37 ,179 ,9 ,159 ,14 ,152 ,34 ,
	180 ,23 ,129 ,59 ,173 ,32 ,182 ,12 ,154 ,57 ,175 ,21 ,131 ,18 ,132 ,62 ,168 ,11 ,157 ,39 ,177 ,68 ,210 ,104 ,254 ,93 ,203 ,113 ,231 ,118 ,224 ,90 ,204 ,111 ,249 ,67 ,213 ,232 ,126 ,196 ,82 ,241 ,103 ,221 ,75 ,218 ,76 ,246 ,96 ,195 ,85 , 239, 121, 140, 26, 160, 54, 149,
	3 ,185 , 47 ,190 ,40 ,146 ,4 ,167 ,49 ,139 ,29 ,176 ,38 ,156 ,10 ,169 ,63 ,133 ,19 ,130 ,20 ,174 ,56 ,155 ,13 ,183 ,33 ,212 ,66 ,248 ,110 ,205 ,91 ,225 ,119 ,230 ,112 ,202 ,92 ,255 ,105 ,211 ,69 ,120 ,238 ,84 ,194 ,97
};


int c, i, k_pos,header,index=1;
char str[200];
char *buf=NULL;
long int size,f_pos;
int main(int argc, char* argv[])
{
	FILE *f;

    do {	//for every input file

        if (argc == 1) {	//no parameter, take .\in as the input file
            f = fopen (".\\in","rb") ;

        } else { //open given files

            f = fopen (argv[index],"rb");
        }

        if (f==NULL) {
            printf("Error reading file (file number %d)\n",&index);
            return -1;
        }

        //copy file to buf
        fseek(f, 0, SEEK_END);
        size=ftell(f);
        buf=malloc(sizeof(char)*size);
        rewind(f);
        while (1) {
            i = fgetc(f);
            if (i==EOF) break;
            buf[size-1]=i;
        }
        fclose(f);

        //decrypt the buffer and save it
        if (argc == 1) {	//no parameter, take .\in as the input file
            f = fopen (".\\in","wb") ;

        } else { //open given files

            f = fopen (argv[index],"wb");
        }
        if (f==NULL) {
            printf("Error writing file (file number %d)\n",&index);
            return -1;
        }
		
		header= 8 ;	//preserve the header "VC*F\0\x01\x02\0"
        k_pos=0;
        f_pos=0;
        while (1) {	//for every byte
            i=buf[f_pos];
            if (header !=0) {	//preserve header bytes
                header--;
                c = i;
            } else {
                    c = i ^ key[k_pos];	//xor the byte with the key
            }

            fputc(c,f); //write byte to file

            k_pos++;
            if (k_pos==KEY_LENGTH) {	//loop the key index
                k_pos=0;
            }

            f_pos++;
            if (f_pos==size) break; //if end of file
        }

        free(buf);
        buf=NULL;
        fflush(f);
        fclose(f);
        index++;

    } while (index < argc);	//until there're no more files pending

	return 0;
}
