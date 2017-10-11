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


#include "ecp_funcoes.h"
#include "ecp_funcoes.cpp"

#define MAX 5000


struct Expressao_posicao
{
	float x1,x2,y1,y2;  // Coordenadas polares de dois pontos (angulo (x) -> nivel digital (y))
	float m;			// Declive da recta		
	float b;			// Coordenada na origem
};


class CComandaRobot{
public:
	CComandaRobot();
	~CComandaRobot();
	void carregamento_ganhos(void);
	int le_ficheiro (int PosVel,int n_junta);
	int carregamento_trajectorias_juntas(void);
	void Transformacao_referencias_entradas(void);
	void inicializar_actuadores(void);
	void Actuacao_robot(int junta);
	void Controlador_PI_digital_completo(int amostra);
	void Controlador_PI_digital(int amostra,int junta);
	void Saturacao_Actuacoes(void);
	void Leitura_estado_robot(int junta);
	void Actuacao_Pe_perna2(int valor_digital);
	void Actuacao_Joelho_perna2(int valor_digital);
	void Actuacao_Anca_perna2(int valor_digital);
	void Actuacao_Pe_perna1(int valor_digital);
	void Actuacao_Joelho_perna1(int valor_digital);
	void Actuacao_Anca_perna1(int valor_digital);
	int Aquisicao_Posicao_Pe_perna2(void);
	int Aquisicao_Posicao_Joelho_perna2(void);
	int Aquisicao_Posicao_Anca_perna2(void);
	int Aquisicao_Posicao_Pe_perna1(void);
	int Aquisicao_Posicao_Joelho_perna1(void);
	int Aquisicao_Posicao_Anca_perna1(void);
	int Aquisicao_Velocidade_Pe_perna2(void);
	int Aquisicao_Velocidade_Joelho_perna2(void);
	int Aquisicao_Velocidade_Anca_perna2(void);
	int Aquisicao_Velocidade_Pe_perna1(void);
	int Aquisicao_Velocidade_Joelho_perna1(void);
	int Aquisicao_Velocidade_Anca_perna1(void);
	void TransformacaoRPM_RPS_juntas(void);
	void Criacao_relacao_posicao(void);
	void Apresenta_referencias_digitais(void);
	void ProcessaJunta(int n_junta);
	void IncrementaNAmostras(void);
	int NAmostras(void);



protected:
	
	void Fechar_ficheiros(void);
	
	int amostra_actual;					// numero da amostra actual
	int NIVEL_DIGITAL_ACTUACAO_MINIMO;
	int NIVEL_DIGITAL_ACTUACAO_MAXIMO;
	int valor_referencia;				// Referencia de 12 bits
	float velocidades_maximas_junta[7];
	Expressao_posicao Expressoes_posicao_junta[7];
	int n_amostras;					// numero de amostras total a interpolar
	float Frequencia_amostragem;	// Frequencia de amostragem em Hertz

	FILE *Sinais_medidos_Posicao;  //Ficheiro com os valores medidos em posicao de junta
	FILE *Sinais_erro_Posicao;	  //Ficheiro com os valores de erro em posicao por junta
	FILE *Sinais_medidos_Velocidade;  //Ficheiro com os valores medidos em velocidade de junta
	FILE *Sinais_erro_Velocidade;     //Ficheiro com os valores de erro em velocidade por junta 
	
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

/*+  Informacao instantanea  +*/
	int Posicao_juntas[7];
	int Velocidade_juntas[7];
	int Sinal_actuacao_controlador[7];
	int Actuacao_anterior[7];
	int Erro_anterior[7];
	
/*++++  Informacao para toda a interpolacao    +*/
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
};

	
#include "Aquisicao.h"
#include "Actuacao.h"
//#include "Calculodigital.h"

#endif

