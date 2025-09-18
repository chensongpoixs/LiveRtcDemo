cmake_minimum_required(VERSION 3.8)

project(crtc_client)




#add_definitions(
				#	-DWIN32
				#	-D_DEBUG
				##	-D_WINDOWS
				#	-D_UNICODE
				#	-DUNICODE
				#	-D_AFXDLL
#)

include_directories(
	#${XRTC_DIR}
	#${XRTC_THIRD_PARTY_DIR}/include
	#${XRTC_DIR}/../xrtc-third_party/NIM_Duilib_Framework
	.
	../libwebrtc
	../deps/libyuv/include
	../deps/abseil-cpp/
)

link_directories(
#	${XRTC_THIRD_PARTY_DIR}/lib
#	${XRTC_DIR}/../xrtc-third_party/out/Windows/lib
)


#

file(GLOB all_src
	*.h
	*.cpp 
	LiveWin32.rc
	video_render/*.h
	video_render/*.cpp
	desktop_capture/*.h 
	desktop_capture/*.cpp

)



set(AllFile ${all_src})
foreach(fileItem ${AllFile})       
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${fileItem}" DIRECTORY)
	
    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")
	#message(status   "---> fileItem = ${fileItem}     GROUP ---->  ${GROUP}")
    # Group into "Source Files" and "Header Files"
    set(GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${fileItem}")
endforeach()
add_executable(${PROJECT_NAME} ${all_src})


#target_link_options(${PROJECT_NAME} PRIVATE
#		/ENTRY:wWinMainCRTStartup
#)
target_link_libraries(${PROJECT_NAME} 





		libwebrtc.lib
		abseil_dll.lib
		absl_cordz_functions.lib
		absl_cordz_handle.lib
		absl_cordz_info.lib
		absl_cordz_sample_token.lib
		absl_flags.lib
		absl_flags_commandlineflag_internal.lib
		absl_flags_internal.lib
		absl_flags_marshalling.lib
		absl_flags_parse.lib
		absl_flags_private_handle_accessor.lib
		absl_flags_program_name.lib
		absl_flags_reflection.lib
		absl_flags_usage.lib
		absl_flags_usage_internal.lib
		absl_low_level_hash.lib
		absl_random_internal_distribution_test_util.lib
		jpeg-static.lib

		# api
		audio_options_api
		
		api.lib
		peerconnection.lib

		#  moudles /video /desktop_capture

		desktop_capture_generic.lib
		primitives
		desktop_capture_differ_sse2

		d3d11.lib
      dxgi.lib
		

		#common_video 

		common_video
		
		proxy.lib
		rtc_pc_base.lib
		checks.lib
		rtc_base.lib
		common_audio.lib
		task_queue.lib
		default_task_queue_factory.lib
		rtc_base_win.lib
		rtc_base_win_wgc.lib
		rtc_base_approved.lib

		rtc_media_base.lib



		# api/video

		video_rtp_headers 						
		video_frame 							
		video_frame_i010    					
		#recordable_encoded_frame 				
		#video_frame_type  						
		#render_resolution 						
		encoded_image 							
		encoded_frame 							
		rtp_video_frame_assembler 				
		#video_codec_constants  				
		video_bitrate_allocation 				
		#video_layers_allocation 				
		video_bitrate_allocator 				
		#video_bitrate_allocator_factory 		
		#video_stream_decoder 					
		video_stream_decoder_create 			
		video_adaptation 						
		#video_stream_encoder 					
		video_frame_metadata 					
		builtin_video_bitrate_allocator_factory


		# api 
		media_stream_interface

			Imm32 
			comctl32
			ws2_32.lib
			winmm.lib


			libyuv.lib
		libcrypto.lib 
		libssl.lib 
		#
		##libredis.lib
		#libzmalloc.lib
		iphlpapi.lib
		#crypto32.lib 
		ws2_32   
		crypt32
		Shell32.lib
		 advapi32
              iphlpapi
              psapi
              shell32
              user32
              userenv
              ws2_32
			  mswsock.lib
			  #  webrtc  timeGetTime  
			  winmm.lib
			  #ucrt.lib
			  #  libuv.lib  的依赖库
			  dbghelp.lib
			)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /SAFESEH:NO")

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})