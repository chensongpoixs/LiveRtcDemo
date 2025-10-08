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

#ifndef _C_RTC_GLOBAL_H_
#define _C_RTC_GLOBAL_H_


 
#include <rtc_base/thread.h>
#include <modules/video_capture/video_capture.h>
 

namespace crtc {

class XRTCEngineObserver;
class HttpManager;

// 单例模式
class CRTCGlobal {
public:
    static CRTCGlobal* Instance();

   // XRTCEngineObserver* engine_observer() { return engine_observer_; }
   // void RegisterEngineObserver(XRTCEngineObserver* observer) {
   //     engine_observer_ = observer;
   // }

    rtc::Thread* api_thread() { return api_thread_.get(); }
    rtc::Thread* worker_thread() { return worker_thread_.get(); }
    rtc::Thread* network_thread() { return network_thread_.get(); }
   // webrtc::VideoCaptureModule::DeviceInfo* video_device_info() {
   //     return video_device_info_.get();
    //}

    HttpManager* http_manager() { return http_manager_; }

    //ice::PortAllocator* port_allocator() { return port_allocator_.get(); }

private:
    CRTCGlobal();
    ~CRTCGlobal();

private:
    std::unique_ptr<rtc::Thread> api_thread_;
    std::unique_ptr<rtc::Thread> worker_thread_;
    std::unique_ptr<rtc::Thread> network_thread_;
    //std::unique_ptr<webrtc::VideoCaptureModule::DeviceInfo> video_device_info_;
   // XRTCEngineObserver* engine_observer_ = nullptr;
    HttpManager* http_manager_ = nullptr;
   // std::unique_ptr<ice::PortAllocator> port_allocator_;
};

} // namespace crtc

#endif // _C_RTC_GLOBAL_H_