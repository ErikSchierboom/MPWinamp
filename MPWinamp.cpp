//////////////////////////////////////////////////////////////////////
//																																	//
// Project: Messenger Plus! Winamp Plugin.													//
// Author: Erik Schierboom																					//
// Last Update: 2004/10/19																					//
//																																	//
//////////////////////////////////////////////////////////////////////

#include "MPWinamp.h"
#include "Utils.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: DLL Entry Point																					//
//																																	//
//////////////////////////////////////////////////////////////////////
BOOL APIENTRY DllMain(HANDLE hModule, DWORD nReason, void* pReserved)
{
	hInstance = hModule;
  	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Initialization function																	//
//																																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL Initialize(/*[in]*/ DWORD nVersion,
								/*[in]*/ const char* sUserEmail,
								/*[in]*/ IDispatch* iMessengerObj)
{
#ifdef _DEBUG
	DebugBreak();
#endif

	// Get the plugin's INI file filename
	//GetPluginIniFile();

	// Get the one-and-only Winamp class instance
	winamp = Winamp::GetInstance();

	// As mask is an array, we cannot perform the initialization in the header
	strcpy( mask, DEF_MASK );

	// Start the timer thread
	hThread = CreateThread( NULL, 0, TimerThread, NULL, 0, NULL );

	// Create the dialogs
	hDialog = CreateDialog( (HINSTANCE)hInstance, (LPCSTR)IDD_DLG_CONFIG, GetActiveWindow(), 
													(DLGPROC)ConfigureDialogProc );
	hHelpDialog = CreateDialog( (HINSTANCE)hInstance, (LPCSTR)IDD_DLG_HELP, GetActiveWindow(), 
								     					(DLGPROC)HelpDialogProc );

	// Create a new messenger object
	messenger = new Messenger( iMessengerObj );

	return TRUE;
}


//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Uninitialization function																//
//																																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_VOID Uninitialize()
{
	// Cancel the waitable timer
	if( hTimer != NULL )
		CancelWaitableTimer( hTimer );

	if( hThread != NULL )
		TerminateThread( hThread, 0 );

	SAFE_CLOSE_HANDLE( hTimer );
	SAFE_CLOSE_HANDLE( hThread );
	SAFE_CLOSE_HANDLE( hEnable );
	SAFE_CLOSE_HANDLE( hEdit );
	SAFE_CLOSE_HANDLE( hUpDown );
	SAFE_CLOSE_HANDLE( hNotify );
	SAFE_CLOSE_HANDLE( hCommands );
	SAFE_CLOSE_HANDLE( hTags );
	SAFE_CLOSE_HANDLE( hConfOk );
	SAFE_CLOSE_HANDLE( hHelpOk );
	
	SAFE_DELETE( winamp );
	SAFE_DELETE( messenger );

	DestroyWindow( hHelpDialog );
	DestroyWindow( hDialog );
}


//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Configuration/Information function											//
//																																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_VOID Configure()
{
	// First read the settings and then use those settings to initialize the config dialog
	ReadSettings();
	InitDialog( hDialog );

	// Show the configure dialog
	ShowWindow( hDialog, SW_SHOW );
}


//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Inform the users about the features of the plugin				//
//																																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL PublishInfo(/*[out]*/ char *sPluginName,
								 /*[out]*/ PLUGIN_PUBLISH_LIST* aCommands,
								 /*[out]*/ PLUGIN_PUBLISH_LIST* aTags)
{
	//Copy the name of the plugin
	strcpy( sPluginName, MPWINAMP_PLUGIN_TITLE );
	
	//Set the number of commands
	aCommands->nCount = 16;

	strcpy( aCommands->sName[0],  MP_WINAMP_CMD_CHANGE_NICK_NAME );
	strcpy( aCommands->sValue[0], MP_WINAMP_CMD_CHANGE_NICK_VALUE );
	strcpy( aCommands->sHelp[0],  MP_WINAMP_CMD_CHANGE_NICK_HELP );

	strcpy( aCommands->sName[1],  MP_WINAMP_CMD_NEXT_NAME );
	strcpy( aCommands->sValue[1], MP_WINAMP_CMD_NEXT_VALUE );
	strcpy( aCommands->sHelp[1],  MP_WINAMP_CMD_NEXT_HELP );

	strcpy( aCommands->sName[2],  MP_WINAMP_CMD_PREV_NAME );
	strcpy( aCommands->sValue[2], MP_WINAMP_CMD_PREV_VALUE );
	strcpy( aCommands->sHelp[2],  MP_WINAMP_CMD_PREV_HELP );

	strcpy( aCommands->sName[3],  MP_WINAMP_CMD_PLAY_NAME );
	strcpy( aCommands->sValue[3], MP_WINAMP_CMD_PLAY_VALUE );
	strcpy( aCommands->sHelp[3],  MP_WINAMP_CMD_PLAY_HELP );

	strcpy( aCommands->sName[4],  MP_WINAMP_CMD_PAUSE_NAME );
	strcpy( aCommands->sValue[4], MP_WINAMP_CMD_PAUSE_VALUE );
	strcpy( aCommands->sHelp[4],  MP_WINAMP_CMD_PAUSE_HELP );

	strcpy( aCommands->sName[5],  MP_WINAMP_CMD_STOP_NAME );
	strcpy( aCommands->sValue[5], MP_WINAMP_CMD_STOP_VALUE );
	strcpy( aCommands->sHelp[5],  MP_WINAMP_CMD_STOP_HELP );

	strcpy( aCommands->sName[6],  MP_WINAMP_CMD_REPEAT_NAME );
	strcpy( aCommands->sValue[6], MP_WINAMP_CMD_REPEAT_VALUE );
	strcpy( aCommands->sHelp[6],  MP_WINAMP_CMD_REPEAT_HELP );

	strcpy( aCommands->sName[7],  MP_WINAMP_CMD_SHUFFLE_NAME );
	strcpy( aCommands->sValue[7], MP_WINAMP_CMD_SHUFFLE_VALUE );
	strcpy( aCommands->sHelp[7],  MP_WINAMP_CMD_SHUFFLE_HELP );

	strcpy( aCommands->sName[8],  MP_WINAMP_CMD_CLOSE_NAME );
	strcpy( aCommands->sValue[8], MP_WINAMP_CMD_CLOSE_VALUE );
	strcpy( aCommands->sHelp[8],  MP_WINAMP_CMD_CLOSE_HELP );

	strcpy( aCommands->sName[9],  MP_WINAMP_CMD_ALWAYS_ON_TOP_NAME );
	strcpy( aCommands->sValue[9], MP_WINAMP_CMD_ALWAYS_ON_TOP_VALUE );
	strcpy( aCommands->sHelp[9],  MP_WINAMP_CMD_ALWAYS_ON_TOP_HELP );

	strcpy( aCommands->sName[10],  MP_WINAMP_CMD_OPEN_FILE_NAME );
	strcpy( aCommands->sValue[10], MP_WINAMP_CMD_OPEN_FILE_VALUE );
	strcpy( aCommands->sHelp[10],  MP_WINAMP_CMD_OPEN_FILE_HELP );

	strcpy( aCommands->sName[11],  MP_WINAMP_CMD_OPEN_URL_NAME );
	strcpy( aCommands->sValue[11], MP_WINAMP_CMD_OPEN_URL_VALUE );
	strcpy( aCommands->sHelp[11],  MP_WINAMP_CMD_OPEN_URL_HELP );

	strcpy( aCommands->sName[12],  MP_WINAMP_CMD_OPEN_JTF_NAME );
	strcpy( aCommands->sValue[12], MP_WINAMP_CMD_OPEN_JTF_VALUE );
	strcpy( aCommands->sHelp[12],  MP_WINAMP_CMD_OPEN_JTF_HELP );

	strcpy( aCommands->sName[13],  MP_WINAMP_CMD_OPEN_JTT_NAME );
	strcpy( aCommands->sValue[13], MP_WINAMP_CMD_OPEN_JTT_VALUE );
	strcpy( aCommands->sHelp[13],  MP_WINAMP_CMD_OPEN_JTT_HELP );

	strcpy( aCommands->sName[14],  MP_WINAMP_CMD_OPEN_FILE_INFO_NAME );
	strcpy( aCommands->sValue[14], MP_WINAMP_CMD_OPEN_FILE_INFO_VALUE );
	strcpy( aCommands->sHelp[14],  MP_WINAMP_CMD_OPEN_FILE_INFO_HELP );

	strcpy( aCommands->sName[15],  MP_WINAMP_CMD_CHANGE_MASK_NAME );
	strcpy( aCommands->sValue[15], MP_WINAMP_CMD_CHANGE_MASK_VALUE );
	strcpy( aCommands->sHelp[15],  MP_WINAMP_CMD_CHANGE_MASK_HELP );

	//Set the number of tags
	aTags->nCount = 4;

	strcpy( aTags->sName[0],  MP_WINAMP_TAG_TITLE_NAME );
	strcpy( aTags->sValue[0], MP_WINAMP_TAG_TITLE_VALUE );	

	strcpy( aTags->sName[1],  MP_WINAMP_TAG_ARTIST_NAME );
	strcpy( aTags->sValue[1], MP_WINAMP_TAG_ARTIST_VALUE );

	strcpy( aTags->sName[2],  MP_WINAMP_TAG_ARTISTTITLE_NAME );
	strcpy( aTags->sValue[2], MP_WINAMP_TAG_ARTISTTITLE_VALUE );

	strcpy( aTags->sName[3],  MP_WINAMP_TAG_SONGINDEX_NAME );
	strcpy( aTags->sValue[3], MP_WINAMP_TAG_SONGINDEX_VALUE );

	return TRUE;
}


//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Provide new commands in Messenger Plus!									//
//																																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL ParseCommand(/*[in]*/  const char* sCommand,
								  /*[in]*/  const char* sCommandArg,
								  /*[in]*/  PLUGIN_PARAM* pParam,
								  /*[out]*/ char* sResult)
{		
	if( stricmp( sCommand, MP_WINAMP_CMD_CHANGE_NICK_PARSED ) == 0 )
	{		
		// Trim the command argument
		char *trimmedCommandArg = Trim( sCommandArg );

		// Check if we should enable the plugin 
		if( stricmp( trimmedCommandArg, MP_WINAMP_ARG_ENABLE ) == 0 ||
			  stricmp( trimmedCommandArg, MP_WINAMP_ARG_ENABLE_ALT ) == 0 )
		{
			enabled = true;
			SaveSettings();
		}
		// Check if we should disable the plugin
		else if( stricmp( trimmedCommandArg, MP_WINAMP_ARG_DISABLE ) == 0 || 
			       stricmp( trimmedCommandArg, MP_WINAMP_ARG_DISABLE_ALT ) == 0 )
		{
			enabled = false;		
			SaveSettings();
		}
		// Check if we should show the config dialog
		else if( stricmp( trimmedCommandArg, MP_WINAMP_ARG_CONFIG ) == 0 )
		{
			Configure();
		}
		else
		{
			// Update the nickname
			UpdateNickname();
		}

		SAFE_ARRAY_DELETE( trimmedCommandArg );

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_CHANGE_MASK_PARSED ) == 0 )
	{
		// Trim the command argument
		char *trimmedCommandArg = Trim( sCommandArg );

		// Get the length of the trimmed string
		int length = strlen( trimmedCommandArg );

		if( length > 0 )
		{
			// Set the mask to the supplied argument
			strcpy( mask, trimmedCommandArg );
			SaveSettings();
		}

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_NEXT_PARSED ) == 0 )
	{
		// Only call the next track function if the winamp object is allocated
		if( winamp != NULL )
			winamp->NextTrack();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_PREV_PARSED ) == 0 )
	{
		// Only call the previous track function if the winamp object is allocated
		if( winamp != NULL )
			winamp->PreviousTrack();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_PLAY_PARSED ) == 0 )
	{
		// Only call the play function if the winamp object is allocated
		if( winamp != NULL )
			winamp->Play();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_PAUSE_PARSED ) == 0 )
	{
		// Only call the pause function if the winamp object is allocated
		if( winamp != NULL )
			winamp->Pause();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_STOP_PARSED ) == 0 )
	{
		// Only call the stop function if the winamp object is allocated
		if( winamp != NULL )
			winamp->Stop();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_REPEAT_PARSED ) == 0 )
	{
		// Only call the toggle repeat function if the winamp object is allocated
		if( winamp != NULL )
			winamp->ToggleRepeat();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_SHUFFLE_PARSED ) == 0 )
	{
		// Only call the toggle shuffle function if the winamp object is allocated
		if( winamp != NULL )
			winamp->ToggleShuffle();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_CLOSE_PARSED ) == 0 )
	{
		// Only call the toggle shuffle function if the winamp object is allocated
		if( winamp != NULL )
			winamp->Close();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_ALWAYS_ON_TOP_PARSED ) == 0 )
	{
		// Only call the toggle always on top function if the winamp object is allocated
		if( winamp != NULL )
			winamp->ToggleAlwaysOnTop();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_OPEN_FILE_PARSED ) == 0 )
	{
		// Only call the open file function if the winamp object is allocated
		if( winamp != NULL )
			winamp->OpenFile();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_OPEN_URL_PARSED ) == 0 )
	{
		// Only call the open URL function if the winamp object is allocated
		if( winamp != NULL )
			winamp->OpenUrl();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_OPEN_JTF_PARSED ) == 0 )
	{
		// Only call the open jump to file function if the winamp object is allocated
		if( winamp != NULL )
			winamp->OpenJumpToFile();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_OPEN_JTT_PARSED ) == 0 )
	{
		// Only call the open jump to time function if the winamp object is allocated
		if( winamp != NULL )
			winamp->OpenJumpToTime();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}
	else if( stricmp( sCommand, MP_WINAMP_CMD_OPEN_FILE_INFO_PARSED ) == 0 )
	{
		// Only call the open file function if the winamp object is allocated
		if( winamp != NULL )
			winamp->OpenFileInfo();

		// Make sure no data is sent over the network
		strcpy( sResult, "" );
				
		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Provide new tags in Messenger Plus!											//
//																																	//
//////////////////////////////////////////////////////////////////////
MPPLUGIN_RETURN_BOOL ParseTag(/*[in]*/  const char* sTag,
															/*[in]*/  PLUGIN_PARAM* pParam,
															/*[out]*/ char* sResult)
{
	// Check if we have received the title tag
	if( stricmp( sTag, MP_WINAMP_TAG_TITLE_VALUE ) == 0 )
	{
		// Get the playing title
		const char *title = winamp->GetPlayingTitle( true );
		
		// Copy the title into the result
		if( title != NULL )
			strcpy( sResult, title );

		return TRUE;
	}
	else if( stricmp( sTag, MP_WINAMP_TAG_ARTIST_VALUE ) == 0 )
	{
		// Get the playing artist
		const char *artist = winamp->GetPlayingArtist( true );
	
		// Copy the artist into the result
		if( artist != NULL )
			strcpy( sResult, artist );

		return TRUE;
	}
	else if( stricmp( sTag, MP_WINAMP_TAG_ARTISTTITLE_VALUE ) == 0 )
	{
		// Get the playing artist-title
		const char *artistTitle = winamp->GetPlayingArtistTitle( true );
		
		// Copy the artist-title into the result
		if( artistTitle != NULL )
			strcpy( sResult, artistTitle );

		return TRUE;
	}
	else if( stricmp( sTag, MP_WINAMP_TAG_SONGINDEX_VALUE ) == 0 )
	{
		// Get the playing song index
		const char *songIndex = winamp->GetPlayingIndexStr( true );
		
		// Copy the song index into the result
		if( songIndex != NULL )
			strcpy( sResult, songIndex );

		return TRUE;
	}

	// We have not handled the tag
	return FALSE;
}


//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Called when the timer is signaled.											//
//																																	//
//////////////////////////////////////////////////////////////////////
VOID CALLBACK RefreshNickname( LPVOID lpArg, DWORD timerLowVal, DWORD timerHighVal )
{
	// Post a message to the dialog thread that the nickname needs to be updated
	PostMessage( hDialog, WM_UPDATENICK, 0, 0 );	
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Intialize the configure dialog.													//
//																																	//
//////////////////////////////////////////////////////////////////////
void InitDialog( HWND hDlg )
{
	// Get handles to the dialog items
	GET_DIALOG_ITEM( hEnable, hDlg, IDC_CHK_ENABLED );
	GET_DIALOG_ITEM( hEdit, hDlg, IDC_EDT_MASK );
	GET_DIALOG_ITEM( hUpDown, hDlg, IDC_SPIN );
	GET_DIALOG_ITEM( hNotify, hDlg, IDC_CHK_NOTIFY );
	GET_DIALOG_ITEM( hConfOk, hDlg, ID_CONF_OK );
	
	// Read the settings
	ReadSettings();
	
	// Configure some controls on the dialog
	SendMessage( hEdit, EM_LIMITTEXT, MAX_MASK_LENGTH, 0 );
	SendMessage( hUpDown, UDM_SETRANGE, 0, (LPARAM)MAKELONG( MAX_RANGE, MIN_RANGE ) );
	SendMessage( hUpDown, UDM_SETPOS, 0,  (LPARAM)MAKELONG( refreshRate, 0 ) );
	SendMessage( hEnable, BM_SETCHECK, ( enabled ) ? BST_CHECKED : BST_UNCHECKED, 0 );
	SendMessage( hNotify, BM_SETCHECK, ( notify ) ? BST_CHECKED : BST_UNCHECKED, 0 );
	SetWindowText( hEdit, mask );
	
	// Set the focus to the editbox      
  SetFocus( hEdit );
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Intialize the help dialog.															//
//																																	//
//////////////////////////////////////////////////////////////////////
void InitHelpDialog( HWND hDlg )
{
	// Get handles to the dialog items
	GET_DIALOG_ITEM( hCommands, hDlg, IDC_LST_COMMANDS );
	GET_DIALOG_ITEM( hTags, hDlg, IDC_LST_TAGS );
	GET_DIALOG_ITEM( hHelpOk, hDlg, ID_HELP_OK );
  
	// Add the columns if it has not already been done
	if( !commandsAdded )
		commandsAdded = InitCommandsList();

	// Add the tags if it has not already been done
	if( !tagsAdded )
		tagsAdded = InitTagsList();
	
	// Set the focus to the editbox      
  SetFocus( hCommands );
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Read the plugin settings from the plugin's ini-file.		//
//																																	//
//////////////////////////////////////////////////////////////////////
void ReadSettings()
{
	HKEY regKey = NULL;

	// Try to open the msg plus registry key in which this user's configs are placed
	if( RegOpenKeyEx( REG_CONF_ROOT_KEY, REG_CONF_KEY_NAME, 0, KEY_QUERY_VALUE, &regKey ) == ERROR_SUCCESS )
	{
		DWORD dataLength = MAX_INI_LENGTH;
		
		// Get the mask value from the registry, if it could not be retrieved set the default value
		if( RegQueryValueEx( regKey, REG_CONF_MASK_VALUE, NULL, NULL, (LPBYTE)mask, &dataLength ) != ERROR_SUCCESS )
			strcpy( mask, INI_MASK_DEF_VAL );

		// Get the notify value from the registry, if it could not be retrieved set the default value
		if( RegQueryValueEx( regKey, REG_CONF_NOTIFY_VALUE, NULL, NULL, (LPBYTE)&notify, &dataLength ) != ERROR_SUCCESS )
			notify = INI_NOTIFY_DEF_VAL;

		// Get the enabled value from the registry, if it could not be retrieved set the default value
		if( RegQueryValueEx( regKey, REG_CONF_ENABLED_VALUE, NULL, NULL, (LPBYTE)&enabled, &dataLength ) != ERROR_SUCCESS )
			enabled = INI_ENABLED_DEF_VAL;

		// Get the refresh rate from the registry, if it could not be retrieved set the default value
		if( RegQueryValueEx( regKey, REG_CONF_REFRESH_VALUE, NULL, NULL, (LPBYTE)&refreshRate, &dataLength ) != ERROR_SUCCESS )
			refreshRate = INI_REFRESH_DEF_VAL;

		// Close the registry key
		RegCloseKey( regKey );
	}
	else	
	{
		// Set the variables to their default settings
		strcpy( mask, INI_MASK_DEF_VAL );
		notify = INI_NOTIFY_DEF_VAL;
		enabled = INI_ENABLED_DEF_VAL;
		refreshRate = INI_REFRESH_DEF_VAL;
	}

	/*
	// Get the values from the ini-file
	GetPrivateProfileString( INI_APP_NAME, INI_MASK_KEY_NAME, INI_MASK_DEF_VAL, mask, MAX_MASK_LENGTH, iniFile );
	refreshRate = GetPrivateProfileInt( INI_APP_NAME, INI_REFRESH_KEY_NAME, INI_REFRESH_DEF_VAL, iniFile );
	enabled = GetPrivateProfileInt( INI_APP_NAME, INI_ENABLED_KEY_NAME, INI_ENABLED_DEF_VAL, iniFile );
	notify = GetPrivateProfileInt( INI_APP_NAME, INI_NOTIFY_KEY_NAME, INI_NOTIFY_DEF_VAL, iniFile );
	*/
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Save the plugin settings to the plugin's ini-file.			//
//																																	//
//////////////////////////////////////////////////////////////////////
void SaveSettings()
{	
	HKEY regKey = NULL;

	// Try to open the plugin registry key
	if( RegCreateKeyEx( REG_CONF_ROOT_KEY, REG_CONF_KEY_NAME, 0, NULL, 
											REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &regKey, NULL ) != ERROR_SUCCESS )
		return;

	// Store the settings in the registry
	RegSetValueEx( regKey, REG_CONF_MASK_VALUE, 0, REG_SZ, (BYTE *)&mask[0], strlen( mask ) + 1 );
	RegSetValueEx( regKey, REG_CONF_NOTIFY_VALUE, 0, REG_DWORD, (BYTE *)&notify, sizeof( notify ) );
	RegSetValueEx( regKey, REG_CONF_ENABLED_VALUE, 0, REG_DWORD, (BYTE *)&enabled, sizeof( enabled ) );
	RegSetValueEx( regKey, REG_CONF_REFRESH_VALUE, 0, REG_DWORD, (BYTE *)&refreshRate, sizeof( refreshRate ) );

	RegCloseKey( regKey );

	/*
	char enabledStr[MAX_ENABLED_LENGTH + 1];
	char refreshStr[MAX_REFRESH_LENGTH + 1];
	char notifyStr[MAX_NOTIFY_LENGTH + 1];

	// Convert the integer values to char arrays, otherwise we can't write them to the INI file
	_itoa( enabled, enabledStr, 2 );
	_itoa( refreshRate, refreshStr, 10 );
	_itoa( notify, notifyStr, 2 );

	// Flush the cache
	WritePrivateProfileString( NULL, NULL, NULL, iniFile ); 
	
	// Save the values to the ini-file
	WritePrivateProfileString( INI_APP_NAME, INI_ENABLED_KEY_NAME, enabledStr, iniFile );
	WritePrivateProfileString( INI_APP_NAME, INI_MASK_KEY_NAME, mask, iniFile );
	WritePrivateProfileString( INI_APP_NAME, INI_REFRESH_KEY_NAME, refreshStr, iniFile );
	WritePrivateProfileString( INI_APP_NAME, INI_NOTIFY_KEY_NAME, notifyStr, iniFile );
	*/
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Update the dialog variables to their latest status.			//
//																																	//
//////////////////////////////////////////////////////////////////////
void UpdateValues()
{		
	// Retrieve the mask text from the editbox
	strcpy( mask, GetDialogText( hEdit ) );
	
	// Get the position of the updown control
	LRESULT upDownPos = SendMessage( hUpDown, UDM_GETPOS, 0, 0 );

	// Check if the position was successfully retrieved, if so get the position and store it
	if( HIWORD( upDownPos ) == 0 )
		refreshRate = (int)LOWORD( upDownPos );

	// Get the enabled values from the checkboxex
	enabled = ( SendMessage( hEnable, BM_GETCHECK, 0, 0 ) == BST_CHECKED );
	notify = ( SendMessage( hNotify, BM_GETCHECK, 0, 0 ) == BST_CHECKED );
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Callback function for the configure dialog's messages.	//
//																																	//
//////////////////////////////////////////////////////////////////////
LRESULT CALLBACK ConfigureDialogProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_UPDATENICK:
			// Update the nickname
			UpdateNickname();
			return TRUE;

		case WM_INITDIALOG:
			// Call the InitDialog function which will do what it's name suggests
			InitDialog( hDlg );
			return FALSE;

		case WM_HELP:
			ShowWindow( hHelpDialog, SW_SHOW );
			return TRUE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					// Update the values to the latest data in the dialog
					UpdateValues();

					// Save the settings
					SaveSettings();
										
					// Hide the window
					ShowWindow( hDialog, SW_HIDE );
					return FALSE;
				case IDCANCEL:
					// Hide the window
					ShowWindow( hDialog, SW_HIDE );
					return FALSE;
				case IDC_CHK_ENABLED:
					// Re-route the message to a specific handler
					CheckboxHandler( hDlg, message, wParam, lParam );
					return TRUE;
			}
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Callback function for the help dialog's messages.	//
//																																	//
//////////////////////////////////////////////////////////////////////
LRESULT CALLBACK HelpDialogProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_INITDIALOG:
			// Call the InitDialog function which will do what it's name suggests
			InitHelpDialog( hDlg );
			return FALSE;

		case WM_CLOSE:
			ShowWindow( hHelpDialog, SW_HIDE );
			return 0;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:															
					// Hide the window
					ShowWindow( hHelpDialog, SW_HIDE );
					return FALSE;				
			}
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Gets the text from a window in a character array.				//
//																																	//
//////////////////////////////////////////////////////////////////////
char * GetDialogText( HWND hwnd )
{
	// Get the length of the text in the window
	int textLength = GetWindowTextLength( hwnd );

	if( textLength == 0 )
		return "";

	char *windowText = new char[textLength + 1];

	// Get the text of the window
	int charsRead = GetWindowText( hwnd, windowText, textLength + 1 );

	if( charsRead == 0 )
	{
		SAFE_ARRAY_DELETE( windowText );
		return "";
	}

	// Make sure the char array is null-terminated
	windowText[textLength] = '\0';

	return windowText;
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Updates the user's nickname using the current settings.	//
//																																	//
//////////////////////////////////////////////////////////////////////
void UpdateNickname()
{
	// Only update the nickname if the plugin is enabled
	if( enabled )
	{
		// Get the latest settings, more specifically the mask used
		ReadSettings();

		// Get the current nickname used by Messenger
		const char *currentNick = ( messenger != NULL ) ? messenger->GetNickname() : NULL;

		// Set the new nickname based on the fact if there is a mask
		const char *newNickname = ParseNickname( mask );

		// Update the user's nickname if required
		if( currentNick != NULL && newNickname != NULL && stricmp( currentNick, newNickname ) != 0 )
		{
			SetNewName( newNickname );

			// Check if we should notify the user that we have changed the nickname
			if( notify )
				DisplayToast( TOAST_MESSAGE, TOAST_TITLE, TOAST_PROGRAM, TOAST_PLAY_SOUND );
		}
				
		SAFE_ARRAY_DELETE( newNickname );
	}
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Handles checkbox messages.															//
//																																	//
//////////////////////////////////////////////////////////////////////
void CheckboxHandler( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( HIWORD( wParam ) )
	{
		case BN_CLICKED:
			// Check if the checkbox is checked
			BOOL checked = ( SendMessage( (HWND)lParam, BM_GETCHECK, 0, 0 ) == BST_CHECKED );
		
			EnableControls( checked );
			break;
	}
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Enables or disables all input controls on the dialog.		//
//																																	//
//////////////////////////////////////////////////////////////////////
void EnableControls( const BOOL enabled )
{
	EnableWindow( hEdit, enabled );
	EnableWindow( hUpDown, enabled );	
	EnableWindow( hNotify, enabled );
}

//////////////////////////////////////////////////////////////////////
//																																	//
// Purpose: Parses the nickname by using the specified mask.				//
//																																	//
//////////////////////////////////////////////////////////////////////
char * ParseNickname( const char *mask )
{
	// Return NULl if the mask could not be found
	ON_NULL_RETURN_VALUE( mask, NULL );

	// Get the mask's length
	int maskLength = strlen( mask );
	int startIndex = -1;
	int stopIndex = -1;

	// Return NULL if the mask has no length
	if( maskLength == 0 )
		return NULL;

	// Get the index of the first '%[' string
	for( int i = 0; i < maskLength - 1; ++i )
	{
		if( mask[i] == '%' && mask[i + 1] == '[' )
		{
			startIndex = i;
			break;
		}
	}

	// Get the index of the last '%[' string
	for( int i = maskLength - 1; i > 0; --i )
	{
		if( mask[i] == ']' && mask[i - 1] == '%' )
		{
			stopIndex = i - 1;
			break;
		}
	}

	// Check if winamp is not playing
	if( winamp == NULL || !winamp->IsPlaying() )
	{
		// Check if we actually need to take into account the start and stop index
		if( startIndex == -1 && stopIndex == -1 )
			return AllocAndCopy( mask );

		int pos = 0;

		// Calculate the new length of the string
		int newLength = maskLength - ( stopIndex - startIndex + 2);
		
		char *nickname = new char[newLength + 1];		

		// Copy the string up to the play start tag
		for( int i = 0; i < startIndex; ++i )
			nickname[pos++] = mask[i];

		// Copy the string from the play end tag
		for( int j = stopIndex + 2; j < maskLength; ++j )
			nickname[pos++] = mask[j];

		// Make sure the string is null-terminated
		nickname[newLength] = '\0';
	
		return nickname;
	}
	else
	{
		// Make sure the winamp data is updated
		winamp->Update();

		int artistCount = 0;
		int titleCount = 0;		
		int artistTitleCount = 0;
		int songIndexCount = 0;

		// Retrieve how many special tags can be found in the mask
		for( int i = 1; i < maskLength; ++i )
		{
			// Check if we have found the artist tag
			if( mask[i] == TAG_ARTIST_CHAR && mask[i - 1] == TAG_CHAR )
				++artistCount;
			// Check if we have found the title tag
			else if( mask[i] == TAG_TITLE_CHAR && mask[i - 1] == TAG_CHAR )
				++titleCount;
			// Check if we have found the artist0title tag
			else if( mask[i] == TAG_ARTIST_TITLE_CHAR && mask[i - 1] == TAG_CHAR )
				++artistTitleCount;
			// Check if we have found the song index tag
			else if( mask[i] == TAG_SONG_INDEX_CHAR && mask[i - 1] == TAG_CHAR )
				++songIndexCount;
		}
		
		// No tags need to be parsed
		if( titleCount == 0 && artistCount == 0 && artistTitleCount == 0 && songIndexCount == 0 )
			return AllocAndCopy( mask );
	
		char *artist = NULL;
		char *title = NULL;
		char *artistTitle = NULL;
		char *songIndex = NULL;

		// If necessary, retrieve the playing artist
		if( artistCount > 0 )
			artist = winamp->GetPlayingArtist();

		// If necessary, retrieve the playing title
		if( titleCount > 0 )
			title = winamp->GetPlayingTitle();

		// If necessary, retrieve the playing artist-title
		if( artistTitleCount > 0 )
			artistTitle = winamp->GetPlayingArtistTitle();

		// If necessary, retrieve the playing song index
		if( songIndexCount > 0 )
			songIndex = winamp->GetPlayingIndexStr();

		int artistLength = ( artist != NULL ) ? strlen( artist ) : 0;
		int titleLength = ( title != NULL ) ? strlen( title ) : 0;
		int artistTitleLength = ( artistTitle != NULL ) ? strlen( artistTitle ) : 0;
		int songIndexLength = ( songIndex != NULL ) ? strlen( songIndex ) : 0;

		// Calculate the new length of the nickname
		int winampTagsComp = ( titleCount + artistCount + artistTitleCount + songIndexCount ) * 2;
		int startEndTagsComp = ( startIndex != -1 && stopIndex != -1 && startIndex < stopIndex ) ? 4 : 0;
		int titleStringsLength = titleCount * titleLength;
		int artistStringsLength = artistCount * artistLength;
		int artistTitleStringLength = artistTitleCount * artistTitleLength;
		int songIndexStringLength = songIndexCount * songIndexLength;
		int newLength = maskLength - winampTagsComp + titleStringsLength + artistStringsLength + 
																 artistTitleStringLength + songIndexStringLength - startEndTagsComp;

		char *nickname = new char[newLength + 1];

		int pos = 0;

		for( int i = 0; i < maskLength -1 ; ++i )
		{
			// Check if we should replace an artist tag
			if( mask[i] == TAG_CHAR && mask[i + 1] == TAG_ARTIST_CHAR )
			{
				// Insert the artist into the nickname
				for( int j = 0; j < artistLength; ++j )
					nickname[pos + j] = artist[j];
				
				pos += artistLength;
				++i;
			}
			// Check if we should replace a title tag
			else if( mask[i] == TAG_CHAR && mask[i + 1] == TAG_TITLE_CHAR )
			{
				// Insert the title into the nickname
				for( int k = 0; k < titleLength; ++k )
					nickname[pos + k] = title[k];
				
				// Update the new position at which the nick
				pos += titleLength;
				++i;
			}
			// Check if we should replace a artist-title tag
			else if( mask[i] == TAG_CHAR && mask[i + 1] == TAG_ARTIST_TITLE_CHAR )
			{
				// Insert the title into the nickname
				for( int l = 0; l < artistTitleLength; ++l )
					nickname[pos + l] = artistTitle[l];
				
				// Update the new position at which the nick
				pos += artistTitleLength;
				++i;
			}
			// Check if we should replace a song index tag
			else if( mask[i] == TAG_CHAR && mask[i + 1] == TAG_SONG_INDEX_CHAR )
			{
				// Insert the title into the nickname
				for( int m = 0; m < songIndexLength; ++m )
					nickname[pos + m] = songIndex[m];
				
				// Update the new position at which the nick
				pos += songIndexLength;
				++i;
			}
			else if( i == startIndex || i == stopIndex )
			{
				++i;
			}
			else
			{
				// Just copy the character
				nickname[pos++] = mask[i];
			}
		}

		nickname[pos] = mask[maskLength -1];
		nickname[newLength] = '\0';

		return nickname;
	}
}

DWORD WINAPI TimerThread( LPVOID lpParameter )
{
	// Try to initialize the timer
	bool initialized = InitTimer();
		
	if( initialized )
	{
		// Keep on sleeping forever, but the thread IS ready to be interrupted by the timer
		while( true )
			SleepEx( INFINITE, TRUE );	
	}

	return (DWORD)initialized;
}

bool InitTimer()
{
	// Create a waitable synchronization timer
	hTimer = CreateWaitableTimer( NULL, FALSE, TIMER_NAME );

	ON_NULL_RETURN_VALUE( hTimer, false );

	return SetTimerInterval( refreshRate, refreshRate );
}

bool SetTimerInterval( const int seconds, const int delaySecs )
{
	LARGE_INTEGER startTime;

	// Calculate the 64-bit time value which is needed to store the relative start time in
	__int64 startTimeInt = -delaySecs * NANO_TO_SECOND;
	
		// Copy the relative time into a LARGE_INTEGER.
	startTime.LowPart  = (DWORD)( startTimeInt & 0xFFFFFFFF );
	startTime.HighPart = (LONG)( startTimeInt >> 32 );

	return( SetWaitableTimer( hTimer, &startTime, seconds * MILLI_TO_SECOND, RefreshNickname, NULL, FALSE ) == TRUE );
}

bool InitCommandsList()
{
	// Make sure we have a handle to the help dialog
	if( hCommands == NULL )
		return false;

	char szText[256];
  LVCOLUMN lvc;

	// Clear the structure
	memset( &lvc, '\0', sizeof( LVCOLUMN ) );

	// Initialize the LVCOLUMN structure. The mask specifies that the format, width, text, and
	// subitem members of the structure are valid. Also the item is aligned to the left.
  lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
	lvc.fmt = LVCFMT_LEFT;
	lvc.pszText = szText;	

	// Loop through all columns
	for( int i = 0; i < CMDS_HELP_COL_COUNT; ++i )
	{
		// Set the column's index, width and retrieve the correct column text
		lvc.iSubItem = i;		
		lvc.cx = MP_WINAMP_CMD_COL_WIDTHS[i];
		strcpy( szText, MPWINAMP_CMDS_COLS[i] );

		// Insert the column
		SendMessage( hCommands, LVM_INSERTCOLUMN, i, (LPARAM)&lvc );
	}

	LVITEM lvi;

	// Clear the structure
	memset( &lvi, '\0', sizeof( LPLVITEM ) );

	// Initialize the LVITEM structure. The mask specifies that the text and state members of the 
	// structure are valid.
	lvi.mask = LVIF_TEXT | LVIF_STATE;
	lvi.state = 0; 
	lvi.stateMask = 0;
	lvi.pszText = szText;
	
	// Loop through all help items rows
	for( int y = 0; y < CMDS_HELP_ROW_COUNT; ++y )
	{
		// Loop through this help items row's columns
		for( int x = 0; x < CMDS_HELP_COL_COUNT; ++x )
		{
			// Set the item index (row nr.), subitem index (column nr.) and insert the right text
			lvi.iItem = y;
			lvi.iSubItem = x;
			strcpy( szText, MPWINAMP_CMDS[y][x] );			

			// Insert the item
			SendMessage( hCommands, ( x > 0 ) ? LVM_SETITEM : LVM_INSERTITEM, 0, (LPARAM)&lvi );
		}
	}

	return true;
}

bool InitTagsList()
{
	// Make sure we have a handle to the help dialog
	if( hTags == NULL )
		return false;

	char szText[256];     // temporary buffer 
  LVCOLUMN lvc;

	// Clear the structure
	memset( &lvc, '\0', sizeof( LVCOLUMN ) );

	// Initialize the LVCOLUMN structure. The mask specifies that the format, width, text, and
	// subitem members of the structure are valid. Also the item is aligned to the left.
  lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
	lvc.fmt = LVCFMT_LEFT;
	lvc.pszText = szText;	

	for( int i = 0; i < TAGS_HELP_COL_COUNT; ++i )
	{
		lvc.iSubItem = i;		
		lvc.cx = MP_WINAMP_TAG_COL_WIDTHS[i];
		strcpy( szText, MPWINAMP_TAGS_COLS[i] );

		SendMessage( hTags, LVM_INSERTCOLUMN, i, (LPARAM)&lvc );
	}

	LVITEM lvi;

	// Clear the structure
	memset( &lvi, '\0', sizeof( LPLVITEM ) );

	lvi.mask = LVIF_TEXT | LVIF_STATE;
	lvi.state = 0; 
	lvi.stateMask = 0;
	
	for( int y = 0; y < TAGS_HELP_ROW_COUNT; ++y )
	{
		for( int x = 0; x < TAGS_HELP_COL_COUNT; ++x )
		{
			lvi.iItem = y;
			lvi.iSubItem = x;
			strcpy( szText, MPWINAMP_TAGS[y][x] );
			lvi.pszText = szText;

			SendMessage( hTags, ( x > 0 ) ? LVM_SETITEM : LVM_INSERTITEM, 0, (LPARAM)&lvi );
		}
	}

	return true;
}

/*
void GetPluginIniFile()
{
	HKEY regKey = NULL;
	
	// Try to open the msg plus registry key in which the plugin directory is specified
	if( RegOpenKeyEx( REG_DIR_ROOT_KEY, REG_DIR_KEY_NAME, 0, KEY_QUERY_VALUE, &regKey ) == ERROR_SUCCESS )
	{
		DWORD dataLength = MAX_INI_LENGTH;
		
		// Get the value of the plugin directory, if it has not succeeded use the default value
		if( RegQueryValueEx( regKey, REG_DIR_KEY_VALUE, NULL, NULL, (LPBYTE)iniFile, &dataLength ) == ERROR_SUCCESS )
		{
			// Make sure the directory is ended with a '\' character
			if( iniFile[dataLength - 2] != '\\' )
				strcat( iniFile, "\\" );

			// Append the filename to the retrieved directory
			strcat( iniFile, INI_FILE_NAME );
		}
		else
		{
			// Use the default INI filename as we can't seem to be able to retrieve it
			strcpy( iniFile, DEF_PLUGIN_DIR );
			strcat( iniFile, INI_FILE_NAME );
		}

		// Close the registry key
		RegCloseKey( regKey );
	}
	else
	{
		// Use the default INI filename as we can't seem to be able to retrieve it
		strcpy( iniFile, DEF_PLUGIN_DIR );
		strcat( iniFile, INI_FILE_NAME );
	}
}
*/