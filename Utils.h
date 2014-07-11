#ifndef UTILS_H
#define UTILS_H

#define ON_NULL_RETURN(x)					if( x == NULL ) return;
#define ON_NULL_RETURN_VALUE(x,y) if( x == NULL ) return y;
#define SAFE_DELETE(x)						if( x != NULL ) { delete x; x = NULL; }
#define SAFE_ARRAY_DELETE(x)			if( x != NULL ) { delete[] x; x = NULL; }
#define SAFE_CLOSE_HANDLE(x)			if( x != NULL ) { CloseHandle( x ); x = NULL; }
#define SAFE_RELEASE(x)						if( x != NULL ) { x.Release(); x = NULL; }
#define GET_DIALOG_ITEM(x,y,z)    if( x == NULL ) x = GetDlgItem( y, z )

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#ifdef _DEBUG
void PrintDebugMessage( const char *message );
#endif

char * AllocAndCopy( const char *str );
char * Trim( const char *str );
char * TrimLeft( const char *str );
char * TrimRight( const char *str );

#endif