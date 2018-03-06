# YoutubeDownloader
개인 공부 목적을 위해 만들고 있음,

##ShellExecute
*참고 : https://msdn.microsoft.com/en-us/library/windows/desktop/bb762153(v=vs.85).aspx

HINSTANCE ShellExecute(
    HWND hwnd,
    LPCTSTR lpOperation,
    LPCTSTR lpFile,
    LPCTSTR lpParameters,
    LPCTSTR lpDirectory,
    INT nShowCmd
);

*ShellExecute 인자 정리
hWnd : parent window. 작업이 window에 관련되있지 않다면 일반적으로 NULL 로 설정.
lpOperation : 작업 종류. 
	- edit : editor 로 해당 문서(lpFile)를 연다. 문서파일(*.txt 는 될테고 다른 확장자는 모르겠음)이 아니면 fail.
	- explore : 탐색기로 해당 폴더(lpFile)를 연다.
	- find : 해당 폴더(lpDirectory)를 검색위치로 검색창을 연다. (테스트 해보았지만 검색위치 지정 실패...)
	- print : 해당 파일(lpFile) 출력창을 연다. 문서파일이 아니면 fail.
	- NULL : 가능하면 default 값 (뭔지 모르겠음), 아니면 open. 둘다 안되면 registry의 첫번째 값.
lpFile : 대상 파일 경로. lpDirectory에 상대경로를 사용하면 lpFile에서는 파일 이름만 사용하라는 것 같다.
lpParameters : lpFIle이 실행가능한 파일일 경우, 파일 뒤에 들어가는 옵션 파라미터들. (/s /f 이런 것)
lpDirectory : 작업폴더 경로. NULL로 지정하면 현재 파일이 있는 폴더로 설정.
nShowCmd : 파일이 열렸을 때 어떻게 보여줄 것인지에 대한 flag. 문서일 경우에는 연결프로그램으로 flag가 넘겨지는데, 그것을 어떻게 처리하는가는 연결프로그램에 달려있다.
	- SW_HIDE(0) : 숨기고 다른 프로그램 활성화
	- SW_MAXIMIZE(3) : 최대화
	- SW_MINIMIZE(6) : 최소화 시키고 창 z-order (활성화 순서) 중 다음것 활성화.
	- SW_RESTORE(9) : 활성화 하고 보여줌. 최소화나 최대화 되어있으면 원래 크기로 복원.
	- SW_SHOW(5) : 현재 크기와 위치로 활성화
	- SW_SHOWDEFAULT(10) : 해당 프로그램의 ShowWindow를 호출하도록 하여 초기값의 메인 윈도우 오픈.
	- SW_SHOWMAXIMIZED(3) : 활성화하고 최대화
	- SW_SHOWMINIMIZED(2) : 활성화하고 최소화
	- SW_SHOWMINNOACTIVE(7) : 최소화해서 보여주고 기존에 활성화 되어있던 창이 활성화.
	- SW_SHOWNA(8) : 현재 상태로 보여줌. 활성화 되어있던 창이 활성되 된 채로 유지.
	- SW_SHOWNORMAL(1) : 활성화하고 보여줌.최소화나 최대화 되어 있으면 원래 크기로 복원. (SW_RESTORE와 약간의 차이가 있으나 생략)

Return Value : HINSTANCE int로 캐스팅 가능
- 0 : 메모리나 리소스 부족
- ERROR_FILE_NOT_FOUND : 파일 없음
- ERROR_PATH_NOT_FOUND : 경로 없음
- ERROR_BAD_FORMAT : 열수 없는 파일
- SE_ERR_ACCESSDENIED : 접근 금지
- SE_ERR_ASSOCINCOMPLETE : 파일명이 불완전하거나 불가능? 
- SE_ERR_DDEBUSY : DDE(Dynamic Data Exchange)가 다른 작업중
- SE_ERR_DDEFAIL :  DDE 실패
- SE_ERR_DDETIMEOUT : DDE 요청 시간 초과
- SE_ERR_DLLNOTFOUND : DLL 파일 없음
- SE_ERR_FNF : = ERROR_FILE_NOT_FOUND
- SE_ERR_NOASSOC : 해당 확장자를 열수 있는 연결프로그램 없음
- SE_ERR_OOM : 메모리 부족
- SE_ERR_PNF : = ERROR_PATH_NOT_FOUND
- SE_ERR_SHARE : 다른 응용프로그램에서 사용중



CreateProcess()사용시 실행파일이 EXE가 아닌경우 가끔 문제가 되어서 
대체 방법으로 찾은 ShellExecuteEx()
BOOL ShellExecuteEx(_LPSHELLEXECUTEINFO lpExecInfo);
성공하면 TRUE값을 반환한다.
사용에는 아래의 구조체가 필요 설명은 적당히 여기저기서 펌 

pedef struct _SHELLEXECUTEINFO {
    DWORD     cbSize;       // 구조체 사이즈(=60)
    ULONG     fMask;        // 옵션
    HWND      hwnd;         // 친윈도우
    LPCTSTR   lpVerb;       // 동작명 ShellExecute()와 동일
    LPCTSTR   lpFile;       // 파일명
    LPCTSTR   lpParameters; // 커멘드 라인 파라미터
    LPCTSTR   lpDirectory;  // 기동시 디렉토리
    int       nShow;        // 표시 형식
    HINSTANCE hInstApp;     // 결과치
    LPVOID    lpIDList;     // 아이템ID리스트
    LPCTSTR   lpClass;      // 클래스명
    HKEY      hkeyClass;    // 파일 클래스의 레지스트리 키
    DWORD     dwHotKey;     // hot key
    union 
	{
        HANDLE  hIcon;      // 파일 클래스의 아이콘
        HANDLE  hMonitor;   // 모니터
    } DUMMYUNIONNAME;
    HANDLE    hProcess;     // 프로세스 핸들
} SHELLEXECUTEINFO, FAR *LPSHELLEXECUTEINFO;

fMask 옵션
SEE_MASK_CLASSNAME
- lpClass 멤버에 의해서 주어지는 클래스명을 사용.
SEE_MASK_CLASSKEY
- hkeyClass 멤버에 의해서 주어지는 클래스 키를 사용.
SEE_MASK_IDLIST
- lpIDList 멤버에 의해서 주어지는 아이템 ID 리스트를 사용.
SEE_MASK_INVOKEIDLIST
- 어플리케이션을 호출하기 위해서 lpIDList 멤버에 의해서 주어지는 아이템 ID 리스트를 사용. 
  lpIDList 멤버가 0 (NULL) 의 경우, 아이템 ID 리스트를 작성하고 어플리케이션을 호출.이 플래그는 SEE_MASK_IDLIST (을)를 포함.
SEE_MASK_ICON
- hIcon 멤버로 주어지는 아이콘을 사용.이 플래그를 SEE_MASK_HMONITOR (와)과 조합해 지정 불가.
SEE_MASK_HOTKEY
- dwHotKey 멤버로 주어지는 hot key를 사용.
SEE_MASK_NOCLOSEPROCESS
- 프로세스 핸들을 클로우즈 하지 않게 함. hProcess 멤버에 프로세스 핸들이 격납.
SEE_MASK_CONNECTNETDRV
- lpName 멤버는 네트워크상의 파일의 UNC(Universal Naming Convention) 패스명인 것.
SEE_MASK_FLAG_DDEWAIT
- DDE 대화가 개시되는 경우, 그것이 종료할 때까지 재개되지 않는다.
SEE_MASK_DOENVSUBST
- lpDirectory 멤버나 lpFile 멤버로 주어지는 문자열로 지정된 환경 변수를 확장.
SEE_MASK_FLAG_NO_UI
- 에러가 발생해도, 에러 메시지 박스를 표시하지 않는다.
SEE_MASK_UNICODE
- Unicode 어플리케이션인 것을 나타내는데 이 플래그를 지정.
SEE_MASK_NO_CONSOLE
- parent process의 콘솔을 사용하지 않고 , 새로운 프로세스를 위해서 콘솔을 작성.이것은 CreateProcess 함수로 CREATE_NEW_CONSOLE 플래그를 지정했을 경우와 동일.
SEE_MASK_HMONITOR
- 멀티 모니터 시스템상에서 모니터를 지정하는 경우, 이 플래그를 사용.사용되는 모니터는 hMonitor 멤버에 의해서 지정.이 플래그를 SEE_MASK_ICON (와)과 조합해 지정불가.
SEE_MASK_FLAG_LOG_USAGE
- Windows XP 이후： 어플리케이션이 기동된 회수를 보관 유지.기동된 회수가 특히 많은 어플리케이션은, 스타트 메뉴의, 자주(잘) 사용되는 어플리케이션의 리스트에 표시.
 

﻿hInstApp 성공하면 33 이상의 값이 실패하면 32 이하의 값
2 (SE_ERR_FNF) 파일이 발견되지 않습니다. 
3 (SE_ERR_PNF) 패스가 발견되지 않습니다. 
5 (SE_ERR_ACCESSDENIED) 파일 액세스가 거부되었습니다. 
8 (SE_ERR_OOM) 메모리 부족합니다. 
26 (SE_ERR_SHARE) 공유 위반이 발생했습니다. 
27 (SE_ERR_ASSOCINCOMPLETE) 파일 관련지어가 완전하지 않을까 무효입니다. 
28 (SE_ERR_DDETIMEOUT) DDE 트랜잭션(transaction)가 타임 아웃에 의해 중단되었습니다. 
29 (SE_ERR_DDEFAIL) DDE 트랜잭션(transaction)가 실패했습니다. 
30 (SE_ERR_DDEBUSY) 다른 DDE 트랜잭션(transaction)가 처리되고 있었기 때문에 DDE 트랜잭션(transaction)를 종료할 수 없었습니다. 
31 (SE_ERR_NOASSOC) 파일 관련지어가 불명합니다. 
32 (SE_ERR_DLLNOTFOUND) DLL 하지만 발견되지 않습니다.[출처] C++ : ShellExecuteEx - 프로세스 실행|작성자 에고소드




CreateProcess 함수

 

CreateProcessW(

    __in_opt    LPCWSTR lpApplicationName,

    __inout_opt LPWSTR lpCommandLine,

    __in_opt    LPSECURITY_ATTRIBUTES lpProcessAttributes,

    __in_opt    LPSECURITY_ATTRIBUTES lpThreadAttributes,

    __in        BOOL bInheritHandles,

    __in        DWORD dwCreationFlags,

    __in_opt    LPVOID lpEnvironment,

    __in_opt    LPCWSTR lpCurrentDirectory,

    __in        LPSTARTUPINFOW lpStartupInfo,

    __out       LPPROCESS_INFORMATION lpProcessInformation

    );

1.     lpApplicationName
생성한 프로세스의 실행파일 이름을 인자로 전달합니다. 경로명을 추가로 지정할 수 있으며 경로명을 지정하지 않을 경우에는 프로그램의 현재 디렉터리에서 찾게 됩니다. 현재 디렉터리에서 찾길 원하면 NULL 값을 지정해 줍니다.

2.     lpCommandLine
main 함수에 argc, argv라는 이름으로 전달되는 것처럼 프로세스에 인자를 전달할 때 이용합니다. 또는 첫 번째 인자에 NULL을 준 다음 이 두 번째 인자에 실행파일의 이름을 더불어 전달할 수도 있습니다. 이 경우엔 실행파일의 이름은 표준 검색경로 기준으로 찾게 됩니다.

3.     lpProcessAttribute
프로세스의 보안 속성을 지정할 때 사용하며 NULL을 전달할 경우 디폴트 보안 속성이 지정됩니다.

4.     lpThreadAttribute
쓰레드의 보안 속성을 지정할 때 사용하며 NULL을 전달할 경우 디폴트 보안 속성이 지정됩니다.

5.     hInheritHandle
전달인자가 TRUE일 경우, 생성되는 자식 프로세스는 부모 프로세스가 소유하는 handle 중 일부를 상속합니다. 

6.     dwCreationFlag
생성하는 프로세스의 특성(특히 우선순위)를 결정지을 때 사용하는 옵션입니다. 설정하지 않을 때는 0을 전달합니다.

7.     lpEnvironment
프로세스마다 Environment Block이라는 메모리 블록을 관리합니다. 이 블록을 이용 프로세스가 실행 시 필요로 하는 문자열을 저장할 수 있습니다. 이 전달인자를 통해서 생성하는 Environment Block을 지정합니다. NULL을 전달하면 자식 프로세스는 부모 프로세스의 환경 블록에 저장되어 있는 문자열을 복사하게 됩니다.

8.     lpCurrentDirectory
생성하는 프로세스의 현재 디렉터리를 설정하는 인자입니다. 전달인자는 디렉터리 정보를 포함하는 완전경로로 구성해야 하며 NULL 전달 시 부모 프로세스의 디렉터리를 현재 디렉터리로 합니다.

9.     lpStartInfo
STARTUPINFO 구조체 변수를 초기화 한 다음에 이 변수의 포인터를 인수로 전달합니다.

10.  lpProcessIormation
생성하는 프로세스 정보를 얻기 위해 사용되는 인자입니다. PROCESS_INFORMATION 구조체 변수의 주소 값을 인자로 전달합니다. 


출처: http://mititch.tistory.com/61 [미티치]




*CreateProcess 사용시
절대경로로 사용할경우
CreateProcess의 첫번째 인자에 절대경로를 넣는다
상대경로로 사용할 경우에는첫째 인자값을 Null로 하고
두번째 인자값을 "./hello/test.exe"로 넣는다






## youtube-dl
http://blog.myso.kr/221196606351

