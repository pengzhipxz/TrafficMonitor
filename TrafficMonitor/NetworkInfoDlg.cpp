// CNetworkInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "NetworkInfoDlg.h"
#include "afxdialogex.h"


// CNetworkInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CNetworkInfoDlg, CDialog)

CNetworkInfoDlg::CNetworkInfoDlg(vector<NetWorkConection>& adapters, MIB_IFROW* pIfRow, int connection_selected, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NETWORK_INFO_DIALOG, pParent), m_connections(adapters), m_pIfRow(pIfRow), m_connection_selected(connection_selected)
{
	m_current_connection = connection_selected;
}

CNetworkInfoDlg::~CNetworkInfoDlg()
{
}


void CNetworkInfoDlg::ShowInfo()
{
	CString temp;
	MIB_IFROW& network_info = m_pIfRow[m_connections[m_connection_selected].index];
	//�ӿ���
	m_info_list.SetItemText(0, 1, network_info.wszName);
	//�ӿ�����
	m_info_list.SetItemText(1, 1, CCommon::StrToUnicode((const char*)network_info.bDescr).c_str());
	//��������
	switch (network_info.dwType)
	{
	case IF_TYPE_OTHER: temp = CCommon::LoadText(IDS_IF_TYPE_OTHER); break;
	case IF_TYPE_ETHERNET_CSMACD: temp = CCommon::LoadText(IDS_IF_TYPE_ETHERNET_CSMACD); break;
	case IF_TYPE_ISO88025_TOKENRING: temp = CCommon::LoadText(IDS_IF_TYPE_ISO88025_TOKENRING); break;
	case IF_TYPE_FDDI: temp = CCommon::LoadText(IDS_IF_TYPE_FDDI); break;
	case IF_TYPE_PPP: temp = CCommon::LoadText(IDS_IF_TYPE_PPP); break;
	case IF_TYPE_SOFTWARE_LOOPBACK: temp = CCommon::LoadText(IDS_IF_TYPE_SOFTWARE_LOOPBACK); break;
	case IF_TYPE_ATM: temp = CCommon::LoadText(IDS_IF_TYPE_ATM); break;
	case IF_TYPE_IEEE80211: temp = CCommon::LoadText(IDS_IF_TYPE_IEEE80211); break;
	case IF_TYPE_TUNNEL: temp = CCommon::LoadText(IDS_IF_TYPE_TUNNEL); break;
	case IF_TYPE_IEEE1394: temp = CCommon::LoadText(IDS_IF_TYPE_IEEE1394); break;
	case IF_TYPE_IEEE80216_WMAN: temp = CCommon::LoadText(IDS_IF_TYPE_IEEE80216_WMAN); break;
	case IF_TYPE_WWANPP: temp = CCommon::LoadText(IDS_IF_TYPE_WWANPP); break;
	case IF_TYPE_WWANPP2: temp = CCommon::LoadText(IDS_IF_TYPE_WWANPP2); break;
	default: temp = CCommon::LoadText(IDS_UNKNOW_CONNECTION); break;
	}
	m_info_list.SetItemText(2, 1, temp);
	//�ٶ�
	temp.Format(_T("%dMbps"), network_info.dwSpeed / 1000000);
	m_info_list.SetItemText(3, 1, temp);
	//�����������ַ
	temp = _T("");
	char buff[3];
	for (size_t i{}; i < network_info.dwPhysAddrLen; i++)
	{
		sprintf_s(buff, "%.2x", network_info.bPhysAddr[i]);
		temp += buff;
		if (i != network_info.dwPhysAddrLen - 1)
			temp += _T('-');
	}
	m_info_list.SetItemText(4, 1, temp);
	//IP��ַ
	m_info_list.SetItemText(5, 1, m_connections[m_connection_selected].ip_address.c_str());
	//��������
	m_info_list.SetItemText(6, 1, m_connections[m_connection_selected].subnet_mask.c_str());
	//Ĭ������
	m_info_list.SetItemText(7, 1, m_connections[m_connection_selected].default_gateway.c_str());
	//����״̬
	switch (network_info.dwOperStatus)
	{
	case IF_OPER_STATUS_NON_OPERATIONAL: temp = CCommon::LoadText(IDS_IF_OPER_STATUS_NON_OPERATIONAL); break;
	case IF_OPER_STATUS_UNREACHABLE: temp = CCommon::LoadText(IDS_IF_OPER_STATUS_UNREACHABLE); break;
	case IF_OPER_STATUS_DISCONNECTED: temp = CCommon::LoadText(IDS_IF_OPER_STATUS_DISCONNECTED); break;
	case IF_OPER_STATUS_CONNECTING: temp = CCommon::LoadText(IDS_IF_OPER_STATUS_CONNECTING); break;
	case IF_OPER_STATUS_CONNECTED: temp = CCommon::LoadText(IDS_IF_OPER_STATUS_CONNECTED); break;
	case IF_OPER_STATUS_OPERATIONAL: temp = CCommon::LoadText(IDS_IF_OPER_STATUS_OPERATIONAL); break;
	default: temp = CCommon::LoadText(IDS_UNKNOW_STATUS); break;
	}
	m_info_list.SetItemText(8, 1, temp);
	//�ѽ����ֽ���
	temp.Format(_T("%s (%s)"), CCommon::IntToString(network_info.dwInOctets, true, true), CCommon::DataSizeToString(network_info.dwInOctets));
	m_info_list.SetItemText(9, 1, temp);
	//�ѷ����ֽ���
	temp.Format(_T("%s (%s)"), CCommon::IntToString(network_info.dwOutOctets, true, true), CCommon::DataSizeToString(network_info.dwOutOctets));
	m_info_list.SetItemText(10, 1, temp);
	//�Գ������������ѽ����ֽ���
	unsigned int in_bytes_since_start;
	in_bytes_since_start = network_info.dwInOctets - m_connections[m_connection_selected].in_bytes;
	temp.Format(_T("%s (%s)"), CCommon::IntToString(in_bytes_since_start, true, true), CCommon::DataSizeToString(in_bytes_since_start));
	m_info_list.SetItemText(11, 1, temp);
	//�Գ������������ѷ����ֽ���
	unsigned int out_bytes_since_start;
	out_bytes_since_start = network_info.dwOutOctets - m_connections[m_connection_selected].out_bytes;
	temp.Format(_T("%s (%s)"), CCommon::IntToString(out_bytes_since_start, true, true), CCommon::DataSizeToString(out_bytes_since_start));
	m_info_list.SetItemText(12, 1, temp);

	//��ʾ��ǰѡ��ָʾ
	CString str;
	str.Format(_T("%d/%d"), m_connection_selected + 1, m_connections.size());
	SetDlgItemText(IDC_INDEX_STATIC, str);
	CFont* font = GetFont();
	CWnd* index_static = GetDlgItem(IDC_INDEX_STATIC);
	if (m_current_connection == m_connection_selected)
		index_static->SetFont(&m_font_bold);
	else
		index_static->SetFont(font);
}

void CNetworkInfoDlg::GetProgramElapsedTime()
{
	//����������ʱ��
	SYSTEMTIME current_time, time;
	GetLocalTime(&current_time);
	time = CCommon::CompareSystemTime(current_time, m_start_time);
	CString temp;
	temp.Format(CCommon::LoadText(IDS_HOUR_MINUTE_SECOND), time.wHour, time.wMinute, time.wSecond);
	m_info_list.SetItemText(13, 1, temp);
}

UINT CNetworkInfoDlg::GetInternetIPThreadFunc(LPVOID lpParam)
{
	CCommon::SetThreadLanguage(theApp.m_general_data.language);		//�����߳�����
	CNetworkInfoDlg* p_instance = (CNetworkInfoDlg*)lpParam;
	wstring ip_address, ip_location;
	CCommon::GetInternetIp(ip_address, ip_location, CCommon::LoadText(IDS_LANGUAGE_CODE) != _T("2"));			//��ȡ����IP��ַ��
	if (!IsWindow(p_instance->GetSafeHwnd()))		//�����ǰ�Ի����Ѿ����٣����˳��߳�
		return 0;
	if (!ip_address.empty())
	{
		CString info;
		if (ip_location.empty())
			info = ip_address.c_str();
		else
			info.Format(_T("%s (%s)"), ip_address.c_str(), ip_location.c_str());
		p_instance->m_info_list.SetItemText(14, 1, info);
	}
	else
	{
		p_instance->m_info_list.SetItemText(14, 1, CCommon::LoadText(IDS_GET_FAILED));
	}
	return 0;
}

void CNetworkInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO_LIST1, m_info_list);
}


BEGIN_MESSAGE_MAP(CNetworkInfoDlg, CDialog)
	ON_COMMAND(ID_COPY_TEXT, &CNetworkInfoDlg::OnCopyText)
	ON_NOTIFY(NM_RCLICK, IDC_INFO_LIST1, &CNetworkInfoDlg::OnNMRClickInfoList1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PREVIOUS_BUTTON, &CNetworkInfoDlg::OnBnClickedPreviousButton)
	ON_BN_CLICKED(IDC_NEXT_BUTTON, &CNetworkInfoDlg::OnBnClickedNextButton)
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(NM_DBLCLK, IDC_INFO_LIST1, &CNetworkInfoDlg::OnNMDblclkInfoList1)
END_MESSAGE_MAP()


// CNetworkInfoDlg ��Ϣ�������


BOOL CNetworkInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(CCommon::LoadText(IDS_TITLE_CONNECTION_DETIAL));
	SetIcon(AfxGetApp()->LoadIcon(IDI_NOFITY_ICON), FALSE);		// ����Сͼ��

	//��ȡ���ڳ�ʼ��С
	CRect rect;
	GetWindowRect(rect);
	m_min_size = rect.Size();

	//���»�ȡIP��ַ
	CAdapterCommon::RefreshIpAddress(m_connections);

	//��ʼ���б�ؼ�
	m_info_list.GetClientRect(rect);
	m_info_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	int width0, width1;
	width0 = rect.Width() / 4;
	width1 = rect.Width() - width0 - theApp.DPI(21);
	m_info_list.InsertColumn(0, CCommon::LoadText(IDS_ITEM), LVCFMT_LEFT, width0);		//�����0��
	m_info_list.InsertColumn(1, CCommon::LoadText(IDS_VALUE), LVCFMT_LEFT, width1);		//�����1��

	//���б��в�����
	m_info_list.InsertItem(0, CCommon::LoadText(IDS_INTERFACE_NAME));
	m_info_list.InsertItem(1, CCommon::LoadText(IDS_INTERFACE_DESCRIPTION));
	m_info_list.InsertItem(2, CCommon::LoadText(IDS_CONNECTION_TYPE));
	m_info_list.InsertItem(3, CCommon::LoadText(IDS_SPEED));
	m_info_list.InsertItem(4, CCommon::LoadText(IDS_ADAPTER_PHYSICAL_ADDRESS));
	m_info_list.InsertItem(5, CCommon::LoadText(IDS_IP_ADDRESS));
	m_info_list.InsertItem(6, CCommon::LoadText(IDS_SUBNET_MASK));
	m_info_list.InsertItem(7, CCommon::LoadText(IDS_DEFAULT_GATEWAY));
	m_info_list.InsertItem(8, CCommon::LoadText(IDS_OPERATIONAL_STATUS));
	m_info_list.InsertItem(9, CCommon::LoadText(IDS_BYTES_RECEIVED));
	m_info_list.InsertItem(10, CCommon::LoadText(IDS_BYTES_SENT));
	m_info_list.InsertItem(11, CCommon::LoadText(IDS_BYTES_RECEIVED_SINCE_START));
	m_info_list.InsertItem(12, CCommon::LoadText(IDS_BYTES_SENT_SINCE_START));
	m_info_list.InsertItem(13, CCommon::LoadText(IDS_PROGRAM_ELAPSED_TIME));
	m_info_list.InsertItem(14, CCommon::LoadText(IDS_INTERNET_IP_ADDRESS));
	if (theApp.m_cfg_data.m_show_internet_ip)
	{
		m_info_list.SetItemText(14, 1, CCommon::LoadText(IDS_ACQUIRING, _T("...")));
	}
	else
	{
		m_info_list.SetItemText(14, 1, CCommon::LoadText(IDS_DOUBLE_CLICK_TO_ACQUIRE));
	}

	//��ʾ�б��е���Ϣ
	LOGFONT lf{};
	GetFont()->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	m_font_bold.CreateFontIndirect(&lf);
	ShowInfo();
	GetProgramElapsedTime();

	//CCommon::GetInternetIp();
	if (theApp.m_cfg_data.m_show_internet_ip)
		m_pGetIPThread = AfxBeginThread(GetInternetIPThreadFunc, this);		//������ȡ����IP���߳�

	//SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		//ȡ���ö�
	m_info_list.GetToolTips()->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	m_menu.LoadMenu(IDR_INFO_MENU); //װ���Ҽ��˵�

	SetTimer(CONNECTION_DETAIL_TIMER, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CNetworkInfoDlg::OnCopyText()
{
	// TODO: �ڴ���������������
	if (!CCommon::CopyStringToClipboard(wstring(m_selected_string)))
		MessageBox(CCommon::LoadText(IDS_COPY_TO_CLIPBOARD_FAILED), NULL, MB_ICONWARNING);
}


void CNetworkInfoDlg::OnNMRClickInfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ����������ı�
	int item, sub_item;
	item = pNMItemActivate->iItem;
	sub_item = pNMItemActivate->iSubItem;
	m_selected_string = m_info_list.GetItemText(item, sub_item);

	//�����Ҽ��˵�
	CMenu* pContextMenu = m_menu.GetSubMenu(0);	//��ȡ��һ�������˵�
	CPoint point1;	//����һ������ȷ�����λ�õ�λ��  
	GetCursorPos(&point1);	//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, this); //��ָ��λ����ʾ�����˵�

	*pResult = 0;
}


void CNetworkInfoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�Ի���ر�ʱǿ�ƽ�����ȡIP��ַ���߳�
	if(theApp.m_cfg_data.m_show_internet_ip)
		TerminateThread(m_pGetIPThread->m_hThread, 0);
	CDialog::OnClose();
}


void CNetworkInfoDlg::OnBnClickedPreviousButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_connection_selected > 0)
	{
		m_connection_selected--;
		ShowInfo();
	}
}


void CNetworkInfoDlg::OnBnClickedNextButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_connection_selected < m_connections.size() - 1)
	{
		m_connection_selected++;
		ShowInfo();
	}
}


BOOL CNetworkInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_LEFT)
		{
			OnBnClickedPreviousButton();
			return TRUE;
		}
		if (pMsg->wParam == VK_RIGHT)
		{
			OnBnClickedNextButton();
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CNetworkInfoDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ƴ�����С��С
	lpMMI->ptMinTrackSize.x = m_min_size.cx;		//������С���
	lpMMI->ptMinTrackSize.y = m_min_size.cy;		//������С�߶�

	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CNetworkInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == CONNECTION_DETAIL_TIMER)
	{
		GetProgramElapsedTime();
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CNetworkInfoDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ͨ�������ַ�ҳ
	if (zDelta > 0)
	{
		OnBnClickedPreviousButton();
	}
	if (zDelta < 0)
	{
		OnBnClickedNextButton();
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


void CNetworkInfoDlg::OnNMDblclkInfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!theApp.m_cfg_data.m_show_internet_ip && pNMItemActivate->iItem == 14)		//˫����IP��ַһ��ʱ
	{
		m_info_list.SetItemText(14, 1, CCommon::LoadText(IDS_ACQUIRING, _T("...")));
		m_pGetIPThread = AfxBeginThread(GetInternetIPThreadFunc, this);
	}
	*pResult = 0;
}
