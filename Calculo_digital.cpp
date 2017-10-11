#include "stdafx.h"
#include "CDIGITAL.h"



/******************************************************************************************/
/****  Constructor do Robot																***/
/******************************************************************************************/
CComandaRobot::CComandaRobot ( int frq_amostragem
							 , LPCTSTR fich_pos1 , LPCTSTR fich_pos2 , LPCTSTR fich_pos3 , LPCTSTR fich_pos4 , LPCTSTR fich_pos5 , LPCTSTR fich_pos6
							 , LPCTSTR fic_vel1 , LPCTSTR fic_vel2 , LPCTSTR fic_vel3 , LPCTSTR fic_vel4 , LPCTSTR fic_vel5 , LPCTSTR fic_vel6							 
							 , LPCTSTR fic_mdposjun , LPCTSTR fic_errposjun , LPCTSTR fic_mdveljun , LPCTSTR fic_errveljun , LPCTSTR fic_rfposdig , LPCTSTR fic_rfveldig							 
							 , LPCTSTR fic_actuacao , LPCTSTR fic_passadas , LPCTSTR fic_refposdig, LPCTSTR fic_refveldig
							 , FILE *fich_pe_chao, FILE *fich_debug 
							 , float *Tabela_param)
{

 temporario=fopen("temporario","w");


 Fich_Posjunta1  =  new char [tam_max]; strcpy(Fich_Posjunta1,fich_pos1);
 Fich_Posjunta2  =  new char [tam_max]; strcpy(Fich_Posjunta2,fich_pos2);
 Fich_Posjunta3  =  new char [tam_max]; strcpy(Fich_Posjunta3,fich_pos3);
 Fich_Posjunta4  =  new char [tam_max]; strcpy(Fich_Posjunta4,fich_pos4);
 Fich_Posjunta5  =  new char [tam_max]; strcpy(Fich_Posjunta5,fich_pos5);
 Fich_Posjunta6  =  new char [tam_max]; strcpy(Fich_Posjunta6,fich_pos6);
 Fich_Veljunta1  =  new char [tam_max]; strcpy(Fich_Veljunta1,fic_vel1);
 Fich_Veljunta2  =  new char [tam_max]; strcpy(Fich_Veljunta2,fic_vel2);
 Fich_Veljunta3  =  new char [tam_max]; strcpy(Fich_Veljunta3,fic_vel3);
 Fich_Veljunta4  =  new char [tam_max]; strcpy(Fich_Veljunta4,fic_vel4);
 Fich_Veljunta5  =  new char [tam_max]; strcpy(Fich_Veljunta5,fic_vel5);
 Fich_Veljunta6  =  new char [tam_max]; strcpy(Fich_Veljunta6,fic_vel6);
 Fich_n_passadas =  new char [tam_max]; strcpy(Fich_n_passadas,fic_passadas);
 Fich_REFPOS	 =  new char [tam_max];	strcpy(Fich_REFPOS,fic_refposdig);
 Fich_REFVEL	 =  new char [tam_max]; strcpy(Fich_REFVEL,fic_refveldig);
 Sinais_medidos_Posicao    = fopen (fic_mdposjun,"w");
 Sinais_erro_Posicao       = fopen (fic_errposjun,"w");
 Sinais_medidos_Velocidade = fopen (fic_mdveljun,"w");
 Sinais_erro_Velocidade    = fopen (fic_errveljun,"w");
 Sinais_actuados           = fopen (fic_actuacao,"w");
 
 ficheiro_debug=fich_debug;
 ficheiro_pe_chao=fich_pe_chao;
 fprintf (ficheiro_debug,"Criacao do Robot...Inicializacoes\n");
	
	/**** Carregamento das variaveis de estado do sistema   *****/
 NIVEL_DIGITAL_ACTUACAO_MINIMO=(int)Tabela_param[51];
 NIVEL_DIGITAL_ACTUACAO_MAXIMO=(int)Tabela_param[50];

/**  Carregar o valor de Frequencia - via ficheiro  */
 Frequencia_amostragem=(float) frq_amostragem;
 h=(float)1/(Frequencia_amostragem);
 clock=(float) Tabela_param[70];
 AmplitudeMaximaPassada = (int) Tabela_param[71];
 perna_assente_chao = (int) Tabela_param[69];
 perna_a_comecar_locomocao = perna_assente_chao;
 if (perna_a_comecar_locomocao == 1) perna2_a_comecar_locomocao = 2;
 else perna2_a_comecar_locomocao = 1;

 fprintf(ficheiro_debug,"(Periodo de amostragem) h=%g segundos\n",h);
 fprintf(ficheiro_debug,"Perna a comecar a locomocao = %d\n",perna_a_comecar_locomocao);
 fprintf(ficheiro_debug,"Amplitude Maxima de cada passada = %d [graus]\n",AmplitudeMaximaPassada);

 //velocidade para o nivel de actuacao 4095 ou 1 (em !!rpm!!)
 velocidades_maximas_junta[1]=(float)Tabela_param[52];
 velocidades_maximas_junta[2]=(float)Tabela_param[53];
 velocidades_maximas_junta[3]=(float)Tabela_param[54];
 velocidades_maximas_junta[4]=(float)Tabela_param[55];
 velocidades_maximas_junta[5]=(float)Tabela_param[56];
 velocidades_maximas_junta[6]=(float)Tabela_param[57];
 //  Colocacao de 2 pontos de controlo por junta para calculo da relacao (posicao angular -> nivel digital)
 Expressoes_posicao_junta[1].x1=(float)0;	//graus
 Expressoes_posicao_junta[1].x2=(float)90;
 Expressoes_posicao_junta[1].y1=(float)1191;	//niveis digitais
 Expressoes_posicao_junta[1].y2=(float)2237;

 Expressoes_posicao_junta[2].x1=(float)0;	//graus
 Expressoes_posicao_junta[2].x2=(float)-90;
 Expressoes_posicao_junta[2].y1=(float)1066;	//niveis digitais
 Expressoes_posicao_junta[2].y2=(float)220;

 Expressoes_posicao_junta[3].x1=(float)90;	//graus
 Expressoes_posicao_junta[3].x2=(float)0;
 Expressoes_posicao_junta[3].y1=(float)2320;	//niveis digitais
 Expressoes_posicao_junta[3].y2=(float)1189;

 Expressoes_posicao_junta[4].x1=(float)90;	//graus
 Expressoes_posicao_junta[4].x2=(float)0;
 Expressoes_posicao_junta[4].y1=(float)2300;	//niveis digitais
 Expressoes_posicao_junta[4].y2=(float)1172;

 Expressoes_posicao_junta[5].x1=(float)-90;	//graus
 Expressoes_posicao_junta[5].x2=(float)0;
 Expressoes_posicao_junta[5].y1=(float)426;	//niveis digitais
 Expressoes_posicao_junta[5].y2=(float)1192;

 Expressoes_posicao_junta[6].x1=(float)90;	//graus
 Expressoes_posicao_junta[6].x2=(float)0;
 Expressoes_posicao_junta[6].y1=(float)194;	//niveis digitais
 Expressoes_posicao_junta[6].y2=(float)1026;

 valor_anterior[1]=0;
 valor_anterior[2]=0;
 valor_anterior2[1]=0;
 valor_anterior2[2]=0;


 amostra_actual=0;
 passada_actual=0;

 Sentido_Rotacao_pos[1]=-1;
 Sentido_Rotacao_pos[2]=-1;
 Sentido_Rotacao_pos[3]=+1;

 Sentido_Rotacao_pos[4]=+1;
 Sentido_Rotacao_pos[5]=+1;
 Sentido_Rotacao_pos[6]=-1; 


 Sentido_Rotacao_vel[1]=+1;
 Sentido_Rotacao_vel[2]=+1; //?
 Sentido_Rotacao_vel[3]=+1; 
 Sentido_Rotacao_vel[4]=+1; 
 Sentido_Rotacao_vel[5]=-1; //?
 Sentido_Rotacao_vel[6]=+1; 

 KCompensacao=1500;
 

 Comunica = new CComunicacoes(); // Criacao do canal de comunicacao com o robot
 inicializar_actuadores();  // Inicializacao de todas as juntas a velocidade de rotacao nula
 TransformacaoRPM_RPS_juntas();  // Transformacao dos limites maximos de velocidade
 Criacao_relacao_posicao();  // Calculo das rectas lineares de posicao vs niveis digitais
 n_amostras=carregamento_trajectorias_juntas(); //Carregamento das trajectorias de cada junta 
// n_amostras=Trajectoria_teste();
 Transformacao_referencias_entradas();  // Transformacao das referencias em posicao e velocidade em niveis digitais
 Apresenta_referencias_digitais();  // Apresentacao dos resultados obtidos na transformacao de referencias
 Carregamento_n_passadas();    // Carregamento do numero de passadas efectuadas em cada instante
 ApresentaIncrementos(ficheiro_debug);  // Apresentacao dos incrementos digitais por grau e vice-versa
 carregamento_ganhos(Tabela_param);  // Carregamento dos ganhos introduzidos pelo Dialog Based
 
 for (int i=1;i<=6;i++) // Inicializacao do vector de ajustes de postura
	Posicoes_ajuste_postura[i] = (int) (Expressoes_posicao_junta[i].b);

};


/******************************************************************************************/
/***	Cria referencia de teste para verificacao da adequacao do controlo				***/
/***	Criacao de referencias em velocidade e posicao em graus							***/
/******************************************************************************************/
int CComandaRobot::Trajectoria_teste(void)
{


	return(-1);
};


/******************************************************************************************/
/***	Calibracao dos offsets dos sinais dos encoders									***/
/******************************************************************************************/
void CComandaRobot::Carregamento_Offset(void)
{
 Offset[1]=2048;
 Offset[3]=2048;
 Offset[4]=2048;
 Offset[6]=2048;



 __int64 Velocidades_Encoders[5];
 int tmp,tmp2;
 int n_encoders=400;

 for (tmp=1 ;tmp <=4 ;tmp++) Velocidades_Encoders[tmp]=0;
 for (tmp=1;tmp<=n_encoders;tmp++)
 {
	inicializar_actuadores();
	Velocidades_Encoders[1]+=Aquisicao_Velocidade_Pe_perna2();
	Velocidades_Encoders[2]+=Aquisicao_Velocidade_Anca_perna2() ;
	Velocidades_Encoders[3]+=Aquisicao_Velocidade_Pe_perna1();
	Velocidades_Encoders[4]+=Aquisicao_Velocidade_Anca_perna1();
 }

 
 for (tmp2=1;tmp2<=4;tmp2++) 
 {
	 Velocidades_Encoders[tmp2]=(int)((float)Velocidades_Encoders[tmp2]/(float)n_encoders);
	 fprintf (ficheiro_debug,"Media da velocidade da junta %d = %d\n",tmp2,Velocidades_Encoders[tmp2]);
 }

 
 Offset[1]=(int)Velocidades_Encoders[1];
 Offset[3]=(int)Velocidades_Encoders[2];
 Offset[4]=(int)Velocidades_Encoders[3];
 Offset[6]=(int)Velocidades_Encoders[4];
}



/**************************************************************************************************************/
/***								  Destructor do robot						**/
/**************************************************************************************************************/
CComandaRobot::~CComandaRobot() 
{
	inicializar_actuadores();
	Fechar_ficheiros();
	fprintf(ficheiro_debug,"Fim de Robot...Destructor\n");
	delete Comunica;
};


/**************************************************************************************************************/
/*****				  Carrega instante inicial de cada passada						***/
/**************************************************************************************************************/
void CComandaRobot::Carregamento_n_passadas(void)
{
	FILE * tmp;
	int status=-2,status2=-2;
	float inf1,inf2;
		
	
	total_n_passadas=-1;
	tmp=fopen (Fich_n_passadas,"r");
	if ( tmp == NULL )
	{  
		fprintf (ficheiro_debug,"O ficheiro %s nao foi aberto\n",Fich_n_passadas);
		saida();
	}
	else  
	{ 
		fprintf (ficheiro_debug,"Ficheiro aberto=%s\n",Fich_n_passadas);
		fprintf (ficheiro_debug,"Carregamento do instante inicial de cada passada\n");
		while (status!=EOF || status2!=EOF)
		{ 
				status=fscanf(tmp,"%f",&inf1);
				status2=fscanf(tmp,"%f",&inf2);	
				if (status!=EOF && status2!=2 && inf2 > total_n_passadas)
				{
					Tempo_Passadas[++total_n_passadas]=inf1;
					fprintf (ficheiro_debug,"  Tempo = %g [segundos] --> Passada num.= %d\n",inf1,total_n_passadas);
				}
		}
	Tempo_Passadas[++total_n_passadas]=(float) -1;
	}
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
void CComandaRobot::carregamento_ganhos(float *ganhos)
{
	// Ganhos Controlador PID da junta 1
	GANHOS_CONTROLADOR[1][0]=(float) ganhos[1];
	GANHOS_CONTROLADOR[1][1]=(float) ganhos[2];
	GANHOS_CONTROLADOR[1][2]=(float) ganhos[3];
	GANHOS_CONTROLADOR[1][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[1][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 2
	GANHOS_CONTROLADOR[2][0]=(float) ganhos[4];
	GANHOS_CONTROLADOR[2][1]=(float) ganhos[5];	
	GANHOS_CONTROLADOR[2][2]=(float) ganhos[6];
	GANHOS_CONTROLADOR[2][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[2][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 3
	GANHOS_CONTROLADOR[3][0]=(float) ganhos[7];
	GANHOS_CONTROLADOR[3][1]=(float) ganhos[8];	
	GANHOS_CONTROLADOR[3][2]=(float) ganhos[9];
	GANHOS_CONTROLADOR[3][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[3][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 4
	GANHOS_CONTROLADOR[4][0]=(float) ganhos[10];
	GANHOS_CONTROLADOR[4][1]=(float) ganhos[11];	
	GANHOS_CONTROLADOR[4][2]=(float) ganhos[12];
	GANHOS_CONTROLADOR[4][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[4][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 5
	GANHOS_CONTROLADOR[5][0]=(float) ganhos[13];
	GANHOS_CONTROLADOR[5][1]=(float) ganhos[14];	
	GANHOS_CONTROLADOR[5][2]=(float) ganhos[15];
	GANHOS_CONTROLADOR[5][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[5][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 6
	GANHOS_CONTROLADOR[6][0]=(float) ganhos[16];
	GANHOS_CONTROLADOR[6][1]=(float) ganhos[17];	
	GANHOS_CONTROLADOR[6][2]=(float) ganhos[18];
	GANHOS_CONTROLADOR[6][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[6][4]=(float) 2;  // kvelocidade

	fprintf (ficheiro_debug,"Parametros do Controlador....\n");
	for (int j=1;j<=N_JUNTAS;j++)
	{	fprintf (ficheiro_debug,"Junta %d --> ",j);
		fprintf (ficheiro_debug,"  Kp = %g\n",GANHOS_CONTROLADOR[j][0]);
		fprintf (ficheiro_debug,"\t      Ti = %g segundos\tKi = %g\n",GANHOS_CONTROLADOR[j][1],(GANHOS_CONTROLADOR[j][0])/(GANHOS_CONTROLADOR[j][1]));
		fprintf (ficheiro_debug,"\t      Td = %g segundos\tKd = %g\n",GANHOS_CONTROLADOR[j][2],(GANHOS_CONTROLADOR[j][0])/(GANHOS_CONTROLADOR[j][2]));
	};

	/***  Inicializacoes dos erros e das actuacoes iniciais   **/
	fprintf (ficheiro_debug,"Inicializacao do erro e da actuacao iniciais...\n");
	for (int i=1;i<=N_JUNTAS;i++) {
				Actuacao_anterior[i] = (int) 0;
				Actuacao_anterior4[i] = (int) 0;
				Erro_anterior_vel[i] = (unsigned long int) 0;
				Erro_anterior_pos[i] = 0;
				Erro_anterior_vel2[i]= (unsigned long int) 0;
				Erro_anterior_pos2[i]= 0;
				//Erro_anterior_pos3[i]= (unsigned long int) (Posjunta[0][i]-0);
				Erro_anterior_pos_rad[i]=(float)0;
				Erro_anterior_pos2_rad[i]=(float)0;
				incremento[i]=0;
	};
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
		fprintf(ficheiro_debug,"O ficheiro %s nao foi aberto\n",ficheiro_aberto);
		saida();
	}
	else  
	{ 
		fprintf(ficheiro_debug,"Ficheiro aberto=%s\n",ficheiro_aberto);
		while (status!=EOF)
		{ 
			for (int y=0;y<2;y++) 
			{ 
			  status=fscanf(tmp, "%f", &inf );
			  if (status!=EOF && y==0 && PosVel==1) Posjunta[linha][0]=inf;
			  if (status!=EOF && y==0 && PosVel==2) Veljunta[linha][0]=inf;
			  else if (status!= EOF) 
			  {
				  if (PosVel==1 && n_junta==1) Posjunta[linha][1]=inf;
				  if (PosVel==1 && n_junta==2) Posjunta[linha][2]=inf;
				  if (PosVel==1 && n_junta==3) Posjunta[linha][3]=inf;
				  if (PosVel==1 && n_junta==4) Posjunta[linha][4]=inf;
				  if (PosVel==1 && n_junta==5) Posjunta[linha][5]=inf;
				  if (PosVel==1 && n_junta==6) Posjunta[linha][6]=inf;
				  if (PosVel==2 && n_junta==1) Veljunta[linha][1]=inf;
				  if (PosVel==2 && n_junta==2) Veljunta[linha][2]=inf;
				  if (PosVel==2 && n_junta==3) Veljunta[linha][3]=inf;
				  if (PosVel==2 && n_junta==4) Veljunta[linha][4]=inf;
				  if (PosVel==2 && n_junta==5) Veljunta[linha][5]=inf;
				  if (PosVel==2 && n_junta==6) Veljunta[linha][6]=inf;
			  }
			}
			linha++;
		}
	if (PosVel==1 && n_junta==1) Posjunta[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==2) Posjunta[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==3) Posjunta[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==4) Posjunta[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==5) Posjunta[linha-1][0]=(float) -1;
	if (PosVel==1 && n_junta==6) Posjunta[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==1) Veljunta[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==2) Veljunta[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==3) Veljunta[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==4) Veljunta[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==5) Veljunta[linha-1][0]=(float) -1;
	if (PosVel==2 && n_junta==6) Veljunta[linha-1][0]=(float) -1;
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
		fprintf (ficheiro_debug,"Os ficheiros de entrada não tem todos a mesma dimensao\n");
		saida();
		return (0);
	};
};


/**************************************************************************************************************/
/**** Calcula os coeficientes da recta de posicao angular vs niveis digitais								***/
/**************************************************************************************************************/
void CComandaRobot::Criacao_relacao_posicao(void)
{
	for (int e=1;e<=N_JUNTAS;e++)
	{
		
		Expressoes_posicao_junta[e].m = (Expressoes_posicao_junta[e].y2-Expressoes_posicao_junta[e].y1)/
									    (Expressoes_posicao_junta[e].x2-Expressoes_posicao_junta[e].x1);
		Expressoes_posicao_junta[e].b = (-Expressoes_posicao_junta[e].m * Expressoes_posicao_junta[e].x1) +
											Expressoes_posicao_junta[e].y1;
	}

	fprintf (ficheiro_debug,"Criacao das Relacoes de Posicao:\n");
	for (e=1;e<=N_JUNTAS;e++)
	{
		fprintf (ficheiro_debug,"\t JUNTA %d --> y [nivel digital] = %g * x [graus] + %g\n",e,Expressoes_posicao_junta[e].m,Expressoes_posicao_junta[e].b);
	}
}


/**************************************************************************************************************/
/**  Transformacao das velocidades de junta maximas em rpm para graus/segundo								**/
/**************************************************************************************************************/
void CComandaRobot::TransformacaoRPM_RPS_juntas(void)
{
	fprintf (ficheiro_debug,"Criacao das Relacoes de Velocidade (Velocidades Maximas Admissiveis):\n");
	for (int r=1;r<=N_JUNTAS;r++) {velocidades_maximas_junta[r]=(velocidades_maximas_junta[r]/60)*360;
	fprintf (ficheiro_debug,"\tJUNTA %d --> %g rps = %g [graus/s]= %g rpm\n",r,velocidades_maximas_junta[r]/360,velocidades_maximas_junta[r],(velocidades_maximas_junta[r]/360)*60);}
}


/**************************************************************************************************************/
/***  Passagem das referencias de graus e graus/segundo para niveis digitais								***/
/**************************************************************************************************************/
void CComandaRobot::Transformacao_referencias_entradas(void)
{ int r=0;
  

	/**  Transformacao de velocidades  ***/
		 while (Veljunta[r][0]!=-1) 
			{ 
				Veljunta[r][1]=2048-( (2048*Veljunta[r][1])/velocidades_maximas_junta[1] ); 
				if (Veljunta[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 1 excedida em %g niveis no instante %g segundos",Veljunta[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta[r][0]);
						saida();
					};
				if (Veljunta[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 1 excedida em %g niveis no instante %g segundos",-Veljunta[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta[r][0]);
						saida();
					};
				r++;
			};
	r=0; while (Veljunta[r][0]!=-1) 
			{ 
				Veljunta[r][2]=2048+( (2048*Veljunta[r][2])/velocidades_maximas_junta[2] ); 
				if (Veljunta[r][2] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 2 excedida em %g niveis no instante %g segundos",Veljunta[r][2]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta[r][0]);
						saida();
					};
				if (Veljunta[r][2] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 2 excedida em %g niveis no instante %g segundos",-Veljunta[r][2]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta[r][0]);
						saida();
					};
				r++;
			}
	r=0; while (Veljunta[r][0]!=-1) 
			{ 
				Veljunta[r][3]=2048+( (2048*Veljunta[r][3])/velocidades_maximas_junta[3] ); 
				if (Veljunta[r][3] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 3 excedida em %g niveis no instante %g segundos",Veljunta[r][3]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta[r][0]);
						saida();
					};
				if (Veljunta[r][3] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 3 excedida em %g niveis no instante %g segundos",-Veljunta[r][3]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta[r][0]);
						saida();					
					};
				r++;
			}
	r=0; while (Veljunta[r][0]!=-1) 
			{ 
				
				Veljunta[r][4]=2048+( (2048*Veljunta[r][4])/velocidades_maximas_junta[4] ); 
				if (Veljunta[r][4] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 4 excedida em %g niveis no instante %g segundos",Veljunta[r][4]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta[r][0]);
						saida();
					};
				if (Veljunta[r][4] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 4 excedida em %g niveis no instante %g segundos",-Veljunta[r][4]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta[r][0]);
						saida();
					};
				r++;
			}
	r=0; while (Veljunta[r][0]!=-1) 
			{ 
				
				Veljunta[r][5]=2048+( (2048*Veljunta[r][5])/velocidades_maximas_junta[5] ); 
				if (Veljunta[r][5] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 5 excedida em %g niveis no instante %g segundos",Veljunta[r][5]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta[r][0]);
						saida();
					};
				if (Veljunta[r][5] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 5 excedida em %g niveis no instante %g segundos",-Veljunta[r][5]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta[r][0]);
						saida();
					};
				r++;
			}
	r=0; while (Veljunta[r][0]!=-1) 
			{ 
		
				Veljunta[r][6]=2048-( (2048*Veljunta[r][6])/velocidades_maximas_junta[6] ); 
				if (Veljunta[r][6] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 6 excedida em %g niveis no instante %g segundos",Veljunta[r][6]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta[r][0]);
						saida();
					};
				if (Veljunta[r][6] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						fprintf (ficheiro_debug,"Velocidade da Junta 6 excedida em %g niveis no instante %g segundos",-Veljunta[r][6]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta[r][0]);
						saida();
					};
				r++;
			}	

	/**  Transformacao de posicoes  ***/
	r=0; while (Posjunta[r][0]!=-1) {	Posjunta[r][1]=(Posjunta[r][1]*Expressoes_posicao_junta[1].m) + Expressoes_posicao_junta[1].b;r++;}
	r=0; while (Posjunta[r][0]!=-1) {	Posjunta[r][2]=(Posjunta[r][2]*Expressoes_posicao_junta[2].m) + Expressoes_posicao_junta[2].b;r++;}
	r=0; while (Posjunta[r][0]!=-1) {	Posjunta[r][3]=(Posjunta[r][3]*Expressoes_posicao_junta[3].m) + Expressoes_posicao_junta[3].b;r++;}
	r=0; while (Posjunta[r][0]!=-1) {	Posjunta[r][4]=(Posjunta[r][4]*Expressoes_posicao_junta[4].m) + Expressoes_posicao_junta[4].b;r++;}
	r=0; while (Posjunta[r][0]!=-1) {	Posjunta[r][5]=(Posjunta[r][5]*Expressoes_posicao_junta[5].m) + Expressoes_posicao_junta[5].b;r++;}
	r=0; while (Posjunta[r][0]!=-1) {	Posjunta[r][6]=(Posjunta[r][6]*Expressoes_posicao_junta[6].m) + Expressoes_posicao_junta[6].b;r++;}
};


/**************************************************************************************************************/
/***	Devolve a posicao em graus para uma dada posicao em niveis digitais									***/
/**************************************************************************************************************/
float CComandaRobot::PosicaoJuntaEmGraus(int junta,int nivel_digital)
{
	return ( ( (nivel_digital - Expressoes_posicao_junta[junta].b) 
		            / (Expressoes_posicao_junta[junta].m)) );
}

/**************************************************************************************************************/
/***	Devolve a posicao em radianos para uma dada posicao em niveis digitais								***/
/**************************************************************************************************************/
float CComandaRobot::PosicaoJuntaEmRads(int junta,int nivel_digital)
{
		return ( ((float)PosicaoJuntaEmGraus(junta,nivel_digital)*(float)pi)/(float)180.0);
}


/**************************************************************************************************************/
/***	Devolve a posicao em digitais para uma dada posicao em niveis digitais								***/
/**************************************************************************************************************/
int  CComandaRobot::PosicaoJuntaEmDigitais(int junta,int graus)
{
	return ((int)(   (Expressoes_posicao_junta[junta].m*graus)+Expressoes_posicao_junta[junta].b));
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

/**************************************************************************************************************/
/***             Aquisicao do estado dos sensores de posicao e velocidade de todas as juntas do robot      ****/
/**************************************************************************************************************/
void CComandaRobot::Leitura_estado_robot(int junta)
{
	if (junta==1)
	{	Posicao_juntas[1]=Aquisicao_Posicao_Pe_perna2();
		Velocidade_juntas[1]=Aquisicao_Velocidade_Pe_perna2();}
	else if (junta==2)	
	{	Posicao_juntas[2]=Aquisicao_Posicao_Joelho_perna2();
		Velocidade_juntas[2]=Aquisicao_Velocidade_Joelho_perna2();}
	else if (junta==3)
	{	Posicao_juntas[3]=Aquisicao_Posicao_Anca_perna2();
		Velocidade_juntas[3]=Aquisicao_Velocidade_Anca_perna2();}
	else if (junta==4)
	{	Posicao_juntas[4]=Aquisicao_Posicao_Pe_perna1();
		Velocidade_juntas[4]=Aquisicao_Velocidade_Pe_perna1();}
	else if (junta==5)
	{	Posicao_juntas[5]=Aquisicao_Posicao_Joelho_perna1();
		Velocidade_juntas[5]=Aquisicao_Velocidade_Joelho_perna1();}
	else if (junta==6)
	{	Posicao_juntas[6]=Aquisicao_Posicao_Anca_perna1();
		Velocidade_juntas[6]=Aquisicao_Velocidade_Anca_perna1();}
}


/**************************************************************************************************************/
/***		Satura os sinais de actuacao aos niveis maximos e minimos									   ****/
/**************************************************************************************************************/
void CComandaRobot::Saturacao_Actuacoes(void)
{
	for (int i=1;i<=N_JUNTAS;i++)
		Sinal_actuacao_controlador[i] = Satura_Actuacao (Sinal_actuacao_controlador[i]);
};


/**************************************************************************************************************/
/***		Satura um sinal ao nivel de actuacao maximo e minimo										*******/
/**************************************************************************************************************/
int CComandaRobot::Satura_Actuacao(int actuacao)
{
	if (actuacao < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
		return (NIVEL_DIGITAL_ACTUACAO_MINIMO);

	else if (actuacao > NIVEL_DIGITAL_ACTUACAO_MAXIMO)
		return (NIVEL_DIGITAL_ACTUACAO_MAXIMO);			

	else return (actuacao);
};


/**************************************************************************************************************/
/****	Filtra o sinal de erro																			*******/
/**************************************************************************************************************/
int CComandaRobot::filtra(int nivel_actuacao)
{
	if (nivel_actuacao > (NIVEL_DIGITAL_ACTUACAO_MAXIMO/2)) return(NIVEL_DIGITAL_ACTUACAO_MAXIMO/2);
	else if (nivel_actuacao < -(NIVEL_DIGITAL_ACTUACAO_MAXIMO/2)) return(-(NIVEL_DIGITAL_ACTUACAO_MAXIMO/2));
		else return(nivel_actuacao);

};


/**************************************************************************************************************/
/***	Converte de niveis digitais para radianos por segundo											*******/
/**************************************************************************************************************/
float CComandaRobot::ConverteRadsSeg(int junta,int n_digital)
{
	return((float)(VelocidadeJuntaEmGraus(junta,n_digital)*pi/(180.0)));
};

/**************************************************************************************************************/
/**** Controlador P digital por junta, mantem as referencias da SIMULACAO									***/
/***** Controlo em posicao																					**/
/****		junta ==  numero da junta a interpolar															**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_P_digital_posicao(int junta)
{
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 

	Sinal_actuacao_controlador[junta] = (int) (GANHOS_CONTROLADOR[junta][0] * (float)Erro_actual_pos[junta]) ;
											  
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta] * Sentido_Rotacao_pos[junta]);
	// Guardar valores para proximo passo da interpolacao
}

/**************************************************************************************************************/
/**** Controlador PI digital por junta, mantem as referencias da SIMULACAO									***/
/***** Controlo em posicao																					**/
/****		junta ==  numero da junta a interpolar									**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PI_digital_posicao(int junta)
{
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 

	Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										(GANHOS_CONTROLADOR[junta][0] * (float)Erro_actual_pos[junta]) -
										(GANHOS_CONTROLADOR[junta][0] * (float)Erro_anterior_pos[junta]) +
										(GANHOS_CONTROLADOR[junta][0] * h / GANHOS_CONTROLADOR[junta][1] * (float)Erro_anterior_pos[junta] )
										);
		
	Actuacao_anterior[junta]=Sinal_actuacao_controlador[junta];
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta] * Sentido_Rotacao_pos[junta]);
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior_pos[junta]=Erro_actual_pos[junta];
}

/**************************************************************************************************************/
/**** Controlador PD digital por junta, mantem as referencias da SIMULACAO									***/
/***** Controlo em posicao																					**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PD_digital_posicao(int junta)
{
	Erro_actual_pos[junta] = ((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 
	Erro_actual_vel[junta] = ((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 

	/*if (( abs(Erro_actual_pos[junta] - Erro_anterior_pos[junta])
		  + abs(incremento[junta])
		) < HISTERESE_INCREMENTO) 
	{
		incremento[junta] = Erro_actual_pos[junta] - Erro_anterior_pos[junta];	
		Erro_actual_pos[junta] = Erro_anterior_pos[junta];
	}
	else 
	{
		Erro_actual_pos[junta] += incremento[junta];
		incremento[junta] = 0;
	}*/

	//fprintf (temporario,"junta=%d\tincremento=%d\tErro_actual=%d\n",junta,incremento[junta],(int)Erro_actual_pos[junta]);	


	//Erro_actual_pos[junta]=40/*amostra_actual*4*/;

	float Kd = (GANHOS_CONTROLADOR[junta][0])/(GANHOS_CONTROLADOR[junta][2]);
	float Kp = GANHOS_CONTROLADOR[junta][0];



	Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										//( Kp * (Erro_actual_pos[junta]-Erro_anterior_pos[junta])) +
										(Kp * (Erro_actual_pos[junta]-Erro_anterior_pos[junta])) +
										//Aproximacao derivativa 1
										//((Kd/h) * (Erro_actual_pos[junta]-Erro_anterior_pos[junta]) )
										
										//Aproximacao derivativa 2 - melhor
										( (Kd/h) * (Erro_actual_pos[junta] - (2.0*Erro_anterior_pos[junta]) + Erro_anterior_pos2[junta]) )
										
										//Aproximacao derivativa 3
										
										/*(Kd/((float)6.0*h)) *
											(
												Erro_actual_pos[junta] +
												(3 * Erro_anterior_pos[junta]) -
												(3 * Erro_anterior_pos2[junta]) -
												Erro_anterior_pos3[junta]										
											)	*/
											
										);

	/*float Td=GANHOS_CONTROLADOR[junta][2];
	
	Sinal_actuacao_controlador[junta]= (int) (
										(Kp * Erro_actual_pos[junta]) +
										(Kp * (Td/h)*(Erro_actual_pos[junta]-Erro_anterior_pos[junta]))
										);*/
	
	//if (junta==4) fprintf (temporario,"actuacao_calculada=%d\tanterior=%d\t",Sinal_actuacao_controlador[junta],Actuacao_anterior[junta]);			
	Erro_anterior_pos2[junta]=Erro_anterior_pos[junta];
	Erro_anterior_pos[junta]=Erro_actual_pos[junta];

	Actuacao_anterior[junta]=(Sinal_actuacao_controlador[junta]);
	//if (junta==4) fprintf (temporario,"anterior_filtrada=%d\t",Actuacao_anterior[junta]);			
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta] * Sentido_Rotacao_pos[junta]);
//	if (junta==4) fprintf (temporario,"actuacao_filtrada=%d\n",Sinal_actuacao_controlador[junta]);			
	// Guardar valores para proximo passo da interpolacao	
};





/**************************************************************************************************************/
/**** Controlador PID digital por junta, mantem as referencias da SIMULACAO									***/
/***** Controlo em posicao																					**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PID_digital_posicao(int junta)
{

	//  Calculo dos sinais de erro

	//Posjunta[amostra_actual][6]=1100 +((600-1100)/((float)n_amostras)*amostra_actual);

	Erro_actual_pos_rad[junta]=PosicaoJuntaEmRads(junta,(int)Posjunta[amostra_actual][junta])-PosicaoJuntaEmRads(junta,(int)Posicao_juntas[junta]); 
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 


/*** Inicio do Controlador em posicao		***/

//	if (junta==6) fprintf (temporario,"%d\t%g\t%g\t%g\n",amostra_actual,Erro_actual_pos_rad[6],Erro_anterior_pos_rad[6],Erro_anterior_pos2_rad[6]);

	float Kd = ((float)(GANHOS_CONTROLADOR[junta][0]))/((float)(GANHOS_CONTROLADOR[junta][2]));
	float Ki = (GANHOS_CONTROLADOR[junta][0])/(GANHOS_CONTROLADOR[junta][1]);
	float Kp = GANHOS_CONTROLADOR[junta][0];



	Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										(Kp * (Erro_actual_pos_rad[junta]-Erro_anterior_pos_rad[junta])) +
										( Ki * h * Erro_actual_pos_rad[junta] ) +
										( (Kd/h) * (Erro_actual_pos_rad[junta] - (2.0*Erro_anterior_pos_rad[junta]) + Erro_anterior_pos2_rad[junta]) ) 
										
										);

	Actuacao_anterior[junta]=filtra(Sinal_actuacao_controlador[junta]);
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta] * Sentido_Rotacao_pos[junta]);
/***  Fim do Controlador em posicao		****/
	


/****  Inicio do Controlador em velocidade   *********/
	float Erro_actual_vel_rad	= ConverteRadsSeg(junta,Erro_actual_vel[junta]);
	float Erro_anterior_vel_rad = ConverteRadsSeg(junta,Erro_anterior_vel[junta]);

	int inc;
	//  Dead Zone - Pi with antiwindup reset
	if (Actuacao_anterior4[junta] < (-NIVEL_DIGITAL_ACTUACAO_MAXIMO/2)) 
		inc = ((Actuacao_anterior4[junta]-(-NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))*Ka);

	else if (Actuacao_anterior4[junta] > (NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))
		inc =  ((Actuacao_anterior4[junta]-(NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))*Ka);

	else inc = 0;

	float constan = h / (float)0.035; // Ti
	float Kp4= 2.0; //kp

	Sinal_actuacao_controlador4[junta] = (int) (
										(Actuacao_anterior4[junta]) +
										(Kp4 * (float)Erro_actual_vel_rad) -
										(Kp4 * (float)Erro_anterior_vel_rad) +
										(Kp4 * constan * (float)Erro_anterior_vel_rad) //+
									//	(- inc)										
										);

	Actuacao_anterior4[junta]=Sinal_actuacao_controlador4[junta];		
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador4[junta] = 2048 + (Sinal_actuacao_controlador4[junta]*Sentido_Rotacao_vel[junta]);
/***** Fim do Controlador em velocidade		*******/



/****** Calculo dos termos graviticos	***************/

			/*** Transformacao para o referencial utilizado no robot ***/
	angulos_junta[3] = (float)(pi/2) - angulos_junta[3];
	angulos_junta[6] = (float)(pi/2) - angulos_junta[6];


	if (junta==1)	fprintf (temporario,"%d\t",amostra_actual);

	switch (junta)
	{
	case 1:case 4: 
			Compensacao_Gravitica = 0;		
	//		fprintf (temporario,"%g\t",Compensacao_Gravitica);
		break;

	case 2: 
			Compensacao_Gravitica = (float)(m2 * l2 * G * cos(angulos_junta[3]+angulos_junta[2]));
		//	fprintf (temporario,"%g\t",Compensacao_Gravitica*KCompensacao);
		break;

	case 3:
			Compensacao_Gravitica = (float)(( m2 * l2 * G * cos(angulos_junta[3]+angulos_junta[2]) )+
										( (m1 + m2) * l1 * G * cos(angulos_junta[3]) ));									
			fprintf (temporario,"%g\t",Compensacao_Gravitica);
		break;
	
	case 5:
			Compensacao_Gravitica = (float)(m2 * l2 * G * cos(angulos_junta[6]+angulos_junta[5])); 
	//		fprintf (temporario,"%g\t%g\t",Compensacao_Gravitica,Compensacao_Gravitica*KCompensacao);
		break;

	case 6:
			Compensacao_Gravitica = (float)(( m2 * l2 * G * cos(angulos_junta[6]+angulos_junta[5]) ) +
									( (m1 + m2) * l1 * G * cos(angulos_junta[6]) ));
		//	fprintf (temporario,"%g\t",Compensacao_Gravitica*KCompensacao);
		break;
	};

			/*** Compensacao da Transformacao para o referencial utilizado no robot ***/
	angulos_junta[3] = (float)(pi/2) - angulos_junta[3];
	angulos_junta[6] = (float)(pi/2) - angulos_junta[6];
	
	Compensacao_Gravitica = Compensacao_Gravitica * KCompensacao;
	

/*****************************************************/



/******************************************************/

	//  Informacao para amostra seguinte
	Erro_anterior_pos2_rad[junta]=Erro_anterior_pos_rad[junta];
	Erro_anterior_pos_rad[junta]=Erro_actual_pos_rad[junta];

	Erro_anterior_vel[junta]=Erro_actual_vel[junta];


	//   Filtragem dos sinais dos 2 controladores
	Sinal_actuacao_controlador[junta] = Satura_Actuacao (Sinal_actuacao_controlador[junta]);
	Sinal_actuacao_controlador4[junta] = Satura_Actuacao (Sinal_actuacao_controlador4[junta]);


	//   Criacao do sinal de controlo por media ponderada dos dois controladores
	if (junta == 2 || junta== 5) 
		Sinal_actuacao_controlador[junta] = (int)( 1.0 * Sinal_actuacao_controlador[junta]);
	else if (junta==3 || junta==6)
		Sinal_actuacao_controlador[junta] = (int)(	1.0 * Sinal_actuacao_controlador[junta] +
													0.0 * Sinal_actuacao_controlador4[junta]); 
	else
		Sinal_actuacao_controlador[junta] = (int)(	1.0 * Sinal_actuacao_controlador[junta] +
													0.0 * Sinal_actuacao_controlador4[junta]); 


	if (junta==3) fprintf (temporario,"%d\t",Sinal_actuacao_controlador[junta]);	

	//  Criacao do sinal de controlo com compensacao da forca gravitica nas juntas do robot
	switch (junta)
	{
	case 2:case 3:Sinal_actuacao_controlador[junta] += (int) Compensacao_Gravitica;break;
	case 5:case 6:Sinal_actuacao_controlador[junta] -= (int) Compensacao_Gravitica;break;
	};

	if (junta==3) fprintf (temporario,"%d\n",Sinal_actuacao_controlador[junta]);	
};





/**************************************************************************************************************/
/**** Controlador P digital por junta, mantem as referencias da SIMULACAO									***/
/**** Controlo em Velocidade																				**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_P_digital_velocidade(int junta)
{
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 

	float Erro_actual_vel_rad=ConverteRadsSeg(junta,Erro_actual_vel[junta]);

	//Sinal_actuacao_controlador[junta] = (int) (GANHOS_CONTROLADOR[junta][0] * (float)Erro_actual_vel[junta]) ;  // niveis digitais
	Sinal_actuacao_controlador[junta] = (int) (GANHOS_CONTROLADOR[junta][0] * (float)Erro_actual_vel_rad) ;  // radianos
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta]*Sentido_Rotacao_vel[junta]);
 
	// Guardar valores para proximo passo da interpolacao
};


/**************************************************************************************************************/
/**** Controlador PD digital por junta, mantem as referencias da SIMULACAO									***/
/**** Controlo em Velocidade																				**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PD_digital_velocidade(int junta)
{
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 

	float Kd = (GANHOS_CONTROLADOR[junta][0])/(GANHOS_CONTROLADOR[junta][2]);

	float Erro_actual_vel_rad	= ConverteRadsSeg(junta,Erro_actual_vel[junta]);
	float Erro_anterior_vel_rad = ConverteRadsSeg(junta,Erro_anterior_vel[junta]);

	Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										(GANHOS_CONTROLADOR[junta][0] * (Erro_actual_vel_rad-Erro_anterior_vel_rad)) +
										//( (Kd/h) * (Erro_actual_vel[junta] - (2.0*Erro_anterior_vel[junta]) + Erro_anterior_vel2[junta]) )
										( (Kd/h) * (Erro_actual_vel_rad - Erro_anterior_vel_rad)	)
										);

	/*Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										(GANHOS_CONTROLADOR[junta][0] * (Erro_actual_vel[junta]-Erro_anterior_vel[junta])) +
										//( (Kd/h) * (Erro_actual_vel[junta] - (2.0*Erro_anterior_vel[junta]) + Erro_anterior_vel2[junta]) )
										( (Kd/h) * (Erro_actual_vel[junta] - Erro_anterior_vel[junta])	)
										);*/

	Actuacao_anterior[junta]=Sinal_actuacao_controlador[junta];	
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta]* Sentido_Rotacao_vel[junta]);
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior_vel2[junta]=Erro_anterior_vel[junta];
	Erro_anterior_vel[junta]=Erro_actual_vel[junta];
	
};
	

/**************************************************************************************************************/
/**** Controlador PID digital por junta, mantem as referencias da SIMULACAO									***/
/***** Controlo em velocidade																					**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PID_digital_velocidade(int junta)
{
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 

	float Kd = (GANHOS_CONTROLADOR[junta][0])/(GANHOS_CONTROLADOR[junta][2]);
	float Ki = (GANHOS_CONTROLADOR[junta][0])/(GANHOS_CONTROLADOR[junta][1]);

	float Erro_actual_vel_rad	= ConverteRadsSeg(junta,Erro_actual_vel[junta]);
	float Erro_anterior_vel_rad = ConverteRadsSeg(junta,Erro_anterior_vel[junta]);
	float Erro_anterior_vel2_rad= ConverteRadsSeg(junta,Erro_anterior_vel2[junta]);


	/*Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										(GANHOS_CONTROLADOR[junta][0] * (Erro_actual_vel[junta]-Erro_anterior_vel[junta])) +
										( Ki * h * Erro_actual_vel[junta] ) +
										( (Kd/h) * (Erro_actual_vel[junta] - (2.0*Erro_anterior_vel[junta]) + Erro_anterior_vel2[junta]) )
										);*/
		
	Sinal_actuacao_controlador[junta] = (int) (
										Actuacao_anterior[junta] +
										(GANHOS_CONTROLADOR[junta][0] * (Erro_actual_vel_rad-Erro_anterior_vel_rad)) +
										( Ki * h * Erro_actual_vel_rad ) +
										( (Kd/h) * (Erro_actual_vel_rad - (2.0*Erro_anterior_vel_rad) + Erro_anterior_vel2_rad) )
										);

	Actuacao_anterior[junta]=Sinal_actuacao_controlador[junta];
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta] * Sentido_Rotacao_vel[junta]);
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior_vel2[junta]=Erro_anterior_vel[junta];
	Erro_anterior_vel[junta]=Erro_actual_vel[junta];
};


/**************************************************************************************************************/
/***	Criacao de uma funcao de dead zone necesssaria para o controlador PI with anti reset windup			***/
/**************************************************************************************************************/
int CComandaRobot::DeadZone(int actuacao)
{

	if (actuacao < (-NIVEL_DIGITAL_ACTUACAO_MAXIMO/2)) 
		return ((actuacao-(-NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))*Ka);

	else if (actuacao > (NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))
		return ((actuacao-(NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))*Ka);

	else return(0);
	
};


/**************************************************************************************************************/
/**** Controlador PI digital por junta, mantem as referencias da SIMULACAO									***/
/**** Controlo em Velocidade																				**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PI_digital_velocidade(int junta)
{
	float constan;

	if (junta == 2 || junta == 5 )
	{
		Controlador_PID_digital_posicao(junta);
	}
	else 

	{
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 

	constan = h / GANHOS_CONTROLADOR[junta][1];

	float Erro_actual_vel_rad	= ConverteRadsSeg(junta,Erro_actual_vel[junta]);
	float Erro_anterior_vel_rad = ConverteRadsSeg(junta,Erro_anterior_vel[junta]);

	int inc;

	//  Dead Zone - Pi with antiwindup reset
	if (Actuacao_anterior[junta] < (-NIVEL_DIGITAL_ACTUACAO_MAXIMO/2)) 
		inc = ((Actuacao_anterior[junta]-(-NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))*Ka);

	else if (Actuacao_anterior[junta] > (NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))
		inc =  ((Actuacao_anterior[junta]-(NIVEL_DIGITAL_ACTUACAO_MAXIMO/2))*Ka);

	else inc = 0;

	
	Sinal_actuacao_controlador[junta] = (int) (
										(Actuacao_anterior[junta]) +
										(GANHOS_CONTROLADOR[junta][0] * (float)Erro_actual_vel_rad) -
										(GANHOS_CONTROLADOR[junta][0] * (float)Erro_anterior_vel_rad) +
										(GANHOS_CONTROLADOR[junta][0] * constan * (float)Erro_anterior_vel_rad ) +
										(- inc)
										);
	



	Actuacao_anterior[junta]=Sinal_actuacao_controlador[junta];		
	
	//  Ajuste da actuacao em funcao do  sinal de controlo em posicao 
	Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta]*Sentido_Rotacao_vel[junta]);

	// Guardar valores para proximo passo da interpolacao
	Erro_anterior_vel[junta]=Erro_actual_vel[junta];

	}
}


/**************************************************************************************************************/
/***   Actuacao das juntas do robot com o sinal obtido pelo controlador									   ****/
/**************************************************************************************************************/
void CComandaRobot::Actuacao_robot(int junta)
{
	Saturacao_Actuacoes();

	if (junta==1) Actuacao_Pe_perna2(Sinal_actuacao_controlador[1]);
	if (junta==2) Actuacao_Joelho_perna2(Sinal_actuacao_controlador[2]);
	if (junta==3) Actuacao_Anca_perna2(Sinal_actuacao_controlador[3]);
	if (junta==4) Actuacao_Pe_perna1(Sinal_actuacao_controlador[4]);
	if (junta==5) Actuacao_Joelho_perna1(Sinal_actuacao_controlador[5]);
	if (junta==6) Actuacao_Anca_perna1(Sinal_actuacao_controlador[6]);
}


/**************************************************************************************************************/
/****			Correspondencia digital das referencias entradas											***/
/**************************************************************************************************************/
void CComandaRobot::Apresenta_referencias_digitais(void)
{
 FILE *fich_vel;	// Ficheiros de saida para verificacao da velocidade e da posicao em niveis digitais
 int r=0;
 
 //  Referencias em velocidade
 fich_vel=fopen(Fich_REFVEL,"w");
 while (Veljunta[r][0]!=-1) {
	 fprintf(fich_vel,"%g\t%g\t%g\t%g\t%g\t%g\t%g\n",
		Veljunta[r][0],
		VelocidadeJuntaEmGraus(1,(int)(Veljunta[r][1]-2048)),
		VelocidadeJuntaEmGraus(2,(int)(Veljunta[r][2]-2048)),
		VelocidadeJuntaEmGraus(3,(int)(Veljunta[r][3]-2048)),
		VelocidadeJuntaEmGraus(4,(int)(Veljunta[r][4]-2048)),
		VelocidadeJuntaEmGraus(5,(int)(Veljunta[r][5]-2048)),
		VelocidadeJuntaEmGraus(6,(int)(Veljunta[r][6]-2048)));
	r++;
 };
 fclose (fich_vel);r=0;

 // Referencias em posicao
 fich_vel=fopen(Fich_REFPOS,"w");
 while (Posjunta[r][0]!=-1) {
	 fprintf(fich_vel,"%g\t%g\t%g\t%g\t%g\t%g\t%g\n",
		Posjunta[r][0],
		PosicaoJuntaEmGraus(1,(int)Posjunta[r][1]),
		PosicaoJuntaEmGraus(2,(int)Posjunta[r][2]),
		PosicaoJuntaEmGraus(3,(int)Posjunta[r][3]),
		PosicaoJuntaEmGraus(4,(int)Posjunta[r][4]),
		PosicaoJuntaEmGraus(5,(int)Posjunta[r][5]),
		PosicaoJuntaEmGraus(6,(int)Posjunta[r][6]));
	 r++;
 };
 fclose (fich_vel);
 
}


/**************************************************************************************************************/
/**** Fecha todos os ficheiros de saida do controlador				****/
/**************************************************************************************************************/
void CComandaRobot::Fechar_ficheiros(void)
{
	fclose (Sinais_medidos_Posicao);
	fclose (Sinais_erro_Posicao);
	fclose (Sinais_medidos_Velocidade);
	fclose (Sinais_erro_Velocidade);
	fclose (Sinais_actuados);
	fclose (temporario);
}


/**************************************************************************************************************/
/***		Processamento de cada junta individualmente	em posicao		***/
/***  tipo_controlador == 1   Controlador Proporcional											**/
/***				   == 2   Controlador Proporcional Integrativo								**/
/***				   == 3   Controlador Proporcional Derivativo								**/
/***                   == 4	  Controlador Proporcional Integrativo Derivativo					**/
/***  n_junta ==  numero da junta a controlar													**/
/***  A amostra a interpolar e a amostra actual													**/
/***  Os ganhos foram especificados antecipadamente, quando da criacao do robot					**/
/**************************************************************************************************************/
void CComandaRobot::ProcessaJuntaIndividualPosicao(int n_junta,int tipo_controlador)
{
	Leitura_estado_robot(n_junta);
	if (tipo_controlador == 1)		Controlador_P_digital_posicao(n_junta);
	else if (tipo_controlador == 2)	Controlador_PI_digital_posicao(n_junta);
		else if (tipo_controlador == 3) Controlador_PD_digital_posicao(n_junta);
			else Controlador_PID_digital_posicao(n_junta);
	Actuacao_robot(n_junta);
	Guarda_informacao_interpolacao(n_junta);
}


/**************************************************************************************************************/
/***		Processamento de cada amostra, com a imagem global do estado do robot em posicao    **/
/***  tipo_controlador == 1   Controlador Proporcional											**/
/***				   == 2   Controlador Proporcional Integrativo								**/
/***				   == 3   Controlador Proporcional Derivativo								**/
/***                   == 4	  Controlador Proporcional Integrativo Derivativo					**/
/***  A amostra a interpolar e a amostra actual													**/
/***  Os ganhos foram especificados antecipadamente, quando da criacao do robot					**/
/**************************************************************************************************************/
void CComandaRobot::ProcessaJuntaGlobalPosicao(int tipo_controlador)
{
	for (int n_junta=1;n_junta<=N_JUNTAS;n_junta++) Leitura_estado_robot(n_junta);

	angulos_junta[2] = PosicaoJuntaEmRads(2,(int)Posicao_juntas[2]);
	angulos_junta[3] = PosicaoJuntaEmRads(3,(int)Posicao_juntas[3]);
	angulos_junta[5] = PosicaoJuntaEmRads(5,(int)Posicao_juntas[5]);
	angulos_junta[6] = PosicaoJuntaEmRads(6,(int)Posicao_juntas[6]);

/**** codigo de teste 
	/*for (int ola=1;ola<=N_JUNTAS;ola++)
	angulos_junta[ola]=PosicaoJuntaEmRads(ola,Posjunta[amostra_actual][ola]);*/

/*	angulos_junta[3]=(pi/2)+(-pi*amostra_actual/n_amostras);
	angulos_junta[2]=(-pi/2)+(pi*amostra_actual/n_amostras);

	angulos_junta[6]=(-pi/2)+(pi*amostra_actual/n_amostras);
	angulos_junta[5]=(pi/2)+(-pi*amostra_actual/n_amostras);*/




	//if (junta==3) fprintf (temporario,"%d\t%g\t",amostra_actual,angulos_junta[3]);
/************************************/	



	for (n_junta=1;n_junta<=N_JUNTAS;n_junta++) 
	{
	if (tipo_controlador == 1)		Controlador_P_digital_posicao(n_junta);
	else if (tipo_controlador == 2)	Controlador_PI_digital_posicao(n_junta);
		else if (tipo_controlador == 3) Controlador_PD_digital_posicao(n_junta);
			else Controlador_PID_digital_posicao(n_junta);	
	}
	for (n_junta=1;n_junta<=N_JUNTAS;n_junta++) Actuacao_robot(n_junta);
	for (n_junta=1;n_junta<=N_JUNTAS;n_junta++) Guarda_informacao_interpolacao(n_junta);
};

/**************************************************************************************************************/
/****   Incrementa o contador de amostras para passar a seguinte					****/
/**************************************************************************************************************/
void CComandaRobot::IncrementaNAmostras(void)
{
	amostra_actual++;
};

/**************************************************************************************************************/
/****   Devolve o numero de amostras total da trajectoria actual											****/
/**************************************************************************************************************/
int CComandaRobot::NAmostras(void)
{
	return (n_amostras);
}

/**************************************************************************************************************/
/*****  Devolve o numero da amostra actual														****/
/**************************************************************************************************************/
int CComandaRobot::AmostraActual(void)
{
	return(amostra_actual);
}


/**************************************************************************************************************/
/**  Apresenta no ficheiro de debug os valores de incrementos de niveis digitais por grau					**/
/**************************************************************************************************************/
void CComandaRobot::ApresentaIncrementos(FILE *fich_debug)
{
	fprintf (ficheiro_debug,"Apresentacao dos incrementos\n");
	for (int h=1;h<=N_JUNTAS;h++)
	{
		fprintf (	fich_debug,
					"Incrementos Junta %d=%g [n_dig/graus] =%g [graus/n_dig]\n",
					h,
					fabs((Expressoes_posicao_junta[h].y2-Expressoes_posicao_junta[h].y1)/(Expressoes_posicao_junta[h].x2-Expressoes_posicao_junta[h].x1)),
					fabs((Expressoes_posicao_junta[h].x2-Expressoes_posicao_junta[h].x1)/(Expressoes_posicao_junta[h].y2-Expressoes_posicao_junta[h].y1))
				);
	}

}


/**************************************************************************************************************/
/***		Processamento de cada junta individualmente	em velocidade		***/
/***  tipo_controlador == 1   Controlador Proporcional											**/
/***				   == 2   Controlador Proporcional Integrativo								**/
/***				   == 3   Controlador Proporcional Derivativo								**/
/***                   == 4	  Controlador Proporcional Integrativo Derivativo					**/
/***  n_junta ==  numero da junta a controlar													**/
/***  A amostra a interpolar e a amostra actual													**/
/***  Os ganhos foram especificados antecipadamente, quando da criacao do robot					**/
/**************************************************************************************************************/
void CComandaRobot::ProcessaJuntaIndividualVelocidade(int n_junta,int tipo_controlador)
{
	Leitura_estado_robot(n_junta);
	if (tipo_controlador == 1)		Controlador_P_digital_velocidade(n_junta);
	else if (tipo_controlador == 2)	Controlador_PI_digital_velocidade(n_junta);
		else if (tipo_controlador == 3) Controlador_PD_digital_velocidade(n_junta);
			else Controlador_PID_digital_velocidade(n_junta);
	Actuacao_robot(n_junta);
	Guarda_informacao_interpolacao(n_junta);
}

/**************************************************************************************************************/
/***		Processamento de cada amostra, com a imagem global do estado do robot em velocidade    **/
/***  tipo_controlador == 1   Controlador Proporcional											**/
/***				   == 2   Controlador Proporcional Integrativo								**/
/***				   == 3   Controlador Proporcional Derivativo								**/
/***                   == 4	  Controlador Proporcional Integrativo Derivativo					**/
/***  A amostra a interpolar e a amostra actual													**/
/***  Os ganhos foram especificados antecipadamente, quando da criacao do robot					**/
/**************************************************************************************************************/
void CComandaRobot::ProcessaJuntaGlobalVelocidade(int tipo_controlador)
{
	for (int n_junta=1;n_junta<=N_JUNTAS;n_junta++) Leitura_estado_robot(n_junta);
	for (n_junta=1;n_junta<=N_JUNTAS;n_junta++) 
	{
	if (tipo_controlador == 1)		Controlador_P_digital_velocidade(n_junta);
	else if (tipo_controlador == 2)	Controlador_PI_digital_velocidade(n_junta);
		else if (tipo_controlador == 3) Controlador_PD_digital_velocidade(n_junta);
			else Controlador_PID_digital_velocidade(n_junta);
			
	}
	for (n_junta=1;n_junta<=N_JUNTAS;n_junta++) Actuacao_robot(n_junta);
	for (n_junta=1;n_junta<=N_JUNTAS;n_junta++) Guarda_informacao_interpolacao(n_junta);
};



/**************************************************************************************************************/
/**** Guarda informacao respeitante a cada uma das junta para analise da trajectoria		**/
/**************************************************************************************************************/
void CComandaRobot::Guarda_informacao_interpolacao(int junta)
{
	if (junta==6) 
	{	
		fprintf (Sinais_erro_Posicao,"%g\n",PosicaoJuntaEmGraus(junta,(int)Posjunta[amostra_actual][junta])-PosicaoJuntaEmGraus(junta,(int)Posicao_juntas[junta]));
		fprintf (Sinais_medidos_Posicao,"%g\n",/*Posicao_juntas[6]*/PosicaoJuntaEmGraus(junta,(int)Posicao_juntas[junta]));
		fprintf (Sinais_erro_Velocidade,"%g\n",/*Erro_actual_vel[6]*/VelocidadeJuntaEmGraus(junta,(int)Veljunta[amostra_actual][junta])-VelocidadeJuntaEmGraus(junta,Velocidade_juntas[junta]));
		fprintf (Sinais_medidos_Velocidade,"%g\n",/*Velocidade_juntas[6]*/VelocidadeJuntaEmGraus(junta,Velocidade_juntas[junta]-2048));
		fprintf (Sinais_actuados,"%d\n",Sinal_actuacao_controlador[junta]);
	}
	else if (junta==1)
	{
		fprintf (Sinais_erro_Posicao,"%d\t%g\t",amostra_actual,PosicaoJuntaEmGraus(junta,(int)Posjunta[amostra_actual][junta])-PosicaoJuntaEmGraus(junta,(int)Posicao_juntas[junta]));
		fprintf (Sinais_medidos_Posicao,"%d\t%g\t",amostra_actual,/*Posicao_juntas[junta]*/PosicaoJuntaEmGraus(junta,(int)Posicao_juntas[junta]));
		fprintf (Sinais_erro_Velocidade,"%d\t%g\t",amostra_actual,/*Erro_actual_vel[junta]*/VelocidadeJuntaEmGraus(junta,(int)Veljunta[amostra_actual][junta])-VelocidadeJuntaEmGraus(junta,Velocidade_juntas[junta]));
		fprintf (Sinais_medidos_Velocidade,"%d\t%g\t",amostra_actual,/*Velocidade_juntas[junta]*/VelocidadeJuntaEmGraus(junta,Velocidade_juntas[junta]-2048));
		fprintf (Sinais_actuados,"%d\t%d\t",amostra_actual,Sinal_actuacao_controlador[junta]);
	}
	else
	{
		fprintf (Sinais_erro_Posicao,"%g\t",PosicaoJuntaEmGraus(junta,(int)Posjunta[amostra_actual][junta])-PosicaoJuntaEmGraus(junta,(int)Posicao_juntas[junta]));
		fprintf (Sinais_medidos_Posicao,"%g\t",/*Posicao_juntas[junta]*/PosicaoJuntaEmGraus(junta,(int)Posicao_juntas[junta]));
		fprintf (Sinais_erro_Velocidade,"%g\t",/*Erro_actual_vel[junta]*/VelocidadeJuntaEmGraus(junta,(int)Veljunta[amostra_actual][junta])-VelocidadeJuntaEmGraus(junta,Velocidade_juntas[junta]));
		fprintf (Sinais_medidos_Velocidade,"%g\t",/*Velocidade_juntas[junta]*/VelocidadeJuntaEmGraus(junta,Velocidade_juntas[junta]-2048));
		fprintf (Sinais_actuados,"%d\t",Sinal_actuacao_controlador[junta]);
	};
};


/**************************************************************************************************************/
/****  Aplicacao de uma referencia em velocidade a todos os actuadores			*/
/**************************************************************************************************************/
void CComandaRobot::FuncaoCaracteristicaServo(int junta_ref,int referencia)
{
	valor_referencia = referencia;
	for (int junta=1;junta<=N_JUNTAS;junta++)
	{
		Leitura_estado_robot(junta);
		Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 
		Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 
		Sinal_actuacao_controlador[junta] = valor_referencia;
		// Guardar valores para proximo passo da interpolacao
		Erro_anterior_vel[junta]=Erro_actual_vel[junta];
		Actuacao_anterior[junta]=Sinal_actuacao_controlador[junta];
		if (junta_ref == junta) Actuacao_robot(junta);	
		Guarda_informacao_interpolacao(junta);
	}
}

/**************************************************************************************************************/
/***	Devolve a velocidade medida anteriormente															***/
/**************************************************************************************************************/
int CComandaRobot::DevolveVelocidadeMedida(int junta)
{
	return (Velocidade_juntas[junta]);
}

/**************************************************************************************************************/
/****  Fim de programa - Saida anormal do programa    ***/
/**************************************************************************************************************/
void CComandaRobot::saida(void)
{
	fprintf (ficheiro_debug,"Fim de Programa...\n");
	exit (-1);
}


/**************************************************************************************************************/
/**** Colocacao do robot na sua postura inicial				*/
/**************************************************************************************************************/
void CComandaRobot::PosturaInicial(int amostra_postura)
{
	int ok_junta[7];

	for (int g=1;g<=N_JUNTAS;g++) ok_junta[g]=0;  // inicializacao do vector de verificacao
	while (ok_junta[1]==0 || ok_junta[2]==0 || ok_junta[3]==0 || ok_junta[4]==0 || ok_junta[5]==0 || ok_junta[6]==0)
	{
		for (g=1;g<=N_JUNTAS;g++)
		{
			Leitura_estado_robot(g);
			if  ( fabs(Posicao_juntas[g]-Posjunta[amostra_postura][g]) > N_NIVEIS_DIGITAIS_ERRO_POSICAO ) 
			{
				ok_junta[g]=0;
				if ((Posjunta[amostra_postura][g]-Posicao_juntas[g]) > 0 )
						Sinal_actuacao_controlador[g]=2048+(MAX_VELOCIDADE_POSTURA*Sentido_Rotacao_pos[g]);
				if ((Posjunta[amostra_postura][g]-Posicao_juntas[g]) < 0 )
						Sinal_actuacao_controlador[g]=2048-(MAX_VELOCIDADE_POSTURA*Sentido_Rotacao_pos[g]);
			}
			else 
			{
				ok_junta[g]=1;
				Sinal_actuacao_controlador[g]=2048;
				fprintf (ficheiro_debug,"Junta %d ajustada na posicao = %d --> Tempo =%g\n",g,Posicao_juntas[g],amostra_postura*h);
			}
			Actuacao_robot (g);
		}
	}

	inicializar_actuadores();
}


/**************************************************************************************************************/
/**  Devolve o numero da passada actual					***/
/**************************************************************************************************************/
int CComandaRobot::NPassadaActual(void)
{
	/*int con=0; // Passada inicial
	
	for (int i=0;i<total_n_passadas;i++)
		if (TempoActual() > Tempo_Passadas[i]) con++; 
		
	return (con);
	*/
	return(passada_actual);
};


/**************************************************************************************************************/
/****   Decrementa o contador de amostras para voltar a anterior				****/
/**************************************************************************************************************/
void CComandaRobot::DecrementaNAmostras(void)
{
	if (amostra_actual > 1) amostra_actual--;
}


/**************************************************************************************************************/
/***   Verifica se a amostra actual e a ultima amostra
/**************************************************************************************************************/
BOOL CComandaRobot::FimAmostragem(void)
{
	if (amostra_actual >= n_amostras) return(TRUE);
	else return(FALSE);
}


/*************************************************************************************************************/
/***	Verificacao se o tempo para efectuar a passada actual ja foi ultrapassado							**/
/*************************************************************************************************************/
BOOL CComandaRobot::UltrapassouTempoPassada(void)
{
	if (((float) (amostra_actual) *h) >= Tempo_Passadas[passada_actual+1])
	{  // Ja devia ter comecado a passada seguinte <-> Parar movimento e esperar que cai no chao
		if (Tempo_Passadas[passada_actual+1] == -1)  return (FALSE);
		return (TRUE);
	}
	else return (FALSE);  // Ainda esta dentro do tempo regulamentar para proceder a passada actual
};


/*************************************************************************************************************/
/***	Actualizacao do numero da passada actual quando uma nova comeca a ser descrita						**/
/*************************************************************************************************************/
int CComandaRobot::IncrementaNumeroPassada(void)
{
	fprintf (ficheiro_debug,"IncrementaNumeroPassada\n");
	passada_actual++;
	if (perna_assente_chao == 1) perna_assente_chao = 2;
	else perna_assente_chao = 1;

	return ((int) ((Tempo_Passadas[passada_actual]-TempoActual())/h) );
}


/*************************************************************************************************************/
/****	Verifica se a perna assente no chao (recebida pela funcao) e aquela que deveria, neste instante,	**/
/****	estar assente no chao																				**/
/*************************************************************************************************************/
BOOL CComandaRobot::CorrectaNoChao(int perna)
{
	//fprintf (ficheiro_debug,"\npassada_actual_robot=%d\n",passada_actual);
 	switch (passada_actual % 2)
	{
	case 0:
		if (perna == perna_a_comecar_locomocao) return (TRUE);
		else return (FALSE);
		break;
	default:
		if (perna == perna2_a_comecar_locomocao) return (TRUE);
		else return (FALSE);		
		break;
	}
};



/*************************************************************************************************************/
/***	Verifica se a amplitude de passada maxima pretendida ja foi ultrapassada							**/
/*************************************************************************************************************/
BOOL CComandaRobot::UltrapassouAmplitudePassada(void)
{
	
	Leitura_estado_robot(3);
	Leitura_estado_robot(6);

/*	fprintf (ficheiro_debug,"UltrapassouAmplitudePassada 3=%d\t6=%d\t31=%d\t61=%d\n",
		PosicaoJuntaEmGraus(3,Posicao_juntas[3])
		,PosicaoJuntaEmGraus(6,Posicao_juntas[6])
		,PosicaoJuntaEmGraus(3,Posicoes_ajuste_postura[3])	
		,PosicaoJuntaEmGraus(6,Posicoes_ajuste_postura[6])	);*/

	if ( fabs(PosicaoJuntaEmGraus(3,Posicao_juntas[3])) >  
				((AmplitudeMaximaPassada/2.0) + PosicaoJuntaEmGraus(3,Posicoes_ajuste_postura[3]))	
		||
		 fabs(PosicaoJuntaEmGraus(6,Posicao_juntas[6])) >  
				((AmplitudeMaximaPassada/2.0) + PosicaoJuntaEmGraus(6,Posicoes_ajuste_postura[6]))	)
	return (TRUE);
	else return (FALSE);
};



/*************************************************************************************************************/
/***	Procede ao ajuste de rotacao da base entre passadas													**/
/*************************************************************************************************************/
void CComandaRobot::AjusteRotacaoBase(void)
{

	fprintf (ficheiro_debug,"ACABEI PASSADA E ESTOU A CORRIGIR POSTURA\n");
	Leitura_estado_robot(6);
	inicializar_actuadores();
	while (abs(Posicao_juntas[6] - PosicaoJuntaEmDigitais(6,0)) > N_NIVEIS_DIGITAIS_ERRO_POSICAO    )
	{
		
	fprintf (ficheiro_debug,"%d\n",Posicao_juntas[6]);

		if (( Posicao_juntas[6] - PosicaoJuntaEmDigitais(6,0)) < 0)
			Sinal_actuacao_controlador[6]=2048+(MAX_VELOCIDADE_POSTURA*Sentido_Rotacao_pos[6]);

		if (( Posicao_juntas[6] - PosicaoJuntaEmDigitais(6,0)) > 0)
			Sinal_actuacao_controlador[6]=2048-(MAX_VELOCIDADE_POSTURA*Sentido_Rotacao_pos[6]);

		Actuacao_robot (6);
	    Leitura_estado_robot(6);	
	}; 

};


/*************************************************************************************************************/
/***	Guarda valores actuais de postura do robot para posterior compensacao								**/
/***	em termos de trajectorias futuras																	**/	
/*************************************************************************************************************/
void CComandaRobot::GuardarValoresCorrectivos(void)
{
/*	for (int g=1;g<=N_JUNTAS;g++) 
	{
		Leitura_estado_robot(g);
		Posicoes_ajuste_postura[g]=Posicao_juntas[g];
	};*/

	//Corresponderia ao valor da rotacao segundo o eixo XX, igual ao oposto da posicao da junta 3/6 ?
};

/*************************************************************************************************************/
/****	Instante actual da interpolacao																		**/
/*************************************************************************************************************/
double CComandaRobot::TempoActual(void)
{
	return ((double) (h*amostra_actual));
};


/*************************************************************************************************************/
/***	Transforma a Velocidade de niveis digitais para graus por segundo									**/
/*************************************************************************************************************/
float CComandaRobot::VelocidadeJuntaEmGraus(int junta,int nivel_digital)
{
	return((velocidades_maximas_junta[junta]/(int)2048.0) * nivel_digital);
};



int CComandaRobot::ForaIntervalo(int junta,int posicao_lida)
{

	int maior=max (PosicaoJuntaEmDigitais(junta,-90),PosicaoJuntaEmDigitais(junta,90));
	int menor=min (PosicaoJuntaEmDigitais(junta,-90),PosicaoJuntaEmDigitais(junta,90));


	if (posicao_lida < menor) return (1);
	else if (posicao_lida > maior) return (1);
	else return(0);

}