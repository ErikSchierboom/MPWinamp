#include ".\messenger.h"
#include "Utils.h"

Messenger::Messenger( IDispatch* iMessengerObj )
{	
	messenger3 = NULL;
	nickname = "";

	IMessenger3 *iMessengerRaw = NULL;
	iMessengerObj->QueryInterface( IID_IMessenger3, reinterpret_cast<void**>( &iMessengerRaw ) );
	if( iMessengerRaw != NULL )
		messenger3.Attach( iMessengerRaw );
}

Messenger::~Messenger( void )
{	
	SAFE_RELEASE( messenger3 );
}

char * Messenger::GetNickname()
{
	// Get the messenger interface pointer
	if( !messenger3.GetInterfacePtr() )
		return NULL;

	BSTR tempNick;

	// Try to retrieve the nickname
	if( messenger3->get_MyFriendlyName( &tempNick ) != S_OK )
		return NULL;

	if( tempNick == NULL )
		return NULL;
	
	// Copy the BSTR
	nickname.Assign( tempNick );

	// Free memory			
	SysFreeString( tempNick );
	
	return (char *)nickname;
}

