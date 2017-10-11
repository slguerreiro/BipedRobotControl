// Parametros_controlador.cpp : implementation file
//

#include "stdafx.h"
#include "Controlador_Robot.h"
#include "Parametros_controlador.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Parametr\os_controlador dialog


Parametros_controlador::Parametros_controlador(CWnd* pParent /*=NULL*/)
	: CDialog(Parametros_controlador::IDD, pParent)
{
	//{{AFX_DATA_INIT(Parametros_controlador)

	/*********************  Ganhos dos controladores PID	*****/
	m_Kp1 = 1800;
	m_Ti1 = 0.6f;
	m_Td1 = 75.0f;
	

	m_Kp2 = 3000.0f;
	m_Ti2 = 0.175f;
	m_Td2 = 75.0f;

	m_Kp3 = 3000.0f;
	m_Ti3 = 0.2f;
	m_Td3 = 50.0f;

	m_Kp4 = 1800;
	m_Ti4 = 0.6f;
	m_Td4 = 75.0f;

	m_Kp5 = 3000.0f;
	m_Ti5 = 0.175f;
	m_Td5 = 75.0f;
	
	m_Kp6 = 3000.0f;
	m_Ti6 = 0.2f;
	m_Td6 = 50.0f;

	/****************			 Variaveis varias				******/
	m_max_digital = 4095;
	m_min_digital = 1;
	m_rot_max1 = (float) (6800/128.0);
	m_rot_max2 = 60.0f;
	m_rot_max3 = (float) (6800/99.0);
	m_rot_max4 = (float) (6800/128.0);
	m_rot_max5 = 60.0f;
	m_rot_max6 = (float) (6800/99.0);	
	m_clock = (float) 1e6;
	m_perna_chao_inicial = 1;
	m_amplitude_max = 30;
	//}}AFX_DATA_INIT
}


void Parametros_controlador::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Parametros_controlador)
	DDX_Text(pDX, IDC_EDIT22, m_Kp1);
	DDX_Text(pDX, IDC_EDIT23, m_Ti1);
	DDX_Text(pDX, IDC_EDIT24, m_Td1);
	DDX_Text(pDX, IDC_EDIT25, m_Kp2);
	DDX_Text(pDX, IDC_EDIT26, m_Ti2);
	DDX_Text(pDX, IDC_EDIT27, m_Td2);
	DDX_Text(pDX, IDC_EDIT28, m_Kp3);
	DDX_Text(pDX, IDC_EDIT29, m_Ti3);
	DDX_Text(pDX, IDC_EDIT30, m_Td3);
	DDX_Text(pDX, IDC_EDIT37, m_Kp4);
	DDX_Text(pDX, IDC_EDIT38, m_Ti4);
	DDX_Text(pDX, IDC_EDIT39, m_Td4);
	DDX_Text(pDX, IDC_EDIT34, m_Kp5);
	DDX_Text(pDX, IDC_EDIT35, m_Ti5);
	DDX_Text(pDX, IDC_EDIT36, m_Td5);
	DDX_Text(pDX, IDC_EDIT40, m_Kp6);
	DDX_Text(pDX, IDC_EDIT41, m_Ti6);
	DDX_Text(pDX, IDC_EDIT42, m_Td6);
	DDX_Text(pDX, IDC_EDIT1, m_max_digital);
	DDX_Text(pDX, IDC_EDIT31, m_min_digital);
	DDX_Text(pDX, IDC_EDIT2, m_rot_max1);
	DDX_Text(pDX, IDC_EDIT3, m_rot_max2);
	DDX_Text(pDX, IDC_EDIT4, m_rot_max3);
	DDX_Text(pDX, IDC_EDIT5, m_rot_max4);
	DDX_Text(pDX, IDC_EDIT6, m_rot_max5);
	DDX_Text(pDX, IDC_EDIT7, m_rot_max6);
	DDX_Text(pDX, IDC_EDIT32, m_clock);
	DDX_Text(pDX, IDC_EDIT33, m_perna_chao_inicial);
	DDX_Text(pDX, IDC_EDIT43, m_amplitude_max);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Parametros_controlador, CDialog)
	//{{AFX_MSG_MAP(Parametros_controlador)
	ON_EN_CHANGE(IDC_EDIT22, OnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, OnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, OnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT27, OnChangeEdit27)
	ON_EN_CHANGE(IDC_EDIT28, OnChangeEdit28)
	ON_EN_CHANGE(IDC_EDIT29, OnChangeEdit29)
	ON_EN_CHANGE(IDC_EDIT30, OnChangeEdit30)
	ON_EN_CHANGE(IDC_EDIT34, OnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT35, OnChangeEdit35)
	ON_EN_CHANGE(IDC_EDIT36, OnChangeEdit36)
	ON_EN_CHANGE(IDC_EDIT37, OnChangeEdit37)
	ON_EN_CHANGE(IDC_EDIT38, OnChangeEdit38)
	ON_EN_CHANGE(IDC_EDIT39, OnChangeEdit39)
	ON_EN_CHANGE(IDC_EDIT40, OnChangeEdit40)
	ON_EN_CHANGE(IDC_EDIT41, OnChangeEdit41)
	ON_EN_CHANGE(IDC_EDIT42, OnChangeEdit42)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT31, OnChangeEdit31)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT32, OnChangeEdit32)
	ON_EN_CHANGE(IDC_EDIT33, OnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT43, OnChangeEdit43)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Parametros_controlador message handlers

void Parametros_controlador::OnOK() {CDialog::OnOK();}
void Parametros_controlador::OnChangeEdit22() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit23() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit24() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit25() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit26() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit27() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit28() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit29() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit30() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit34() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit35() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit36() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit37() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit38() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit39() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit40() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit41() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit42() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit1()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit2()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit3()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit31() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit4()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit5()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit6()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit7()  {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit32() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit33() {UpdateData(TRUE);}
void Parametros_controlador::OnChangeEdit43() {UpdateData(TRUE);}



/********************************************************************/
/***	Devolução dos valores dos parametros			*************/
/********************************************************************/
float Parametros_controlador::Devolve_valores_lidos(int valor)
{
	switch (valor)
	{
		case 1:  return(m_Kp1);break;
		case 2:  return(m_Ti1);break;
		case 3:  return(m_Td1);break;
		case 4:  return(m_Kp2);break;
		case 5:  return(m_Ti2);break;
		case 6:  return(m_Td2);break;
		case 7:  return(m_Kp3);break;
		case 8:  return(m_Ti3);break;
		case 9:  return(m_Td3);break;
		case 10: return(m_Kp4);break;
		case 11: return(m_Ti4);break;
		case 12: return(m_Td4);break;
		case 13: return(m_Kp5);break;
		case 14: return(m_Ti5);break;
		case 15: return(m_Td5);break;
		case 16: return(m_Kp6);break;
		case 17: return(m_Ti6);break;
		case 18: return(m_Td6);break;	
		case 50: return((float)m_max_digital);break;
		case 51: return((float)m_min_digital);break;
		case 52: return(m_rot_max1);break;
		case 53: return(m_rot_max2);break;
		case 54: return(m_rot_max3);break;
		case 55: return(m_rot_max4);break;
		case 56: return(m_rot_max5);break;
		case 57: return(m_rot_max6);break;
		case 69: return((float)m_perna_chao_inicial);break;
		case 70: return(m_clock);break;
		case 71: return((float)m_amplitude_max);break;
		default: return ((float)-1); break;
	}
};
