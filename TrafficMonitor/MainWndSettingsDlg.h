#pragma once
#include "ColorStatic.h"
#include "afxwin.h"
#include "SpinEdit.h"
#include "TabDlg.h"
#include "MainWndColorDlg.h"

// CMainWndSettingsDlg �Ի���

class CMainWndSettingsDlg : public CTabDlg
{
	DECLARE_DYNAMIC(CMainWndSettingsDlg)

public:
	CMainWndSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainWndSettingsDlg();

	//ѡ����������
	MainWndSettingData m_data;

	bool m_text_disable{ false };	//���Ϊtrue�����������á���ʾ�ı����������������ϴ������ص�λ��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_WND_SETTINGS_DIALOG };
#endif

protected:
	//�ؼ�����
	CColorStatic m_color_static;
	CToolTipCtrl m_toolTip;
	CComboBox m_unit_combo;
	CButton m_hide_unit_chk;
	CSpinEdit m_font_size_edit;
	CComboBox m_double_click_combo;

	void DrawStaticColor();
	void IniUnitCombo();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeUploadEdit();
	afx_msg void OnEnChangeDownloadEdit();
	afx_msg void OnEnChangeCpuEdit();
	afx_msg void OnEnChangeMemoryEdit();
	afx_msg void OnBnClickedSetDefaultButton();
	afx_msg void OnBnClickedSetFontButton();
	afx_msg void OnBnClickedSwitchUpDownCheck();
	afx_msg void OnBnClickedFullscreenHideCheck();
	afx_msg void OnBnClickedSpeedShortModeCheck2();
	afx_msg void OnCbnSelchangeUnitCombo();
	afx_msg void OnBnClickedHideUnitCheck();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	afx_msg void OnBnClickedHidePercentageCheck();
protected:
	afx_msg LRESULT OnStaticClicked(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedSpecifyEachItemColorCheck();
	afx_msg void OnCbnSelchangeDoubleClickCombo();
	afx_msg void OnBnClickedSeparateValueUnitCheck();
	afx_msg void OnBnClickedUnitByteRadio();
	afx_msg void OnBnClickedUnitBitRadio();
};
