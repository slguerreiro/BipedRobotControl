#include "stdafx.h"
#include "CDIGITAL.h"


void CComandaRobot::Actuacao_Pe_perna1(int valor_digital)   // Junta 4
{
	Comunica->escrever(1912,valor_digital,4,0);
}
void CComandaRobot::Actuacao_Joelho_perna1(int valor_digital)  // Junta 5
{
	Comunica->escrever (1912,valor_digital,5,0);
}

void CComandaRobot::Actuacao_Anca_perna1(int valor_digital)  // Junta 6
{
	Comunica->escrever (1912,valor_digital,6,0);
}

void CComandaRobot::Actuacao_Pe_perna2(int valor_digital)  // Junta 1
{
	Comunica->escrever(1912,valor_digital,1,0);
}

void CComandaRobot::Actuacao_Joelho_perna2(int valor_digital)  // Junta 2
{
	Comunica->escrever(1912,valor_digital,2,0);
};

void CComandaRobot::Actuacao_Anca_perna2(int valor_digital)   // Junta 3
{
	Comunica->escrever(1912,valor_digital,3,0);
};
