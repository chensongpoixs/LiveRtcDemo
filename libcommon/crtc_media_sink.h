
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

#ifndef _C_RTC_MEDIA_SINK_H_
#define _C_RTC_MEDIA_SINK_H_

#include <string>
#include <map>
#include "rtc_base/third_party/sigslot/sigslot.h"
#include "libp2p_peerconnection/cp2p_peerconnection.h"
namespace crtc {


class HttpReply;

class CRTCMediaSink :  
                      public sigslot::has_slots<>
{
public:
    CRTCMediaSink( );
    ~CRTCMediaSink() ;
     
    bool Start() ;
    void Setup(const std::string& /*json_config*/) ;
    void Stop() ;
   


	
	libp2p_peerconnection::p2p_peer_connection*  GetPeerConnection() { return pc_; }
	void set_http_param(const std::string & action, std::string & url, const std::string & user_name, const std::string & stream_name);


public:
	void OnTragetTransferRate(libp2p_peerconnection::p2p_peer_connection *, const libice::TargetTransferRate& target);
	sigslot::signal2<crtc::CRTCMediaSink*, const libice::TargetTransferRate&> SignalTargetTransferRate;

private: 
private:
     
     
     

private: 
    std::string url_;
    std::string protocol_;
    std::string host_;
    std::string action_;
	std::string user_name_;
	std::string stream_name_; 

	libp2p_peerconnection::p2p_peer_connection*  pc_;
};

} // namespace crtc

#endif // _C_MEDIA_SINK_H_