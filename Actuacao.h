#ifndef ACTUACAO_H
#define ACTUACAO_H

void CComandaRobot::Actuacao_Pe_perna2(int valor_digital)
{
	escrever(1912,valor_digital,2,0);
}

void CComandaRobot::Actuacao_Joelho_perna2(int valor_digital)
{
   escrever (1912,valor_digital,1,0);
   
}

void CComandaRobot::Actuacao_Anca_perna2(int valor_digital)
{

}

void CComandaRobot::Actuacao_Pe_perna1(int valor_digital)
{

}

void CComandaRobot::Actuacao_Joelho_perna1(int valor_digital)
{

}

void CComandaRobot::Actuacao_Anca_perna1(int valor_digital)
{

}


#endif