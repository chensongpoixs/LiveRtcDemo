/******************************************************************************
 *  Copyright (c) 2025 The CRTC project authors . All Rights Reserved.
 *
 *  Please visit https://chensongpoixs.github.io for detail
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 ******************************************************************************/
 /*****************************************************************************
				   Author: chensong
				   date:  2025-09-18



 ******************************************************************************/



#include "http/crtc_global.h"

#include <modules/video_capture/video_capture_factory.h>

#include "http/crtc_http.h"

namespace crtc {


	namespace {



		rtc::Thread* MaybeStartThread(rtc::Thread* old_thread,
			const std::string& thread_name,
			bool with_socket_server,
			std::unique_ptr<rtc::Thread>& thread_holder) {
			if (old_thread) {
				return old_thread;
			}
			if (with_socket_server) {
				thread_holder = rtc::Thread::CreateWithSocketServer();
			}
			else {
				thread_holder = rtc::Thread::Create();
			}
			thread_holder->SetName(thread_name, nullptr);
			thread_holder->Start();
			return thread_holder.get();
		}
	}


// 单例
CRTCGlobal* CRTCGlobal::Instance() {
    static CRTCGlobal* const instance = new CRTCGlobal();
    return instance;
}

CRTCGlobal::CRTCGlobal() :
    api_thread_(MaybeStartThread(nullptr, "api_thread", false, api_thread_)),
    worker_thread_(MaybeStartThread(nullptr, "worker_thread", false, worker_thread_)),
    network_thread_(MaybeStartThread(nullptr, "network_thread", true, network_thread_))
  // , video_device_info_(webrtc::VideoCaptureFactory::CreateDeviceInfo())
{
 /*   api_thread_->SetName("api_thread", nullptr);
    api_thread_->Start();

    worker_thread_->SetName("worker_thread", nullptr);
    worker_thread_->Start();

    network_thread_->SetName("network_thread", nullptr);
    network_thread_->Start();*/

    http_manager_ = new HttpManager();
    http_manager_->Start();

   // ice::NetworkConfig config;
   // port_allocator_ = std::make_unique<ice::PortAllocator>(config);
}

CRTCGlobal::~CRTCGlobal() {

}

} // namespace crtc