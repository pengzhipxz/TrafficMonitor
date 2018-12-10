#pragma once
#include"Common.h"
#include "afxcmn.h"
#include "AdapterCommon.h"

// CNetworkInfoDlg �Ի���

class CNetworkInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetworkInfoDlg)

public:
	CNetworkInfoDlg(vector<NetWorkConection>& adapters, MIB_IFROW* pIfRow, int connection_selected, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetworkInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETWORK_INFO_DIALOG };
#endif

	SYSTEMTIME m_start_time;		//����������ʱ��

protected:

	vector<NetWorkConection>& m_connections;
	MIB_IFROW* m_pIfRow;
	int m_connection_selected;		//��ǰ�Ի�����ʾ������
	int m_current_connection;		//��ʼѡ�������

	CListCtrl m_info_list;
	CMenu m_menu;
	CString m_selected_string;
	CSize m_min_size;
	CFont m_font_bold;		//Ĭ������Ĵ���

	CWinThread* m_pGetIPThread;			//��ȡ����IP���߳�

	//void GetIPAddress();	//��ȡIP��ַ
	void ShowInfo();
	void GetProgramElapsedTime();

	//��ȡ����IP���̺߳���
	static UINT GetInternetIPThreadFunc(LPVOID lpParam);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCopyText();
	afx_msg void OnNMRClickInfoList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnBnClickedPreviousButton();
	afx_msg void OnBnClickedNextButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNMDblclkInfoList1(NMHDR *pNMHDR, LRESULT *pResult);
};
