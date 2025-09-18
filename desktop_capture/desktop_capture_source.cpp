﻿
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

#include "desktop_capture/desktop_capture_source.h"

#include "api/video/i420_buffer.h"
#include "api/video/video_rotation.h"
#include "rtc_base/logging.h"

namespace crtc {

void DesktopCaptureSource::AddOrUpdateSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink,
    const rtc::VideoSinkWants& wants) {
  broadcaster_.AddOrUpdateSink(sink, wants);
  UpdateVideoAdapter();
}

void DesktopCaptureSource::RemoveSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) {
  broadcaster_.RemoveSink(sink);
  UpdateVideoAdapter();
}

void DesktopCaptureSource::UpdateVideoAdapter() {
  video_adapter_.OnSinkWants(broadcaster_.wants());
	rtc::VideoSinkWants wants = broadcaster_.wants();
	//video_adapter_.OnOutputFormatRequest( wants.resolutions);
}

void DesktopCaptureSource::OnFrame(const webrtc::VideoFrame& frame) {
  
  broadcaster_.OnFrame(frame);
  return;
  //if (!video_adapter_.AdaptFrameResolution(
  //        frame.width(), frame.height(), frame.timestamp_us() * 1000,
  //        &cropped_width, &cropped_height, &out_width, &out_height)) {
  //  // Drop frame in order to respect frame rate constraint.
  //  return;
  //}

//  if (out_height != frame.height() || out_width != frame.width()) {
//    // Video adapter has requested a down-scale. Allocate a new buffer and
//    // return scaled version.
//    // For simplicity, only scale here without cropping.
//    rtc::scoped_refptr<webrtc::I420Buffer> scaled_buffer =
//        webrtc::I420Buffer::Create(out_width, out_height);
//    scaled_buffer->ScaleFrom(*frame.video_frame_buffer()->ToI420());
//    webrtc::VideoFrame::Builder new_frame_builder =
//        webrtc::VideoFrame::Builder()
//            .set_video_frame_buffer(scaled_buffer)
//			.set_timestamp_rtp(0)
//			.set_timestamp_ms(rtc::TimeMillis())
//            .set_rotation(webrtc::kVideoRotation_0)
//            .set_timestamp_us(frame.timestamp_us())
//            .set_id(frame.id());
//    ;
//
//
//	/*
//	VideoFrame captureFrame =
//      VideoFrame::Builder()
//          .set_video_frame_buffer(buffer)
//          .set_timestamp_rtp(0)
//          .set_timestamp_ms(rtc::TimeMillis())
//          .set_rotation(!apply_rotation ? _rotateFrame : kVideoRotation_0)
//          .build();
//  captureFrame.set_ntp_time_ms(captureTime);
//  RTC_LOG(INFO) << "[chensong]ntp time ms = " << captureTime;
//	
//	*/
//    /*if (frame.has_update_rect()) {
//      webrtc::VideoFrame::UpdateRect new_rect =
//          frame.update_rect().ScaleWithFrame(frame.width(), frame.height(), 0,
//                                             0, frame.width(), frame.height(),
//                                             out_width, out_height);
//      new_frame_builder.set_update_rect(new_rect);
//    }*/
//    broadcaster_.OnFrame(new_frame_builder.build());
//  } else {
//    // No adaptations needed, just return the frame as is.
//
//    broadcaster_.OnFrame(frame);
//  }
}

}  // namespace  