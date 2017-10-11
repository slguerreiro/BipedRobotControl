// Parametros_controlador.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Parametros_controlador dialog

class Parametros_controlador : public CDialog
{
// Construction
public:
	Parametros_controlador(CWnd* pParent = NULL);   // standard constructor
	float Devolve_valores_lidos(int);	// Vector com valores da dialog box

// Dialog Data
	//{{AFX_DATA(Parametros_controlador)
	enum { IDD = IDD_DIALOG1 };
	/******************   Variaveis de controlo dos parametros	******/
	float	m_Kp1;
	float	m_Ti1;
	float	m_Td1;
	float	m_Kp2;
	float	m_Ti2;
	float	m_Td2;
	float	m_Kp3;
	float	m_Ti3;
	float	m_Td3;
	float	m_Kp4;
	float	m_Ti4;
	float	m_Td4;
	float	m_Kp5;
	float	m_Ti5;
	float	m_Td5;
	float	m_Kp6;
	float	m_Ti6;
	float	m_Td6;
	int		m_max_digital;
	int		m_min_digital;
	float	m_rot_max1;
	float	m_rot_max2;
	float	m_rot_max3;
	float	m_rot_max4;
	float	m_rot_max5;
	float	m_rot_max6;
	float	m_clock;
	int		m_perna_chao_inicial;
	int		m_amplitude_max;
	/*******************************************************************/
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Parametros_controlador)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Parametros_controlador)
	virtual void OnOK();
	afx_msg void OnChangeEdit22();
	afx_msg void OnChangeEdit23();
	afx_msg void OnChangeEdit24();
	afx_msg void OnChangeEdit25();
	afx_msg void OnChangeEdit26();
	afx_msg void OnChangeEdit27();
	afx_msg void OnChangeEdit28();
	afx_msg void OnChangeEdit29();
	afx_msg void OnChangeEdit30();
	afx_msg void OnChangeEdit34();
	afx_msg void OnChangeEdit35();
	afx_msg void OnChangeEdit36();
	afx_msg void OnChangeEdit37();
	afx_msg void OnChangeEdit38();
	afx_msg void OnChangeEdit39();
	afx_msg void OnChangeEdit40();
	afx_msg void OnChangeEdit41();
	afx_msg void OnChangeEdit42();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit31();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit32();
	afx_msg void OnChangeEdit33();
	afx_msg void OnChangeEdit43();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
