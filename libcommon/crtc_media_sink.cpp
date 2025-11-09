
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


#include "crtc_media_sink.h"

#include <rtc_base/logging.h>
#include <rtc_base/task_utils/to_queued_task.h>

#include "crtc_global.h"
 
//#include "modules/rtp_rtcp/rtp_format_h264.h"
#include "httplib.h"
#include "json.hpp"


namespace crtc {

	CRTCMediaSink::CRTCMediaSink()
		: pc_(new libp2p_peerconnection::p2p_peer_connection())
{

		pc_->SignalTargetTransferRate.connect(this, &CRTCMediaSink::OnTragetTransferRate);
   
}

CRTCMediaSink::~CRTCMediaSink() { 
	RTC_LOG_F(LS_WARNING) << "";


	CRTCGlobal::Instance()->worker_thread()->PostTask(RTC_FROM_HERE, [p = std::move(pc_)]() {
		delete p;
	});

	//delete  pc_;
}

bool CRTCMediaSink::Start() {
   
 

	libp2p_peerconnection::RTCOfferAnswerOptions  options;
	std::string offer_sdp =  pc_->create_offer(options, "chensong");
	CRTCGlobal::Instance()->worker_thread()->PostTask(RTC_FROM_HERE, [=]() {
		/*
		
			action_ = action;
	url_ = url;
	user_name_ = user_name;
	stream_name_ = stream_name;
		*/
		std::string rtc_url = "webrtc://" + url_ + "/" + app_ + "/" + stream_name_;
		nlohmann::json data = {
   {"type", "offer"},
   { "sdp", offer_sdp}, 
   {"streamurl", rtc_url},
   {"clientid",  stream_name_}
		};

		httplib::Client cli("http://" + url_);

		auto res = cli.Post("/rtc/push", data.dump(), "application/json");
		if (res && res->status == 200) {
			std::cout << "Response: " << res->body << std::endl;
			RTC_LOG_T_F(LS_INFO) <<  res->body;
			nlohmann::json response;
			try
			{
				response = nlohmann::json::parse(res->body);
			}
			catch (const std::exception&)
			{
				RTC_LOG_T_F(LS_INFO) << "request /rtc/push    [msg = "
					<< res->body <<"] json parse failed !!!";
				 return;
			}

			if (pc_)
			{
				pc_->set_remote_sdp(response["sdp"]);


				 
			}
		}
		else {
			std::cout << "Error in response" << std::endl;
		}
	});

    return true;
}

void CRTCMediaSink::Setup(const std::string& json_config) {
    
}

void CRTCMediaSink::Stop() {
    RTC_LOG(LS_INFO) << "CRTCMediaSink Stop";
   
}
 
 


void CRTCMediaSink::set_http_param(const std::string & action, std::string & url, const std::string & app, const std::string & stream_name)
{
	action_ = action;
	url_ = url;
	app_ = app;
	stream_name_ = stream_name;
}
 

 
 
void CRTCMediaSink::OnTragetTransferRate(libp2p_peerconnection::p2p_peer_connection *, const libice::TargetTransferRate& target)
{


	SignalTargetTransferRate(this, target);
}

 
}  