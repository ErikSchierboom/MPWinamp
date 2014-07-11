#include "Utils.h"

#ifdef _DEBUG

void PrintDebugMessage( const char *message )
{
	MessageBox( GetActiveWindow(), message, "Debug message", MB_OK );
}

#endif

char * AllocAndCopy( const char *str )
{
	ON_NULL_RETURN_VALUE( str, NULL );

	// Get the length of the string
	int textLength = strlen( str );

	if( textLength == 0 )
		return "";

	// Copy the string
	char *copy = new char[textLength + 1];
	strncpy( copy, str, textLength );
	copy[textLength] = '\0';

	return copy;
}

char * TrimLeft( const char *str )
{
	// Return null if there is no string
	ON_NULL_RETURN_VALUE( str, NULL );

	int length = strlen( str );

	int trimPos = -1;

	// Loop through the string to find the first non-space character
	for( int i = 0; i < length; ++i )
	{
		if( isspace( str[i] ) )
			trimPos = i;
		else
			break;
	}
	
	if( trimPos == -1 )
	{
		char *trimmed = new char[length + 1 ];
		strcpy( trimmed, str );
		trimmed[length] = '\0';
		return trimmed;
	}

	int newLength = length - trimPos - 1;

	char *trimmed = new char[newLength + 1];

	int pos = 0;

	for( int i = trimPos + 1; i < length; ++i )
		trimmed[pos++] = str[i];
	
	trimmed[newLength] = '\0';

	return trimmed;
}


char * TrimRight( const char *str )
{
	// Return null if there is no string
	ON_NULL_RETURN_VALUE( str, NULL );

	int length = strlen( str );
	int trimPos = -1;

	// Loop through the string to find the first non-space character
	for( int i = length - 1; i >= 0; --i )
	{
		if( isspace( str[i] ) )
			trimPos = i;
		else
			break;
	}

	if( trimPos == -1 )
	{
		char *trimmed = new char[length + 1 ];
		strcpy( trimmed, str );
		trimmed[length] = '\0';
		return trimmed;
	}

	int newLength = trimPos;

	char *trimmed = new char[newLength + 1];
	for( int i = 0; i < trimPos; ++i )
		trimmed[i] = str[i];
	
	trimmed[newLength] = '\0';

	return trimmed;
}

char * Trim( const char *str )
{
	// Trim the left part of the string
	char *trimmed = TrimLeft( str );

	// Also trim the right of the string
	return TrimRight( trimmed );
}