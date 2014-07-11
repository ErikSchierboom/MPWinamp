//////////////////////////////////////////////////////////////////////
//																	//
// File: MPPluginHeader.h											//
// Content: Messenger Plus! Plugin API - Declarations				//
// Author: Patchou													//
//																	//
// Last Update: 2004/09/17											//
//																	//
//////////////////////////////////////////////////////////////////////


//Quick function reference
//
//  Initialization function
//     Initialize()
//  Uninitialization function
//     Uninitialize()
//  Configuration function
//     Configure()
//
//  Inform the users about the features of the plugin
//     PublishInfo()
//     PublishInfoW()
//  Provide new commands in Messenger Plus!	
//     ParseCommand()
//     ParseCommandW()
//  Provide new tags in Messenger Plus!
//     ParseTag()
//     ParseTagW()
//  Allow special actions when a plugin command message is received
//     ReceiveNotify()
//     ReceiveNotifyW()
//  
//  Display toast popups
//     DisplayToast()
//     DisplayToastW()
//  Change the display name of the user
//     SetNewName()
//     SetNewNameW()


//Make sure this file is included only once
#ifndef _MPPLUGIN_HEADER_H
#define _MPPLUGIN_HEADER_H
#include <windows.h>

//This defines how the compiler must export the functions so that
//Messenger Plus! can import them properly.
#define MPPLUGIN_CALL extern "C" __declspec(dllexport)

#define MPPLUGIN_RETURN_BOOL MPPLUGIN_CALL BOOL __stdcall
#define MPPLUGIN_RETURN_VOID MPPLUGIN_CALL void __stdcall


//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Declarations of global interest							//
//																	//
// Note: for more information about these variables, structures		//
// and functions, check MPPluginImpl.cpp.							//
//																	//
//////////////////////////////////////////////////////////////////////
struct PLUGIN_PARAM;
struct PLUGIN_PARAMW;
struct PLUGIN_PUBLISH_LIST;
struct PLUGIN_PUBLISH_LISTW;

extern const char* sCCNotify;
extern const char* sCCColor;
extern const char* sCCBold;
extern const char* sCCItalic;
extern const char* sCCUnderline;
extern const char* sCCStrikeout;
extern const char* sCCReset;
extern const char* sCCNoIcon;
extern const char* sCCMeStart;
extern const char* sCCMeEnd;

extern const char sMessengerServiceName[];
extern const char sMessengerServiceID[];



//////////////////////////////////////////////////////////////////////
//																	//
// Recognized plugin functions										//
//																	//
// Note: functions that end with a "W" are widechar (unicode)		//
// versions of the correspondent ANSI function. These methods are  //
// called in Windows NT4/2000/XP when defined. You are not forced	//
// to define them; if they don't exist, Messenger Plus! will do the //
// proper character conversions and use the ANSI functions.			//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Initialization function									//
//																	//
// Definition:														//
//   This function is called when Messenger starts and each time a	//
//   different user signs-in in Messenger. Note: this function MUST //
//   be exported by your plugin. If it isn't, Messenger Plus!       //
//   automatically disables the plugin, permanently, in the user's  //
//   preferences for security reasons (it will remain disabled      //
//   until Messenger Plus! is uninstalled and reinstalled).         //
//																	//
// Parameters:														//
//   * nVersion: plugin support version. This will be used in the	//
//	   future to identify different levels of support. Messenger	//
//	   Plus! 3.20 sets this value to 5.								//
//	 * sUserEmail: email of the current user in Messenger. If		//
//	   Messenger is not signed-in, this parameter is the email of	//
//	   the last user who signed in. Messenger Plus! uses this value //
//	   to load its own settings.									//
//	 * iMessengerObj: Messenger COM interface. This pointer			//
//	   can be used to retrieve an IMessenger3 interface from the	//
//	   Messenger API. For more information, consult the public		//
//	   Messenger API documentation on Microsoft's web site. 		//
//	 * return value: if your initialization is successfull, return  //
//	   TRUE to notify Messenger Plus! that the plugin is ready to   //
//	   use.															//
//																	//
// IMPORTANT: if this method is called in your plugin, if it		//
// returns TRUE, and if Messenger Plus! still doesn't call your     //
// other functions, the reason is probably that your plugin doesn't //
// export its functions correctly. ALL your functions MUST be       //
// declared with the __stdcall keyword (included in the             //
// MPPLUGIN_RETURN_xxx defines).								    //
//																	//
// Technical Note: in some occasions, the iMessengerObj parameter   //
// may be null.	Also, you MUST NOT call Release() on this interface //
// (Messenger Plus! will do it for you during uninitialization).    //
// Finally, it is striclly prohibited for a plugin to try to get    //
// an IMessenger interface by calling COM functions such as			//
// CoCreateInstance(). Doing so will create many problems in		//
// Messenger and will always result in the crach of the process.	//
//																	//
// Plugin Version Index:											//
//     Messenger Plus! 2.20: 1		Messenger Plus! 3.00: 4			//
//	   Messenger Plus! 2.21: 2		Messenger Plus! 3.20: 5			//
//	   Messenger Plus! 2.50: 3										//
//																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL Initialize(/*[in]*/ DWORD nVersion,
								/*[in]*/ const char* sUserEmail,
								/*[in]*/ IDispatch* iMessengerObj);



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Uninitialization function								//
//																	//
// Definition:														//
//	 This function is called when a different user signs-in in		//
//   Messenger (before Initialize() called for the new user). It is //
//   not guarenteed that this function will be called when			//
//   Messenger exits.												//
//																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_VOID Uninitialize();



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Configuration/Information function						//
//																	//
// Definition:														//
//	 This function is called when the user clicks on "Configure" in //
//   the Plugins section of the Preferences of Messenger Plus! 3.00 //
//   and above. Use it to display a configuration panel or an about //
//   box.															//
//																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_VOID Configure();



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Inform the users about the features of the plugin		//
//																	//
// Definition:														//
//	 This function is called by Messenger Plus! to get some			//
//   information about the plugin. You are not forced to implement  //
//   this function but doing so will help informing your users		//
//   about the features you provide (your plugin will be listed in  //
//   the Plus! menu along with its commands and tags).				//
//																	//
// Parameters:														//
//	 * sPluginName: copy the name of your plugin in this buffer.	//
//	   Your plugin will be listed using this name in the Plugins	//
//	   menu. The maximum size for this parameter is 128 characters. //
//   * aCommands: list of commands supported by your plugin.		//
//	   - nCount: number of commands you set in in the other	values. //
//     - sName: name you want to be displayed for the command in    //
//		 the Plugins menu.											//
//	   - sValue: command string. Do NOT include "/" at the 			//
//		 beginning of the command. Example: "xping".				//
//	   - sHelp: optional help you want to be displayed when the		//
//		 user selects the command from the Plugins menu. This is	//
//		 useful only when the command accepts arguments.			//
//   * aTags: list of tags supported by your plugin.				//
//	   - nCount: number of tags you set in in the other	values.		//
//     - sName: name you want to be displayed for the tag in		//
//		 the Plugins menu.											//
//	   - sValue: tag string. This parameter is the complete tag, 	//
//		 including the parenthesis. Remember that it is case		//
//		 sensitive. Example: "(!XSAMP)".							//
//	 * return value: if you want Messenger Plus! to display all the	//
//	   information to the user in the Plugins menu, return TRUE,    //
//	   else, return FALSE.											//
//																	//
//	Note that the commands and the tags will be listed in the order //
//  you put them in the lists. Also, it is a good practice to add	//
//  a command, with the name of your plugin, that displays a		//
//  readme, an about box, or any other kind of help.				//
//																	//
//////////////////////////////////////////////////////////////////////
struct PLUGIN_PUBLISH_LIST
{
	int nCount;
	char sName[50][128];
	char sValue[50][128];
	char sHelp[50][256];
};
MPPLUGIN_RETURN_BOOL PublishInfo(/*[out]*/ char *sPluginName,
								 /*[out]*/ PLUGIN_PUBLISH_LIST* aCommands,
								 /*[out]*/ PLUGIN_PUBLISH_LIST* aTags);

struct PLUGIN_PUBLISH_LISTW
{
	int nCount;
	WCHAR sName[50][128];
	WCHAR sValue[50][128];
	WCHAR sHelp[50][256];
};
MPPLUGIN_RETURN_BOOL PublishInfoW(/*[out]*/ WCHAR *sPluginName,
								  /*[out]*/ PLUGIN_PUBLISH_LISTW* sCommands,
								  /*[out]*/ PLUGIN_PUBLISH_LISTW* sTags);



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Parameter structure used by several functions			//
//																	//
// Members:															//
//	 * iConversationWnd: Messenger Conversation Window COM			//
//	   interface. This pointer can be used to retrieve an			//
//	   IMessengerConversationWnd interface from the Messenger API.	//
//	   Important: in some occasions, this parameter may be null.	//
//	   Also, you MUST NOT call Release() on this interface			//
//	   (Messenger Plus! will do it for you when the function		//
//	   returns).													//
//   * sContactName. When used, this parameter indicates the		//
//	   friendly name of the contact who's action is the source of	//
//	   the call.													//
//																	//
//////////////////////////////////////////////////////////////////////
struct PLUGIN_PARAM
{
	IDispatch *iConversationWnd;
	char sContactName[512];
};

struct PLUGIN_PARAMW
{
	IDispatch *iConversationWnd;
	WCHAR sContactName[512];
};



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Provide new commands in Messenger Plus!					//
//																	//
// Definition:														//
//   This function is called everytime Messenger Plus! needs its	//
//   plugins to analyze a command. This happens when the following	//
//	 two conditions are met:										//
//		* the user entered a message and chose to send it			//
//		* the message begins by "/x". Commands defined by plugins	//
//		  must begin with an "x" (and a command always begins by a  //
//		  "/").														//
//																	//
// Parameters:														//
//	 * sCommand: the command entered by the user, including the "/" //
//	   character. Note that commands are not case sensitive.		//
//   * sCommandArg: all the text that followed the space after the	//
//	   command.														//
//	 * pParam: additional information sent by Messenger Plus!. For  //
//	   more information, read the documentation of the PLUGIN_PARAM //
//	   structure. iConversationWnd is used.							//
//	 * sResult: if you recognize the command passed in sCommand,	//
//	   you must copy the new text to send in this parameter. If		//
//	   you copy an empty string, the text will be ignored and won't //
//	   be sent on the network. Important: the size of this buffer   //
//	   is 4096 characters and it is YOUR responsability to verify	//
//	   that you don't write more characters to avoid memory faults. //
//	 * return value: if you recognized the command and filled the   //
//	   sResult buffer, return TRUE, else, return FALSE.				//
//																	//
// Example:															//
//	 The user sends the following text: "/xquote hello you".		//
//	 sCommand = "/xquote"											//
//	 sCommandArg = "hello you"										//
//	 You could return in sResult this text: "I salute you"			//
//																	//
// Advanced: if the plugin version returned by Initialize() is 2 or //
// above, you can specify more than one message or command in		//
// sResult. Simply create new lines with # as first character (use  //
// '\n' to create new lines in your string). Up to 20 actions can   //
// be specified, each being executed at a 0.5 second interval. A	//
// different delay can even be entered for each action. After the   //
// first #, just put a digit between 1 and 9 and another #.			//
//   Example: sResult = "#First message\n#Second msg\n#5#Third msg" //
//																	//
// Important: keep in mind that several plugins can be installed	//
// and that the user sends a lot of text. If you don't support		//
// the command passed in parameter, you must return as fast as		//
// possible and without doing anything else.						//
//																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL ParseCommand(/*[in]*/  const char* sCommand,
								  /*[in]*/  const char* sCommandArg,
								  /*[in]*/  PLUGIN_PARAM* pParam,
								  /*[out]*/ char* sResult);

MPPLUGIN_RETURN_BOOL ParseCommandW(/*[in]*/  const WCHAR* sCommand,
								   /*[in]*/  const WCHAR* sCommandArg,
								   /*[in]*/  PLUGIN_PARAMW* pParam,
								   /*[out]*/ WCHAR* sResult);



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Provide new tags in Messenger Plus!						//
//																	//
// Definition:														//
//   This function is called everytime Messenger Plus! needs its	//
//   plugins to analyze a tag. This happens when the following two	//
//	 conditions are met:											//
//		* the user entered a message and chose to send it			//
//		* the message contains a tag that begins by "x" or "X". A	//
//		  tag is always formatted this way: "(!tag)", is case		//
//		  sensitive and doesn't contain space characters. So plugin //
//		  tags must look like "(!xtag)" (where "tag" can be			//
//		  anything you want).										//
//																	//
// Parameters:														//
//	 * sTag: the tag entered by the user, containing the			//
//	   parenthesis.													//
//	 * pParam: additional information sent by Messenger Plus!. For  //
//	   more information, read the documentation of the PLUGIN_PARAM //
//	   structure. iConversationWnd is used.							//
//	 * sResult: if you recognize the tag passed in sTag, you	    //
//	   must copy the text that will replace the tag in this			//
//	   parameter. Important: the size of this buffer is 2048		//
//	   characters and it is YOUR responsability to verify that you	//
//	   don't write more characters to avoid memory faults. In any	//
//	   case, no more than 1100 characters will be sent on the		//
//	   network, even if the original text contained several tags	//
//	   using, for example, 500 characters each.						//
//	 * return value: if you recognized the tag and filled the		//
//	   sResult buffer, return TRUE, else, return FALSE.				//
//																	//
// Example:															//
//	 The user sends the following text: "my horoscope: (!XH)".		//
//	 sTag = "(!XH)"													//
//	 You could return in sResult this text: "you'll meet somone		//
//		today" and text sent on the network will be "my horoscope: 	//
//		you'll meet someone today".									//
//																	//
// Important: keep in mind that several plugins can be installed	//
// and that the user sends a lot of text. If you don't support		//
// the tag passed in parameter, you must return as fast as			//
// possible and without doing anything else.						//
//																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL ParseTag(/*[in]*/  const char* sTag,
							  /*[in]*/  PLUGIN_PARAM* pParam,
							  /*[out]*/ char* sResult);

MPPLUGIN_RETURN_BOOL ParseTagW(/*[in]*/  const WCHAR* sTag,
							   /*[in]*/  PLUGIN_PARAMW* pParam,
							   /*[out]*/ WCHAR* sResult);



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Allow special actions when a plugin message is received	//
//																	//
// Definition:														//
//   This function is called everytime Messenger Plus! detects a	//
//   plugin text ID in a message received from a user. This ID is	//
//	 generally placed at the beginning of a text by a plugin		//
//	 command to perform an action on the destination computers.		//
//	 This can be used, for example, to play a sound. See the		//
//	 control characters section for more information.				//
//																	//
// Parameters:														//
//	 * sNotifyCode: this 5 character string is the notify code that //
//	   was sent next to the plugin ID control character. Use it to  //
//	   identify what action to perform.								//
//	 * sText: the rest of the received message. You can use it to	//
//	   get more information about the action you want to perform.	//
//	   However, you MUST NOT use this parameter to determine if an  //
//	   action is supported by your plugin. Use sNotifyCode instead. //
//	 * pParam: additional information sent by Messenger Plus!. For  //
//	   more information, read the documentation of the PLUGIN_PARAM //
//	   structure. iConversationWnd and sContactName are used.		//
//	 * sTextToSend: this parameter is optional. You can use it if	//
//	   you want to ask Messenger Plus! to send a new message after  //
//	   this one has been displayed. This WON'T modify the message	//
//	   associated with the notify code, this will simply send a new //
//	   one. Important: the size of this buffer is 4096 characters	//
//	   and it is YOUR responsability to verify that you don't write //
//	   more characters to avoid memory faults.
//	 * return value: if you recognized the notify code return TRUE, //
//	   else, return FALSE.											//
//																	//
// Advanced: if the plugin version returned by Initialize() is 2 or //
// above, you can specify more than one message or command in		//
// sTextToSend. Simply create new lines with # as first character   //
// (use '\n' to create new lines in your string). Up to 20 actions  //
// can be specified, each being executed at a 0.5 second interval.  //
// A different delay can even be entered for each action. After the //
// first #, just put a digit between 1 and 9 and another #.			//
//   Example: sTextToSend = "#First message\n#5#Second message"		//
//																	//
// Important: keep in mind that several plugins can be installed	//
// and that a lot of text is received. If you don't support the		//
// notify code passed in parameter, you must return as fast as		//
// possible and without doing anything else.						//
//																	//
//////////////////////////////////////////////////////////////////////					 
MPPLUGIN_RETURN_BOOL ReceiveNotify(/*[in]*/  const char* sNotifyCode,
								   /*[in]*/  const char* sText,
								   /*[in]*/  PLUGIN_PARAM* pParam,
								   /*[out]*/ char* sTextToSend);

MPPLUGIN_RETURN_BOOL ReceiveNotifyW(/*[in]*/  const WCHAR* sNotifyCode,
									/*[in]*/  const WCHAR* sText,
									/*[in]*/  PLUGIN_PARAMW* pParam,
									/*[out]*/ WCHAR* sTextToSend);



//////////////////////////////////////////////////////////////////////
//																	//
// Messenger Plus! utility functions								//
//																	//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Display toast popups									//
//																	//
// Definition:														//
//   If the plugin engine version is 3 or above (see Initialize()), //
//   your plugin can call this function to display a toast popup.   //
//   The function returns immediately, it doesn't wait for the      //
//   toast to be displayed.											//
//																	//
// Parameters:														//
//	 * sMessage: the text that will be displayed in the middle of   //
//	   the toast. If the text is too long to fit the window, it     //
//	   will be truncated.											//
//	 * sTitle: the title displayed on top of the toast. If NULL,    //
//	   the default title is displayed.								//
//   * sProgram: a program, or web link, that will be executed if   //
//	   the user clicks on the toast. If NULL, clicking on the toast //
//     will do nothing.	If this parameter is an email, Messenger    //
//     Plus! will attempt to start a new chat with the user.		//
//   * bPlaySound: set to true if you want Messenger Plus! to play  //
//     the default sound associated for notifications in the		//
//     preferences of the user.										//
//																	//
//   Note: as the user may have configured Messenger Plus! not to   //
//   display notifications when he/she is busy, do not assume that  //
//   the toast will always be displayed.							//
//																	//
//   Technical Note: the message must be sent from the same thread  //
//   Initialize() was called, else, Messenger Plus! will reject the //
//   call for security reasons.										//
//																	//
//////////////////////////////////////////////////////////////////////
void DisplayToast(/*[in]*/  const char* sMessage,
				  /*[in]*/  const char* sTitle,
				  /*[in]*/  const char* sProgram,
				  /*[in]*/  bool bPlaySound);

void DisplayToastW(/*[in]*/  const WCHAR* sMessage,
				   /*[in]*/  const WCHAR* sTitle,
				   /*[in]*/  const WCHAR* sProgram,
				   /*[in]*/  bool bPlaySound);



//////////////////////////////////////////////////////////////////////
//																	//
// Purpose: Change the display name of the user						//
//																	//
// Definition:														//
//   If the plugin engine version is 5 or above (see Initialize()), //
//   your plugin can call this function to change the name of the   //
//   user who is currently signed-in. The function returns          //
//   immediately, it doesn't wait for the name to be actually		//
//   changed by the server.											//
//																	//
// Parameters:														//
//	 * sNewName: the new name of the user. If it contains			//
//     multi-formatcontrol codes, the name will be processed to     //
//	   make sure the server accepts the codes.						//
//																	//
//   Note: the server uses several rules to ensure the validity of  //
//   a display name. If the change is rejected by the server, an    //
//   error message will be displayed by Messenger.					//
//																	//
//   Technical Note: the message must be sent from the same thread  //
//   Initialize() was called, else, Messenger Plus! will reject the //
//   call for security reasons.										//
//																	//
//////////////////////////////////////////////////////////////////////
void SetNewName(/*[in]*/  const char* sName);

void SetNewNameW(/*[in]*/  const WCHAR* sName);


#endif //_MPPLUGIN_HEADER_H
