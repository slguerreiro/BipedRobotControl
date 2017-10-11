



/**************************************************************************************************************/
/**** Controlador P digital por junta, mantem as referencias da SIMULACAO									***/
/**** Controlo em Velocidade																				**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_P_digital_velocidade(int)
{

};


/**************************************************************************************************************/
/**** Controlador PD digital por junta, mantem as referencias da SIMULACAO									***/
/**** Controlo em Velocidade																				**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PD_digital_velocidade(int)
{

};
	

/**************************************************************************************************************/
/**** Controlador PID digital por junta, mantem as referencias da SIMULACAO									***/
/***** Controlo em velocidade																					**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PID_digital_velocidade(int)
{

};


/**************************************************************************************************************/
/**** Controlador PI digital por junta, mantem as referencias da SIMULACAO									***/
/**** Controlo em Velocidade																				**/
/**************************************************************************************************************/
void CComandaRobot::Controlador_PI_digital_velocidade(int junta)
{
	Erro_actual_pos[junta]=((int)Posjunta[amostra_actual][junta])-Posicao_juntas[junta]; 
	Erro_actual_vel[junta]=((int)Veljunta[amostra_actual][junta])-Velocidade_juntas[junta]; 
	
	Sinal_actuacao_controlador[junta] = 
		Actuacao_anterior[junta]+
		GANHOS_CONTROLADOR[junta][0] * (float)Erro_actual_vel[junta] -
		GANHOS_CONTROLADOR[junta][0] * Erro_anterior_vel[junta] +
		GANHOS_CONTROLADOR[junta][0] * ((1/Frequencia_amostragem)/GANHOS_CONTROLADOR[junta][1]) * Erro_anterior_vel[junta];
				 

	//Sinal_actuacao_controlador[junta] = 2048 + (Sinal_actuacao_controlador[junta] * SentidoRotacao[junta]);
	// Guardar valores para proximo passo da interpolacao
	Erro_anterior_vel[junta]=Erro_actual_vel[junta];
	Actuacao_anterior[junta]=Sinal_actuacao_controlador[junta];
  
	// Calculo do sinal de controlo em velocidade
	/*
		// Calculo do erro
		//erro_actual=valor_referencia-Velocidade_juntas[1];  // Controlo de Velocidade
	  Sinal_actuacao_controlador[2] = Actuacao_anterior[2] +
									(GANHOS_CONTROLADOR[2][0] * (float)erro_actual) -
									(GANHOS_CONTROLADOR[2][0] * Erro_anterior[2]) +														
									(GANHOS_CONTROLADOR[2][0] * (((float)1/Frequencia_amostragem)/GANHOS_CONTROLADOR[2][1]) * Erro_anterior[2]);
	*/



	// Calculo do sinal de controlo em velocidade
	/*
		// Calculo do erro
		//erro_actual=valor_referencia-Velocidade_juntas[1];  // Controlo de Velocidade
	  Sinal_actuacao_controlador[2] = Actuacao_anterior[2] +
									(GANHOS_CONTROLADOR[2][0] * (float)erro_actual) -
									(GANHOS_CONTROLADOR[2][0] * Erro_anterior[2]) +														
									(GANHOS_CONTROLADOR[2][0] * (((float)1/Frequencia_amostragem)/GANHOS_CONTROLADOR[2][1]) * Erro_anterior[2]);
	*/








}
