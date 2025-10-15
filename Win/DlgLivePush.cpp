﻿/*
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
#include "DlgLivePush.h"

#include  "libcross_platform_collection_render/desktop_capture/desktop_capture_source.h"
#include "pc/video_track_source.h"
#include "libcross_platform_collection_render/desktop_capture/desktop_capture.h"
#include "http/crtc_global.h"

// DlgRtmpPush 对话框

static const char * capture_type = "摄像头";

IMPLEMENT_DYNAMIC(DlgLivePush, CDialog)

DlgLivePush::DlgLivePush()
	: CDialog(DlgLivePush::IDD)
#if 0
	, m_strUrl(("http://127.0.0.1:8087"))
#else 
	, m_strUrl("webrtc://120.48.112.56:8087/crtc/123456")
#endif 
//	, m_strUserName("1234")
	//, m_strStreamName("crtc")
	, m_strAudioDeviceType("")
	, m_strCaptureType(capture_type)
	//, m_pAVRtmpstreamer(NULL)
	, m_pDlgVideoMain(NULL)
	, video_render_factory_(new libcross_platform_collection_render::cvideo_render_factory())
	, video_renderer_(nullptr)
	, capture_track_source_(nullptr)
	, crtc_media_sink_ (new crtc::CRTCMediaSink())
	, x264_encoder_(new  libmedia_codec::X264Encoder())
	, audio_capture_(new libcross_platform_collection_render::AudioCapture(video_render_factory_->worker_thread()))
	, opus_encoder2_(new libmedia_codec::OpusEncoder2())
{
	crtc_media_sink_->SignalTargetTransferRate.connect(this, &DlgLivePush::OnTragetTransferRate);
	//crtc_media_sink_->get_pc_obj()-
	x264_encoder_->SetSendFrame(crtc_media_sink_->get_video_obj());
	opus_encoder2_->SetSendFrame(crtc_media_sink_->get_audio_obj());
//	rtc::LogMessage::LogToDebug(rtc::LS_VERBOSE);

	x264_encoder_->Start();
//	opus_encoder2_->Start();
}

DlgLivePush::~DlgLivePush()
{
	if (capture_track_source_)
	{
		capture_track_source_->Stop();
		//capture_track_source_ = nullptr;
	}
	x264_encoder_->SetSendFrame(nullptr);
	x264_encoder_->Stop();
	delete x264_encoder_;
	x264_encoder_ = nullptr;
	//rtc::split();
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
	delete crtc_media_sink_;
}

void DlgLivePush::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_editUrl);
	DDX_Control(pDX, IDC_BTN_PUSH, m_btnRtmp);
	DDX_Text(pDX, IDC_EDIT_URL, m_strUrl);

	//DDX_Control(pDX, IDC_RTC_USER, m_editUserName);
	//DDX_Text(pDX, IDC_RTC_USER, m_strUserName);

	//DDX_Control(pDX, IDC_RTC_STREAM_NAME, m_editStreamName);
	//DDX_Text(pDX, IDC_RTC_STREAM_NAME, m_strStreamName);
	DDX_Control(pDX, IDC_STATIC_CAPTRUE, m_staticCaptrue);

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CComboBox* pComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	//向列表中添加几个项
	int nIndex = 0;
	//pComboBox->AddString(_T("RTC"));
	//pComboBox->AddString(_T("RTMP"));
	//pComboBox->AddString(_T("RTSP"));
	 
	/*nIndex = pComboBox->InsertString(0, _T("RTC"));
 
	nIndex = pComboBox->InsertString(1, _T("RTMP"));
 
	nIndex = pComboBox->InsertString(  2, _T("RTSP"));*/
 
	nIndex = pComboBox2->InsertString(0, _T("桌面"));

	nIndex = pComboBox2->InsertString(1, _T("摄像头"));

	//nIndex = pComboBox->InsertString(2, _T("RTSP"));
	// 假设您想删除索引为 0 的项（即第一个项）
//	pComboBox->DeleteString(0);

	// 删除项后，后续项的索引将改变。例如，如果您删除原来索引为 1 的项，需要删除现在索引为0的项。
//	pComboBox->DeleteString(0);

//	pComboBox->AddString(_T("选项 1"));
	//pComboBox->AddString(_T("选项 2"));
	//pComboBox->AddString(_T("选项 3"));

	//ResetContent用于清空组合框中的所有项
	//pComboBox->ResetContent();


	int32_t audio_device_count = audio_capture_->GetAudioDeviceCount();
	 
	WCHAR buffer[128] = {0};
	auto bytetowchar= [&](const std::string &src) {
		if (MultiByteToWideChar(CP_UTF8, 0, src.c_str(), src.size(), buffer,
			128) == 0) {
			RTC_LOG(LS_ERROR)
				<< "MultiByteToWideChar(CP_UTF8) failed with error code "
				<< GetLastError();
		}
	};
	//std::string audio_
	//m_strLiveType
	for (int32_t i = 0; i < audio_device_count; ++i)
	{
		std::string audio_name;
		std::string audio_guild;
		audio_capture_->GetAudioDeviceInfo(i, audio_name, audio_guild);
		// 这个很奇怪呢 UTF-8
		bytetowchar(audio_name);
		m_strAudioDeviceType = buffer;
		audio_gurild_.insert(std::make_pair(m_strAudioDeviceType,  audio_guild));
		pComboBox->InsertString(i, m_strAudioDeviceType);
		
	}

	// IDC_COMBO1
	DDX_Control(pDX, IDC_COMBO1, m_comboxType);
	DDX_Text(pDX, IDC_COMBO1, m_strAudioDeviceType);
	DDX_Control(pDX, IDC_COMBO2, m_comboxcaptureType);
	DDX_Text(pDX, IDC_COMBO2, m_strCaptureType);
	
}


BEGIN_MESSAGE_MAP(DlgLivePush, CDialog)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_MY_PUSH_MESSAGE, OnMyMessage)
//	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PUSH, &DlgLivePush::OnBnClickedBtnPush)
//	ON_STN_CLICKED(IDC_STATIC_URL, &DlgLivePush::OnStnClickedStaticUrl)
ON_BN_CLICKED(OPEN_AUDIO_VIDEO, &DlgLivePush::OnBnClickedAudioVideo)
//ON_EN_CHANGE(RTC_STREAM_NAME, &DlgLivePush::OnEnChangeStreamName)
//ON_CBN_SELCHANGE(IDC_COMBO1, &DlgLivePush::OnCbnSelchangeCombo1)
//ON_CBN_SELCHANGE(IDC_COMBO2, &DlgLivePush::OnCbnSelchangeCombo2)
ON_CBN_SELCHANGE(IDC_COMBO2, &DlgLivePush::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// DlgRtmpPush 消息处理程序

void DlgLivePush::OnOK()
{
}

void DlgLivePush::OnCancel()
{
	CDialog::EndDialog(0);
}

void DlgLivePush::OnClose()
{
	CDialog::EndDialog(0);
}

BOOL DlgLivePush::OnInitDialog()
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

BOOL DlgLivePush::DestroyWindow()
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

BOOL DlgLivePush::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void DlgLivePush::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDblClk(nFlags, point);
}

void DlgLivePush::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}

LRESULT DlgLivePush::OnMyMessage(WPARAM wParam, LPARAM lParam)
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

void DlgLivePush::OnBnClickedBtnPush()
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

		char rtc_url[512] = {0};
		memset(rtc_url, 0, 512);
		//GetWindowText()
		GetDlgItem(IDC_EDIT_URL)->GetWindowText(m_strUrl);
		//GetWindowText(m_editUrl, (LPSTR)&rtc_url[0], 512);
		int fnlen = m_strUrl.GetLength();
		for (int i = 0; i <= fnlen; i++) {
			rtc_url[i] = m_strUrl.GetAt(i);
		}

		/*char rtc_username[128] = { 0 };
		memset(rtc_username, 0, 128);
		GetDlgItem(IDC_RTC_USER)->GetWindowText(m_strUserName);
		 fnlen = m_strUserName.GetLength();
		for (int i = 0; i <= fnlen; i++) {
			rtc_username[i] = m_strUserName.GetAt(i);
		}

		char rtc_streamname[128] = { 0 };
		memset(rtc_streamname, 0, 128);
		GetDlgItem(IDC_RTC_STREAM_NAME)->GetWindowText(m_strStreamName);
		 fnlen = m_strStreamName.GetLength();
		for (int i = 0; i <= fnlen; i++) {
			rtc_streamname[i] = m_strStreamName.GetAt(i);
		}*/
		// webrtc://120.48.112.56:8087/crtc/123456
		std::vector<std::string>  fileds;
		rtc::split(rtc_url, '/', &fileds);
		std::string rtc_username;
		std::string  rtc_streamname;
		if (fileds.size() < 4)
		{
			RTC_LOG(LS_WARNING) << "url parse failed !!! url : " << rtc_url;
			return;
		}
		std::string url = "http://";
		rtc_username = fileds[fileds.size() -1];
		rtc_streamname = fileds[fileds.size() - 2];
		url += fileds[fileds.size() - 3];
		crtc_media_sink_->set_http_param("push", std::string(url), std::string(rtc_username), std::string(rtc_streamname));
		crtc_media_sink_->Start();
		m_btnRtmp.SetWindowText("推流");
		//m_pAVRtmpstreamer->SetVideoCapturer(NULL);
		//m_pAVRtmpstreamer->StopRtmpStream();
	//	RTMPHoster::Destory(m_pAVRtmpstreamer);
		//m_pAVRtmpstreamer = NULL;
	}






}

void DlgLivePush::OnTragetTransferRate(crtc::CRTCMediaSink *, const libice::TargetTransferRate & target)
{
	if (x264_encoder_)
	{
		x264_encoder_->SetBitrate(target.target_rate.kbps());
	}
}



 


void DlgLivePush::OnBnClickedAudioVideo()
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
	char curcapture_type[128] = { 0 };
	memset(curcapture_type, 0, 128);
	GetDlgItem(IDC_COMBO2)->GetWindowText(m_strCaptureType);
	int fnlen = m_strCaptureType.GetLength();
	for (int i = 0; i <= fnlen; i++) {
		curcapture_type[i] = m_strCaptureType.GetAt(i);
	}
	
	//if (capture_track_source_)
	{

		video_render_factory_->signaling_thread()->PostTask(RTC_FROM_HERE, [this, curcapture_type] {
			CRect rc;
			m_staticCaptrue.GetWindowRect(rc);
			capture_track_source_ = libcross_platform_collection_render::CapturerTrackSource::Create(std::string(curcapture_type) == std::string(capture_type));
			capture_track_source_->set_catprue_callback(x264_encoder_, video_render_factory_->signaling_thread());

			// 需要信令
			rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track_(video_render_factory_->create_video_render("desktop", capture_track_source_));
			//rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track_(
			//	peer_connection_factory_->CreateVideoTrack(kVideoLabel, video_device));
			//main_wnd_->StartLocalRenderer(video_track_);

			video_renderer_ = (libcross_platform_collection_render::cvideo_renderer::Create(m_pDlgVideoMain->m_hWnd, rc.Width(), rc.Height(), video_track_));
			capture_track_source_->StartCapture();
		});
		char audio_type[128] = { 0 };
		memset(audio_type, 0, 128);
		GetDlgItem(IDC_COMBO1)->GetWindowText(m_strAudioDeviceType);
		int fnlen = m_strAudioDeviceType.GetLength();
		for (int i = 0; i <= fnlen; i++) {
			audio_type[i] = m_strAudioDeviceType.GetAt(i);
		}
		audio_capture_->SetAudioEncoder(opus_encoder2_);
		audio_capture_->Start(audio_gurild_[audio_type]);
		opus_encoder2_->Start();
	//	m_staticCaptrue.ShowWindow(SW_SHOWNORMAL);
		//m_pDlgVideoMain->ShowWindow(SW_SHOWNORMAL);
	}
}


//void DlgRtmpPush::OnEnChangeStreamName()
//{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
//}


//void DlgLivePush::OnCbnSelchangeCombo1()
//{
//	// TODO: Add your control notification handler code here
//}


//void DlgLivePush::OnCbnSelchangeCombo2()
//{
//	// TODO: Add your control notification handler code here
//}


void DlgLivePush::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
}
