/**
 * 	@file	FGridDef.h
 *	VSFlexGrid 7.0 �äζ������x�ե�����
 * 
 *	@date	2005.07.27	s.yotsutsu ����
 */

#ifndef	_FGRIDDEF_H_
#define	_FGRIDDEF_H_

	typedef enum RESIZE_KIND{
		XY_RESIZE = 0,		///<X����Y����΁I�����Resize
		X_RESIZE,			///<X����Resize
		Y_RESIZE,			///<Y����Resize
	}ResizeKind;

	typedef enum MERGE_KIND{
		MERGE_NEVER = 0,	// 0	flexMergeNever	�ީ`�����ʤ����ǥե���ȣ�
		MERGE_FREE,			// 1	flexMergeFree	����gλͬһ���ݤ�֤��O�Ӥ��������ީ`�����ޤ���MergeRow�ޤ���MergeCol�Τ����줫��True���O������Ƥ�����ϣ���
		MERGE_ROWS,			// 2	flexMergeRestrictRows	�з�����Υ��뤬�ީ`���������ϤΤߡ��Ф�ީ`�����ޤ���
		MERGE_COLS,			// 3	flexMergeRestrictColumns	�з����ϤΥ��뤬�ީ`���������ϤΤߡ��Ф�ީ`�����ޤ���
		MERGE_ALL,			// 4	flexMergeRestrictAll	�Ф����Ϥ��뤤����Υ��뤬�ީ`���������ϤΤߡ������ީ`�����ޤ���
		MERGE_FIXED,		// 5	flexMergeFixedOnly	�̶�����Τ�
		MERGE_SPILL,		// 6	flexMergeSpill	�O�ؤϤߤ����O�Υ��뤬�դǤ����ޤꡢ�L������ȥ���O�Υ���ˤϤ߳����Ʊ�ʾ�Ǥ��ޤ���
		MERGE_OUTLINE,		// 7	flexMergeOutline	СӋ�Ф��O�ؤϤߤ���СӋ�Ф΂����O�Ӥ���հץ����ϤˤϤߤ����Ʊ�ʾ�Ǥ��ޤ��������O������ʹ�ä���ȡ������ȥ饤��Ω`���ϤˤϥΩ`����������ͨ�����У��Ω`�ɤǤϤʤ��У��ˤϥǩ`�����ʾ�Ǥ��ޤ���
	}MergeKind;

#endif	/* _FGRIDDEF_H_*/