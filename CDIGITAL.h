#ifndef CDIGITAL_H
#define CDIGITAL_H

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
#define MAX 100000			// Numero maximo de amostras suportadas
#define MAX_N_PASSADAS 50	// Numero maximo de passadas a suportar pelo controlador
#define N_NIVEIS_DIGITAIS_ERRO_POSICAO 50 // Numero maximo de erro digital para a colocacao do robot numa postura determinada anteriormente
#define MAX_VELOCIDADE_POSTURA 500  // Velocidade maxima para colocacao do robot numa postura determinada anteriormente
#define N_JUNTAS 6					// Numero de graus de liberdade do robot
#define tam_max 30					// Tamanho maximo dos nomes dos ficheiros de entrada
#define HISTERESE_INCREMENTO 300	// Utilizacao de uma histerese no controlador (antiga versão)
#define Ka 40						// Ganho do dead-Time
#define pi  3.1415926535897			// Constante pi
//		Simulacao dos termos graviticos
#define m1 0.2						// Massa do troço 1 
#define m2 0.35						// Massa do troço 2
#define l1 0.15						// Comprimento do troço 1		
#define l2 0.15						// Comprimento do troço 2
#define G 9.86						// Constante da aceleracao da gravidade


struct Expressao_posicao
{
	float x1,x2,y1,y2;  // Coordenadas polares de dois pontos (angulo (x) -> nivel digital (y))
	float m;			// Declive da recta		
	float b;			// Coordenada na origem
};

#include "Ccomunicacoes.h"


class CComandaRobot{
public:
	CComandaRobot( int , 
				   LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR,
				   LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR,
				   LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR,
				   LPCTSTR , LPCTSTR , LPCTSTR , LPCTSTR , 
				   FILE *  , FILE *,
				   float *);
	~CComandaRobot();
	void IncrementaNAmostras(void);
	void DecrementaNAmostras(void);
	int  NAmostras(void);
	int  AmostraActual(void);
	void ProcessaJuntaGlobalPosicao(int);
	void ProcessaJuntaIndividualPosicao(int,int);
	void ProcessaJuntaGlobalVelocidade(int);
	void ProcessaJuntaIndividualVelocidade(int,int);
	void FuncaoCaracteristicaServo(int,int);
	void PosturaInicial(int);
	int  NPassadaActual(void);
	void inicializar_actuadores(void);
	BOOL FimAmostragem(void);

	BOOL UltrapassouTempoPassada(void);
	int  Aquisicao_Sensores_Contacto(void);
	int IncrementaNumeroPassada(void);
	BOOL CorrectaNoChao(int);

	BOOL UltrapassouAmplitudePassada(void);
	void AjusteRotacaoBase(void);
	void GuardarValoresCorrectivos(void);
	double TempoActual(void);
	int DevolveVelocidadeMedida(int);
	void Carregamento_Offset(void);
	
protected:
	void Fechar_ficheiros(void);
	void Controlador_PI_digital_velocidade(int);
	void Controlador_P_digital_velocidade(int);
	void Controlador_PD_digital_velocidade(int);
	void Controlador_PID_digital_velocidade(int);
	void Controlador_P_digital_posicao(int);
	void Controlador_PI_digital_posicao(int);
	void Controlador_PD_digital_posicao(int);
	void Controlador_PID_digital_posicao(int);
	void Saturacao_Actuacoes(void);
	void Actuacao_robot(int);
	void Leitura_estado_robot(int);
	void Actuacao_Pe_perna2(int);
	void Actuacao_Joelho_perna2(int);
	void Actuacao_Anca_perna2(int);
	void Actuacao_Pe_perna1(int);
	void Actuacao_Joelho_perna1(int);
	void Actuacao_Anca_perna1(int);
	int  Aquisicao_Posicao_Pe_perna2(void);
	int  Aquisicao_Posicao_Joelho_perna2(void);
	int  Aquisicao_Posicao_Anca_perna2(void);
	int  Aquisicao_Posicao_Pe_perna1(void);
	int  Aquisicao_Posicao_Joelho_perna1(void);
	int  Aquisicao_Posicao_Anca_perna1(void);
	int  Aquisicao_Velocidade_Pe_perna2(void);
	int  Aquisicao_Velocidade_Joelho_perna2(void);
	int  Aquisicao_Velocidade_Anca_perna2(void);
	int  Aquisicao_Velocidade_Pe_perna1(void);
	int  Aquisicao_Velocidade_Joelho_perna1(void);
	int  Aquisicao_Velocidade_Anca_perna1(void);
	void carregamento_ganhos(float*);
	int  le_ficheiro (int,int);
	int  carregamento_trajectorias_juntas(void);
	void Transformacao_referencias_entradas(void);
	void TransformacaoRPM_RPS_juntas(void);
	void Criacao_relacao_posicao(void);
	void Apresenta_referencias_digitais(void);
	void Guarda_informacao_interpolacao(int);
	void saida(void);
	void Carregamento_n_passadas(void);
	void ApresentaIncrementos(FILE *);	
	void conversao_binario(BYTE converter);
	float PosicaoJuntaEmGraus(int,int);
	double ConverteDouble(void);
	__int64 ConverterLeitura(__int64);
	int filtra(int);
	int PosicaoJuntaEmDigitais(int,int);
	float VelocidadeJuntaEmGraus(int,int);
	int Le_canal(int junta,int canal);

	int ForaIntervalo(int,int);
	int DeadZone(int);
	float ConverteRadsSeg(int,int);

	int Satura_Actuacao(int);
	float PosicaoJuntaEmRads(int,int);

	int Trajectoria_teste(void);

	
	
	int amostra_actual;					// numero da amostra actual
	int Perna_chao;						// Informacao relativa a qual a perna em contacto com o chao em cada instante
	int NIVEL_DIGITAL_ACTUACAO_MINIMO;  // Nivel de actuacao minimo a que deve ser efectuada a saturacao negativa
	int NIVEL_DIGITAL_ACTUACAO_MAXIMO;	// Nivel de actuacao maximo a que deve ser efectuada a saturacao positiva
	int valor_referencia;				// Referencia de 12 bits
	float velocidades_maximas_junta[N_JUNTAS+1]; // Vector com as velocidades maximas admissiveis por cada actuador
	Expressao_posicao Expressoes_posicao_junta[N_JUNTAS+1];
	int Sentido_Rotacao_pos[N_JUNTAS+1];	//  Vector do sinal do sentido de rotacao de cada actuador em posicao
	int Sentido_Rotacao_vel[N_JUNTAS+1];	//  Vector do sinal do sentido de rotacao de cada actuador em velocidade
	int n_amostras;					//  numero de amostras total a interpolar
	float Frequencia_amostragem;	//  Frequencia de amostragem em Hertz
	float h;						//  Periodo de amostragem
	float clock;					//  Frequencia do sinal de clock de contagem
	char devolver[9];				//  String com o valor binario convertido
	int total_n_passadas;			//  Numero total de passadas a efectuar nesta interpolacao
	int passada_actual;				//  Numero da passada actual 
	int perna_assente_chao;			//  Perna que devera estar assente no chao em cada passada
	int perna_a_comecar_locomocao;	//  Perna que deve ser colocada em primeiro lugar
	int perna2_a_comecar_locomocao;	//  Perna a colocar na locomocao em segundo lugar
	int AmplitudeMaximaPassada;		//  Amplitude maxima que as juntas da anca devem suportar
	int KCompensacao;				//  Ganho da compensacao gravitica


	FILE *Sinais_medidos_Posicao;		//  Ficheiro com os valores medidos em posicao de junta
	FILE *Sinais_erro_Posicao;			//  Ficheiro com os valores de erro em posicao por junta
	FILE *Sinais_medidos_Velocidade;	//  Ficheiro com os valores medidos em velocidade de junta
	FILE *Sinais_erro_Velocidade;		//  Ficheiro com os valores de erro em velocidade por junta 
	FILE *Sinais_actuados;				//  Niveis de actuacao por junta
	FILE *ficheiro_debug;				//  Ficheiro para guardar informacao relativa a todos os acontecimentos da interpolacao
	FILE *ficheiro_pe_chao;				//  Ficheiro para guardar informacao relativa a interaccao do robot com o chao
	

	/***********   Nomes dos ficheiros com trajectoria de velocidade por junta      **********************************/
	char *Fich_Veljunta1;
	char *Fich_Veljunta2;
	char *Fich_Veljunta3;
	char *Fich_Veljunta4;
	char *Fich_Veljunta5;
	char *Fich_Veljunta6;

	/***********   Nomes dos ficheiros com trajectoria de posicao por junta      **********************************/
	char *Fich_Posjunta1; 
	char *Fich_Posjunta2; 
	char *Fich_Posjunta3; 
	char *Fich_Posjunta4;
	char *Fich_Posjunta5;
	char *Fich_Posjunta6;

	/***********   Nome do ficheiro com a informacao relativa ao numero de cada passada em cada instante   **/
	char *Fich_n_passadas;
	
	/***********  Nomes dos ficheiros de saida com a informacao relativa aos valores a interoplar     ****/
	char *Fich_REFPOS;
	char *Fich_REFVEL;

	/**********    Tabelas de armazenamento da informacao relevante       **************************/
	float GANHOS_CONTROLADOR[N_JUNTAS+1][5];			//  Ganhos a utilizar no controlador
	float Tempo_Passadas[MAX_N_PASSADAS];	//  Tempo de inicio de cada uma das passadas

/*+  Informacao instantanea  (para cada amostra da interpolacao)+*/
	int Posicao_juntas[N_JUNTAS+1];
	int Velocidade_juntas[N_JUNTAS+1];
	int Sinal_actuacao_controlador[N_JUNTAS+1];
	int Sinal_actuacao_controlador4[N_JUNTAS+1];

	int Actuacao_anterior[N_JUNTAS+1];
	int Actuacao_anterior4[N_JUNTAS+1];

	unsigned long int Erro_anterior_vel[N_JUNTAS+1];
	int Erro_anterior_pos[N_JUNTAS+1];
	int Erro_actual_pos[N_JUNTAS+1];
	unsigned long int Erro_actual_vel[N_JUNTAS+1];
	int Erro_anterior_pos2[N_JUNTAS+1];
	int Erro_anterior_pos3[N_JUNTAS+1];
	unsigned long int Erro_anterior_vel2[N_JUNTAS+1];
	int Posicoes_ajuste_postura[N_JUNTAS+1];
	double valor_anterior[3],valor_anterior2[3];
	
	float Erro_anterior_pos_rad[N_JUNTAS+1];
	float Erro_actual_pos_rad[N_JUNTAS+1];
	float Erro_anterior_pos2_rad[N_JUNTAS+1];

	float angulos_junta[N_JUNTAS+1];

	float Compensacao_Gravitica;

/*++++  Informacao para toda a interpolacao    +*/
	/*	1..6 - Junta  **/
	float Veljunta[MAX][N_JUNTAS+1];
	float Posjunta[MAX][N_JUNTAS+1];

	float Posicao_junta_ant[N_JUNTAS+1];
	float Posicao_junta_ant2[N_JUNTAS+1];

	int incremento[N_JUNTAS+1];
	int Offset[N_JUNTAS+1];



	FILE *temporario;			// Ficheiro de saida temporario para debug
	CComunicacoes *Comunica;	// Canal de comunicacoes com o robot

};

#endif

