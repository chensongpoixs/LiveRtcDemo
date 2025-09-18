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
#ifndef __VIDEO_RENDERER_WIN32_H__
#define __VIDEO_RENDERER_WIN32_H__
#include "stdafx.h"
#include <cstdint>
//#include "avrtmplayer_interface.h"

class VideoRendererWin32 //: public AVRtmpVideoRender
{
public:
	virtual ~VideoRendererWin32();
	static VideoRendererWin32* Create(HWND wnd, int width, int height);

	void Lock() {
		::EnterCriticalSection(&buffer_lock_);
	}

	void Unlock() {
		::LeaveCriticalSection(&buffer_lock_);
	}

	virtual void OnYuv(uint8_t*pYUV420Data[3], int nStride[3], int nWidth, int nHeight);

protected:
	VideoRendererWin32(HWND wnd, int width, int height);

	CRITICAL_SECTION buffer_lock_;

	void* ds_;
};

#endif	// __VIDEO_RENDERER_WIN32_H__