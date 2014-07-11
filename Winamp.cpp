#include "Winamp.h"
#include "Utils.h"

// Initialize the singleton instance to NULL
Winamp *Winamp::instance = NULL;

Winamp::Winamp()
{
	winampWindow = DEFAULT_WINAMP_WINDOW;
	playing = DEFAULT_PLAYING;
	artist = DEFAULT_ARTIST;
	title = DEFAULT_TITLE;
	songIndexStr = DEFAULT_SONG_INDEX_STR;
	songIndex = DEFAULT_SONG_INDEX;
}

Winamp::~Winamp()
{
	SAFE_ARRAY_DELETE( playing );
	SAFE_ARRAY_DELETE( artist );
	SAFE_ARRAY_DELETE( title );
	SAFE_ARRAY_DELETE( songIndexStr );
	winampWindow = NULL;
}

HWND Winamp::GetWinampWindow()
{
	// Try to retrieve the handle to the Winamp window
	winampWindow = FindWindow( WINAMP_CLASS, NULL );

	return winampWindow;
}

void Winamp::Update()
{
	// If the winamp window was and could not be retrieved, return
	if( winampWindow == NULL && GetWinampWindow() == NULL )
		return;

	// Get the length of the window's text
	int textLength = GetWindowTextLength( winampWindow );

	// If there is no window text, return
	if( textLength == 0 )
		return;

	// Allocate memory for the window text string
	char *windowText = new char[textLength + 1];

	__try
	{
		// Get's the window's text and places it in the buffer
		GetWindowText( winampWindow, windowText, textLength + 1 );

		// Make sure the string is null-terminated
		windowText[textLength] = '\0';

		// Parse the text retrieved from the winamp window, extracting the information from it
		ParseWinampText( windowText );
	}
	__finally
	{
		SAFE_ARRAY_DELETE( windowText );
	}
}

bool Winamp::IsStarted( bool update )
{
	// Check if we should update
	if( update )
		GetWinampWindow();

	return( winampWindow != NULL );
}

bool Winamp::IsPlaying( bool update )
{
	// If Winamp is not started, return false
	if( !IsStarted( update ) )
		return false;

	// Get the latest information
	Update();

	// Return true if we have succesfully retrieved one of the values
	return( artist != NULL || title != NULL || songIndexStr || NULL );
}

char * Winamp::GetPlayingArtistTitle( bool update )
{
	// Check if we should update our winamp retrieved data
	if( update )
		Update();
		
	return playing;
}

char * Winamp::GetPlayingArtist( bool update )
{
	// Check if we should update our winamp retrieved data
	if( update )
		Update();

	return artist;
}

char * Winamp::GetPlayingTitle( bool update )
{
	// Check if we should update our winamp retrieved data
	if( update )
		Update();

	return title;
}

char * Winamp::GetPlayingIndexStr( bool update )
{
	// Check if we should update our winamp retrieved data
	if( update )
		Update();

	return songIndexStr;
}

int Winamp::GetPlayingIndex( bool update )
{
	// Check if we should update our winamp retrieved data
	if( update )
		Update();

	return songIndex;
}

void Winamp::NextTrack()
{
	// Post the next track message
	PostWinampMessage( WINAMP_MSG_NEXT );
}

void Winamp::PreviousTrack()
{
	// Post the previous track message
	PostWinampMessage( WINAMP_MSG_PREV );
}

void Winamp::Play()
{
	// Post the play message
	PostWinampMessage( WINAMP_MSG_PLAY );	
}

void Winamp::Pause()
{
	// Post the pause message
	PostWinampMessage( WINAMP_MSG_PAUSE );	
}

void Winamp::Stop()
{
	// Post the stop message
	PostWinampMessage( WINAMP_MSG_STOP );	
}

void Winamp::ToggleRepeat()
{
	// Post the toggle repeat message
	PostWinampMessage( WINAMP_MSG_REPEAT );	
}

void Winamp::ToggleShuffle()
{
	// Post the toggle shuffle message
	PostWinampMessage( WINAMP_MSG_SHUFFLE );	
}

void Winamp::ToggleAlwaysOnTop()
{
	// Post the toggle always on top winamp message
	PostWinampMessage( WINAMP_MSG_ALWAYS_ON_TOP );	
}

void Winamp::Close()
{
	// Post the close winamp message
	PostWinampMessage( WINAMP_MSG_CLOSE );	
}

void Winamp::OpenFile()
{
	// Post the open file winamp message
	PostWinampMessage( WINAMP_MSG_OPEN_FILE );	
}

void Winamp::OpenUrl()
{
	// Post the open file winamp message
	PostWinampMessage( WINAMP_MSG_OPEN_URL );
}

void Winamp::OpenJumpToFile()
{
	// Post the open jump to file winamp message
	PostWinampMessage( WINAMP_MSG_OPEN_JUMP_TO_FILE );	
}

void Winamp::OpenJumpToTime()
{
	// Post the open jump to file winamp message
	PostWinampMessage( WINAMP_MSG_OPEN_JUMP_TO_TIME );	
}

void Winamp::OpenFileInfo()
{
	// Post the open file info winamp message
	PostWinampMessage( WINAMP_MSG_OPEN_FILE_INFO );	
}

void Winamp::PostWinampMessage( WPARAM winampMessage )
{
	// If we have found the winamp window, post the stop message
	if( IsStarted() )
		PostMessage( winampWindow, WM_COMMAND, winampMessage, 0 );
}

void Winamp::ParseWinampText( char *text )
{
	// Reset the values
	SAFE_ARRAY_DELETE( playing );
	SAFE_ARRAY_DELETE( artist );
	SAFE_ARRAY_DELETE( title );
	SAFE_ARRAY_DELETE( songIndexStr );
	playing = DEFAULT_PLAYING;
	artist = DEFAULT_ARTIST;
	title = DEFAULT_TITLE;
	songIndexStr = DEFAULT_SONG_INDEX_STR;
	songIndex = DEFAULT_SONG_INDEX;

	ON_NULL_RETURN( text );

	// Get the length of the full string
	size_t textLength = strlen( text );

	// Check if the string has at least the required length
	if( textLength <= MIN_TITLE_LENGTH )
		return;
	
	// Find the different title parts
	char *afterIndexStr = strstr( text, WINAMP_TITLE_BEGIN ) + strlen( WINAMP_TITLE_BEGIN );
	char *afterArtistStr = strstr( text, WINAMP_TITLE_MIDDLE ) + strlen( WINAMP_TITLE_MIDDLE );
	char *afterTitleStr = strstr( text, WINAMP_TITLE_END );

	__try
	{
		ON_NULL_RETURN( afterIndexStr );
		ON_NULL_RETURN( afterArtistStr );
		ON_NULL_RETURN( afterTitleStr );

		// Calculate the length of the various strings		
		size_t afterIndexLength = strlen( afterIndexStr );
		size_t afterArtistLength = strlen( afterArtistStr );
		size_t afterTitleLength = strlen( afterTitleStr );
		size_t titleMiddleLength = strlen( WINAMP_TITLE_MIDDLE );
		size_t songIndexLength = textLength - afterIndexLength - strlen( WINAMP_TITLE_BEGIN );
		size_t artistLength = afterIndexLength - afterArtistLength - titleMiddleLength;
		size_t titleLength = afterArtistLength - afterTitleLength;
		size_t playingLength = afterIndexLength - afterTitleLength;

		// Allocate memory for the char arrays
		artist = new char[artistLength + 1];
		title = new char[titleLength + 1];
		playing = new char[playingLength + 1];
		songIndexStr = new char[songIndexLength + 1];

		// Copy the respective strings
		strncpy( artist, afterIndexStr, artistLength );
		strncpy( title, afterArtistStr, titleLength );
		strncpy( playing, afterIndexStr, playingLength );
		strncpy( songIndexStr, text, songIndexLength );

		// Make sure the char arrays are null-terminated
		artist[artistLength] = '\0';
		title[titleLength] = '\0';
		playing[playingLength] = '\0';
		songIndexStr[songIndexLength] = '\0';

		// Convert the character(s) to an integer 
		songIndex = atoi( songIndexStr );
	}
	__finally
	{
		afterIndexStr = NULL;
		afterArtistStr = NULL;
		afterTitleStr = NULL;
	}
}

Winamp * Winamp::GetInstance( void )
{
	// If the one-and-only instance has not yet been created, create it
	if( instance == NULL )
		instance = new Winamp();

	return instance;
}