//////////////////////////////////////////////////////////////////////
//																																	//
// Header file for the Messenger Plus! simple plugin project				//
//																																	//
//////////////////////////////////////////////////////////////////////
#pragma once

// Name of the plugin
#define MPWINAMP_PLUGIN_TITLE								"MPWinamp"

// Winamp commands

// Change nickname command
#define MP_WINAMP_CMD_CHANGE_NICK_NAME			"Changes Nickname"
#define MP_WINAMP_CMD_CHANGE_NICK_VALUE			"xwinampnick"
#define MP_WINAMP_CMD_CHANGE_NICK_HELP			"change nickname"
#define MP_WINAMP_CMD_CHANGE_NICK_PARSED		"/xwinampnick"

// Change massk command
#define MP_WINAMP_CMD_CHANGE_MASK_NAME			"Change the nickname mask"
#define MP_WINAMP_CMD_CHANGE_MASK_VALUE			"xwinampmask"
#define MP_WINAMP_CMD_CHANGE_MASK_HELP			"change the nickname mask"
#define MP_WINAMP_CMD_CHANGE_MASK_PARSED		"/xwinampmask"

// Play next song in winamp command
#define MP_WINAMP_CMD_NEXT_NAME							"Plays next song in winamp"
#define MP_WINAMP_CMD_NEXT_VALUE						"xwinampnext"
#define MP_WINAMP_CMD_NEXT_HELP							"play next song in winamp"
#define MP_WINAMP_CMD_NEXT_PARSED						"/xwinampnext"

// Play previous song in winamp command
#define MP_WINAMP_CMD_PREV_NAME							"Plays previous song in winamp"
#define MP_WINAMP_CMD_PREV_VALUE						"xwinampprev"
#define MP_WINAMP_CMD_PREV_HELP							"play previous song in winamp"
#define MP_WINAMP_CMD_PREV_PARSED						"/xwinampprev"

// Start playing in winamp command
#define MP_WINAMP_CMD_PLAY_NAME							"Play current song in winamp"
#define MP_WINAMP_CMD_PLAY_VALUE						"xwinampplay"
#define MP_WINAMP_CMD_PLAY_HELP							"play current song in winamp"
#define MP_WINAMP_CMD_PLAY_PARSED						"/xwinampplay"

// Pause playing in winamp command
#define MP_WINAMP_CMD_PAUSE_NAME						"Pause current song in winamp"
#define MP_WINAMP_CMD_PAUSE_VALUE						"xwinamppause"
#define MP_WINAMP_CMD_PAUSE_HELP						"pause current song in winamp"
#define MP_WINAMP_CMD_PAUSE_PARSED					"/xwinamppause"

// Stop playing in winamp command
#define MP_WINAMP_CMD_STOP_NAME							"Stop current song in winamp"
#define MP_WINAMP_CMD_STOP_VALUE						"xwinampstop"
#define MP_WINAMP_CMD_STOP_HELP							"stop current song in winamp"
#define MP_WINAMP_CMD_STOP_PARSED						"/xwinampstop"

// Toggle repeat in winamp command
#define MP_WINAMP_CMD_REPEAT_NAME						"Toggle repeat in winamp"
#define MP_WINAMP_CMD_REPEAT_VALUE					"xwinamprepeat"
#define MP_WINAMP_CMD_REPEAT_HELP						"Toggle repeat in winamp"
#define MP_WINAMP_CMD_REPEAT_PARSED					"/xwinamprepeat"

// Toggle shuffle in winamp command
#define MP_WINAMP_CMD_SHUFFLE_NAME					"Toggle shuffle in winamp"
#define MP_WINAMP_CMD_SHUFFLE_VALUE					"xwinampshuffle"
#define MP_WINAMP_CMD_SHUFFLE_HELP					"Toggle shuffle in winamp"
#define MP_WINAMP_CMD_SHUFFLE_PARSED				"/xwinampshuffle"

// Toggle always on top command
#define MP_WINAMP_CMD_ALWAYS_ON_TOP_NAME		"Toggle always on top in winamp"
#define MP_WINAMP_CMD_ALWAYS_ON_TOP_VALUE		"xwinampontop"
#define MP_WINAMP_CMD_ALWAYS_ON_TOP_HELP		"toggle always on top in winamp"
#define MP_WINAMP_CMD_ALWAYS_ON_TOP_PARSED	"/xwinampontop"

// Close winamp command
#define MP_WINAMP_CMD_CLOSE_NAME						"Close winamp"
#define MP_WINAMP_CMD_CLOSE_VALUE						"xwinampclose"
#define MP_WINAMP_CMD_CLOSE_HELP						"close winamp"
#define MP_WINAMP_CMD_CLOSE_PARSED					"/xwinampclose"

// Open file dialog command
#define MP_WINAMP_CMD_OPEN_FILE_NAME				"Open file dialog in winamp"
#define MP_WINAMP_CMD_OPEN_FILE_VALUE				"xwinampopenfile"
#define MP_WINAMP_CMD_OPEN_FILE_HELP				"open file dialog in winamp"
#define MP_WINAMP_CMD_OPEN_FILE_PARSED			"/xwinampopenfile"

// Open URL dialog command
#define MP_WINAMP_CMD_OPEN_URL_NAME					"Open URL dialog in winamp"
#define MP_WINAMP_CMD_OPEN_URL_VALUE				"xwinampopenurl"
#define MP_WINAMP_CMD_OPEN_URL_HELP					"open URL dialog in winamp"
#define MP_WINAMP_CMD_OPEN_URL_PARSED				"/xwinampopenurl"

// Open jump-to-file dialog command
#define MP_WINAMP_CMD_OPEN_JTF_NAME					"Open jump-to-file dialog in winamp"
#define MP_WINAMP_CMD_OPEN_JTF_VALUE				"xwinampopenjtf"
#define MP_WINAMP_CMD_OPEN_JTF_HELP					"open ump-to-file dialog in winamp"
#define MP_WINAMP_CMD_OPEN_JTF_PARSED				"/xwinampopenjtf"

// Open jump-to-time dialog command
#define MP_WINAMP_CMD_OPEN_JTT_NAME					"Open jump-to-time dialog in winamp"
#define MP_WINAMP_CMD_OPEN_JTT_VALUE				"xwinampopenjtt"
#define MP_WINAMP_CMD_OPEN_JTT_HELP					"open ump-to-time dialog in winamp"
#define MP_WINAMP_CMD_OPEN_JTT_PARSED				"/xwinampopenjtt"
	
// Open file info dialog command
#define MP_WINAMP_CMD_OPEN_FILE_INFO_NAME		"Open file info dialog in winamp"
#define MP_WINAMP_CMD_OPEN_FILE_INFO_VALUE	"xwinampopenfileinfo"
#define MP_WINAMP_CMD_OPEN_FILE_INFO_HELP		"open file info dialog in winamp"
#define MP_WINAMP_CMD_OPEN_FILE_INFO_PARSED	"/xwinampopenfileinfo"

// Plugin tags

// Winamp title tag
#define MP_WINAMP_TAG_TITLE_NAME						"Title"
#define MP_WINAMP_TAG_TITLE_VALUE						"(!XTITLE)"

// Winamp artist tag
#define MP_WINAMP_TAG_ARTIST_NAME						"Artist"
#define MP_WINAMP_TAG_ARTIST_VALUE					"(!XARTIST)"

// Winamp artist-title tag
#define MP_WINAMP_TAG_ARTISTTITLE_NAME			"Artist title"
#define MP_WINAMP_TAG_ARTISTTITLE_VALUE			"(!XARTISTTITLE)"

// Winamp songindex tag
#define MP_WINAMP_TAG_SONGINDEX_NAME				"Song index"
#define MP_WINAMP_TAG_SONGINDEX_VALUE				"(!XSONGINDEX)"

// Winamp /xwinampnick arguments
#define MP_WINAMP_ARG_ENABLE								"on"
#define MP_WINAMP_ARG_DISABLE								"off"
#define MP_WINAMP_ARG_ENABLE_ALT						"enable"
#define MP_WINAMP_ARG_DISABLE_ALT						"disable"
#define MP_WINAMP_ARG_CONFIG								"config"

// INI-file definitiona
#define INI_FILE_NAME						"mpwinamp.ini"
#define INI_APP_NAME						"settings"
#define INI_ENABLED_KEY_NAME		"enabled"
#define INI_MASK_KEY_NAME				"mask"
#define INI_REFRESH_KEY_NAME  	"refresh"
#define INI_NOTIFY_KEY_NAME   	"notify"
#define INI_ENABLED_DEF_VAL			DEF_ENABLED
#define INI_MASK_DEF_VAL				DEF_MASK
#define INI_REFRESH_DEF_VAL			DEF_REFRESH_RATE
#define INI_NOTIFY_DEF_VAL			DEF_NOTIFY

// Registry definitions
#define REG_DIR_ROOT_KEY				HKEY_LOCAL_MACHINE
#define REG_DIR_KEY_NAME				"SOFTWARE\\Patchou\\MsgPlus2"
#define REG_DIR_KEY_VALUE				"PluginDir"

#define REG_CONF_ROOT_KEY				HKEY_CURRENT_USER
#define REG_CONF_KEY_NAME				"SOFTWARE\\Patchou\\MsgPlus2\\Plugins\\MPWinamp\\"
#define REG_CONF_MASK_VALUE			"mask"
#define REG_CONF_NOTIFY_VALUE		"notify"
#define REG_CONF_ENABLED_VALUE  "enabled"
#define REG_CONF_REFRESH_VALUE	"refreshrate"

// The tags that can be used in the mask
#define TAG_CHAR								'%'
#define TAG_ARTIST_CHAR					'1'
#define TAG_TITLE_CHAR					'2'
#define TAG_ARTIST_TITLE_CHAR		'3'
#define TAG_SONG_INDEX_CHAR			'4'
#define TAG_PLAY_START					'['
#define TAG_PLAY_END						']'

// User defined messages which indicates that the nickname should be changed
#define WM_UPDATENICK						WM_APP + 10

// Conversion to seconds helpers
#define NANO_TO_SECOND					10000000
#define MILLI_TO_SECOND					1000

// Some max. and min. values
#define MAX_ENABLED_LENGTH			1
#define MAX_MASK_LENGTH					80
#define MAX_REFRESH_LENGTH			4
#define MAX_NOTIFY_LENGTH				1
#define MAX_INI_LENGTH					MAX_PATH
#define MAX_RANGE								300
#define MIN_RANGE								1

// Default values
#define DEF_ENABLED							TRUE
#define DEF_MASK								""
#define DEF_REFRESH_RATE				10
#define DEF_NOTIFY							FALSE
#define DEF_PLUGIN_DIR					"c:\\"

// Toast settings
#define TOAST_MESSAGE						"Changing nickname..."
#define TOAST_TITLE							"MPWinamp plugin."
#define TOAST_PROGRAM						NULL
#define TOAST_PLAY_SOUND				false

// Windows NT version
#define _WIN32_WINNT						0x0400

// Name of the timer
#define TIMER_NAME							"MPWinamp Timer"

// The widths of the two columns in the help listviews
#define FIRST_COL_WIDTH					120
#define SECOND_COL_WIDTH				220

// Commands column- and row lengths for the help listviews in which 
// the tags and commands are displayed
#define CMDS_HELP_COL_COUNT			2
#define CMDS_HELP_ROW_COUNT			21
#define TAGS_HELP_COL_COUNT			2
#define TAGS_HELP_ROW_COUNT			4

// Text of the columns
static const char *MPWINAMP_TAGS_COLS[TAGS_HELP_COL_COUNT] = { "Tag", "Description" };
static const char *MPWINAMP_CMDS_COLS[CMDS_HELP_COL_COUNT] = { "Command", "Description" };

// Column widths for the two listboxes
static const int MP_WINAMP_TAG_COL_WIDTHS[TAGS_HELP_COL_COUNT] = { FIRST_COL_WIDTH, SECOND_COL_WIDTH };
static const int MP_WINAMP_CMD_COL_WIDTHS[CMDS_HELP_COL_COUNT] = { FIRST_COL_WIDTH, SECOND_COL_WIDTH };

// A list of commands with their descriptions
static const char *MPWINAMP_CMDS[CMDS_HELP_ROW_COUNT][CMDS_HELP_COL_COUNT] = { 
										{ "/xwinampnick" , "Update the nickname." },
										{ "/xwinampnick on", "Enable the updating of the nickname." },
										{ "/xwinampnick off", "Disable the updating of the nickname." },
										{ "/xwinampnick enable", "Enable the updating of the nickname." },
										{ "/xwinampnick disable", "Disable the updating of the nickname." },
										{ "/xwinampnick config", "Show the configuration window." },
										{ "/xwinampmask %1", "Change the nickname mask to \"%1\"." },
										{ "/xwinampnext", "Play the next song." },
										{ "/xwinampprev", "Play the previous song." },
										{ "/xwinampplay", "Play the current song." },
										{ "/xwinamppause", "Pause the current song." },
										{ "/xwinampstop", "Stop the current song." },
										{ "/xwinamprepeat", "Toggle repeat on/off." },
										{ "/xwinampshuffle", "Toggle shuffle on/off." },
										{ "/xwinampontop", "Toggle always on-top on/off." },
										{ "/xwinampclose", "Close Winamp." },
										{ "/xwinampopenfile", "Show the open file dialog." },
										{ "/xwinampopenurl", "Show the open URL dialog." },
										{ "/xwinampopenjtf", "Show the jump-to-file dialog." },
										{ "/xwinampopenjtt" , "Show the jump-to-time dialog." },
										{ "/xwinampopenfileinfo", "Show the file info dialog." }
									 };

// A list of tags with their descriptions
static const char *MPWINAMP_TAGS[TAGS_HELP_ROW_COUNT][TAGS_HELP_COL_COUNT] = { 
										{ "(!XTITLE)" , "Title of the current song in Winamp." },
										{ "(!XARTIST)", "Artist of the current song in Winamp." },
										{ "(!XARTISTTITLE)", "Arist - title of the current song in Winamp." },
										{ "(!XSONGINDEX)", "Song index of the current song in Winamp." }
									 };

#include <windows.h>
#include "MPPluginHeader.h"
#include "Winamp.h"
#include "Messenger.h"
#include <stdio.h>
#include <commctrl.h>

typedef void (*UpdateNicknamePointer)( void );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Called when the timer is signaled.											//
//																																	//
//////////////////////////////////////////////////////////////////////
VOID CALLBACK RefreshNickname( LPVOID lpArg, DWORD timerLowVal, DWORD timerHighVal );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Intialize the configure dialog.													//
//																																	//
//////////////////////////////////////////////////////////////////////
void InitDialog( HWND hDlg );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Intialize the help dialog.													//
//																																	//
//////////////////////////////////////////////////////////////////////
void InitHelpDialog( HWND hDlg );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Read the plugin settings from the plugin's ini-file.		//
//																																	//
//////////////////////////////////////////////////////////////////////
void ReadSettings();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Save the plugin settings to the plugin's ini-file.			//
//																																	//
//////////////////////////////////////////////////////////////////////
void SaveSettings();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Update the dialog variables to their latest status.			//
//																																	//
//////////////////////////////////////////////////////////////////////
void UpdateValues();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Callback function for the configure dialog's messages.	//
//																																	//
//////////////////////////////////////////////////////////////////////
LRESULT CALLBACK ConfigureDialogProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Callback function for the help dialog's messages.	//
//																																	//
//////////////////////////////////////////////////////////////////////
LRESULT CALLBACK HelpDialogProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Gets the text from a window in a character array.				//
//																																	//
//////////////////////////////////////////////////////////////////////
char * GetDialogText( HWND hwnd );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Updates the user's nickname using the current settings.	//
//																																	//
//////////////////////////////////////////////////////////////////////
void UpdateNickname();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Handles checkbox messages.															//
//																																	//
//////////////////////////////////////////////////////////////////////
void CheckboxHandler( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Enables or disables all input controls on the dialog.		//
//																																	//
//////////////////////////////////////////////////////////////////////
void EnableControls( const BOOL enabled );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Parses the nickname by using the specified mask.				//
//																																	//
//////////////////////////////////////////////////////////////////////
char * ParseNickname( const char *mask );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Thread in which the timer is created and the regular		//
//					updating of the nickname occurs.												//
//																																	//
//////////////////////////////////////////////////////////////////////
DWORD WINAPI TimerThread( LPVOID lpParameter );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Initializes the timer which refreshes the nickname.			//
//																																	//
//////////////////////////////////////////////////////////////////////
bool InitTimer();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Sets the interval of the timer used.										//
//																																	//
//////////////////////////////////////////////////////////////////////
bool SetTimerInterval( const int seconds, const int delaySecs = 0 );

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Initialize the values in the help dialog's commands			//
//          listbox.																								//
//																																	//
//////////////////////////////////////////////////////////////////////
bool InitCommandsList();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Initialize the values in the help tag's commands				//
//          listbox.																								//
//																																	//
//////////////////////////////////////////////////////////////////////
bool InitTagsList();

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Gets the plugin's INI file.															//
//																																	//
//////////////////////////////////////////////////////////////////////
//void GetPluginIniFile();

LRESULT CALLBACK OnConfOk( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

HANDLE hInstance = NULL;
HANDLE hTimer = NULL;
HANDLE hThread = NULL;

// Handles to the dialog controls
HWND hMain = NULL;
HWND hDialog = NULL;
HWND hHelpDialog = NULL;
HWND hEnable = NULL;
HWND hEdit = NULL;
HWND hUpDown = NULL;
HWND hNotify = NULL;
HWND hCommands = NULL;
HWND hTags = NULL;
HWND hConfOk = NULL;
HWND hHelpOk = NULL;

// Variables which will hold the contents of the INI file
char iniFile[MAX_INI_LENGTH + 1];
char mask[MAX_MASK_LENGTH + 1];
int refreshRate = DEF_REFRESH_RATE;
BOOL enabled = DEF_ENABLED;
BOOL notify = DEF_NOTIFY;

// Pointer to the Messenger object
Messenger *messenger = NULL;

// Handle to the Winamp object
Winamp *winamp = NULL;

// Initially no commands and tags have been added
bool commandsAdded = false;
bool tagsAdded = false;