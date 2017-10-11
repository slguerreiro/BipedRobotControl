#include "stdafx.h"
#include "CDIGITAL.h"


/********************************************************************************************/
/***   Converte um BYTE para binario no formato string								********/
/********************************************************************************************/
void CComandaRobot::conversao_binario(BYTE converter) 
{
	BYTE tmp;

	for (int a=7;a>=0;a--)
	{
		tmp=converter;
		tmp=tmp >> a;
		if (tmp == 0) devolver[7-a]='0';
		else devolver[7-a]='1';
		converter=(BYTE) (converter-(tmp*pow(2,a)));
	}
	devolver[8]=NULL;
};




/********************************************************************************************/
/***	Converte de binario (string) para double										*****/
/********************************************************************************************/
double CComandaRobot::ConverteDouble(void)
{
	double retornar=0;

	for (int y=7;y>=0;y--)
	{
		retornar = retornar + ((devolver[7-y]-48)*pow(2,y));
	
	}
	return (retornar);
}

/********************************************************************************************/
/***	Converte o valor lido, ajustando o erro de hardware								   **/
/********************************************************************************************/
__int64 CComandaRobot::ConverterLeitura(__int64 c)
{
	BYTE bytes[4];

	bytes[0] = (char) (c >> 24);
	bytes[1] = (char) (c >> 16);
	bytes[2] = (char) (c >> 8);
	bytes[3] = (char) (c);
	char tmp,tmp2;
	__int64 ret=0,conv,conversao;
	
	for (int a=0;a<=3;a++)
	{
		conversao_binario(bytes[a]);
		tmp=devolver[1];
		devolver[1]=devolver[2];
		devolver[2]=devolver[3];
		devolver[3]=tmp;
		tmp2=devolver[5];
		devolver[5]=devolver[6];
		devolver[6]=devolver[7];
		devolver[7]=tmp2;
		conversao=(__int64) ConverteDouble();
		switch (a)
		{
		case 0:
			conv = conversao << 24;
			ret = ret + conv;
			break;
		case 1:
			conv = conversao << 16;
			ret = ret + conv;
			break;
		case 2:
			conv = conversao << 8;
			ret = ret + conv;
			break;
		case 3:ret = ret + conversao;break;
		}
	}
	return (ret);
}


