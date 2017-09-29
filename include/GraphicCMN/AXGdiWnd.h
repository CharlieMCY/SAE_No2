// AXGdiWnd.h ���饹�Υ��󥿩`�ե�����
//
/********************************************************
// CLineStyleDisp	:�饤��&�ީ`���`�������룫ɫ����TEXTWnd���饹
// CLineButton		:�饤��&�ީ`���`��������ܥ��󥯥饹
// CLineStyleDlg	:�饤��&�ީ`���`������������������饹
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(_AXGDIWND_H_INCLUDED_)
#define _AXGDIWND_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxGdiCore.h"

/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp ������ɥ�
class CLineStyleDisp : public CAXStringWnd, public CAXLineStyle, public CAXMarkerStyle
{
// ���󥹥ȥ饯�����
public:
	CLineStyleDisp(COLORREF bkColor = ICTRLCOLOR);

// ���ȥ�ӥ�`��
public:
	///<�軭�ީ`����
	inline int SetLineMargins(int iMargin = 2);
	inline int GetLineMargins(void)	{	return m_iMargin;	}
	///<�ָ�
	inline BOOL SetSeparateRatio(double dblRatio);
	inline double GetSeparateRatio(void)	{	return m_dblSeparateRatio;	}

// ���ڥ�`�����
public:
	//�軭
	virtual void DrawItem( CDC *pDC, CRect rect, CFont *pTextFont = NULL );
	void DrawSeparater( CDC *pDC, const CRect &rect );
	inline BOOL ShowSepareter(BOOL bShow = TRUE);
	void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){
			Invalidate(bErase);
			UpdateWindow();
		}
	};

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CLineStyleDisp)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	virtual BOOL OnChangeStyle(AXGCNOTIFY *pNotifyMsg );
// ����ץ���Ʃ`�����
public:
	virtual ~CLineStyleDisp();

	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	//{{AFX_MSG(CLineStyleDisp)
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	int			m_iMargin;				///< �ީ`����
	BOOL		m_bSepareterVisible;	///< ���ѥ�`�Ȗ���ʾ�ե饰
	double		m_dblSeparateRatio;		///< ���ѥ�`��
};
/////////////////////////////////////////////////////////////////////////////
// CLineButton ������ɥ�
/// ɫ�Ĥ��ܥ���
class CLineButton : public CButton, virtual public CAXGDIFrame, virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
// ���󥹥ȥ饯�����
public:
	CLineButton();

// ���ȥ�ӥ�`��
public:

// ���ڥ�`�����
public:

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CLineButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// ����ץ���Ʃ`�����
public:
	virtual ~CLineButton();

	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	//{{AFX_MSG(CLineButton)

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	UINT		m_uiStyle;			///< �ܥ��󥹥�����
	BOOL		m_bBtnDown;			///< �ܥ���Ѻ���Хե饰
	int			m_iCheck;			///< �F�ڤΥ����å�״�B

protected:

public:
	// �ٱ�ʾ
	virtual void Redraw(BOOL bErase = FALSE);
	
	// �����å�״�B�O��/ȡ��
	int  GetCheck();
	void SetCheck( int iCheck );
};
/////////////////////////////////////////////////////////////////////////////
// CLineStyleDlg ��������

class CLineStyleDlg : public CColorDialog,  virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
	DECLARE_DYNAMIC(CLineStyleDlg)

public:
	CLineStyleDlg( COLORREF clrInit = 0, DWORD dwFlags = 0, CWnd* pParentWnd = NULL );

	//{{AFX_DATA(CLineStyleDlg)
	CComboBox	m_lineTypeCombo;
	CComboBox	m_lineSizeCombo;
	CComboBox	m_markTypeCombo;
	CComboBox	m_markSizeCombo;
	CComboBox	m_markBkStyleCombo;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CLineStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ���ݩ`��
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CLineStyleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//�O�������x
protected:
	static const int CLineStyleDlg::c_iLineStyle[];
	static const int CLineStyleDlg::c_iMarkStyle[];
	static const char * CLineStyleDlg::c_cLineSize[];
	static const char * CLineStyleDlg::c_cMarkSize[];
	static const char * CLineStyleDlg::c_cMarkBkStyle[];

private:
	int m_iShowLineType;	///< ���N������������ܱ�ʾ/�Ǳ�ʾ
	int m_iShowLineSize;	///< ����������������ܱ�ʾ/�Ǳ�ʾ
	int m_iShowMarkType;	///< �ީ`���N��������ܱ�ʾ/�Ǳ�ʾ
	int m_iShowMarkSize;	///< �ީ`������������ܱ�ʾ/�Ǳ�ʾ
	int m_iShowMarkBkStyle;	///< �ީ`���`��������ܱ�ʾ/�Ǳ�ʾ

private:
	void OnOK();

public:
	int DoModal( int iStyle = PS_SOLID, int iSize = 0, int iMarker = 0, int iMarkSize = 8 );

	int DoModal( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
	{	
		CAXLineStyle::SetLineStyle(lineStyle);
		CAXMarkerStyle::SetMarkerStyle(markStyle);
		return CColorDialog::DoModal();
	}

	int DoModal( const LINESTYLE &lineStyle )
	{	
		CAXLineStyle::SetLineStyle(lineStyle);
		ShowMark(FALSE);
		return CColorDialog::DoModal();
	}

	/**
	 * 	���������O���α�ʾ/�Ǳ�ʾ.
	 * 	@param bEnable	TRUE:��ʾ FALSE:�Ǳ�ʾ
	 */
	void ShowLineSize( BOOL bEnable ){
		m_iShowLineSize = bEnable? SW_SHOW: SW_HIDE;
	}

	/**
	 * 	�ީ`���O���α�ʾ/�Ǳ�ʾ.
	 * 	@param bEnable	TRUE:��ʾ FALSE:�Ǳ�ʾ
	 */
	void ShowMark( BOOL bEnable ){
		m_iShowMarkType = bEnable? SW_SHOW: SW_HIDE;
		m_iShowMarkSize = bEnable? SW_SHOW: SW_HIDE;
		m_iShowMarkBkStyle = bEnable? SW_SHOW: SW_HIDE;	///< �ީ`���`��������ܱ�ʾ/�Ǳ�ʾ
	}

	/**
	 * 	�ީ`���������O���α�ʾ/�Ǳ�ʾ.
	 * 	@param bEnable	TRUE:��ʾ FALSE:�Ǳ�ʾ
	 */
	void ShowMarkSize( BOOL bEnable ){
		m_iShowMarkSize = bEnable? SW_SHOW: SW_HIDE;
	}
	/**
	 * 	�ީ`���`�����α�ʾ/�Ǳ�ʾ.
	 * 	@param bEnable	TRUE:��ʾ FALSE:�Ǳ�ʾ
	 */
	void ShowMarkBack( BOOL bEnable ){
		m_iShowMarkBkStyle = bEnable? SW_SHOW: SW_HIDE;	///< �ީ`���`��������ܱ�ʾ/�Ǳ�ʾ
	}
	/**
	 * 	����ä�С����Υ��������ˤ���.
	 */
	void SetSmallSize( void ){
		m_cc.lpTemplateName = "ChooseLineStyleEx";
	}
};
/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp
///////////////////////////////////////
/**
 * 	�軭�ީ`������O������.
 * 
 * 	@param iMargin	�軭�ީ`����
 * 	@return			��ǰ���軭�ީ`����
 */
inline int CLineStyleDisp::SetLineMargins(int iMargin /*= 2*/)
{
	int iOldMargin = m_iMargin;
	m_iMargin = iMargin;
	return iOldMargin;
}
///////////////////////////////////////
/**
 * 	���ѥ�`�ȱ��ʤ��O������.
 * 
 * 	@param bShow	���ѥ�`�ȱ��ʣ����^�Ζ��α���0.0��1.0)
 * 	@return			�O��OK/NG
 */
inline BOOL CLineStyleDisp::SetSeparateRatio(double dblRatio)
{
	if(dblRatio < 0.0 || dblRatio > 1.0 )	{	return FALSE;	}
	m_dblSeparateRatio = dblRatio;
	return TRUE;
}
///////////////////////////////////////
/**
 * 	���ѥ�`�Ȗ���ʾ�ե饰
 * 
 * 	@param bShow	���ѥ�`�Ȗ���ʾ �Є�/�o��
 * 	@return			��ǰ�Υ��ѥ�`�Ȗ���ʾ�ե饰
 */
inline BOOL CLineStyleDisp::ShowSepareter(BOOL bShow /*= TRUE*/)
{	
	BOOL bOld = m_bSepareterVisible;
	m_bSepareterVisible = bShow;
	return bOld;
}
#endif // !defined(_AXGDIWND_H_INCLUDED_)