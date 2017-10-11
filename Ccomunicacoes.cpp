
#include "stdafx.h"
#include "CComunicacoes.h"




CComunicacoes::CComunicacoes(void)
{

 com=fopen("teste.ser","w");
 inicializacoes();			// Inicializacoes da porta paralela
};


CComunicacoes::~CComunicacoes()
{
	fclose (com);
};



void CComunicacoes::outparallel(int address,int data)
{
	int mystatus;
	
	if (address >= 0x778)	
	{
		address=address-0x778;
		Poke8( (USHORT) 2, (USHORT) address,(USHORT) data,&mystatus);
	}

	else if (address >= 0x3F8) 
	{
		address=address-0x3F8;
		Poke8( (USHORT) 3, (USHORT) address,(USHORT) data,&mystatus);
	}

	else if (address >= 0x378) 
	{
		address=address-0x378;
		Poke8( (USHORT) 0, (USHORT) address,(USHORT) data,&mystatus);
	}

};




int CComunicacoes::inparallel(int address)
{
	int mystatus,rtn;


	if (address >= 0x778)	
	{
		address=address-0x778;
		rtn=Peek8( (USHORT) 2, (USHORT) address,&mystatus);
	}
	else if (address >= 0x3F8) 
	{
		address=address-0x3F8;
		rtn=Peek8( (USHORT) 3, (USHORT) address,&mystatus);
	}

	else if (address >= 0x378) 
	{
		address=address-0x378;
		rtn=Peek8( (USHORT) 0, (USHORT) address,&mystatus);
	}

	return (rtn);
};



//funcao que recebe um valor decimal entre 0..4095
// e manda para o endereco de saida ->  6 bits de cada vez (H_byte e L_byte)
void CComunicacoes::escrever_porta_paralela(int endereco,int valor)
{
 outparallel(endereco,valor >> 6);
 outparallel(endereco,valor);
 outparallel(890,199);
 outparallel(890,197);
 outparallel(890,199);
 outparallel(890,195);
 outparallel(890,203);
 outparallel(890,201);
 outparallel(890,203);
 outparallel(890,195);
 
}




//funcao que faz a multiplexagem dos valores escritos e lidos para a porta paralela
//escrita_leitura=0 -> modo escrita -> faz o mux do motor que vai ser escrito
//escrita_leitura=1 -> modo leitura -> faz o mux do sensor que vai ser lido
void CComunicacoes::conversor_endereco(int endereco_mux,int escrita_leitura,int sensor_vp)
{
 int v,p,maior7;

 v=1;p=1;
 if (endereco_mux>7) {maior7=1;endereco_mux=endereco_mux-8;}
	else maior7=0;
 if (escrita_leitura==1&&sensor_vp==1) {v=0;p=1;}
	else if (escrita_leitura==1&&sensor_vp==0) {v=1;p=0;}
		else {v=1;p=1;}
 
 
 outparallel(1912,endereco_mux+(v << 4)+(p << 3)+(maior7 << 5));
 outparallel(890,193);
 outparallel(1016+4,0);
 outparallel(1016+4,3);
 outparallel(890,195);
 
}





__int64 CComunicacoes::ler_porta_paralela1(int endereco)
{
 int H_byte,L_byte;
 
  outparallel(890,227);
  outparallel(890,235);
  outparallel(890,239);
  H_byte=inparallel(endereco) << 4;  // le o H_byte da porta paralela(4 bits)  
  L_byte=((inparallel(889) >> 3)-16);    // le o L_byte da porta paralela (8 bits)
  outparallel(890,195); 
  return (H_byte + L_byte);
}



__int64 CComunicacoes::ler_porta_paralela2(int endereco)
{
 int H_byte,M_byte,L_byte,M1_byte;
 
 outparallel (890,198); 
 outparallel(890,238);
 
 H_byte=inparallel(endereco) << 24;   // le o H_byte da porta paralela(8 bits) 
 
 outparallel(890,234);
 M_byte=inparallel(endereco) << 16;   // le o M_byte da porta paralela(8 bits) 

 outparallel(1016+4,0);
 L_byte=inparallel(endereco);   // le o L_byte da porta paralela(8 bits) 
 outparallel(1016+4,3);
 
 outparallel(890,238);
 M1_byte=inparallel(endereco) << 8;   // le o M_byte da porta paralela(8 bits)  

 outparallel(890,195);
 return(H_byte+M_byte+M1_byte+L_byte);
}

/*  Antiga versao		***/
 /*__int64 H_byte,M_byte,L_byte,M1_byte;
 
 outparallel (890,198); 

 setPortCBit(5,1,890); // modo de leitura  
 setPortCBit(3,1,890); 
 //H_byte=inparallel(endereco) << 24;   // le o M_byte da porta paralela(8 bits) 
 

 //printf("\nH_byte=%d\n",H_byte >> 24); 
 setPortCBit(2,0,890); 
 M_byte=inparallel(endereco) << 8;   // le o M_byte da porta paralela(8 bits) 
 
//printf("\nM_byte=%d\n",M_byte >> 16); 
 setPortCBit(1,0,890);
 setPortCBit(0,1,890);
 
 L_byte=inparallel(endereco);   // le o H_byte da porta paralela(8 bits) 
 
 //printf("\nL_byte=%d\n",L_byte); 
 //setPortCBit(2,1,890); //REtirado

 //M1_byte=inparallel(endereco) << 16;   // le o M_byte da porta paralela(8 bits)  
 
//printf("\nM1_byte=%d\n",M1_byte >> 8); 
 setPortCBit(3,0,890);
 setPortCBit(5,0,890); // anula modo leitura
 outparallel(890,195);*/
// return(/*H_byte+*/M_byte/*+M1_byte*/+L_byte);
//}



//funcao que escreve na porta paralela um valor dado o endereco da porta,
//o endereco do motor e se estamos em modo escrita(escrita_leitura=1)
//ou modo leitura(escrita_leitura=0)
void CComunicacoes::escrever(int endereco,int valor,int endereco_motor,int escrita_leitura)
{
 conversor_endereco(endereco_motor,escrita_leitura,0);
 escrever_porta_paralela(endereco,valor);
}


// le o H_byte(8 bits)-> atraves dos 8 bits de data
// le o L_byte(4 bits)-> atraves dos bits de status
// dados o endereco donde e lido o H_byte, o endereco do sensor
//e se estamos em modo escrita(escrita_leitura=1) ou modo leitura(escrita_leitura=0)
// devolve o valor lido em decimal entre 0..4095
__int64 CComunicacoes::ler(int endereco,int endereco_sensor,int escrita_leitura,int sensor_vp)
{ 
int leitura;
int passa = 0;

 conversor_endereco(endereco_sensor,escrita_leitura,sensor_vp); 
 if (sensor_vp==0) 
 {
	while (!passa)
	{
		leitura = (int)ler_porta_paralela1(endereco);
		if (leitura < (int) 4095) passa=1;
		else 
		{ 
			fprintf (com,"Bloquei no endereco = %d\t%d\n",endereco_sensor,leitura);
			for (int u=1;u<=10;u++) ler (1912,u,1,0);
		};	
		//passa=1;
	};		
	return (leitura);
 }
    else return (ler_porta_paralela2(endereco));

}



//inicializa a porta paralela e as variáveis de controlo
void CComunicacoes::inicializacoes(void)
{
 mapDeviceToPort(2,0x778,8); //porto 1912 = 0x778 com 8 offsets disponiveis
 mapDeviceToPort(3,0x3F8,8); //porto 1016 = 0x3F8 com 8 offsets disponiveis
for (int i=0;i<5;i++)
		printf ("%x\n",getPortAddress(i));

 
 outparallel(890,193);
 outparallel(890,195);
 outparallel(890,193);
 outparallel(890,195);

 outparallel(1914,104);
 outparallel(890,195);
 
 escrever(1912,2048,1,0);
 escrever(1912,2048,2,0);
 escrever(1912,2048,3,0);
 escrever(1912,2048,4,0);
 escrever(1912,2048,5,0);
 escrever(1912,2048,6,0);

 outparallel (1016+3,80); /* Activa bit DLAB */
 outparallel (1016,1); /* Baud (Divisor Latch - LSB) 0x0C = 9600 */
 outparallel (1016+1,0); /* Baud (Divisor Latch - MSB) */
 outparallel (1016+3,3); /* 8 bits, paridade desligada, 1 stop bit */
 outparallel (1016+1,0); // Desliga interrupcoes 
 outparallel (1016+2,7);
 outparallel (1016+4,0); 
}






