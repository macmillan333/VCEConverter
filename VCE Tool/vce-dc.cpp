#include <iostream>

using namespace std;

// vce-de.cpp : de-encryptor for djmax's vce, vci and vcq files.
// Generic xor (un)masker
// Input: files to decrypt
// Output: new decrypted files, apending ".vceDC" to the filename.
//
// Made by intron ( fdbf11@gmail.com )

#include <stdio.h>
#include stlib.h
#include "string.h"

#define KEY_LENGTH 256
const unsigned char key[] = {
	247 ,77 ,219 ,74 ,220 ,102 ,240 ,83 ,197 ,127 ,233 ,28 ,138 ,48 ,166 ,5 ,147 ,41 ,191 ,46 ,184 ,2 ,148 ,55 ,161 ,27 ,141 ,0 ,150 ,44 ,186 ,25 ,143 ,53 ,163 ,50 ,164 ,30 ,136 ,43 ,189 ,7 ,145 ,100 ,242 ,72 ,222 ,125 ,235 ,81 ,
	199 ,86 ,192 ,122 ,236 ,79 ,217 ,99 ,245 ,200 ,94 ,228 ,114 ,209 ,71 ,253 ,107 ,250 ,108 ,214 ,64 ,227 ,117 ,207 ,89 ,172 ,58 ,128 ,22 ,181 ,35 ,153 ,15 ,158 ,8 ,178 ,36 ,135 ,17 ,171 ,61 ,144 ,6 ,188 ,42 ,137 ,31 ,165 ,51 ,162 ,
	52 ,142 ,24 ,187 ,45 ,151 ,1 ,244 ,98 ,216 ,78 ,237 ,123 ,193 ,87 ,198 ,80 ,234 ,124 ,223 ,73 ,243 ,101 ,88 ,206 ,116 ,226 ,65 ,215 ,109 ,251 ,106 ,252 ,70 ,208 ,115 ,229 ,95 ,201 ,60 ,170 ,16 ,134 ,37 ,179 ,9 ,159 ,14 ,152 ,34 ,
	180 ,23 ,129 ,59 ,173 ,32 ,182 ,12 ,154 ,57 ,175 ,21 ,131 ,18 ,132 ,62 ,168 ,11 ,157 ,39 ,177 ,68 ,210 ,104 ,254 ,93 ,203 ,113 ,231 ,118 ,224 ,90 ,204 ,111 ,249 ,67 ,213 ,232 ,126 ,196 ,82 ,241 ,103 ,221 ,75 ,218 ,76 ,246 ,96 ,195 ,85 ,
	239, 121, 140, 26, 160, 54, 149,
	3 ,185 , 47 ,190 ,40 ,146 ,4 ,167 ,49 ,139 ,29 ,176 ,38 ,156 ,10 ,169 ,63 ,133 ,19 ,130 ,20 ,174 ,56 ,155 ,13 ,183 ,33 ,212 ,66 ,248 ,110 ,205 ,91 ,225 ,119 ,230 ,112 ,202 ,92 ,255 ,105 ,211 ,69 ,120 ,238 ,84 ,194 ,97
};


int c, i, k, pos,header,index=1;
char str[200];
char *buf=NULL;
int main(int argc, char* argv[])
{
	FILE *in,*out;

    do {	//for every input file

        header= 8 ;	//preserve the header "VC*F\0\x01\x02\0"
        pos= 0 ;

        if (argc == 1) {	//no parameter, take .\in as the input file
            in = fopen (".\\in","rb") ;
            out = fopen (".\\out.vceDC","wb");

        } else { //open given files

            in = fopen (argv[index],"rb");
            strcpy(str,argv[index]);
            strcat(str, ".vceDC");
            out = fopen (str,"wb");
        }

        if (in==NULL||out==NULL) {
            printf("Error opening file(s) (file number %d) for reading, or write error.\n",&index);
            return -1;
        }

        buf=malloc()
         sizeof(char)

        while (1) {	//until the end of the file.

            i = fgetc(in);

            if (i==EOF) break;

            if (header !=0) {	//preserve header
                c =i;
                header--;
            } else {
                    c = i ^ key[pos];	//xor the byte with the key
            }

            fputc(c,out);

            pos++;
            if (pos==KEY_LENGTH) {	//loop the key index
                pos=0;
            }

        }

        fclose(in);
        fclose(out);
        index++;

    } while (index < argc);

	return 0;
}
