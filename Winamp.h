#ifndef WINAMP_H
#define WINAMP_H

#define WINAMP_CLASS									"Winamp v1.x"
#define WINAMP_TITLE_BEGIN						". "
#define WINAMP_TITLE_MIDDLE						" - "
#define WINAMP_TITLE_END							" - Winamp"

// Winamp defined WM_COMMAND messages
#define WINAMP_MSG_PREV								40044
#define WINAMP_MSG_NEXT								40048
#define WINAMP_MSG_PLAY								40045
#define WINAMP_MSG_PAUSE							40046
#define WINAMP_MSG_STOP								40047
#define WINAMP_MSG_REPEAT							40022
#define WINAMP_MSG_SHUFFLE						40023
#define WINAMP_MSG_CLOSE							40001
#define WINAMP_MSG_ALWAYS_ON_TOP			40019
#define WINAMP_MSG_OPEN_FILE					40029
#define WINAMP_MSG_OPEN_URL						40155
#define WINAMP_MSG_OPEN_JUMP_TO_TIME	40193
#define WINAMP_MSG_OPEN_JUMP_TO_FILE	40194
#define WINAMP_MSG_OPEN_FILE_INFO			40188

#define MIN_TITLE_LENGTH							5

#define DEFAULT_WINAMP_WINDOW					NULL
#define DEFAULT_PLAYING								NULL
#define DEFAULT_TITLE									NULL
#define DEFAULT_ARTIST								NULL
#define DEFAULT_SONG_INDEX_STR				NULL
#define DEFAULT_SONG_INDEX						0

#include <windows.h>

class Winamp
{
public:	
	~Winamp();

	// Gets the one and only winamp instance.
	static Winamp * GetInstance();

	// Gets a handle to the winamp window.
	HWND GetWinampWindow();

	// Updates the now playing information.
	void Update();

	// Indicates if Winamp is started.
	bool IsStarted( bool update = true );

	// Indicates if Winamp is playing.
	bool IsPlaying( bool update = true );

	// Gets the playing artist-title.
	char * GetPlayingArtistTitle( bool update = false );

	// Gets the playing title.
	char * GetPlayingTitle( bool update = false );

	// Gets the playing artist.
	char * GetPlayingArtist( bool update = false );

	// Gets the playing index as a string.
	char * GetPlayingIndexStr( bool update = false );

	// Gets the playing title.
	int    GetPlayingIndex( bool update = false );

	// Play the next track.
	void NextTrack();

	// Play the previous track.
	void PreviousTrack();

	// Start playing.
	void Play();

	// Pause playing.
	void Pause();

	// Stop playing.
	void Stop();

	// Toggle repeat on/off.
	void ToggleRepeat();

	// Toggle shuffle on/off.
	void ToggleShuffle();

	// Toggle always on-top on/off.
	void ToggleAlwaysOnTop();

	// Close winamp.
	void Close();	

	// Show the open file dialog.
	void OpenFile();

	// Show the open URL dialog.
	void OpenUrl();

	// Show the jump-to-file dialog.
	void OpenJumpToFile();

	// Show the jump-to-time dialog.
	void OpenJumpToTime();

	// Show the file info dialog.
	void OpenFileInfo();	 

protected:
	Winamp();	

private:
	// Parses the next of the current winamp window and retrieves information from it.
	void ParseWinampText( char *text );

	// Post a message to the winamp window.
	void PostWinampMessage( WPARAM winampMessage );

	static Winamp *instance;	

	HWND winampWindow;
	char *playing;
	char *title;
	char *artist;
	char *songIndexStr;
	int songIndex;
};

/*
WM_COMMAND Messages
Fadeout and stop 40147 
Stop after current track 40157 
Fast-forward 5 seconds 40148 
Fast-rewind 5 seconds 40144 
Start of playlist 40154 
Go to end of playlist 40158 
Set time display mode to elapsed 40037 
Set time display mode to remaining 40038 
Toggle preferences screen 40012 
Open visualization options 40190 
Open visualization plug-in options 40191 
Execute current visualization plug-in 40192 
Toggle about box 40041 
Toggle title Autoscrolling 40189 
Toggle Windowshade 40064 
Toggle Playlist Windowshade 40266 
Toggle doublesize mode 40165 
Toggle EQ 40036 
Toggle playlist editor 40040 
Toggle main window visible 40258 
Toggle minibrowser 40298 
Toggle easymove 40186 
Raise volume by 1% 40058 
Lower volume by 1% 40059 
Open skin selector 40219 
Configure current visualization plug-in 40221 
Reload the current skin 40291 
Moves back 10 tracks in playlist 40197 
Show the edit bookmarks 40320 
Adds current track as a bookmark 40321 
Play audio CD 40323 
Load a preset from EQ 40253 
Save a preset to EQF 40254 
Opens load presets dialog 40172 
Opens auto-load presets dialog 40173 
Load default preset 40174 
Opens save preset dialog 40175 
Opens auto-load save preset 40176 
Opens delete preset dialog 40178 
Opens delete an auto load preset dialog 40180 
*/

#endif