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
#ifndef _C_LIVE_WIN32_H_
#define _C_LIVE_WIN32_H_

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLiveWin32App: 
// �йش����ʵ�֣������ LiveWin32.cpp
//

class CLiveWin32App : public CWinApp
{
public:
	CLiveWin32App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLiveWin32App theApp;

#endif // _C_LIVE_WIN32_H_