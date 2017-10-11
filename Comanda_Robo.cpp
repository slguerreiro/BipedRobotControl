#include "pi_C_digital.h"


void main(void)
{
	struct _timeb inicio_interpolacao;
	struct _timeb fim_interpolacao;

	int duration_millis;
	int hora_antes,hora_depois,minutos_antes,minutos_depois,segundos_antes,segundos_depois;
	char *timeline;
	int jun;



 
	CComandaRobot *robot;
	robot = new CComandaRobot;

 /***********************  INICIO DO CICLO DE INTERPOLACAO         **********************************************/
 _ftime (&inicio_interpolacao);
 for (int h_actual=0;h_actual<=robot->NAmostras();h_actual++)
 {
	 for (jun=1;jun<=6;jun++) robot->ProcessaJunta(jun);
	 robot->IncrementaNAmostras();
 
	//printf ("amostra= %d \n",h);	
	//_sleep(1);
 }
 _ftime (&fim_interpolacao);
/***********************  FIM DO CICLO DE INTERPOLACAO         **********************************************/

 
 
 
 
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
 
 /***********************************************************************************************/

 delete (robot);

 
 
} // EOF