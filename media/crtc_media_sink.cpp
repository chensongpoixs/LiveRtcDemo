
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


#include "media/crtc_media_sink.h"

#include <rtc_base/logging.h>
#include <rtc_base/task_utils/to_queued_task.h>

#include "http/crtc_global.h"
#include "http/crtc_http.h"
#include "http/crtc_json.h"
//#include "modules/rtp_rtcp/rtp_format_h264.h"

namespace crtc {

	CRTCMediaSink::CRTCMediaSink()
		: pc_(new libp2p_peerconnection::p2p_peer_connection())
{
   /* MediaFormat video_fmt;
    video_fmt.media_type = MainMediaType::kMainTypeVideo;
    video_fmt.sub_fmt.video_fmt.type = SubMediaType::kSubTypeH264;
    video_in_pin_->set_format(video_fmt);*/


    CRTCGlobal::Instance()->http_manager()->AddObject(this);
	//CRTCGlobal::Instance()->worker_thread()->PostTask(RTC_FROM_HERE, [this]() {
	//	pc_ = new libp2p_peerconnection::p2p_peer_connection();
	//});
//	pc_ = new libice::p2p_peer_connection();
   // pc_->SignalConnectionState.connect(this, &CRTCMediaSink::OnConnectionState);
  //  pc_->SignalNetworkInfo.connect(this, &CRTCMediaSink::OnNetworkInfo);
}

CRTCMediaSink::~CRTCMediaSink() {
    CRTCGlobal::Instance()->http_manager()->RemoveObject(this);

	RTC_LOG_F(LS_WARNING) << "";


	CRTCGlobal::Instance()->worker_thread()->PostTask(RTC_FROM_HERE, [p = pc_]() {
		delete p;
	});

	//delete  pc_;
}

bool CRTCMediaSink::Start() {
    // 解析Url
   // if (!ParseUrl(url_, protocol_, host_, action_, request_params_)) {
  //      return false;
  //  }

   // if (action_ != "push" || request_params_["uid"].empty() || request_params_["streamName"].empty()) 
	//{
   //     RTC_LOG(LS_WARNING) << "invalid url: " << url_;
   //     return false;
   // }

    // 发送信令请求
    // https://www.chensong.com/signaling/push?uid=xxx&streamName=xxx&audio=1&video=1&isDtls=0
    // 构造body
    std::stringstream body;
    body << "uid=" << user_name_
        << "&streamName=" << stream_name_
        << "&audio=1&video=1&isDtls=1";
    std::string url = url_ + "/signaling/push";
    HttpRequest request(url, body.str());

    // 发送请求
    CRTCGlobal::Instance()->http_manager()->Post(request, [=](HttpReply reply) {
        RTC_LOG(LS_INFO) << "signaling push response, url: " << reply.get_url()
            << ", body: " << reply.get_body()
            << ", status: " << reply.get_status_code()
            << ", err_no: " << reply.get_errno()
            << ", err_msg: " << reply.get_err_msg()
            << ", response: " << reply.get_resp();

        std::string type;
        std::string sdp;

        if (!ParseReply(reply, type, sdp)) {
           // if (media_chain_) {
           //     media_chain_->OnChainFailed(this, XRTCError::kPushRequestOfferErr);
           // }
			RTC_LOG_F(LS_WARNING) << "parse failed !!!  sdp =" << sdp;
            return;
        }


		RTC_LOG_F(LS_INFO) << "post --> ";
		//libice::p2p_peer_connection* p = pc_.get();
		pc_->GetContext()->signaling_thread()->PostTask(RTC_FROM_HERE, [ =]() {
			RTC_LOG_F(LS_INFO) << "set remoter sdp ....";
			pc_->set_remote_sdp(sdp);
			 libp2p_peerconnection::RTCOfferAnswerOptions options;
				options.recv_audio = false;
			 options.recv_video = false;
			 std::string answer =  pc_->create_answer(options, user_name_);
			 SendAnswer(answer);
		});

        //if (pc_->SetRemoteSDP(sdp) != 0) {
        //    return;
       // }

        //RTCOfferAnswerOptions options;
       // options.recv_audio = false;
       // options.recv_video = false;
       // std::string answer = pc_->CreateAnswer(options, request_params_["uid"]);
      //  SendAnswer(answer);

    }, this);

    return true;
}

void CRTCMediaSink::Setup(const std::string& json_config) {
   /* JsonValue value;
    value.FromJson(json_config);
    JsonObject jobj = value.ToObject();
    JsonObject jxrtc_media_sink = jobj["xrtc_media_sink"].ToObject();
    url_ = jxrtc_media_sink["url"].ToString();*/
}

void CRTCMediaSink::Stop() {
    RTC_LOG(LS_INFO) << "CRTCMediaSink Stop";
    // 向后台服务发送停止推流请求
    SendStop();
}
//
//void CRTCMediaSink::OnNewMediaFrame(std::shared_ptr<MediaFrame> frame) {
//    // 通过网络线程，将x264压缩后的数据发送到服务器
//    CRTCGlobal::Instance()->network_thread()->PostTask(webrtc::ToQueuedTask([=]() {
//        if (MainMediaType::kMainTypeVideo == frame->fmt.media_type) {
//            PacketAndSendVideo(frame);
//        }
//    }));
//}
//
//void CRTCMediaSink::OnNetworkInfo(PeerConnection*, int64_t rtt_ms, 
//    int32_t packets_lost, uint8_t fraction_lost, uint32_t jitter) 
//{
//    CRTCGlobal::Instance()->api_thread()->PostTask(
//        webrtc::ToQueuedTask([=]() {
//            CRTCGlobal::Instance()->engine_observer()->OnNetworkInfo(
//                rtt_ms, packets_lost, fraction_lost, jitter);
//        }));
//}

//void CRTCMediaSink::OnConnectionState(PeerConnection*, 
//    PeerConnectionState pc_state) 
//{
//    if (PeerConnectionState::kConnected == pc_state) {
//        if (media_chain_) {
//            media_chain_->OnChainSuccess();
//        }
//    }
//    else if (PeerConnectionState::kFailed == pc_state) {
//        if (media_chain_) {
//            media_chain_->OnChainFailed(this, XRTCError::kPushIceConnectionErr);
//        }
//    }
//}



void CRTCMediaSink::set_http_param(const std::string & action, std::string & url, const std::string & user_name, const std::string & stream_name)
{
	action_ = action;
	url_ = url;
	user_name_ = user_name;
	stream_name_ = stream_name;
}

bool CRTCMediaSink::ParseReply(const HttpReply& reply, std::string& type,
    std::string& sdp) 
{
    if (reply.get_status_code() != 200 || reply.get_errno() != 0) {
        RTC_LOG(LS_WARNING) << "signaling response error";
        return false;
    }

    JsonValue value;
    if (!value.FromJson(reply.get_resp())) {
        RTC_LOG(LS_WARNING) << "invalid json response";
        return false;
    }

    JsonObject jobj = value.ToObject();
    int err_no = jobj["errNo"].ToInt();
    if (err_no != 0) {
        RTC_LOG(LS_WARNING) << "response errNo is not 0, err_no: " << err_no;
        return false;
    }

    JsonObject data = jobj["data"].ToObject();
    type = data["type"].ToString();
    sdp = data["sdp"].ToString();

    if (sdp.empty()) {
        RTC_LOG(LS_WARNING) << "sdp is empty";
        return false;
    }

    return true;
}

void CRTCMediaSink::SendAnswer(const std::string& answer) {
  //  if (request_params_["uid"].empty() || request_params_["streamName"].empty()) {
   //     RTC_LOG(LS_WARNING) << "send answer failed, invalid url: " << url_;
  //      return;
  //  }

    // 构造body
    std::stringstream body;
	body << "uid=" << user_name_
        << "&streamName=" <<  stream_name_
        << "&type=push"
        << "&answer=" << HttpManager::UrlEncode(answer);

    std::string url = url_ + "/signaling/sendanswer";
    HttpRequest request(url, body.str());
    // 发送请求
    CRTCGlobal::Instance()->http_manager()->Post(request, [=](HttpReply reply) {
        RTC_LOG(LS_INFO) << "signaling sendanswer response, url: " << reply.get_url()
            << ", body: " << reply.get_body()
            << ", status: " << reply.get_status_code()
            << ", err_no: " << reply.get_errno()
            << ", err_msg: " << reply.get_err_msg()
            << ", response: " << reply.get_resp();

        if (reply.get_status_code() != 200 || reply.get_errno() != 0) {
            RTC_LOG(LS_WARNING) << "signaling sendanswer response error";
            return;
        }

        JsonValue value;
        if (!value.FromJson(reply.get_resp())) {
            RTC_LOG(LS_WARNING) << "invalid json response";
            return;
        }

        JsonObject jobj = value.ToObject();
        int err_no = jobj["errNo"].ToInt();
        if (err_no != 0) {
            RTC_LOG(LS_WARNING) << "response errNo is not 0, err_no: " << err_no;
            return;
        }

     }, this);
}

void CRTCMediaSink::SendStop() {
    // 发送停止推流的信令请求
    // https://www.chensong.com/signaling/stoppush?uid=xxx&streamName=xxx
    // 构造body
    std::stringstream body;
    body << "uid=" << user_name_
        << "&streamName=" << stream_name_;
    std::string url = url_ + "/signaling/stoppush";
    HttpRequest request(url, body.str());

    // 发送请求
    CRTCGlobal::Instance()->http_manager()->Post(request, [=](HttpReply reply) {
        RTC_LOG(LS_INFO) << "signaling stoppush response, url: " << reply.get_url()
            << ", body: " << reply.get_body()
            << ", status: " << reply.get_status_code()
            << ", err_no: " << reply.get_errno()
            << ", err_msg: " << reply.get_err_msg()
            << ", response: " << reply.get_resp();

        if (reply.get_status_code() != 200 || reply.get_errno() != 0) {
            RTC_LOG(LS_WARNING) << "signaling stoppush response error";
            return;
        }

        JsonValue value;
        if (!value.FromJson(reply.get_resp())) {
            RTC_LOG(LS_WARNING) << "invalid json response";
            return;
        }

        JsonObject jobj = value.ToObject();
        int err_no = jobj["errNo"].ToInt();
        if (err_no != 0) {
            RTC_LOG(LS_WARNING) << "response errNo is not 0, err_no: " << err_no;
            return;
        }

    }, this);
}

//void CRTCMediaSink::PacketAndSendVideo(std::shared_ptr<MediaFrame> frame) {
//    pc_->SendEncodedImage(frame);
//}

} // namespace xrtc