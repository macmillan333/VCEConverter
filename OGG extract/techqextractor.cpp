// techqextractor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{

	
	FILE * archivopak;
	FILE * archivosalida;
	int c,encontrados=0,e,i=0,tamano;
	char strpos=0;
	char str[]={'O','g','g','S',0,2,0,0,0,0,0,0,0,0};
	char input[]="pak.fpk";
	char output[]="eee.ogg";
	long oggstarts[999],puntero=0;


	archivopak=fopen(input,"rb");
	

	//buscar


	while((c = fgetc(archivopak)) != EOF) {
		
		puntero++;

		if (c==str[strpos]) {

			strpos++;
			if (strpos==14) {	//se encontro el header
				oggstarts[encontrados]=puntero-14;
				encontrados++;
				strpos=0;
				fseek ( archivopak , 500 , SEEK_CUR );
				puntero=puntero+500;
				printf("%d\n",(oggstarts[encontrados-1]));
			}

		} else {
			if (strpos!=0) {
				fseek ( archivopak , ((strpos)*(-1)) , SEEK_CUR );
				puntero=puntero-strpos;
				strpos=0;
			}
		}
		
	}

	oggstarts[encontrados+1]=puntero-1;	//eof

		printf("encontrados: %d    puntero:%d \n",encontrados, puntero);

	//escribir

	fseek ( archivopak , 0 , SEEK_SET );

	i=0;
	while (i<(encontrados-1)) {
		e=i;
		e=e%10;
		output[2]=e;	//unidades

		e=i-output[2];
		e=e%100;
		e=e/10;
		output[1]=e;	//decenas

		e=i-(output[1]*10)-output[2];
		e=e/100;
		output[0]=e;	//centenas

		output[0]=output[0]+0x30;
		output[1]=output[1]+0x30;
		output[2]=output[2]+0x30;


		archivosalida=fopen(output,"wb");
		fseek ( archivosalida , 0 , SEEK_SET );
		fseek ( archivopak , oggstarts[i] , SEEK_SET );

		tamano=oggstarts[i+1]-oggstarts[i];
		puntero=0;
		printf("nombre: %s, tamaño: %d  bytes\n",output,tamano);
		while (puntero<tamano) {


			fputc(fgetc(archivopak),archivosalida);
			puntero++;

		}

		fclose(archivosalida);
		i++;

	}





	fclose(archivopak);
	return 0;
}

