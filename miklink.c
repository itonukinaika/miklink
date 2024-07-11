#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

char ServerIP[128]="127.0.0.1";
char ServerPort[16]="80";
char Client[128]="KM-USR-00001";
char Pid[16]="000000";
char Oprt[16]="open";
char VersionInfo[32]="MikLink 0.1";
char IntCharBuffer[128]="";
char XMLBuffer[1024]="";

WSADATA wsaData;
SOCKADDR_IN ServerSockAddr;
HOSTENT *lpHost;
SOCKET Sock;
char SockBuffer[2048];

const char HTTPRequestPreamble[512]=
"POST /KimServer/KimService.asmx HTTP/1.1\r\n"
"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; MS Web Services Client Protocol 2.0.50727.5420)\r\n"
"Content-Type: text/xml; charset=utf-8\r\n"
"SOAPAction: \"http://tempuri.org/KIMServer/PostKimLink4ScreenChange\"\r\n"
"Host: ";

const char HTTPRequestRN[3]="\r\n";
const char HTTPRequestContentLength[32]="Content-Length: ";
const char HTTPRequestPostamble[32]="Connection: Keep-Alive\r\n\r\n";

const char XMLPreamble[512]=
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">"
"<soap:Body>"
"<PostKimLink4ScreenChange xmlns=\"http://tempuri.org/KIMServer\">"
"<prm_app />"
"<prm_client>";

const char XMLPidString[128]=
"</prm_client>"
"<prm_uname /><prm_pass />"
"<prm_pid>";

const char XMLOprtString[128]=
"</prm_pid>"
"<prm_stdate />"
"<prm_stuid />"
"<prm_sopuid />"
"<prm_frmno />"
"<prm_oprt>";

const char XMLPostamble[128]=
"</prm_oprt>"
"</PostKimLink4ScreenChange>"
"</soap:Body>"
"</soap:Envelope>";

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , PSTR lpCmdLine , int nCmdShow ) {
	
	int i=0;
	for (i = 0; i < __argc; i++) {
		switch(i){
			case 1:
				strcpy(ServerIP, __argv[1]);
				break;
			case 2:
				strcpy(ServerPort, __argv[2]);
				break;
			case 3:
				strcpy(Client, __argv[3]);
				break;
			case 4:
				strcpy(Pid, __argv[4]);
				break;
			case 5:
				strcpy(Oprt, __argv[5]);
				break;
		}
	}
	
	WSAStartup(MAKEWORD(2,0), &wsaData);
	lpHost = gethostbyname(ServerIP);
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_port = htons(atoi(ServerPort));
	ServerSockAddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);
	
	//Very unsafe
	memset(XMLBuffer, 0, sizeof(XMLBuffer));
	strcpy(XMLBuffer, XMLPreamble);
	strcat(XMLBuffer, Client);
	strcat(XMLBuffer, XMLPidString);
	strcat(XMLBuffer, Pid);
	strcat(XMLBuffer, XMLOprtString);
	strcat(XMLBuffer, Oprt);
	strcat(XMLBuffer, XMLPostamble);
	
	memset(SockBuffer, 0, sizeof(SockBuffer));
	strcpy(SockBuffer,HTTPRequestPreamble);
	strcat(SockBuffer,ServerIP);
	strcat(SockBuffer,HTTPRequestRN);
	strcat(SockBuffer,HTTPRequestContentLength);
	sprintf(IntCharBuffer, "%d", strlen(XMLBuffer));
	strcat(SockBuffer,IntCharBuffer);
	strcat(SockBuffer,HTTPRequestRN);
	strcat(SockBuffer,HTTPRequestPostamble);
	strcat(SockBuffer,XMLBuffer);
	
	Sock = socket(AF_INET, SOCK_STREAM, 0);
	connect(Sock, (PSOCKADDR)&ServerSockAddr, sizeof(ServerSockAddr));
	send(Sock, SockBuffer, (int)strlen(SockBuffer), 0);
	memset(SockBuffer, 0, sizeof(SockBuffer));
	recv(Sock, SockBuffer, (int)sizeof(SockBuffer) - 1, 0);
	closesocket(Sock);
	
	WSACleanup();
	return 0;
}
