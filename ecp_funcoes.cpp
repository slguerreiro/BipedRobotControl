#include "ecp_funcoes.h"



int z,y;


void outparallel(int address,int data)
{
	int mystatus;
	
//	printf ("\n adress=%x data=%d",address,(USHORT)data);
	if (address >= 0x778)	
	{
		address=address-0x778;
		Poke8( (USHORT) 2, (USHORT) address,(USHORT) data,&mystatus);
	}
	else if (address >= 0x378) 
	{
		address=address-0x378;
		Poke8( (USHORT) 0, (USHORT) address,(USHORT) data,&mystatus);
	}

	//printf ("\n erro=%d",mystatus);
//	printf (" offset=%d",address);
};


int inparallel(int address)
{
	int mystatus,rtn;

	//printf ("\n adress=%x",address);
	if (address >= 0x778)	
	{
		address=address-0x778;
		rtn=Peek8( (USHORT) 2, (USHORT) address,&mystatus);
	}
	else if (address >= 0x378) 
	{
		address=address-0x378;
		rtn=Peek8( (USHORT) 0, (USHORT) address,&mystatus);
	}
	//printf ("\n erro=%d",mystatus);
	//printf (" offset=%d",address);
	return (rtn);
};





void setPortCBit(char n, int v, int IO_PORT) // funcao que faz o enable ou
{                               // o disable de qualquer bit
								// do port IO_PORT
   if(v) outparallel(IO_PORT,inparallel(IO_PORT)|  (0x1<<n));
   else  outparallel(IO_PORT,inparallel(IO_PORT)& ~(0x1<<n));
}



//funcao que recebe um valor decimal entre 0..4095
// e manda para o endereco de saida ->  6 bits de cada vez (H_byte e L_byte)
void escrever_porta_paralela(int endereco,int valor)
{
 setPortCBit(1,0,890);
 setPortCBit(1,1,890);
 outparallel(endereco,valor >> 6);
 outparallel(endereco,valor);
 setPortCBit(2,1,890);
 setPortCBit(1,0,890);
 setPortCBit(1,1,890);
 setPortCBit(2,0,890);
 setPortCBit(3,1,890);
 setPortCBit(1,0,890);
 setPortCBit(1,1,890);
 setPortCBit(3,0,890);
}


//funcao que faz a multiplexagem dos valores escritos e lidos para a porta paralela
//escrita_leitura=0 -> modo escrita -> faz o mux do motor que vai ser escrito
//escrita_leitura=1 -> modo leitura -> faz o mux do sensor que vai ser lido
void conversor_endereco(int endereco_mux,int escrita_leitura,int sensor_vp)
{
 int v,p,maior7;

 v=1;p=1;
 if (endereco_mux>7) {maior7=1;endereco_mux=endereco_mux-8;}
	else maior7=0;
 if (escrita_leitura==1&&sensor_vp==1) {v=0;p=1;}
	else if (escrita_leitura==1&&sensor_vp==0) {v=1;p=0;}
		else {v=1;p=1;}
 setPortCBit(1,0,890);
 setPortCBit(1,1,890);
 outparallel(1912,endereco_mux+(v << 4)+(p << 3)+(maior7 << 5));
 setPortCBit(1,0,890);
 setPortCBit(0,0,890);
 setPortCBit(0,1,890);
 setPortCBit(1,1,890); 
}




__int64 ler_porta_paralela1(int endereco)
{
 __int64 H_byte,L_byte;
 clock_t goal;
 

  setPortCBit(5,1,890); // modo de leitura  
  setPortCBit(3,1,890); 
  goal = 0.00004 + clock();
  while( goal > clock() );
  setPortCBit(2,1,890); 
  H_byte=inparallel(endereco) << 4;  // le o H_byte da porta paralela(4 bits) 
  L_byte=((inparallel(889) >> 3)-16);    // le o L_byte da porta paralela (8 bits)
  setPortCBit(3,0,890);
  setPortCBit(5,0,890); // anula modo leitura
  outparallel(890,195);
  return (H_byte + L_byte);
}


__int64 ler_porta_paralela2(int endereco)
{
 __int64 H_byte,M_byte,L_byte,M1_byte;
 
 outparallel (890,198); 
 setPortCBit(5,1,890); // modo de leitura  
 setPortCBit(3,1,890); 

 H_byte=inparallel(endereco) << 24;   // le o M_byte da porta paralela(8 bits) 
 //printf("\nH_byte=%d\n",H_byte >> 24); 
 setPortCBit(2,0,890); 
 
 M_byte=inparallel(endereco) << 16;   // le o M_byte da porta paralela(8 bits) 
//printf("\nM_byte=%d\n",M_byte >> 16); 
 setPortCBit(1,0,890);
 setPortCBit(0,1,890);
 L_byte=inparallel(endereco);   // le o H_byte da porta paralela(8 bits) 
 //printf("\nL_byte=%d\n",L_byte); 
 setPortCBit(2,1,890); 

 M1_byte=inparallel(endereco) << 8;   // le o M_byte da porta paralela(8 bits)  
//printf("\nM1_byte=%d\n",M1_byte >> 8); 
 setPortCBit(3,0,890);
 setPortCBit(5,0,890); // anula modo leitura
 outparallel(890,195);
 return(H_byte+M_byte+M1_byte+L_byte);
}

//funcao que escreve na porta paralela um valor dado o endereco da porta,
//o endereco do motor e se estamos em modo escrita(escrita_leitura=1)
//ou modo leitura(escrita_leitura=0)
void escrever(int endereco,int valor,int endereco_motor,int escrita_leitura)
{
 conversor_endereco(endereco_motor,escrita_leitura,0);
 escrever_porta_paralela(endereco,valor);
}


// le o H_byte(8 bits)-> atraves dos 8 bits de data
// le o L_byte(4 bits)-> atraves dos bits de status
// dados o endereco donde e lido o H_byte, o endereco do sensor
//e se estamos em modo escrita(escrita_leitura=1) ou modo leitura(escrita_leitura=0)
// devolve o valor lido em decimal entre 0..4095
__int64 ler(int endereco,int endereco_sensor,int escrita_leitura,int sensor_vp)
{ 
 int valor1,valor2;
 int ok;


 while (ok)
 {
   conversor_endereco(endereco_sensor,escrita_leitura,sensor_vp); 
  if (sensor_vp==0) 
  {
	  valor1=ler_porta_paralela1(endereco);
      if (valor1!=4095) ok=0;
  }
  else {valor2=ler_porta_paralela2(endereco); /*if (valor2!=65535&&valor2>1000)*/ ok=0;}
 }
 if (sensor_vp==0) return (valor1);
 else return (valor2);

}


//inicializa a porta paralela e as variáveis de controlo
void inicializacoes(void)
{
 mapDeviceToPort(2,0x778,8); //porto 1912 = 0x778 com 8 offsets disponiveis
for (int i=0;i<5;i++)
		printf ("%x\n",getPortAddress(i));
 setPortCBit(1,0,890);
 setPortCBit(1,1,890);
 setPortCBit(1,0,890);
 setPortCBit(1,1,890);
 outparallel(1914,104);
 outparallel(890,195);
 escrever(1912,2048,1,0);
 escrever(1912,2048,2,0);
 escrever(1912,2048,3,0);
 escrever(1912,2048,4,0);
 escrever(1912,2048,5,0);
 escrever(1912,2048,6,0);

}
