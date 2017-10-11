// Controlador_RobotDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CControlador_RobotDlg dialog

#include "CDIGITAL.h"
#include "Parametros_controlador.h"


class CControlador_RobotDlg : public CDialog
{
// Construction
public:
	CControlador_RobotDlg(CWnd* pParent = NULL);	// standard constructor
	float Param[100];
	Parametros_controlador *parametros;
	
// Dialog Data
	//{{AFX_DATA(CControlador_RobotDlg)
	enum { IDD = IDD_CONTROLADOR_ROBOT_DIALOG };
	CProgressCtrl	m_progress;
	CComandaRobot *Robot;
	int		m_edit1;
	CString	m_fichPos2;
	CString	m_fichPos1;
	CString	m_fichPos3;
	CString	m_fichPos4;
	CString	m_fichPos5;
	CString	m_fichPos6;
	CString	m_fichvel1;
	CString	m_fichvel2;
	CString	m_fichvel3;
	CString	m_fichvel4;
	CString	m_fichvel5;
	CString	m_fichvel6;
	CString	m_posjunMedidas;
	CString	m_errposjunMedidas;
	CString	m_veljunMedidas;
	CString	m_errveljunMedidas;
	CString	m_refdigpos;
	CString	m_refdigvel;
	CString	m_debug;
	BOOL m_global_individual;
	BOOL m_posicao_velocidade;
	BOOL m_tipo_controlador;
	CString	m_actuacao;
	CString	m_fichPassadas;
	BOOL m_passo_a_passo;
	BOOL comecar_interpolacao;
	BOOL m_leitura_sensores_contacto;
	BOOL m_ajuste_rotacao;
	CString	m_pe_chao;
	BOOL criou_robot;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlador_RobotDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	int final;
	FILE *fich_debug;		// Ficheiro de saida para efectuar debug do controlador
	FILE *Pe_chao;			// Ficheiro do actual pe no chao
	FILE *ficheiro_linearidade;	// Ficheiro de debug do controlador - Verificacao da linearidade do motor
	struct _timeb interp;		// Estrutura de carregamento do tempo actual
	BOOL Parametros_lidos;		// Verifica actualizacao da janela de parametros de controlador
	BOOL sair;					// Verifica pedido de saida do programa
	void SegueTrajectoria(int);	// Segue trajectoria pretendida
	void Rampa(int);			// Actua motor em rampa
	void Escalao(int,int);		// Actua motor em escalao
	void VerificacaoLinearidadeActuador(int);	// Verifica linearidade de cada motor
	void FimInterpolacao(int);	// Actualizacoes necessria no fi mda interpolacao
	void Degrau(int actuador);	// Actua motor em degrau
	BOOL Mudouperna(int);		// funcao que determina se mudou de perna	
	void AvancaAmostras(void);	// Avanca amostras da interpolacao
	void EscreveEstado(CString); // Escreve estado do controlador no ecran
	BOOL apaga_tudo;			// Para apagar ecran todo
	int contador_linhas;		// Numero de linhas escritas no ecran
	CString *EscreverEstado;	// String a escrever	
	int NUM_MAX_LINHAS;			// Numero maximo de linahs no ecran
	CRect *Janela,*Janela2;		// Janelas de escrita na dialog box do controlador
	char *buffer;				// Buffer temporario		
	int PernaActualChao;		// Qual a perna no chão em cada instante
	BOOL escreve;				// Permissao para escrever o estado no ecran 
	BOOL imprime_tempo;			// Permissao para o tempo no ecran
	char *string_tempo;			// Buffer para escrita do tempo actual
	

	// Generated message map functions
	//{{AFX_MSG(CControlador_RobotDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnChangeEdit21();
	afx_msg void OnChangeEdit22();
	afx_msg void OnChangeEdit23();
	afx_msg void OnChangeEdit24();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnParametros();
	afx_msg void OnChangeEdit40();
	afx_msg void OnChangeEdit10();
	afx_msg void OnChangeEdit11();
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit16();
	afx_msg void OnChangeEdit17();
	afx_msg void OnChangeEdit18();
	afx_msg void OnChangeEdit19();
	afx_msg void OnChangeEdit20();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnChangeEdit44();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
