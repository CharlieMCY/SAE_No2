#if !defined(AFX_VSFLEXDATASOURCE_H__04391F14_757C_4375_A07C_C19C76B6DA62__INCLUDED_)
#define AFX_VSFLEXDATASOURCE_H__04391F14_757C_4375_A07C_C19C76B6DA62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//  Microsoft Visual C++ �ˤ�ä��Ԅ����ɤ��줿 IDispatch ��å� ���饹

// ���: ���Υե���������ݤ򾎼����ʤ��Ǥ��������� ���Υ��饹���ٶ�
//  Microsoft Visual C++ �����ɤ��줿���ϡ�������ϕ������ޤ���

/////////////////////////////////////////////////////////////////////////////
// CVSFlexDataSourceLU ��å� ���饹

class CVSFlexDataSourceLU : public COleDispatchDriver
{
public:
	CVSFlexDataSourceLU() {}		// COleDispatchDriver �ǥե���� ���󥹥ȥ饯�����
	CVSFlexDataSourceLU(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVSFlexDataSourceLU(const CVSFlexDataSourceLU& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// ���ȥ�ӥ�`��
public:

// ���ڥ�`�����
public:
	long GetFieldCount();
	long GetRecordCount();
	CString GetFieldName(long Field);
	CString GetData(long Field, long Record);
	void SetData(long Field, long Record, LPCTSTR newData);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ ��ǰ�Ф�ֱǰ��׷�Ӥ����Ԥ��뤷�ޤ���

#endif // !defined(AFX_VSFLEXDATASOURCE_H__04391F14_757C_4375_A07C_C19C76B6DA62__INCLUDED_)