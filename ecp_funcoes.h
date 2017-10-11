// funcao que faz o enable ou o disable de qualquer bit do port IO_PORT
//ecp_funcoes.h

#ifndef ECP_FUNCOES_H
#define ECP_FUNCOES_H

#include <conio.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glaux.h>
#include <GL/glu.h>

#include "Apicdecl.h"

void outparallel(int address,int data);

int inparallel(int address);

void setPortCBit(char n, int v, int IO_PORT); 
                               

//funcao que escreve na porta paralela um valor dado o endereco da porta,
//o endereco do motor e se estamos em modo escrita(escrita_leitura=0)
//ou modo leitura(escrita_leitura=1)

void escrever(int endereco,int valor,int endereco_motor,int escrita_leitura);


// le o H_byte(8 bits)-> atraves dos 8 bits de data
// le o L_byte(4 bits)-> atraves dos bits de status
// dados o endereco donde e lido o valor, o endereco do sensor, 
// velocidade(sensor_vp=1) posicao(sensor_vp=0)
//e se estamos em modo escrita(escrita_leitura=0) ou modo leitura(escrita_leitura=1)
// devolve o valor lido em decimal entre 0..4095
__int64 ler(int endereco,int endereco_sensor,int escrita_leitura,int sensor_vp);


// faz as inicializacoes da porta paralela e das variaveis
void inicializacoes(void);



#endif //ECP_FUNCOES_H
