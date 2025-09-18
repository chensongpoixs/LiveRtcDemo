
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

namespace crtc {


class HttpReply;

class CRTCMediaSink : //public MediaObject,
                      public sigslot::has_slots<>
{
public:
    CRTCMediaSink( );
    ~CRTCMediaSink() ;

    // MediaObject
    bool Start() ;
    void Setup(const std::string& /*json_config*/) ;
    void Stop() ;
   // void OnNewMediaFrame(std::shared_ptr<MediaFrame>) override;
    /*std::vector<InPin*> GetAllInPins() override {
        return std::vector<InPin*>({ video_in_pin_.get() });
    }

    std::vector<OutPin*> GetAllOutPins() override {
        return std::vector<OutPin*>();
    }*/


	void set_http_param(const std::string & action, std::string & url, const std::string & user_name, const std::string & stream_name);
private:
   /* void OnNetworkInfo(PeerConnection*, int64_t rtt_ms,
        int32_t packets_lost, uint8_t fraction_lost,
        uint32_t jitter);*/
   // void OnConnectionState(PeerConnection*, PeerConnectionState pc_state);
    
private:
    bool ParseReply(const HttpReply& reply, std::string& type, std::string& sdp);
    void SendAnswer(const std::string& answer);
    void SendStop();
   // void PacketAndSendVideo(std::shared_ptr<MediaFrame> frame);

private:
   // MediaChain* media_chain_;
   // std::unique_ptr<InPin> video_in_pin_;
    std::string url_;
    std::string protocol_;
    std::string host_;
    std::string action_;
	std::string user_name_;
	std::string stream_name_;
   // std::map<std::string, std::string> request_params_;
   // std::unique_ptr<PeerConnection> pc_;
};

} // namespace crtc

#endif // _C_MEDIA_SINK_H_