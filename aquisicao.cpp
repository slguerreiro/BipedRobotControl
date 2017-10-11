#include "stdafx.h"
#include "CDIGITAL.h"



int CComandaRobot::Le_canal(int junta,int canal)
{
	int tmp;
	BOOL n_passa = TRUE;

	while (n_passa)
	{
		tmp=(int) Comunica->ler (1912,canal,1,0);
		if (ForaIntervalo(junta,tmp)) 
		{
		//	n_passa=TRUE;
			n_passa=FALSE;
			fprintf (temporario,"Bloquei leitura no nivel 0 junta=%d nivel=%d\n",junta,tmp);
		}
		else n_passa = FALSE;
		
	}

	return (tmp);
}

int CComandaRobot::Aquisicao_Posicao_Pe_perna2(void) // Junta 1
{
	return ((int) Comunica->ler (1912,1,1,0));
}

int CComandaRobot::Aquisicao_Posicao_Joelho_perna2(void) // Junta 2
{
	return ((int) Comunica->ler(1912,2,1,0));
}

int CComandaRobot::Aquisicao_Posicao_Anca_perna2(void)  // Junta 3
{
	return ((int) Comunica->ler (1912,3,1,0));
}

int CComandaRobot::Aquisicao_Posicao_Pe_perna1(void)  // Junta 4
{
	return ((int) Comunica->ler (1912,4,1,0));
}

int CComandaRobot::Aquisicao_Posicao_Joelho_perna1(void)  //  Junta 5
{
	return ((int) Comunica->ler (1912,5,1,0));
}

int CComandaRobot::Aquisicao_Posicao_Anca_perna1(void)   // Junta 6
{
	return ((int) Comunica->ler(1912,6,1,0));
}

int CComandaRobot::Aquisicao_Velocidade_Pe_perna2(void)  // Junta 1
{
	return (((int)Comunica->ler(1912,8,1,0))+abs(2048-Offset[1]));
}

int CComandaRobot::Aquisicao_Velocidade_Joelho_perna2(void)   //  Junta 2
{
	
	double a;
	double b;
	double ret;
	int JANELA_HISTERESE_SENTIDO = 25;


	__int64 c= Comunica->ler(1912,3,1,1);
	c = ConverterLeitura(c);
	//__int64 tmp=(__int64) c;
	/*conversao_binario((BYTE) (tmp>>24));
	fprintf (ficheiro_debug,"%s ",devolver);
	conversao_binario((BYTE) (tmp>>16));
	fprintf (ficheiro_debug,"%s ",devolver);
	conversao_binario((BYTE) (tmp>>8));
	fprintf (ficheiro_debug,"%s ",devolver);
	conversao_binario((BYTE) tmp);
	fprintf (ficheiro_debug,"%s\t",devolver);*/
	a = ((double) 1 / (double) clock) * (double) c * (double)500; // segundos por volta
	//fprintf(ficheiro_debug,"rps=%g rpm=%g -> %d\t",1.0/a,(1.0/a)*60,c);
	a = (double)1.0 / a; // velocidade em rps

	ret =(int) ((double)(a*2048.0)/(double)(velocidades_maximas_junta[2]/(double)60.0));
	
//	fprintf (ficheiro_debug,"ret=%d valor_anterior=%d",(int)ret,(int)valor_anterior[1]);

	int dvelocidade = ((int)ret - (int)valor_anterior[1]) / h;
	
	valor_anterior[1] = (int)ret;

/*	if ((ret == valor_anterior[1]) && (valor_anterior[1] == valor_anterior2[1])) ret = 2048;
	else
	{
	valor_anterior2[1]=(double)valor_anterior[1];
	valor_anterior[1]=(double)ret;
	if (ret > 4095) ret=4095;
		else if (ret <0 ) ret=0;
	}*/

	if (dvelocidade == 0) ret=0;
	if (ret > 2048) ret = 2048;	

	/***** Módulo da velocidade de rotacao existente em ret	***/
	/***** Calculo do sentido de rotacao					***/

	int sentido_rot = (int)Posicao_juntas[2] - (int)Posicao_junta_ant[2];

//	fprintf (ficheiro_debug,"\nsentido_rot=%d \n",sentido_rot);

	if (abs(sentido_rot) > JANELA_HISTERESE_SENTIDO) Posicao_junta_ant[2]=Posicao_juntas[2];
	else Posicao_junta_ant[2]=Posicao_junta_ant[2];

	if (sentido_rot > 0) ret = 2048 - ret;
		else ret = 2048 + ret ;
			
	
//	fprintf (ficheiro_debug,"RET=%g ",ret);
	return (/*ret*/c);		

}

int CComandaRobot::Aquisicao_Velocidade_Anca_perna2(void)   //  Junta 3
{
	return (((int)Comunica->ler(1912,10,1,0))+abs(2048-Offset[3]));
}

int CComandaRobot::Aquisicao_Velocidade_Pe_perna1(void)   //  Junta 4
{
	return(((int)Comunica->ler (1912,7,1,0))+abs(2048-Offset[4]));
}

int CComandaRobot::Aquisicao_Velocidade_Joelho_perna1(void)   // Junta 5
{
	double a;
	double b;
	double ret;
	int JANELA_HISTERESE_SENTIDO = 25;

	
	__int64 c= Comunica->ler(1912,2,1,1);
	c = ConverterLeitura(c);
	//__int64 tmp=(__int64) c;
	/*conversao_binario((BYTE) (tmp>>24));
	fprintf (ficheiro_debug,"%s ",devolver);
	conversao_binario((BYTE) (tmp>>16));
	fprintf (ficheiro_debug,"%s ",devolver);
	conversao_binario((BYTE) (tmp>>8));
	fprintf (ficheiro_debug,"%s ",devolver);
	conversao_binario((BYTE) tmp);
	fprintf (ficheiro_debug,"%s\t",devolver);*/
	a = ((double) 1 / (double) clock) * (double) c * (double)500; // segundos por volta
	//fprintf(ficheiro_debug,"rps=%g rpm=%g -> %d\t",1.0/a,(1.0/a)*60,c);
	a = (double)1.0 / a; // velocidade em rps

	ret =(int) ((double)(a*2048.0)/(double)(velocidades_maximas_junta[5]/(double)60.0));
	
	/*fprintf (ficheiro_debug,"ret=%d valor_anterior=%d",(int)ret,(int)valor_anterior[2]);

	int dvelocidade = ((int)ret - (int)valor_anterior[2]) / h;
	
	valor_anterior[2] = (int)ret;

/*	if ((ret == valor_anterior[1]) && (valor_anterior[1] == valor_anterior2[1])) ret = 2048;
	else
	{
	valor_anterior2[1]=(double)valor_anterior[1];
	valor_anterior[1]=(double)ret;
	if (ret > 4095) ret=4095;
		else if (ret <0 ) ret=0;
	}*/

	/*if (dvelocidade == 0) ret=0;
	if (ret > 2048) ret = 2048;	

	/***** Módulo da velocidade de rotacao existente em ret	***/
	/***** Calculo do sentido de rotacao					***/

	/*int sentido_rot = (int)Posicao_juntas[5] - (int)Posicao_junta_ant[5];

	fprintf (ficheiro_debug,"\nsentido_rot=%d \n",sentido_rot);

	if (abs(sentido_rot) > JANELA_HISTERESE_SENTIDO) Posicao_junta_ant[5]=Posicao_juntas[5];
	else Posicao_junta_ant[5]=Posicao_junta_ant[5];

	if (sentido_rot > 0) ret = 2048 - ret;
		else ret = 2048 + ret ;
			
	
	fprintf (ficheiro_debug,"RET=%g ",ret);*/
	return (ret);		







}

int CComandaRobot::Aquisicao_Velocidade_Anca_perna1(void)   //  Junta 6
{
	return (((int)Comunica->ler (1912,9,1,0))+abs(2048-Offset[6]));
}


/*************************************************************************************/
/****  Valores de retorno:																		**/
/****		0 - Se nenhum dos sensores estiver activo								**/
/****		1 - Se apenas os sensores da perna 1 estiverem activos					**/
/****		2 - Se apenas os sensores da perna 2 estiverem activos					**/
/****		3 - Se os sensores da perna 1 e da 2 estiverem activos					**/
/*************************************************************************************/
int CComandaRobot::Aquisicao_Sensores_Contacto(void)
{
	int sensor_contacto;

	// Aquisicao dos sinais dos sensores de contacto das duas pernas
	sensor_contacto=(int)Comunica->ler(1912,1,1,1);
	sensor_contacto=sensor_contacto >> 24;
					 
	if (sensor_contacto == 95) return (0);
	else if (sensor_contacto == -33) return(1);
		else if (sensor_contacto == 127) return(2);
			else if (sensor_contacto == -1) return(3);
	return (-1); // Erro na leitura dos sensores de contacto*/
}
 