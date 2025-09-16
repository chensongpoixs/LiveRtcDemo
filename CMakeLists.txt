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


			Imm32 
			comctl32
			ws2_32.lib
			winmm.lib
			)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /SAFESEH:NO")

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})