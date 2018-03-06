#pragma once

#define LIST_MAX_SIZE 10

#define EXE_TARGET		 _T("youtube-dl.exe")
#define EXE_CMD_OPTION	 _T(" -f 137+140 ")
//#define EXE_CMD_OPTION _T(" -f bestvideo+bestaudio ")

#define MSG_START_DOWNLOAD		  _T("MSG :: 영상 다운로드를 시작합니다!")		
#define MSG_ERROR_INPUT_EMPTY	  _T("MSG :: 주소가 입력되지 않았습니다!")		
#define MSG_ERROR_CONNECTED_PIPE  _T("MSG :: PIPE가 연결되지 않았습니다!")
#define MSG_ERROR_CREATE_PROCESS  _T("MSG :: 프로세스가 생성되지 않았습니다!")
#define MSG_ERROR_URL			  _T("MSG :: 영상의 URL이 잘못 설정 되었습니다, 확인을 누르면 다음 영상을 다운로드합니다!")
#define MSG_SUCCESS_DOWNLOAD	  _T("MSG :: 영상 다운로드가 완료 되었습니다!")
#define MSG_LIST_SIZE_FULL		  _T("MSG :: 리스트는 최대 10개까지 가능합니다.")

