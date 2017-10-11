#ifndef __MDCTEXT_H__
#define __MDCTEXT_H__

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;
class CPicture;

/////////////////////////////////////////////////////////////////////////////
// CMdcText wrapper class

class CMdcText : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMdcText)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8bd21d10, 0xec42, 0x11ce, { 0x9e, 0xd, 0x0, 0xaa, 0x0, 0x60, 0x2, 0xf3 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	// method 'QueryInterface' not emitted because of invalid return type or parameter type
	unsigned long AddRef();
	unsigned long Release();
	// method 'GetTypeInfoCount' not emitted because of invalid return type or parameter type
	// method 'GetTypeInfo' not emitted because of invalid return type or parameter type
	// method 'GetIDsOfNames' not emitted because of invalid return type or parameter type
	// method 'Invoke' not emitted because of invalid return type or parameter type
	void SetAutoSize(BOOL bNewValue);
	BOOL GetAutoSize();
	void SetAutoTab(BOOL bNewValue);
	BOOL GetAutoTab();
	void SetAutoWordSelect(BOOL bNewValue);
	BOOL GetAutoWordSelect();
	void SetBackColor(long nNewValue);
	long GetBackColor();
	void SetBackStyle(long nNewValue);
	long GetBackStyle();
	void SetBorderColor(long nNewValue);
	long GetBorderColor();
	void SetBorderStyle(long nNewValue);
	long GetBorderStyle();
	void SetBordersSuppress(BOOL bNewValue);
	BOOL GetBordersSuppress();
	BOOL GetCanPaste();
	void SetCurLine(long nNewValue);
	long GetCurLine();
	long GetCurTargetX();
	long GetCurTargetY();
	void SetCurX(long nNewValue);
	long GetCurX();
	void SetCurY(long nNewValue);
	long GetCurY();
	void SetDropButtonStyle(long nNewValue);
	long GetDropButtonStyle();
	void SetEnterKeyBehavior(BOOL bNewValue);
	BOOL GetEnterKeyBehavior();
	void SetEnabled(BOOL bNewValue);
	BOOL GetEnabled();
	void Set_Font_Reserved(LPDISPATCH newValue);
	void SetFont(LPDISPATCH newValue);
	COleFont GetFont();
	void SetFontBold(BOOL bNewValue);
	BOOL GetFontBold();
	void SetFontItalic(BOOL bNewValue);
	BOOL GetFontItalic();
	void SetFontName(LPCTSTR lpszNewValue);
	CString GetFontName();
	void SetFontSize(const CY& newValue);
	CY GetFontSize();
	void SetFontStrikethru(BOOL bNewValue);
	BOOL GetFontStrikethru();
	void SetFontUnderline(BOOL bNewValue);
	BOOL GetFontUnderline();
	void SetFontWeight(short nNewValue);
	short GetFontWeight();
	void SetForeColor(long nNewValue);
	long GetForeColor();
	void SetHideSelection(BOOL bNewValue);
	BOOL GetHideSelection();
	void SetIntegralHeight(BOOL bNewValue);
	BOOL GetIntegralHeight();
	long GetLineCount();
	void SetLocked(BOOL bNewValue);
	BOOL GetLocked();
	void SetMaxLength(long nNewValue);
	long GetMaxLength();
	void SetMouseIcon(LPDISPATCH newValue);
	void SetMouseIcon(LPDISPATCH newValue);
	CPicture GetMouseIcon();
	void SetMousePointer(long nNewValue);
	long GetMousePointer();
	void SetMultiLine(BOOL bNewValue);
	BOOL GetMultiLine();
	void SetPasswordChar(LPCTSTR lpszNewValue);
	CString GetPasswordChar();
	void SetScrollBars(long nNewValue);
	long GetScrollBars();
	void SetSelectionMargin(BOOL bNewValue);
	BOOL GetSelectionMargin();
	void SetSelLength(long nNewValue);
	long GetSelLength();
	void SetSelStart(long nNewValue);
	long GetSelStart();
	void SetSelText(LPCTSTR lpszNewValue);
	CString GetSelText();
	void SetShowDropButtonWhen(long nNewValue);
	long GetShowDropButtonWhen();
	void SetSpecialEffect(long nNewValue);
	long GetSpecialEffect();
	void SetTabKeyBehavior(BOOL bNewValue);
	BOOL GetTabKeyBehavior();
	void SetText(LPCTSTR lpszNewValue);
	CString GetText();
	void SetTextAlign(long nNewValue);
	long GetTextAlign();
	long GetTextLength();
	BOOL GetValid();
	void SetValue(VARIANT* newValue);
	VARIANT GetValue();
	void SetWordWrap(BOOL bNewValue);
	BOOL GetWordWrap();
	void Copy();
	void Cut();
	void Paste();
	void SetIMEMode(long nNewValue);
	long GetIMEMode();
	void SetEnterFieldBehavior(long nNewValue);
	long GetEnterFieldBehavior();
	void SetDragBehavior(long nNewValue);
	long GetDragBehavior();
	long GetDisplayStyle();
};

#endif // __MDCTEXT_H__