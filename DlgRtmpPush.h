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
#ifndef _C_DLG_RTMP_PUSH_H_
#define _C_DLG_RTMP_PUSH_H_


#include "Resource.h"
//#include "RtmpHoster.h"
#include "DlgVideo.h"


#include "video_render/cvideo_render_factory.h"
#include "video_render/cvideo_render.h"




#define WM_MY_PUSH_MESSAGE (WM_USER + 101)

// DlgVideo 对话框
class CLiveWin32Dlg;
class DlgRtmpPush : public CDialog//, public RTMPHosterEvent
{
	DECLARE_DYNAMIC(DlgRtmpPush)

public:
	DlgRtmpPush();   // 标准构造函数
	virtual ~DlgRtmpPush();

// 对话框数据
	enum { IDD = IDD_DIALOG_PUSH };

protected:
	//* For RTMPHosterEvent
	virtual void OnRtmpStreamOK() {};
	virtual void OnRtmpStreamReconnecting(int times) {};
	virtual void OnRtmpStreamStatus(int delayMs, int netBand) {};
	virtual void OnRtmpStreamFailed(int code) {};
	virtual void OnRtmpStreamClosed() {};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	virtual void OnTimer(UINT nIDEvent);

	CEdit	m_editUrl;
	CButton	m_btnRtmp;
	CString m_strUrl;
	CStatic m_staticCaptrue;
	afx_msg void OnBnClickedBtnPush();

protected:
	DlgVideo		*m_pDlgVideoMain;
	//RTMPHoster		*m_pAVRtmpstreamer;
public:
	//afx_msg void OnStnClickedStaticUrl();
	afx_msg void OnBnClickedAudioVideo();


private:

	crtc::cvideo_render_factory*   video_render_factory_;
	std::unique_ptr < crtc::cvideo_renderer>         video_renderer_;
};

#endif // _C_DLG_RTMP_PUSH_H_