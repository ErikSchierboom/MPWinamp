//////////////////////////////////////////////////////////////////////
//																	//
// File: MPPluginImpl.cpp											//
// Content: Messenger Plus! Plugin API - Implementation				//
// Author: Patchou													//
//																	//
// Last Update: 2004/09/17											//
//																	//
//////////////////////////////////////////////////////////////////////

//If you include this file in a Visual C++ project, go in the
//properties of the file and select "Not using precompiled headers"
//or uncomment the following #include statement
//#include "stdafx.h"
#include "MPPluginHeader.h"

//////////////////////////////////////////////////////////////////////
//																	//
// Messenger Plus! control characters								//
//																	//
// The Notify control character is for exclusive use by plugins. It //
// is generally inserted by plugin commands. This code must be at	//
// the beginning of a message and must be followed by a 5			//
// characters notify code unique to your plugin.					//
//																	//
// Example: "XsamplHello!" (where "X" is the 0x12 character)		//
// When received, the user will only see "Hello!" and				//
// ReceiveNotify() will be called with "sampl" in sNotifyCode.		//
//																	//
//////////////////////////////////////////////////////////////////////
const char* sCCNotify = "\x12";


//////////////////////////////////////////////////////////////////////
//																	//
// Messenger Plus! control characters								//
//																	//
// These control characters are used by Messenger Plus! to perform  //
// different kind of actions. Feel free to use them in your own		//
// messages.														//
//																	//
//////////////////////////////////////////////////////////////////////
const char* sCCColor		= "\x03"; //Ctrl+K multi-format
const char* sCCBold			= "\x02"; //Ctrl+B multi-format
const char* sCCItalic		= "\x05"; //Ctrl+T multi-format
const char* sCCUnderline	= "\x1F"; //Ctrl+U multi-format
const char* sCCStrikeout	= "\x06"; //Ctrl+S multi-format
const char* sCCReset		= "\x0F"; //Ctrl+O multi-format

//When placed at the beginning of a message, this control character
//asks Messenger Plus! to temporary disable emoticons for the
//message.
const char* sCCNoIcon		= "\x08";

//To display action message (/me), put these control characters at
//the beginning and at the end of your message.
const char* sCCMeStart		= "«I ";
const char* sCCMeEnd		= "»";


//////////////////////////////////////////////////////////////////////
//                                                                  //
// These strings can be used when a service name or a service ID    //
// is required as parameter of a function of the Messenger API.     //
//                                                                  //
//////////////////////////////////////////////////////////////////////
const char sMessengerServiceName[] = ".NET Messenger Service";
const char sMessengerServiceID[] = "{9b017612-c9f1-11d2-8d9f-0000f875c541}";



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Display toast popups - function implementation			//
// Note: for more information, check MPPluginHeader.h.				//
//																	//
//////////////////////////////////////////////////////////////////////
struct MPL_TOAST_INFO
{
	const void* sTitle;
	const void* sMessage;
	const void* sProgram;
	int nSoundFile; //Can also be used as a string

	DWORD nReserved;
};

void DisplayToast(const char* sMessage, const char* sTitle, const char* sProgram, bool bPlaySound)
{
	char sMessageSafe[256]; sMessageSafe[255] = '\0';
	strncpy(sMessageSafe, sMessage, 255);

	MPL_TOAST_INFO info;
	info.sMessage = sMessageSafe;
	info.sTitle = sTitle;
	info.sProgram = sProgram;
	info.nSoundFile = (bPlaySound ? -1 : NULL);

	UINT nMsg = RegisterWindowMessage("MessengerPlus_DisplayToast");
	SendMessage(HWND_BROADCAST, nMsg, (WPARAM)&info, FALSE);
}

void DisplayToastW(const WCHAR* sMessage, const WCHAR* sTitle, const WCHAR* sProgram, bool bPlaySound)
{
	WCHAR sMessageSafe[256]; sMessageSafe[255] = '\0';
	wcsncpy(sMessageSafe, sMessage, 255);

	MPL_TOAST_INFO info;
	info.sMessage = sMessage;
	info.sTitle = sTitle;
	info.sProgram = sProgram;
	info.nSoundFile = (bPlaySound ? -1 : NULL);

	UINT nMsg = RegisterWindowMessage("MessengerPlus_DisplayToast");
	SendMessage(HWND_BROADCAST, nMsg, (WPARAM)&info, TRUE);
}


//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Change the name of the user - function implementation	//
// Note: for more information, check MPPluginHeader.h.				//
//																	//
//////////////////////////////////////////////////////////////////////
void SetNewName(const char* sName)
{
	UINT nMsg = RegisterWindowMessage("MessengerPlus_SetName");
	SendMessage(HWND_BROADCAST, nMsg, (WPARAM)sName, FALSE);
}

void SetNewNameW(const WCHAR* sName)
{
	UINT nMsg = RegisterWindowMessage("MessengerPlus_SetName");
	SendMessage(HWND_BROADCAST, nMsg, (WPARAM)sName, TRUE);
}
