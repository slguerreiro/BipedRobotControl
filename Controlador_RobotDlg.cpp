// Controlador_RobotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Controlador_Robot.h"
#include "Controlador_RobotDlg.h"

//#include "Parametros_controlador.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlador_RobotDlg dialog

CControlador_RobotDlg::CControlador_RobotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlador_RobotDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlador_RobotDlg)
	m_edit1 = 100;
	m_fichPos2 = _T("Teta2");
	m_fichPos1 = _T("Teta1");
	m_fichPos3 = _T("Teta3");
	m_fichPos4 = _T("Teta4");
	m_fichPos5 = _T("Teta5");
	m_fichPos6 = _T("Teta6");
	m_fichvel1 = _T("SIMULACAO_VEL_JUNTA1");
	m_fichvel2 = _T("SIMULACAO_VEL_JUNTA2");
	m_fichvel3 = _T("SIMULACAO_VEL_JUNTA3");
	m_fichvel4 = _T("SIMULACAO_VEL_JUNTA4");
	m_fichvel5 = _T("SIMULACAO_VEL_JUNTA5");
	m_fichvel6 = _T("SIMULACAO_VEL_JUNTA6");
	m_posjunMedidas = _T("MdPosJun");
	m_errposjunMedidas = _T("ErPosJun");
	m_veljunMedidas = _T("MdVelJun");
	m_errveljunMedidas = _T("ErVelJun");
	m_refdigpos = _T("RfPosDig");
	m_refdigvel = _T("RfVelDig");
	m_debug = _T("debug.ser");
	m_global_individual=-1;
	m_posicao_velocidade=-1;
	m_tipo_controlador=-1;
	m_actuacao = _T("ActuaJun");
	m_fichPassadas = _T("N_PASSADAS");
	m_passo_a_passo = FALSE;
	comecar_interpolacao = FALSE;
	m_leitura_sensores_contacto=FALSE;
	m_ajuste_rotacao=FALSE;
	Parametros_lidos = FALSE;
	apaga_tudo=TRUE;
	contador_linhas=0;
	NUM_MAX_LINHAS=16;
	EscreverEstado = new CString();
	Janela=new CRect(350,500,800,700);
	Janela2=new CRect (660,190,660+100,190+30);
	m_pe_chao = _T("Perna_Chao_Saida");
	buffer = new char(50);
	PernaActualChao = -1;
	escreve = TRUE;
	criou_robot = FALSE;
	imprime_tempo = FALSE;
	string_tempo=new char(20);
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	sair=TRUE;
}

void CControlador_RobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlador_RobotDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MinMaxInt(pDX, m_edit1, 1, 100);
	DDX_Text(pDX, IDC_EDIT3, m_fichPos2);
	DDV_MaxChars(pDX, m_fichPos2, 30);
	DDX_Text(pDX, IDC_EDIT2, m_fichPos1);
	DDV_MaxChars(pDX, m_fichPos1, 30);
	DDX_Text(pDX, IDC_EDIT4, m_fichPos3);
	DDV_MaxChars(pDX, m_fichPos3, 30);
	DDX_Text(pDX, IDC_EDIT5, m_fichPos4);
	DDV_MaxChars(pDX, m_fichPos4, 30);
	DDX_Text(pDX, IDC_EDIT6, m_fichPos5);
	DDV_MaxChars(pDX, m_fichPos5, 30);
	DDX_Text(pDX, IDC_EDIT7, m_fichPos6);
	DDV_MaxChars(pDX, m_fichPos6, 30);
	DDX_Text(pDX, IDC_EDIT8, m_fichvel1);
	DDV_MaxChars(pDX, m_fichvel1, 30);
	DDX_Text(pDX, IDC_EDIT9, m_fichvel2);
	DDV_MaxChars(pDX, m_fichvel2, 30);
	DDX_Text(pDX, IDC_EDIT10, m_fichvel3);
	DDV_MaxChars(pDX, m_fichvel3, 30);
	DDX_Text(pDX, IDC_EDIT11, m_fichvel4);
	DDV_MaxChars(pDX, m_fichvel4, 30);
	DDX_Text(pDX, IDC_EDIT12, m_fichvel5);
	DDV_MaxChars(pDX, m_fichvel5, 30);
	DDX_Text(pDX, IDC_EDIT13, m_fichvel6);
	DDV_MaxChars(pDX, m_fichvel6, 30);
	DDX_Text(pDX, IDC_EDIT14, m_posjunMedidas);
	DDX_Text(pDX, IDC_EDIT15, m_errposjunMedidas);
	DDX_Text(pDX, IDC_EDIT16, m_veljunMedidas);
	DDX_Text(pDX, IDC_EDIT17, m_errveljunMedidas);
	DDX_Text(pDX, IDC_EDIT18, m_refdigpos);
	DDX_Text(pDX, IDC_EDIT19, m_refdigvel);
	DDX_Text(pDX, IDC_EDIT20, m_debug);
	DDX_Text(pDX, IDC_EDIT21, m_actuacao);
	DDX_Text(pDX, IDC_EDIT40, m_fichPassadas);
	DDV_MaxChars(pDX, m_fichPassadas, 30);
	DDX_Text(pDX, IDC_EDIT44, m_pe_chao);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CControlador_RobotDlg, CDialog)
	//{{AFX_MSG_MAP(CControlador_RobotDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_EN_CHANGE(IDC_EDIT21, OnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, OnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnChangeEdit24)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDParametros, OnParametros)
	ON_EN_CHANGE(IDC_EDIT40, OnChangeEdit40)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, OnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, OnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, OnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, OnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_EN_CHANGE(IDC_EDIT44, OnChangeEdit44)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlador_RobotDlg message handlers

BOOL CControlador_RobotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	parametros = new Parametros_controlador;		
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CControlador_RobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CControlador_RobotDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CFont MyFont;
	
		MyFont.CreateFont(12,
			0,
			0,
			0,
			400,
			FALSE,
			FALSE,
			0,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			"Arial");
		CFont *pOldFont = dc.SelectObject(&MyFont);

		if (imprime_tempo)
		{				
			dc.TextOut(660,200,*EscreverEstado);
			dc.SelectObject(pOldFont);
		}
		else if (!apaga_tudo)
		{
			dc.TextOut(360+(200*((contador_linhas+1) % 2)),
						500+((int)((contador_linhas+1)/2))*10,*EscreverEstado);
			dc.SelectObject(pOldFont);
		}
	CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CControlador_RobotDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CControlador_RobotDlg::Degrau(int actuador)
{

	if (Robot->AmostraActual() < 10000/3)
	{
		Robot->FuncaoCaracteristicaServo(actuador,2100); // Rampa
	}
	else if (Robot->AmostraActual() < 2*(10000/3))
	{
		Robot->FuncaoCaracteristicaServo(actuador,1900); // Rampa
	}
	else Robot->FuncaoCaracteristicaServo(actuador,2100); // Rampa


	Robot->IncrementaNAmostras();
	m_progress.SetStep(1);
	m_progress.StepIt();

}


/*******************************************************************************************/
/****	Seguimento da trajectoria pre-definida											****/
/****	Se incrementa = 0  nao actualiza o identificador da posicao actual do movimento ****/
/****	Se incrementa = 1 actualiza o identificador da posicao actual do movimento		****/
/*******************************************************************************************/
void CControlador_RobotDlg::SegueTrajectoria(int incrementa)
{
	if (m_global_individual == TRUE && m_posicao_velocidade == TRUE)	Robot->ProcessaJuntaGlobalPosicao(m_tipo_controlador);
	else if (m_global_individual == TRUE && m_posicao_velocidade == FALSE) Robot->ProcessaJuntaGlobalVelocidade(m_tipo_controlador);
		else if (m_global_individual == FALSE && m_posicao_velocidade == TRUE) {for (int jun=1;jun<=6;jun++) Robot->ProcessaJuntaIndividualPosicao(jun,m_tipo_controlador);}
			else {for (int jun=1;jun<=6;jun++) Robot->ProcessaJuntaIndividualVelocidade(jun,m_tipo_controlador);}
			
	if (incrementa)
	{
		Robot->IncrementaNAmostras();
		m_progress.StepIt();
	}
};


/*******************************************************************************************/
/***	Seguimento de uma rampa															****/
/*******************************************************************************************/
void CControlador_RobotDlg::Rampa(int actuador)
{
	Robot->FuncaoCaracteristicaServo(actuador,/*2048+*/Robot->AmostraActual()*(4096/4000)  ); // Rampa
	Robot->IncrementaNAmostras();
	m_progress.SetStep(1);
	m_progress.StepIt();
};

/*******************************************************************************************/
/***	Seguimento de uma referencia													****/
/*******************************************************************************************/
void CControlador_RobotDlg::Escalao(int referencia,int actuador)
{
	Robot->FuncaoCaracteristicaServo(actuador,referencia);  // Escalao
	Robot->IncrementaNAmostras();
	m_progress.SetStep(1);
	m_progress.StepIt();
};

/*******************************************************************************************/
/****	Teste em velocidade para qualquer actuador. Permite obter o ganho real de cada actuador**/
/*******************************************************************************************/
void CControlador_RobotDlg::VerificacaoLinearidadeActuador(int actuador)
{
	int nivel_actuacao;
	
	if ((Robot->AmostraActual()) < ((Robot->NAmostras())))
		nivel_actuacao = 2048 - ((2048*Robot->AmostraActual())/((Robot->NAmostras())));
//	else nivel_actuacao = 2048 - (2048*(Robot->AmostraActual()-(Robot->NAmostras()/2))) / (Robot->NAmostras()/2);
	Robot->FuncaoCaracteristicaServo(actuador,nivel_actuacao);  
	Robot->IncrementaNAmostras();
	m_progress.SetStep(1);
	m_progress.StepIt();
	fprintf (ficheiro_linearidade,"%d\t%d\t%d\n",Robot->AmostraActual(),nivel_actuacao,Robot->DevolveVelocidadeMedida(actuador));
};

/*****************************************************************************************/
/***	Verifica mudanca da perna em contacto com o chao							******/
/*****************************************************************************************/
BOOL CControlador_RobotDlg::Mudouperna(int nova_perna)
{
	if (nova_perna != PernaActualChao)
	{	
		PernaActualChao=nova_perna;
		return(TRUE);
	}
	else return(FALSE);
}



/*****************************************************************************************/
/***	Avanca as amostras ate a passada actual - Quando houve mudanca de passada		**/
/*****************************************************************************************/
void CControlador_RobotDlg::AvancaAmostras(void)
{
 int amostras_saltadas=Robot->IncrementaNumeroPassada();
 for (int i=1;i<=amostras_saltadas;i++) 
 {
		Robot->IncrementaNAmostras();
	//	m_progress.SetStep(1);
		m_progress.StepIt();
 }
}



/*****************************************************************************************/
/********   Processamento de cada uma das interpolacoes									**/
/*****************************************************************************************/
void CControlador_RobotDlg::OnTimer(UINT nIDEvent) 
{
	BOOL comecar_passada_seguinte=FALSE;


	/*****************  Verificacao do tempo actual	*****/
	_ftime (&interp);
	char *timeline = ctime( & ( interp.time ) );		
	imprime_tempo=TRUE;
	_gcvt( (Robot->TempoActual()), 5, string_tempo);
   	*EscreverEstado = CString((LPCTSTR) "t=") + ((LPCTSTR)string_tempo) + CString((LPCTSTR) " segundos");
	InvalidateRect(Janela2,TRUE);
	OnPaint();
	imprime_tempo=FALSE;
	/******************************************************/
 
	if (!Robot->FimAmostragem()) 
	{

		if (m_leitura_sensores_contacto == TRUE)  // Passadas com interacção com o chao
		{
			//  Aquisicao por polling do estado do contacto do robot com o chao
			int Contacto_chao = Robot->Aquisicao_Sensores_Contacto();
			if (Mudouperna(Contacto_chao)) escreve = TRUE;
			else escreve = FALSE;

			if (contador_linhas >= NUM_MAX_LINHAS) 
			{
				apaga_tudo=TRUE;
				if (escreve) 
				{
					InvalidateRect(Janela,TRUE);
					contador_linhas=0;
				}

			}
			apaga_tudo=FALSE;
			

			fprintf (Pe_chao,"%g\t%d\n",Robot->TempoActual(),Contacto_chao);
			_gcvt( Robot->TempoActual(), 5, buffer );
   			*EscreverEstado = CString((LPCTSTR) "t=") + ((LPCTSTR) buffer);

			switch (Contacto_chao)
			{
			case 0:
				fprintf (fich_debug,"OnTimer %d\t%.19s.%hu Passada Actual=%d  !!O robot esta no ar!...\n", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());
				Robot->inicializar_actuadores();
				*EscreverEstado += ((LPCSTR) "s Nenhuma perna no chao");
				break; // Nenhuma no chao

			case 1:case 2: 
				if (Robot->CorrectaNoChao(Contacto_chao))
				{
										
					if (Robot->UltrapassouAmplitudePassada())	//Nao efectuar movimento
					{
						fprintf (fich_debug,"OnTimer %d\t%.19s.%hu Passada Actual=%d  !!O robot ja efectou todo o movimento para esta passada\n", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());
						Robot->inicializar_actuadores();
						//Robot->ReiniciarContadorAmostras();
					}
					else // continuar passada
					{
						if (Robot->UltrapassouTempoPassada()) SegueTrajectoria(0);
						else SegueTrajectoria(1);
						fprintf(fich_debug, "OnTimer %d\t%.19s.%hu Passada Actual=%d  !!Ainda nao acabou de descrever a passada actual\n", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());	

						if (Robot->UltrapassouTempoPassada())
						fprintf (fich_debug,"Ultrapassou tempo\n");
						else fprintf (fich_debug,"Nao Ultrapassou tempo\n");
					}
				}
				else //Comecar passada seguinte
				{
					fprintf (fich_debug,"\nEntrei no InCorrecta no chao");
					comecar_passada_seguinte=TRUE; 
				};

				if (Contacto_chao == 1) (*EscreverEstado) += (LPCSTR) "s Perna 1 no chão";
				else (*EscreverEstado) += (LPCSTR) "s Perna 2 no chão";
				break; // Perna 1 no chao ou Perna 2 no chao

			case 3: //Comecar passada seguinte
				comecar_passada_seguinte=TRUE; 
				(*EscreverEstado) += (LPCSTR) "s Duas pernas no chão";
				break; // Duas pernas no chao
			}
			
			if (escreve) 
			{
				contador_linhas++;
				InvalidateRect(Janela,FALSE);
			}
			
			if (comecar_passada_seguinte)
			{
				fprintf(fich_debug, "OnTimer %d\t%.19s.%hu Passada Actual=%d  !!Comeco de nova passada", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());	
				if (m_ajuste_rotacao)
				{
					KillTimer(1);
					fprintf (fich_debug,", com ajuste de rotacao\n");
					Robot->AjusteRotacaoBase();
					// SetTimer de novo...
				}
				else 
				{
					Robot->GuardarValoresCorrectivos();
					fprintf (fich_debug,", sem ajuste de rotacao\n");
				};
				AvancaAmostras();
				SegueTrajectoria(1);
				if (m_ajuste_rotacao) SetTimer(1,(int) ((float)((float)1.0/(float)m_edit1)*1000),NULL);
			}
		}
		else  // Passadas sem interaccao com o chao - Descricao das trajectorias no ar 
		{
		
		//////Para teste*/////////////
		int Contacto_chao = Robot->Aquisicao_Sensores_Contacto();
		fprintf (Pe_chao,"%g\t%d\n",Robot->TempoActual(),Contacto_chao);
		/////////////////////////////////////////
		
		SegueTrajectoria(1);
		fprintf(fich_debug, "OnTimer %d\t%.19s.%hu Passada Actual=%d\n", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());
		}
	}

	else // Fim de interpolacao - Atingiu instante final
	{
		KillTimer(1);
		FimInterpolacao(1);
	}
	CDialog::OnTimer(nIDEvent);
}


/*****************************************************************************************/
/***	Fim de interpolacao - validacao das variaveis necessarias					******/
/*****************************************************************************************/
void CControlador_RobotDlg::FimInterpolacao(int saida)
{
	delete (Robot);
	criou_robot = FALSE;
	MessageBeep((WORD) -1);
	switch (saida)
	{
		case 1: MessageBox("Fim de Interpolacao",NULL,MB_ICONINFORMATION); break;
		case 2: MessageBox("Amostra final, nao ha mais amostras a interpolar",NULL,MB_ICONINFORMATION);break;
		case 3: MessageBox("Amostra inicial, nao ha amostras a interpolar abaixo desta",NULL,MB_ICONSTOP);break;
	};
	fclose (fich_debug);
	fclose (Pe_chao);
	fclose (ficheiro_linearidade);
	comecar_interpolacao = FALSE;
	contador_linhas=0;
	apaga_tudo=TRUE;
	InvalidateRect(Janela);
}


/*****************************************************************************************/
/****	Imprime informacao sobre o estado actual do controlador							**/
/*****************************************************************************************/
void CControlador_RobotDlg::EscreveEstado(CString mensagem)
{
	contador_linhas++;
	*EscreverEstado = mensagem;
	InvalidateRect(Janela,FALSE);
	OnPaint();
}


/*****************************************************************************************/
/****  Inicio da interpolacao															**/
/*****************************************************************************************/
void CControlador_RobotDlg::OnOK() 
{
  fich_debug=fopen((LPCTSTR)m_debug,"w");
  Pe_chao=fopen ((LPCTSTR) m_pe_chao,"w");
  ficheiro_linearidade = fopen ("LINEARIDADE.ser","w");
  sair=FALSE;
  if (m_posicao_velocidade!=-1 && m_global_individual!=-1 && m_tipo_controlador!=-1)
  {
    if (Parametros_lidos == FALSE)
	{
		for (int con=1;con<=80;con++) Param[con]=parametros->Devolve_valores_lidos(con);
	};
	apaga_tudo=FALSE;
	EscreveEstado("Criacao do Robot...");
	Robot = new CComandaRobot	( m_edit1
								, (LPCTSTR) m_fichPos1
								, (LPCTSTR) m_fichPos2
								, (LPCTSTR) m_fichPos3
								, (LPCTSTR) m_fichPos4
								, (LPCTSTR) m_fichPos5
								, (LPCTSTR) m_fichPos6
								, (LPCTSTR) m_fichvel1
								, (LPCTSTR) m_fichvel2
								, (LPCTSTR) m_fichvel3
								, (LPCTSTR) m_fichvel4
								, (LPCTSTR) m_fichvel5
								, (LPCTSTR) m_fichvel6
								, (LPCTSTR) m_posjunMedidas
								, (LPCTSTR) m_errposjunMedidas
								, (LPCTSTR) m_veljunMedidas
								, (LPCTSTR) m_errveljunMedidas
								, (LPCTSTR) m_refdigpos
								, (LPCTSTR) m_refdigvel
								, (LPCTSTR) m_actuacao
								, (LPCTSTR) m_fichPassadas
								, (LPCTSTR) m_refdigpos
								, (LPCTSTR) m_refdigvel
								, Pe_chao
								, fich_debug 
								, Param);

	EscreveEstado("...Fim de criacao do Robot");
	criou_robot = TRUE;
	final = Robot->NAmostras();
	m_progress.SetRange(1,final+5);
	m_progress.SetStep(1);
	m_progress.SetPos(0);
	fprintf (fich_debug,"OnOK, N_amostras_totais=%d, Frequencia=%d\n",final,m_edit1);

	switch (m_global_individual)
	{
	case TRUE:	
		switch(m_posicao_velocidade)
		{
		case TRUE:fprintf (fich_debug,"Controlo Global - em posicao\n");break;
		case FALSE:fprintf (fich_debug,"Controlo Global - em velocidade\n");break;
		};
	break;
	case FALSE:
		switch(m_posicao_velocidade)
		{
		case TRUE:fprintf (fich_debug,"Controlo Individual - em posicao\n");break;
		case FALSE:fprintf (fich_debug,"Controlo Individual - em velocidade\n");break;
		};
	break;
	};
	
	switch (m_tipo_controlador)
	{
	case 1:fprintf (fich_debug,"Controlo Proporcional\n");break;
	case 2:fprintf (fich_debug,"Controlo Proporcional Integrativo\n");break;
	case 3:fprintf (fich_debug,"Controlo Proporcional Derivativo\n");break;
	case 4:fprintf (fich_debug,"Controlo Proporcional Integrativo Derivativo\n");break;
	};

	switch (m_leitura_sensores_contacto)
	{
	case TRUE:fprintf (fich_debug,"Proceder a leitura dos sensores de contacto\n");break;
	case FALSE:fprintf (fich_debug,"Nao proceder a leitura dos sensores de contacto\n");break;
	};

	switch (m_ajuste_rotacao)
	{
	case TRUE:fprintf (fich_debug,"Proceder ao ajuste de rotacao entre passadas\n");break;
	case FALSE:fprintf (fich_debug,"Nao proceder ao ajuste de rotacao entre passadas\n");break;
	};
	
	/*******  Calibracao do nivel 0 dos taquimetros		*****/
	EscreveEstado("Inicio de Calibracao...");
	Robot->Carregamento_Offset();
	EscreveEstado("...Fim Calibracao");
	/***********************************************************/

	/**** Colocacao do robot na sua postura inicial  ***/
	fprintf (fich_debug,"Colocacao na postura inicial ...\n");
	EscreveEstado("Colocacao na postura inicial...");
	Robot->PosturaInicial(0);
	EscreveEstado("...Robot na postura inicial");
	MessageBox("Na Posicao inicial... Inicio de Interpolacao");
	/***********************************************************/
	

	/*** Colocacao numa posicao  estatica antes de avancar		***/
	/**************************************************************/


	fprintf (fich_debug,"Inicio de Interpolacao...\n");
	if (m_passo_a_passo == FALSE) SetTimer(1,(int) ((float)((float)1.0/(float)m_edit1)*1000),NULL);
	comecar_interpolacao = TRUE;
  }
  else if (m_posicao_velocidade==-1) MessageBox("Variavel a controlar nao definida",NULL,MB_ICONSTOP);
  else if (m_global_individual==-1) MessageBox("Forma do controlo nao definido",NULL,MB_ICONSTOP);
  else if (m_tipo_controlador==-1) MessageBox("Tipo do controlador nao definido",NULL,MB_ICONSTOP);

}


/*****************************************************************************************/
/***	Fim de programa																******/
/*****************************************************************************************/
void CControlador_RobotDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(1);

	if (criou_robot) delete (Robot);

	if (sair == TRUE) 
	{
		fich_debug = fopen((LPCTSTR)m_debug,"w");
		Pe_chao = fopen((LPCTSTR)m_pe_chao,"w");
		ficheiro_linearidade = fopen ("LINEARIDADE.ser","w");
	}
	else fich_debug=fopen((LPCTSTR) m_debug ,"a");

	fprintf (fich_debug,"OnCancel, Fim de programa");
	fclose (fich_debug);
	fclose (Pe_chao);
	fclose (ficheiro_linearidade);
	delete (parametros);
	CDialog::OnCancel();
}




/********************************************************************************/
/******	FUNCOES DE ACTUALIZACAO DOS NOMES DAS VARIAVEIS DE ENTRADA E SAIDA	*****/
void CControlador_RobotDlg::OnChangeEdit21() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit22() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit23() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit24() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit40() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit10() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit11() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit12() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit13() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit14() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit15() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit16() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit17() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit18() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit19() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit20() {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit3()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit4()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit5()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit6()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit7()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit8()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit9()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit1()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit2()  {UpdateData(TRUE);}
void CControlador_RobotDlg::OnChangeEdit44() {UpdateData(TRUE);}

void CControlador_RobotDlg::OnRadio1() 
{
 m_global_individual = TRUE;
 UpdateData(TRUE);
}

void CControlador_RobotDlg::OnRadio2() 
{
	m_global_individual = FALSE;
	UpdateData(TRUE);
}

void CControlador_RobotDlg::OnRadio3() 
{
	m_posicao_velocidade=TRUE;
	UpdateData(TRUE);
}

void CControlador_RobotDlg::OnRadio4() 
{
	m_posicao_velocidade=FALSE;
	UpdateData(TRUE);
}


/********************************************************/
/*  m_tipo_controlador									*/
/*	=1 -> proporcional									*/
/*	=2 -> PI											*/
/*  =3 -> PD											*/
/*  =4 -> PID											*/
/********************************************************/ 
void CControlador_RobotDlg::OnRadio5() 
{
	m_tipo_controlador=1;	
	UpdateData(TRUE);
}

void CControlador_RobotDlg::OnRadio6() 
{
	m_tipo_controlador=2;	
	UpdateData(TRUE);
}

void CControlador_RobotDlg::OnRadio7() 
{
	m_tipo_controlador=3;	
	UpdateData(TRUE);
}

void CControlador_RobotDlg::OnRadio8() 
{
	m_tipo_controlador=4;	
	UpdateData(TRUE);
}

void CControlador_RobotDlg::OnParametros() 
{
	parametros->DoModal();	
	for (int con=1;con<=18;con++) Param[con]=parametros->Devolve_valores_lidos(con);
	for (con=50;con<58;con++) Param[con]=parametros->Devolve_valores_lidos(con);
	
	Parametros_lidos = TRUE;
}



/**** Button +  */
void CControlador_RobotDlg::OnButton3() 
{
	if (m_passo_a_passo == FALSE) MessageBox("Fora do modo Passo a Passo",NULL,MB_ICONSTOP);
	else 
	{
		if (comecar_interpolacao)
		{
			if (Robot->AmostraActual() < Robot->NAmostras())
			{
				_ftime (&interp);
				char *timeline = ctime( & ( interp.time ) );		
				if (final > Robot->AmostraActual())
				{
					for (int jun=1;jun<=6;jun++) Robot->ProcessaJuntaIndividualPosicao(jun,m_tipo_controlador);
					Robot->IncrementaNAmostras();
					m_progress.SetStep(1);
					m_progress.StepIt();
					fprintf(fich_debug, "Passo a Passo %d\t%.19s.%hu Passada Actual=%d\n", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());
					Robot->inicializar_actuadores();
				}
			}
			else 
			{	
				FimInterpolacao(2);
			}
		}
		else MessageBox("Iniciar Interpolacao em 'Comecar Interpolacao'",NULL,MB_ICONINFORMATION);
	};
}


/**** Button -  */
void CControlador_RobotDlg::OnButton2() 
{
	if (m_passo_a_passo == FALSE) MessageBox("Fora do modo Passo a Passo",NULL,MB_ICONSTOP);
	else 
	{
		if (comecar_interpolacao)
		{
			if (Robot->AmostraActual() > 1)
			{
				_ftime (&interp);
				char *timeline = ctime( & ( interp.time ) );		
				if (final > Robot->AmostraActual())
				{
					for (int jun=1;jun<=6;jun++) Robot->ProcessaJuntaIndividualPosicao(jun,m_tipo_controlador);
					Robot->DecrementaNAmostras();
					m_progress.SetStep(-1);
					m_progress.StepIt();
					fprintf(fich_debug, "Passo a Passo %d\t%.19s.%hu Passada Actual=%d\n", Robot->AmostraActual(),timeline, interp.millitm,Robot->NPassadaActual());
					Robot->inicializar_actuadores();
				}
			}
			else 
			{
				FimInterpolacao(3);
			}
		}
		else MessageBox("Iniciar Interpolacao em 'Comecar Interpolacao'",NULL,MB_ICONINFORMATION);
	};
}

/*** Check box do modo passo a passo   */
void CControlador_RobotDlg::OnCheck2() 
{
	if (comecar_interpolacao == FALSE) 
	{
		if (m_passo_a_passo == FALSE) m_passo_a_passo=TRUE;	
		else m_passo_a_passo = FALSE;
	}
}

void CControlador_RobotDlg::OnCheck3() 
{
	if (m_leitura_sensores_contacto == FALSE) m_leitura_sensores_contacto=TRUE;	
	else m_leitura_sensores_contacto=FALSE;
}

void CControlador_RobotDlg::OnCheck4() 
{
	if (m_ajuste_rotacao == FALSE) m_ajuste_rotacao = TRUE;	
	else m_ajuste_rotacao = FALSE;
	
}

/*******	FIM DAS FUNCOES DE ACTUALIZACAO DE INTERFACE			*************/
/********************************************************************************/