#if !defined(AFX_VSFLEXNODELU_H__802E30BE_044B_4421_A0C2_479B130FAC39__INCLUDED_)
#define AFX_VSFLEXNODELU_H__802E30BE_044B_4421_A0C2_479B130FAC39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//  Microsoft Visual C++ �ˤ�ä��Ԅ����ɤ��줿 IDispatch ��å� ���饹

// ���: ���Υե���������ݤ򾎼����ʤ��Ǥ��������� ���Υ��饹���ٶ�
//  Microsoft Visual C++ �����ɤ��줿���ϡ�������ϕ������ޤ���


// ���Υ��󥿩`�ե������ˤ�äƲ��դ����ǥ����ѥå� ���󥿩`�ե�������
class CPicture;

/////////////////////////////////////////////////////////////////////////////
// CVSFlexNodeLU ��å� ���饹

class CVSFlexNodeLU : public COleDispatchDriver
{
public:
	CVSFlexNodeLU() {}		// COleDispatchDriver �ǥե���� ���󥹥ȥ饯�����
	CVSFlexNodeLU(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVSFlexNodeLU(const CVSFlexNodeLU& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// ���ȥ�ӥ�`��
public:

// ���ڥ�`�����
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CString GetKey();
	void SetKey(LPCTSTR lpszNewValue);
	CPicture GetImage();
	void SetImage(LPDISPATCH newValue);
	void SetRefImage(LPDISPATCH newValue);
	BOOL GetExpanded();
	void SetExpanded(BOOL bNewValue);
	short GetLevel();
	long GetChildren();
	long GetRow();
	void SetRow(long nNewValue);
	BOOL Move(long MoveTo, const VARIANT& TargetNode);
	void Sort(long How);
	void EnsureVisible();
	void Select();
	CVSFlexNodeLU GetNode(long Which);
	CVSFlexNodeLU AddNode(long AddWhere, LPCTSTR Item, const VARIANT& Key, const VARIANT& Image);
	void RemoveNode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ ��ǰ�Ф�ֱǰ��׷�Ӥ����Ԥ��뤷�ޤ���

#endif // !defined(AFX_VSFLEXNODELU_H__802E30BE_044B_4421_A0C2_479B130FAC39__INCLUDED_)