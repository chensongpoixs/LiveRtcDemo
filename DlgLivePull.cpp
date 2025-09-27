/*
*  Copyright (c) 2025 The CRTC project authors . All Rights Reserved.
*
*  Please visit https://chensongpoixs.github.io for detail
*
*  Use of this source code is governed by a BSD-style license
*  that can be found in the LICENSE file in the root of the source
*  tree. An additional intellectual property rights grant can be found
*  in the file PATENTS.  All contributing project authors may
*  be found in the AUTHORS file in the root of the source tree.
*/
/*****************************************************************************
				  Author: chensong
				  date:  2025-09-17



******************************************************************************/
#include "stdafx.h"
#include "DlgLivePull.h"
// DlgLivePull 对话框

IMPLEMENT_DYNAMIC(DlgLivePull, CDialog)

DlgLivePull::DlgLivePull()
	: CDialog(DlgLivePull::IDD)
	, m_strUrl(_T("http://chensong.com:8087"))
	//, m_pAVRtmplayer(NULL)
	, m_pDlgVideoMain(NULL)
{
}

DlgLivePull::~DlgLivePull()
{
}

void DlgLivePull::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_editUrl);
	DDX_Control(pDX, IDC_BTN_PULL, m_btnLive);
	DDX_Text(pDX, IDC_EDIT_URL, m_strUrl);
	DDX_Control(pDX, IDC_STATIC_CAPTRUE, m_staticCaptrue);
}


BEGIN_MESSAGE_MAP(DlgLivePull, CDialog)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_MY_PULL_MESSAGE, OnMyMessage)
	ON_BN_CLICKED(IDC_BTN_PULL, &DlgLivePull::OnBnClickedBtnPull)
//	ON_STN_CLICKED(IDC_STATIC_URL, &DlgLivePull::OnStnClickedStaticUrl)
END_MESSAGE_MAP()


// DlgLivePull 消息处理程序

void DlgLivePull::OnOK()
{
}

void DlgLivePull::OnCancel()
{
	CDialog::EndDialog(0);
}

void DlgLivePull::OnClose()
{
	CDialog::EndDialog(0);
}

BOOL DlgLivePull::OnInitDialog()
{
	CDialog::OnInitDialog();

	{// Video player
		m_pDlgVideoMain = new DlgVideo(this);
		m_pDlgVideoMain->Create(DlgVideo::IDD, this);
		CRect rc;
		m_staticCaptrue.GetWindowRect(rc);
		m_staticCaptrue.ShowWindow(SW_HIDE);
		ScreenToClient(rc);
		m_pDlgVideoMain->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL DlgLivePull::DestroyWindow()
{
	//if (m_pAVRtmplayer) {
	//	m_pAVRtmplayer->StopRtmpPlay();
	//	RTMPGuester::Destory(m_pAVRtmplayer);
	//	m_pAVRtmplayer = NULL;
	//}
	if (m_pDlgVideoMain) {
		m_pDlgVideoMain->DestroyWindow();
		delete m_pDlgVideoMain;
		m_pDlgVideoMain = NULL;
	}

	return CDialog::DestroyWindow();
}

BOOL DlgLivePull::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

LRESULT DlgLivePull::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	CString *pstrGet = (CString *)lParam;
	char ss[128];
	memset(ss, 0, 128);
	int fnlen = pstrGet->GetLength();
	for (int i = 0; i <= fnlen; i++) {
		ss[i] = pstrGet->GetAt(i);
	}
	DlgVideo* ptrDlg = NULL;
	delete pstrGet;
	return 0;
}

void DlgLivePull::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDblClk(nFlags, point);
}

void DlgLivePull::OnBnClickedBtnPull()
{
	// TODO:  在此添加控件通知处理程序代码
	//if (m_pAVRtmplayer == NULL) {
	//	m_pAVRtmplayer = RTMPGuester::Create(*this);
	//	UpdateData(TRUE);
	//	char ss[128];
	//	memset(ss, 0, 128);
	//	int fnlen = m_strUrl.GetLength();
	//	for (int i = 0; i <= fnlen; i++) {
	//		ss[i] = m_strUrl.GetAt(i);
	//	}
	//	m_pAVRtmplayer->StartRtmpPlay(ss, m_pDlgVideoMain->m_hWnd);
	//	m_btnRtmp.SetWindowTextW(L"结束");
	//}
	//else 
	{
		m_btnLive.SetWindowText("拉流");
		//m_pAVRtmplayer->StopRtmpPlay();
		//RTMPGuester::Destory(m_pAVRtmplayer);
		//m_pAVRtmplayer = NULL;
	}
}



