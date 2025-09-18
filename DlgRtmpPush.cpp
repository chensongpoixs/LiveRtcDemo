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
#include "DlgRtmpPush.h"

#include  "desktop_capture/desktop_capture_source.h"
#include "pc/video_track_source.h"
#include "desktop_capture/desktop_capture.h"

// DlgRtmpPush 对话框

IMPLEMENT_DYNAMIC(DlgRtmpPush, CDialog)

DlgRtmpPush::DlgRtmpPush()
	: CDialog(DlgRtmpPush::IDD)
	, m_strUrl(_T("http://chensong.com:8087"))
	//, m_pAVRtmpstreamer(NULL)
	, m_pDlgVideoMain(NULL)
	, video_render_factory_(new crtc::cvideo_render_factory())
	, video_renderer_(nullptr)
	, capture_track_source_(nullptr)
{
}

DlgRtmpPush::~DlgRtmpPush()
{
	if (capture_track_source_)
	{
		capture_track_source_->Stop();
		//capture_track_source_ = nullptr;
	}
	
	if (video_render_factory_)
	{

		if (video_renderer_)
		{
			//delete video_renderer_;
			//video_renderer_.reset();
			video_render_factory_->worker_thread()->PostTask(RTC_FROM_HERE, [=] {
				//video_renderer_.reset();
				delete video_renderer_;
			});
		}
	
		delete video_render_factory_;
		video_render_factory_ = nullptr;
	}
	
}

void DlgRtmpPush::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_editUrl);
	DDX_Control(pDX, IDC_BTN_PUSH, m_btnRtmp);
	DDX_Text(pDX, IDC_EDIT_URL, m_strUrl);
	DDX_Control(pDX, IDC_STATIC_CAPTRUE, m_staticCaptrue);
}


BEGIN_MESSAGE_MAP(DlgRtmpPush, CDialog)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_MY_PUSH_MESSAGE, OnMyMessage)
//	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PUSH, &DlgRtmpPush::OnBnClickedBtnPush)
//	ON_STN_CLICKED(IDC_STATIC_URL, &DlgRtmpPush::OnStnClickedStaticUrl)
ON_BN_CLICKED(OPEN_AUDIO_VIDEO, &DlgRtmpPush::OnBnClickedAudioVideo)
END_MESSAGE_MAP()


// DlgRtmpPush 消息处理程序

void DlgRtmpPush::OnOK()
{
}

void DlgRtmpPush::OnCancel()
{
	CDialog::EndDialog(0);
}

void DlgRtmpPush::OnClose()
{
	CDialog::EndDialog(0);
}

BOOL DlgRtmpPush::OnInitDialog()
{
	CDialog::OnInitDialog();

	//_CrtSetBreakAlloc(358);
	SetTimer(1, 25, NULL);

	{// Video captrue
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

BOOL DlgRtmpPush::DestroyWindow()
{
	KillTimer(1);
	//if (m_pAVRtmpstreamer) {
	//	m_pAVRtmpstreamer->SetVideoCapturer(NULL);
	//	m_pAVRtmpstreamer->StopRtmpStream();
	//	RTMPHoster::Destory(m_pAVRtmpstreamer);
	//	m_pAVRtmpstreamer = NULL;
	//}

	if (m_pDlgVideoMain) {
		m_pDlgVideoMain->DestroyWindow();
		delete m_pDlgVideoMain;
		m_pDlgVideoMain = NULL;
	}

	return CDialog::DestroyWindow();
}

BOOL DlgRtmpPush::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void DlgRtmpPush::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDblClk(nFlags, point);
}

void DlgRtmpPush::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}

LRESULT DlgRtmpPush::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	CString *pstrGet = (CString *)lParam;
	char ss[128];
	memset(ss, 0, 128);
	int fnlen = pstrGet->GetLength();
	for (int i = 0; i <= fnlen; i++) {
		ss[i] = pstrGet->GetAt(i);
	}
	DlgVideo* ptrDlg = NULL;
	//std::string ss(W2A(*pstrGet));

	delete pstrGet;
	return 0;
}

void DlgRtmpPush::OnBnClickedBtnPush()
{
	// TODO:  在此添加控件通知处理程序代码
	//if (m_pAVRtmpstreamer == NULL) {
	//	m_pAVRtmpstreamer = RTMPHoster::Create(*this);
	//	m_pAVRtmpstreamer->SetVideoCapturer(m_pDlgVideoMain->m_hWnd);
	//	{
	//		UpdateData(TRUE);
	//		char ss[128];
	//		memset(ss, 0, 128);
	//		int fnlen = m_strUrl.GetLength();
	//		for (int i = 0; i <= fnlen; i++) {
	//			ss[i] = m_strUrl.GetAt(i);
	//		}
	//		m_pAVRtmpstreamer->StartRtmpStream(ss);
	//		m_btnRtmp.SetWindowText(L"结束");
	//	}
	//}
	//else 
	{
		m_btnRtmp.SetWindowText("推流");
		//m_pAVRtmpstreamer->SetVideoCapturer(NULL);
		//m_pAVRtmpstreamer->StopRtmpStream();
	//	RTMPHoster::Destory(m_pAVRtmpstreamer);
		//m_pAVRtmpstreamer = NULL;
	}
}



 


void DlgRtmpPush::OnBnClickedAudioVideo()
{
	// TODO: Add your control notification handler code here
	if (!video_render_factory_)
	{
		return;
	}
	if (!m_pDlgVideoMain)
	{
		return;
	}

	capture_track_source_ = crtc::CapturerTrackSource::Create();
	if (capture_track_source_)
	{
		video_render_factory_->signaling_thread()->PostTask(RTC_FROM_HERE, [=] {
			// 需要信令
			rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track_(video_render_factory_->create_video_render("desktop", capture_track_source_));
			//rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track_(
			//	peer_connection_factory_->CreateVideoTrack(kVideoLabel, video_device));
			//main_wnd_->StartLocalRenderer(video_track_);

			CRect rc;
			m_staticCaptrue.GetWindowRect(rc);
			video_renderer_ = (crtc::cvideo_renderer::Create(m_pDlgVideoMain->m_hWnd, rc.Width(), rc.Height(), video_track_));
		});
	//	m_staticCaptrue.ShowWindow(SW_SHOWNORMAL);
		//m_pDlgVideoMain->ShowWindow(SW_SHOWNORMAL);
	}
}
