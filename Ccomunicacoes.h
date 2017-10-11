#ifndef CCOMUNICACOES_H
#define CCOMUNICACOES_H

#include <conio.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glaux.h>
#include <GL/glu.h>

#include "Apicdecl.h"
#include "basetsd.h"



class CComunicacoes
{
public :
	CComunicacoes();
	~CComunicacoes();
	void outparallel(int address,int data);
	int inparallel(int address);
	void setPortCBit(char n, int v, int IO_PORT); 
	void escrever(int endereco,int valor,int endereco_motor,int escrita_leitura);
	__int64 ler(int endereco,int endereco_sensor,int escrita_leitura,int sensor_vp);
	void inicializacoes(void);

protected:
	int z,y;
	void escrever_porta_paralela(int endereco,int valor);
	void conversor_endereco(int endereco_mux,int escrita_leitura,int sensor_vp);
	__int64 ler_porta_paralela1(int endereco);
	__int64 ler_porta_paralela2(int endereco);
	
	FILE *com;
};



#endif