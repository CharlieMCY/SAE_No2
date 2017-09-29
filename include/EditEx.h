#if !defined(AFX_EDITEX_H__8471DBE6_A41F_441D_8705_AA6B3B894FBC__INCLUDED_)
#define AFX_EDITEX_H__8471DBE6_A41F_441D_8705_AA6B3B894FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEx.h : �إå��` �ե�����
//

typedef enum EDITEX_FMTTYPE {
	EDITEX_FMTTYPE_NORMAL	= 0,	//�ʤ�Ǥ���������
	EDITEX_FMTTYPE_INT,				//�������Τ��ܸ�
	EDITEX_FMTTYPE_DOUBLE,			//С���ܸ�
};

/////////////////////////////////////////////////////////////////////////////
// CEditEx ������ɥ�

class CEditEx : public CEdit
{
// ���󥹥ȥ饯�����
public:
	CEditEx();

// ���ȥ�ӥ�`��
public:

// ���ڥ�`�����
public:

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CEditEx)
	//}}AFX_VIRTUAL

// ����ץ���Ʃ`�����
public:
	virtual ~CEditEx();
	void SetRange(double dblMin, double dblMax);
	void SetFormat(EDITEX_FMTTYPE fmtType);
	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	double			m_foldValue;
	double			m_dblMinValue;
	double			m_dblMaxValue;
	BOOL			m_bChanging;
	CString			m_strFormat;
	EDITEX_FMTTYPE	m_fmtType;
	void OnChangeDouble();
	void OnChangeInt();
	//{{AFX_MSG(CEditEx)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ ��ǰ�Ф�ֱǰ��׷�Ӥ����Ԥ��뤷�ޤ���

#endif // !defined(AFX_EDITEX_H__8471DBE6_A41F_441D_8705_AA6B3B894FBC__INCLUDED_)