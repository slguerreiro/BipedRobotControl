#ifndef PI_C_DIGITAL_H
#define PI_C_DIGITAL_H


#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <GL/glaux.h>
#include <GL/glu.h>
#include "stdio.h"
#include "math.h"
#include <conio.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Aquisicao.h"
#include "Actuacao.h"

//#include "BibliotecasIO"
#define MAX 5000


class CComandaRobot{
public:
	CComandaRobot();
	~CComandaRobot();
	void carregamento_ganhos(void);
	int le_ficheiro (int PosVel,int n_junta);
	int carregamento_trajectorias_juntas(void);
	void Transformacao_referencias_entradas(void);
	void inicializar_actuadores(void);
	void Actuacao_robot(void);
	void Controlador_PI_digital_completo(int amostra);
	void Controlador_PI_digital(int amostra);
	void Saturacao_Actuacoes(void);
	void Leitura_estado_robot(void);
	void Calculo(void);

protected:
	#define NIVEL_DIGITAL_ACTUACAO_MINIMO 10
	#define NIVEL_DIGITAL_ACTUACAO_MAXIMO 4090
	#define valor_referencia 3072		// Referencia de 12 bits
	int n_amostras;

	float Frequencia_amostragem;	// Frequencia de amostragem em Hertz
	/***********   Nomes dos ficheiros com trajectoria de velocidade por junta      **********************************/
	#define Fich_Veljunta1 "SIMULACAO_VEL_JUNTA1"
	#define Fich_Veljunta2 "SIMULACAO_VEL_JUNTA2"
	#define Fich_Veljunta3 "SIMULACAO_VEL_JUNTA3"
	#define Fich_Veljunta4 "SIMULACAO_VEL_JUNTA4"
	#define Fich_Veljunta5 "SIMULACAO_VEL_JUNTA5"
	#define Fich_Veljunta6 "SIMULACAO_VEL_JUNTA6"

	/***********   Nomes dos ficheiros com trajectoria de posicao por junta      **********************************/
	#define Fich_Posjunta1 "Teta1"
	#define Fich_Posjunta2 "Teta2"
	#define Fich_Posjunta3 "Teta3"
	#define Fich_Posjunta4 "Teta4"
	#define Fich_Posjunta5 "Teta5"
	#define Fich_Posjunta6 "Teta6"

	/**********    Tabelas de armazenamento da informacao relevante       **************************/
	float GANHOS_CONTROLADOR[7][5];
	int Posicao_juntas[7];
	int Velocidade_juntas[7];
	int Sinal_actuacao_controlador[7];
	int Actuacao_anterior[7];
	int Erro_anterior[7];
	

	float Veljunta1[MAX][2];
	float Veljunta2[MAX][2];
	float Veljunta3[MAX][2];
	float Veljunta4[MAX][2];
	float Veljunta5[MAX][2];
	float Veljunta6[MAX][2];

	float Posjunta1[MAX][2];
	float Posjunta2[MAX][2];
	float Posjunta3[MAX][2];
	float Posjunta4[MAX][2];
	float Posjunta5[MAX][2];
	float Posjunta6[MAX][2];



	/********   ficheiros de saida    ************************************/
	FILE *ficheiro,*erro;	
};

	

/**************************************************************************************************************/
/***  Ganhos dos Termos proporcionais, integrativos e derivativos do controlador PID					      */
/***  linha = numero do actuador																			  */
/***  coluna 0 = Kp																							  */
/***  coluna 1 = Ti																							  */
/***  coluna 2 = Td																							  */
/***  coluna 3 = Ganho do controlo de posicao																  */
/***  coluna 4 = Ganho do controlo de velocidade															  */
/***            Carregamento dos sinais de erro e de actuacao iniciais										  */
/**************************************************************************************************************/
void CComandaRobot::carregamento_ganhos(void)
{
	// Ganhos Controlador PID da junta 1
	GANHOS_CONTROLADOR[1][0]=(float) 100;
	GANHOS_CONTROLADOR[1][1]=(float) 0.2;	
	GANHOS_CONTROLADOR[1][2]=(float) 2;
	GANHOS_CONTROLADOR[1][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[1][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 2
	GANHOS_CONTROLADOR[2][0]=(float) 100;
	GANHOS_CONTROLADOR[2][1]=(float) 0.2;	
	GANHOS_CONTROLADOR[2][2]=(float) 2;
	GANHOS_CONTROLADOR[2][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[2][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 3
	GANHOS_CONTROLADOR[3][0]=(float) 100;
	GANHOS_CONTROLADOR[3][1]=(float) 0.2;	
	GANHOS_CONTROLADOR[3][2]=(float) 2;
	GANHOS_CONTROLADOR[3][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[3][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 4
	GANHOS_CONTROLADOR[4][0]=(float) 100;
	GANHOS_CONTROLADOR[4][1]=(float) 0.2;	
	GANHOS_CONTROLADOR[4][2]=(float) 2;
	GANHOS_CONTROLADOR[4][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[4][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 5
	GANHOS_CONTROLADOR[5][0]=(float) 100;
	GANHOS_CONTROLADOR[5][1]=(float) 0.2;	
	GANHOS_CONTROLADOR[5][2]=(float) 2;
	GANHOS_CONTROLADOR[5][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[5][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 6
	GANHOS_CONTROLADOR[6][0]=(float) 100;
	GANHOS_CONTROLADOR[6][1]=(float) 0.2;	
	GANHOS_CONTROLADOR[6][2]=(float) 2;
	GANHOS_CONTROLADOR[6][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[6][4]=(float) 2;  // kvelocidade

	for (int i=1;i<7;i++) Actuacao_anterior[i]=(int)0;


    Erro_anterior[1]=valor_referencia;
	
	/***** Seguimento das trajectorias pretendidas  (Controlo em velocidade) *****/
	/*  //  Quando controlo total = somado Posicao_referencia + Velociadde_referencia(controlo total)
	Erro_anterior[1]=Posjunta1[0][1];
	Erro_anterior[2]=Posjunta2[0][1];
	Erro_anterior[3]=Posjunta3[0][1];
	Erro_anterior[4]=Posjunta4[0][1];
	Erro_anterior[5]=Posjunta5[0][1];
	Erro_anterior[6]=Posjunta6[0][1];
  */

};



/**************************************************************************************************************/
/*  Leitura de um ficheiro e respectivo armazenamento da informacao em memoria
/*  PosVel=1    sensor de posicao
/*	PosVel=2    sensor de velocidade 
/*  n_junta     Numero de junta
/**************************************************************************************************************/
int CComandaRobot::le_ficheiro (int PosVel,int n_junta)
{
	int linha=0,status=-2,n_am;
	float inf;
 	FILE *tmp;
	char *ficheiro_aberto;

	if (PosVel==1 && n_junta==1) { tmp = fopen(Fich_Posjunta1, "r"); ficheiro_aberto=Fich_Posjunta1;} 
	if (PosVel==1 && n_junta==2) { tmp = fopen(Fich_Posjunta2, "r"); ficheiro_aberto=Fich_Posjunta2;}
	if (PosVel==1 && n_junta==3) { tmp = fopen(Fich_Posjunta3, "r"); ficheiro_aberto=Fich_Posjunta3;}
	if (PosVel==1 && n_junta==4) { tmp = fopen(Fich_Posjunta4, "r"); ficheiro_aberto=Fich_Posjunta4;}
	if (PosVel==1 && n_junta==5) { tmp = fopen(Fich_Posjunta5, "r"); ficheiro_aberto=Fich_Posjunta5;}
	if (PosVel==1 && n_junta==6) { tmp = fopen(Fich_Posjunta6, "r"); ficheiro_aberto=Fich_Posjunta6;}
	if (PosVel==2 && n_junta==1) { tmp = fopen(Fich_Veljunta1, "r"); ficheiro_aberto=Fich_Veljunta1;}
	if (PosVel==2 && n_junta==2) { tmp = fopen(Fich_Veljunta2, "r"); ficheiro_aberto=Fich_Veljunta2;}
	if (PosVel==2 && n_junta==3) { tmp = fopen(Fich_Veljunta3, "r"); ficheiro_aberto=Fich_Veljunta3;}
	if (PosVel==2 && n_junta==4) { tmp = fopen(Fich_Veljunta4, "r"); ficheiro_aberto=Fich_Veljunta4;}
	if (PosVel==2 && n_junta==5) { tmp = fopen(Fich_Veljunta5, "r"); ficheiro_aberto=Fich_Veljunta5;}
	if (PosVel==2 && n_junta==6) { tmp = fopen(Fich_Veljunta6, "r"); ficheiro_aberto=Fich_Veljunta6;}
	

	if ( tmp == NULL )
	{  
		printf( "O ficheiro %s nao foi aberto\n",ficheiro_aberto);
		exit(-1);
	}
	else  
	{ while (status!=EOF)
		{ 
			for (int y=0;y<2;y++) 
			{ 
			  status=fscanf(tmp, "%f", &inf );
			  if (status!= EOF) 
			  {
				  if (PosVel==1 && n_junta==1) Posjunta1[linha][y]=inf;
				  if (PosVel==1 && n_junta==2) Posjunta2[linha][y]=inf;
				  if (PosVel==1 && n_junta==3) Posjunta3[linha][y]=inf;
				  if (PosVel==1 && n_junta==4) Posjunta4[linha][y]=inf;
				  if (PosVel==1 && n_junta==5) Posjunta5[linha][y]=inf;
				  if (PosVel==1 && n_junta==6) Posjunta6[linha][y]=inf;
				  if (PosVel==2 && n_junta==1) Veljunta1[linha][y]=inf;
				  if (PosVel==2 && n_junta==2) Veljunta2[linha][y]=inf;
				  if (PosVel==2 && n_junta==3) Veljunta3[linha][y]=inf;
				  if (PosVel==2 && n_junta==4) Veljunta4[linha][y]=inf;
				  if (PosVel==2 && n_junta==5) Veljunta5[linha][y]=inf;
				  if (PosVel==2 && n_junta==6) Veljunta6[linha][y]=inf;
			  }
			}
			linha++;
		}
	if (PosVel==1 && n_junta==1) Posjunta1[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==2) Posjunta2[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==3) Posjunta3[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==4) Posjunta4[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==5) Posjunta5[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==6) Posjunta6[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==1) Veljunta1[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==2) Veljunta2[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==3) Veljunta3[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==4) Veljunta4[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==5) Veljunta5[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==6) Veljunta6[linha-1][0]=(float) -1;
	fclose( tmp );
   };
   n_am=linha-2;
   return (n_am);
}



/**************************************************************************************************************/
/****  Leitura dos ficheiros correspondentes as velocidades e posicoes de junta ao longo do tempo		     **/
/**************************************************************************************************************/
int CComandaRobot::carregamento_trajectorias_juntas(void)
{ 
	int n_amostras1,n_amostras2,n_amostras3,n_amostras4,n_amostras5,n_amostras6,n_amostras7,n_amostras8,n_amostras9,n_amostras10;
	int n_amostras11,n_amostras12;

	
	n_amostras1=le_ficheiro(1,1);
	n_amostras2=le_ficheiro(1,2);
	n_amostras3=le_ficheiro(1,3);
	n_amostras4=le_ficheiro(1,4);
	n_amostras5=le_ficheiro(1,5);
	n_amostras6=le_ficheiro(1,6);
	n_amostras7=le_ficheiro(2,1);
	n_amostras8=le_ficheiro(2,2);
	n_amostras9=le_ficheiro(2,3);
	n_amostras10=le_ficheiro(2,4);
	n_amostras11=le_ficheiro(2,5);
	n_amostras12=le_ficheiro(2,6);

/********  Verificacao de tamanho constante dos ficheiros    ***********************************************/
	if ( n_amostras1==n_amostras2  && n_amostras2==n_amostras3   &&
		 n_amostras3==n_amostras4  && n_amostras4==n_amostras5   &&
		 n_amostras5==n_amostras6  && n_amostras6==n_amostras7   &&
		 n_amostras7==n_amostras8  && n_amostras8==n_amostras9   &&
		 n_amostras9==n_amostras10 && n_amostras10==n_amostras11 &&
		 n_amostras11==n_amostras12 )  
	return (n_amostras1);
    else
	{
		printf ("Os ficheiros não tem todos a mesma dimensao\n");
		exit (-1);
		return (0);
	};
};



/**************************************************************************************************************/
/***  Passagem das referencias de graus e graus/segundo para niveis digitais								***/
/**************************************************************************************************************/
void CComandaRobot::Transformacao_referencias_entradas(void)
{

}




/**************************************************************************************************************/
/*  Inicializacao dos motores para uma velocidade de rotacao nula
/**************************************************************************************************************/
void CComandaRobot::inicializar_actuadores(void)
{
	Actuacao_Pe_perna2((int) 2048);
	Actuacao_Joelho_perna2((int) 2048);
	Actuacao_Anca_perna2((int) 2048);
	Actuacao_Pe_perna1((int) 2048);
	Actuacao_Joelho_perna1((int) 2048);
	Actuacao_Anca_perna1((int) 2048);
}


void CComandaRobot::Calculo(void)
{
	double a=34567834510.6348734,b=10453894593.3434586345345,c,d;
	for (int i=1;i<1000;i++) c=a+b;
	for (i=1;i<1000;i++) d=c*b;
	for (i=1;i<1000;i++) c=cos(d)*sin(a)*sin(b);
}


/**************************************************************************************************************/
/***             Aquisicao do estado dos sensores de posicao e velocidade de todas as juntas do robot      ****/
/**************************************************************************************************************/
void CComandaRobot::Leitura_estado_robot(void)
{
	Posicao_juntas[1]=Aquisicao_Posicao_Pe_perna2();
	Posicao_juntas[2]=Aquisicao_Posicao_Joelho_perna2();
	Posicao_juntas[3]=Aquisicao_Posicao_Anca_perna2();
	Posicao_juntas[4]=Aquisicao_Posicao_Pe_perna1();
	Posicao_juntas[5]=Aquisicao_Posicao_Joelho_perna1();
	Posicao_juntas[6]=Aquisicao_Posicao_Anca_perna1();
	Velocidade_juntas[1]=Aquisicao_Velocidade_Pe_perna2();
	Velocidade_juntas[2]=Aquisicao_Velocidade_Joelho_perna2();
	Velocidade_juntas[3]=Aquisicao_Velocidade_Anca_perna2();
	Velocidade_juntas[4]=Aquisicao_Velocidade_Pe_perna1();
	Velocidade_juntas[5]=Aquisicao_Velocidade_Joelho_perna1();
	Velocidade_juntas[6]=Aquisicao_Velocidade_Anca_perna1();
}


/**************************************************************************************************************/
/***		Satura o sinal de actuacao aos niveis maximos e minimos										   ****/
/**************************************************************************************************************/
void CComandaRobot::Saturacao_Actuacoes(void)
{
	for (int i=1;i<7;i++)
	{
		if (Sinal_actuacao_controlador[i] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
			         Sinal_actuacao_controlador[i]=NIVEL_DIGITAL_ACTUACAO_MINIMO;

		else if (Sinal_actuacao_controlador[i] > NIVEL_DIGITAL_ACTUACAO_MAXIMO)
					 Sinal_actuacao_controlador[i]=NIVEL_DIGITAL_ACTUACAO_MAXIMO;

	}
};




void CComandaRobot::Controlador_PI_digital(int amostra)
{
	int erro_actual;

	// Calculo do erro
	erro_actual=valor_referencia-Velocidade_juntas[1];  // Controlo de Velocidade
	//erro_actual=valor_referencia-Posicao_juntas[1];  // Controlo de Posicao
  
	// Calculo do sinal de controlo
	Sinal_actuacao_controlador[1] = Actuacao_anterior[1] +
									(GANHOS_CONTROLADOR[1][0] * (float)erro_actual) -
									(GANHOS_CONTROLADOR[1][0] * Erro_anterior[1]) +														
									(GANHOS_CONTROLADOR[1][0] * (((float)1/Frequencia_amostragem)/GANHOS_CONTROLADOR[1][1]) * Erro_anterior[1]);
						
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior[1]=erro_actual;
	Actuacao_anterior[1]=Sinal_actuacao_controlador[1];

}


/**************************************************************************************************************/
/**** Controlador PI digital por junta, mantem as referencias da SIMULACAO									***/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PI_digital_completo(int amostra)
{
	int erro_actual[7];

	// Calculo dos erros de posicao
	erro_actual[1]=Posjunta1[amostra][1]-Posicao_juntas[1];
	erro_actual[2]=Posjunta2[amostra][1]-Posicao_juntas[1];
	erro_actual[3]=Posjunta3[amostra][1]-Posicao_juntas[1];
	erro_actual[4]=Posjunta4[amostra][1]-Posicao_juntas[1];
	erro_actual[5]=Posjunta5[amostra][1]-Posicao_juntas[1];
	erro_actual[6]=Posjunta6[amostra][1]-Posicao_juntas[1];

	// Calculo dos sinais de controlo
	for (int i=1;i<7;i++) 
	{
		Sinal_actuacao_controlador[i] = Actuacao_anterior[i] +
									(GANHOS_CONTROLADOR[i][0] * (float)erro_actual[i]) -
									(GANHOS_CONTROLADOR[i][0] * Erro_anterior[i]) +														
									(GANHOS_CONTROLADOR[i][0] * (((float)1/Frequencia_amostragem)/GANHOS_CONTROLADOR[i][1]) * Erro_anterior[i]);
	}

	// Guardar valores para proximo passo da interpolacao
	for (i=1;i<7;i++) Erro_anterior[i]=erro_actual[i];
	for (i=1;i<7;i++) Actuacao_anterior[i]=Sinal_actuacao_controlador[i];
}



/**************************************************************************************************************/
/***   Actuacao das juntas do robot com o sinal obtido pelo controlador									   ****/
/**************************************************************************************************************/
void CComandaRobot::Actuacao_robot(void)
{
	Saturacao_Actuacoes();

//	printf ("\n%d",Sinal_actuacao_controlador[1]);
	Actuacao_Pe_perna2(Sinal_actuacao_controlador[1]);
	Actuacao_Joelho_perna2(Sinal_actuacao_controlador[2]);
	Actuacao_Anca_perna2(Sinal_actuacao_controlador[3]);
	Actuacao_Pe_perna1(Sinal_actuacao_controlador[4]);
	Actuacao_Joelho_perna1(Sinal_actuacao_controlador[5]);
	Actuacao_Anca_perna1(Sinal_actuacao_controlador[6]);
}


#endif

void main(void)
{
	struct _timeb inicio_interpolacao;
	struct _timeb fim_interpolacao;

	struct _timeb inicio;
	struct _timeb fim;

	int duration;
	int duration_millis;
	int hora_antes,hora_depois,minutos_antes,minutos_depois,segundos_antes,segundos_depois;
	char *timeline;



// inicializacoes();			// Inicializacoes da porta paralela
//inicializar_actuadores();  // Inicializacao de todas as juntas a velocidade de rotacao nula
 n_amostras=carregamento_trajectorias_juntas(); //Carregamento das trajectorias de cada junta 
 Transformacao_referencias_entradas();  // Transformacao das referencias
 carregamento_ganhos();		// Carregamento dos ganhos de cada controlador PID de cada junta

 ficheiro=fopen("medidaPI","w");
 erro=fopen("erroPI","w");

 
 Frequencia_amostragem=200;
  //printf ("%g\n\n",(float) ((1/Frequencia_amostragem)*1000));



 /***********************  INICIO DO CICLO DE INTERPOLACAO         **********************************************/
 _ftime (&inicio_interpolacao);
 for (int h=0;h<=n_amostras;h++)
 {

	Leitura_estado_robot();
	Controlador_PI_digital(h);
	Actuacao_robot();
	
 }
 _ftime (&fim_interpolacao);
/***********************  FIM DO CICLO DE INTERPOLACAO         **********************************************/





 inicializar_actuadores();

 /**** Apresentacao do tempo total de interpolacao   *****/ 
 duration_millis=fim_interpolacao.millitm-inicio_interpolacao.millitm;
 if (duration_millis < 0.0) duration_millis=(1000+fim_interpolacao.millitm)-inicio_interpolacao.millitm;
 
 timeline = ctime( & ( inicio_interpolacao.time ) );		
 printf( "\nThe time is %.19s.%hu %s", timeline, inicio_interpolacao.millitm, &timeline[20] );
 hora_antes=atoi(&timeline[11]);
 minutos_antes=atoi(&timeline[14]);
 segundos_antes=atoi(&timeline[17]);

 timeline = ctime( & ( fim_interpolacao.time ) );		
 printf( "The time is %.19s.%hu %s", timeline, fim_interpolacao.millitm, &timeline[20] );
 hora_depois=atoi(&timeline[11]);
 minutos_depois=atoi(&timeline[14]);
 segundos_depois=atoi(&timeline[17]);


 printf ("\n%d %d",hora_antes,hora_depois);
 printf ("  %d %d",minutos_antes,minutos_depois);
 printf ("  %d %d",segundos_antes,segundos_depois);

 printf( "\nTEMPO PROCESSAMENTO TOTAL DE INTERPOLACAO: %g miliseconds\n", (double)duration_millis );
  

 fclose(ficheiro);
 fclose (erro);
 

} // EOF