#ifndef CALCULODIGITAL_H
#define CALCULODIGITAL_H



CComandaRobot::CComandaRobot()
{
	/**** Carregamento das variaveis de estado do sistema   *****/
 NIVEL_DIGITAL_ACTUACAO_MINIMO=10/*1000*/;
 NIVEL_DIGITAL_ACTUACAO_MAXIMO=4090/*3000*/;
 valor_referencia=3000;

/**  Carregar o valor de Frequencia - via ficheiro  */
 Frequencia_amostragem=(float)200;

 //velocidade para o nivel de actuacao 4095 ou 1 (em !!rpm!!)
 velocidades_maximas_junta[1]=(float)53.125;
 velocidades_maximas_junta[2]=(float)100;
 velocidades_maximas_junta[3]=(float)1000;
 velocidades_maximas_junta[4]=(float)1000;
 velocidades_maximas_junta[5]=(float)1000;
 velocidades_maximas_junta[6]=(float)1000;
 //  Colocacao de 2 pontos de controlo por junta para calculo da relacao (posicao angular -> nivel digital)
 Expressoes_posicao_junta[1].x1=(float)0;	//graus
 Expressoes_posicao_junta[1].x2=(float)90;
 Expressoes_posicao_junta[1].y1=(float)1930;	//niveis digitais
 Expressoes_posicao_junta[1].y2=(float)3934;
 Expressoes_posicao_junta[2].x1=(float)0;	//graus
 Expressoes_posicao_junta[2].x2=(float)90;
 Expressoes_posicao_junta[2].y1=(float)2095;	//niveis digitais
 Expressoes_posicao_junta[2].y2=(float)4000;
 Expressoes_posicao_junta[3].x1=(float)90;	//graus
 Expressoes_posicao_junta[3].x2=(float)0;
 Expressoes_posicao_junta[3].y1=(float)1000;	//niveis digitais
 Expressoes_posicao_junta[3].y2=(float)2000;
 Expressoes_posicao_junta[4].x1=(float)90;	//graus
 Expressoes_posicao_junta[4].x2=(float)0;
 Expressoes_posicao_junta[4].y1=(float)1000;	//niveis digitais
 Expressoes_posicao_junta[4].y2=(float)2000;
 Expressoes_posicao_junta[5].x1=(float)90;	//graus
 Expressoes_posicao_junta[5].x2=(float)0;
 Expressoes_posicao_junta[5].y1=(float)1000;	//niveis digitais
 Expressoes_posicao_junta[5].y2=(float)2000;
 Expressoes_posicao_junta[6].x1=(float)90;	//graus
 Expressoes_posicao_junta[6].x2=(float)0;
 Expressoes_posicao_junta[6].y1=(float)1000;	//niveis digitais
 Expressoes_posicao_junta[6].y2=(float)2000;
 amostra_actual=0;

 inicializacoes();			// Inicializacoes da porta paralela
 inicializar_actuadores();  // Inicializacao de todas as juntas a velocidade de rotacao nula
 TransformacaoRPM_RPS_juntas();  // Transformacao dos limites maximos de velocidade
 Criacao_relacao_posicao();  // Calculo das rectas lineares de posicao vs niveis digitais
 n_amostras=carregamento_trajectorias_juntas(); //Carregamento das trajectorias de cada junta 
 Transformacao_referencias_entradas();  // Transformacao das referencias em posicao e velocidade em niveis digitais
 carregamento_ganhos();		// Carregamento dos ganhos de cada controlador PID de cada junta
 Apresenta_referencias_digitais();  // Apresentacao dos resultados obtidos na transformacao de referencias
 
 Sinais_medidos_Posicao=fopen("MdPosJun","w");
 Sinais_erro_Posicao=fopen("ErPosJun","w");
 Sinais_medidos_Velocidade=fopen("MdVelJun","w");
 Sinais_erro_Velocidade=fopen("ErVelJun","w");
};


CComandaRobot::~CComandaRobot() 
{
	inicializar_actuadores();
	Fechar_ficheiros();
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
/*	GANHOS_CONTROLADOR[1][0]=(float) 0.0012631;
	GANHOS_CONTROLADOR[1][1]=(float) 0.055;	*/  //em  Velocidade
	GANHOS_CONTROLADOR[1][0]=(float) 5;
	GANHOS_CONTROLADOR[1][1]=(float) 0.1;
	GANHOS_CONTROLADOR[1][2]=(float) 2;
	GANHOS_CONTROLADOR[1][3]=(float) 2; // Kposicao
	GANHOS_CONTROLADOR[1][4]=(float) 2;  // kvelocidade
	// Ganhos Controlador PID da junta 2
	GANHOS_CONTROLADOR[2][0]=(float) 5;
	GANHOS_CONTROLADOR[2][1]=(float) 0.1;	
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
		fprintf(ficheiro_debug,"O ficheiro %s nao foi aberto\n",ficheiro_aberto);
		saida();
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
		fprintf (ficheiro_debug,"Os ficheiros não tem todos a mesma dimensao\n");
		saida();
		return (0);
	};
};


/**************************************************************************************************************/
/**** Calcula os coeficientes da recta de posicao angular vs niveis digitais								***/
/**************************************************************************************************************/
void CComandaRobot::Criacao_relacao_posicao(void)
{
	for (int e=1;e<7;e++)
	{
		
		Expressoes_posicao_junta[e].m = (Expressoes_posicao_junta[e].y2-Expressoes_posicao_junta[e].y1)/
									    (Expressoes_posicao_junta[e].x2-Expressoes_posicao_junta[e].x1);
		Expressoes_posicao_junta[e].b = (-Expressoes_posicao_junta[e].m * Expressoes_posicao_junta[e].x1) +
											Expressoes_posicao_junta[e].y1;
	}

/*	printf ("\n");
	for (e=0;e<90;e++)
	{

		printf ("\t y=%f",(Expressoes_posicao_junta[1].m*e+Expressoes_posicao_junta[1].b));
	}*/

}


/**************************************************************************************************************/
/**  Transformacao das velocidades de junta maximas em rpm para graus/segundo								**/
/**************************************************************************************************************/
void CComandaRobot::TransformacaoRPM_RPS_juntas(void)
{
	for (int r=1;r<7;r++) {velocidades_maximas_junta[r]=(velocidades_maximas_junta[r]/60)*360;
	printf ("\nactuador1 [graus/segundo (maximo)]=%g rps",velocidades_maximas_junta[r]);}
}


/**************************************************************************************************************/
/***  Passagem das referencias de graus e graus/segundo para niveis digitais								***/
/**************************************************************************************************************/
void CComandaRobot::Transformacao_referencias_entradas(void)
{ int r=0;
  

	/**  Transformacao de velocidades  ***/
/*		 while (Veljunta1[r][0]!=-1) 
			{ 
				Veljunta1[r][1]=2048+( (2048*Veljunta1[r][1])/velocidades_maximas_junta[1] ); 
				if (Veljunta1[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						printf ("\nVelocidade da Junta 1 excedida em %g niveis no instante %g segundos",Veljunta1[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta1[r][0]);
						exit(-1);
					};
				if (Veljunta1[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						printf ("\nVelocidade da Junta 1 excedida em %g niveis no instante %g segundos",-Veljunta1[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta1[r][0]);
						exit(-1);
					};
				r++;
			};
	r=0; while (Veljunta2[r][0]!=-1) 
			{ 
				Veljunta2[r][1]=2048+( (2048*Veljunta2[r][1])/velocidades_maximas_junta[2] ); 
				if (Veljunta2[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						printf ("\nVelocidade da Junta 2 excedida em %g niveis no instante %g segundos",Veljunta2[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta2[r][0]);
						exit(-1);
					};
				if (Veljunta2[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						printf ("\nVelocidade da Junta 2 excedida em %g niveis no instante %g segundos",-Veljunta2[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta2[r][0]);
						exit(-1);
					};
				r++;
			}
	r=0; while (Veljunta3[r][0]!=-1) 
			{ 
				Veljunta3[r][1]=2048+( (2048*Veljunta3[r][1])/velocidades_maximas_junta[3] ); 
				if (Veljunta3[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						printf ("\nVelocidade da Junta 3 excedida em %g niveis no instante %g segundos",Veljunta3[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta3[r][0]);
						exit(-1);
					};
				if (Veljunta3[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						printf ("\nVelocidade da Junta 3 excedida em %g niveis no instante %g segundos",-Veljunta3[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta3[r][0]);
						exit(-1);
					};
				r++;
			}
	r=0; while (Veljunta4[r][0]!=-1) 
			{ 
				
				Veljunta4[r][1]=2048+( (2048*Veljunta4[r][1])/velocidades_maximas_junta[4] ); 
				if (Veljunta4[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						printf ("\nVelocidade da Junta 4 excedida em %g niveis no instante %g segundos",Veljunta4[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta4[r][0]);
						exit(-1);
					};
				if (Veljunta4[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						printf ("\nVelocidade da Junta 4 excedida em %g niveis no instante %g segundos",-Veljunta4[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta4[r][0]);
						exit(-1);
					};
				r++;
			}
	r=0; while (Veljunta5[r][0]!=-1) 
			{ 
				
				Veljunta5[r][1]=2048+( (2048*Veljunta5[r][1])/velocidades_maximas_junta[5] ); 
				if (Veljunta5[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						printf ("\nVelocidade da Junta 5 excedida em %g niveis no instante %g segundos",Veljunta5[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta5[r][0]);
						exit(-1);
					};
				if (Veljunta5[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						printf ("\nVelocidade da Junta 5 excedida em %g niveis no instante %g segundos",-Veljunta5[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta5[r][0]);
						exit(-1);
					};
				r++;
			}
	r=0; while (Veljunta6[r][0]!=-1) 
			{ 
		
				Veljunta6[r][1]=2048+( (2048*Veljunta6[r][1])/velocidades_maximas_junta[6] ); 
				if (Veljunta6[r][1] > NIVEL_DIGITAL_ACTUACAO_MAXIMO) 
					{
						printf ("\nVelocidade da Junta 6 excedida em %g niveis no instante %g segundos",Veljunta6[r][1]-NIVEL_DIGITAL_ACTUACAO_MAXIMO,Veljunta6[r][0]);
						exit(-1);
					};
				if (Veljunta6[r][1] < NIVEL_DIGITAL_ACTUACAO_MINIMO) 
					{
						printf ("\nVelocidade da Junta 6 excedida em %g niveis no instante %g segundos",-Veljunta6[r][1]-NIVEL_DIGITAL_ACTUACAO_MINIMO,Veljunta6[r][0]);
						exit(-1);
					};
				r++;
			}	
*/
	/**  Transformacao de posicoes  ***/
	r=0; while (Posjunta1[r][0]!=-1) {	Posjunta1[r][1]=(Posjunta1[r][1]*Expressoes_posicao_junta[1].m) + Expressoes_posicao_junta[1].b;r++;}
	r=0; while (Posjunta2[r][0]!=-1) {	Posjunta2[r][1]=(Posjunta2[r][1]*Expressoes_posicao_junta[2].m) + Expressoes_posicao_junta[2].b;r++;}
	r=0; while (Posjunta3[r][0]!=-1) {	Posjunta3[r][1]=(Posjunta3[r][1]*Expressoes_posicao_junta[3].m) + Expressoes_posicao_junta[3].b;r++;}
	r=0; while (Posjunta4[r][0]!=-1) {	Posjunta4[r][1]=(Posjunta4[r][1]*Expressoes_posicao_junta[4].m) + Expressoes_posicao_junta[4].b;r++;}
	r=0; while (Posjunta5[r][0]!=-1) {	Posjunta5[r][1]=(Posjunta5[r][1]*Expressoes_posicao_junta[5].m) + Expressoes_posicao_junta[5].b;r++;}
	r=0; while (Posjunta6[r][0]!=-1) {	Posjunta6[r][1]=(Posjunta6[r][1]*Expressoes_posicao_junta[6].m) + Expressoes_posicao_junta[6].b;r++;}
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
		Aquisicao_Velocidade_Anca_perna2();}
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




void CComandaRobot::Controlador_PI_digital(int amostra,int junta)
{
	int erro_actual;

	// Calculo do erro
	//erro_actual=valor_referencia-Velocidade_juntas[1];  // Controlo de Velocidade

	if (junta == 1) 
	{
		erro_actual=((int)Posjunta1[amostra][1])-Posicao_juntas[1];  // Controlo de Posicao
	}
	if (junta == 2) 
	{
			erro_actual=(int)(Posjunta2[amostra][1])-Posicao_juntas[2];  // Controlo de Posicao
	}
  
	// Calculo do sinal de controlo em velocidade
	/*Sinal_actuacao_controlador[2] = Actuacao_anterior[2] +
									(GANHOS_CONTROLADOR[2][0] * (float)erro_actual) -
									(GANHOS_CONTROLADOR[2][0] * Erro_anterior[2]) +														
									(GANHOS_CONTROLADOR[2][0] * (((float)1/Frequencia_amostragem)/GANHOS_CONTROLADOR[2][1]) * Erro_anterior[2]);
	*/

if (junta==1)
{
	Sinal_actuacao_controlador[1] = (GANHOS_CONTROLADOR[1][0] * (float)erro_actual) ;
	Sinal_actuacao_controlador[1] = Sinal_actuacao_controlador[1] + 2048;
				
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior[1]=erro_actual;
	Actuacao_anterior[1]=Sinal_actuacao_controlador[1];
	fprintf (Sinais_erro_Posicao,"%d\t%d\t",amostra,erro_actual);
	fprintf (Sinais_medidos_Posicao,"%d\t%d\t",amostra,Posicao_juntas[1]);
};


if (junta==2)
{
	Sinal_actuacao_controlador[2] = (GANHOS_CONTROLADOR[2][0] * (float)erro_actual) ;
	Sinal_actuacao_controlador[2] = Sinal_actuacao_controlador[2] + 2048;
				
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior[2]=erro_actual;
	Actuacao_anterior[2]=Sinal_actuacao_controlador[2];
	fprintf (Sinais_erro_Posicao,"%d\t",erro_actual);
	fprintf (Sinais_medidos_Posicao,"%d\t",Posicao_juntas[2]);
}

if (junta==3) 
{	fprintf (Sinais_erro_Posicao,"%d\t",erro_actual);
	fprintf (Sinais_medidos_Posicao,"%d\t",Posicao_juntas[2]);
}

if (junta==4)
{
	fprintf (Sinais_erro_Posicao,"%d\t",erro_actual);
	fprintf (Sinais_medidos_Posicao,"%d\t",Posicao_juntas[2]);
}

if (junta==5)
{
	fprintf (Sinais_erro_Posicao,"%d\t",erro_actual);
	fprintf (Sinais_medidos_Posicao,"%d\t",Posicao_juntas[2]);
}

if (junta==6)
{
	fprintf (Sinais_erro_Posicao,"%d\n",erro_actual);
	fprintf (Sinais_medidos_Posicao,"%d\n",Posicao_juntas[2]);
}




}


/**************************************************************************************************************/
/**** Controlador PI digital por junta, mantem as referencias da SIMULACAO									***/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PI_digital_completo(int amostra)
{
	int erro_actual[7];

	// Calculo dos erros de posicao
	erro_actual[1]=(int)Veljunta1[amostra][1]-Velocidade_juntas[1];
	erro_actual[2]=(int)Veljunta2[amostra][1]-Velocidade_juntas[2];
	erro_actual[3]=(int)Veljunta3[amostra][1]-Velocidade_juntas[3];
	erro_actual[4]=(int)Veljunta4[amostra][1]-Velocidade_juntas[4];
	erro_actual[5]=(int)Veljunta5[amostra][1]-Velocidade_juntas[5];
	erro_actual[6]=(int)Veljunta6[amostra][1]-Velocidade_juntas[6];

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

/*	fprintf (erro,"%d\t%d\n",amostra,erro_actual[1]);
	fprintf (ficheiro,"%d\t%d\n",amostra,Velocidade_juntas[1]);*/
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
 fich_vel=fopen("RfVelDig","w");
 while (Veljunta1[r][0]!=-1) {fprintf(fich_vel,"%g\t%g\t%g\t%g\t%g\t%g\t%g\n",Veljunta1[r][0],Veljunta1[r][1],Veljunta2[r][1],Veljunta3[r][1],Veljunta4[r][1],Veljunta5[r][1],Veljunta6[r][1]);r++;};
 fclose (fich_vel);r=0;

 // Referencias em posicao
 fich_vel=fopen("RfPosDig","w");
 while (Posjunta1[r][0]!=-1) {fprintf(fich_vel,"%g\t%g\t%g\t%g\t%g\t%g\t%g\n",Posjunta1[r][0],Posjunta1[r][1],Posjunta2[r][1],Posjunta3[r][1],Posjunta4[r][1],Posjunta5[r][1],Posjunta6[r][1]);r++;};
 fclose (fich_vel);
 
}

void CComandaRobot::Fechar_ficheiros(void)
{
	fclose (Sinais_medidos_Posicao);
	fclose (Sinais_erro_Posicao);
	fclose (Sinais_medidos_Velocidade);
	fclose (Sinais_erro_Velocidade);
}


void CComandaRobot::ProcessaJunta(int n_junta)
{
	Leitura_estado_robot(n_junta);
	Controlador_PI_digital(amostra_actual,n_junta);
	Actuacao_robot(n_junta);
};

void CComandaRobot::IncrementaNAmostras(void)
{
	amostra_actual++;
};

int CComandaRobot::NAmostras(void)
{
	return (n_amostras);
}

#endif