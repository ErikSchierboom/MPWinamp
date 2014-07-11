#pragma once

#include <comdef.h>

//Messenger API
#include "Messenger API\msgrua.h"

//Smart pointers of interfaces declared in the API of Messenger
_COM_SMARTPTR_TYPEDEF( IMessenger3, __uuidof( IMessenger3 ) );

class Messenger
{
public:
	Messenger( IDispatch* iMessengerObj );
	~Messenger( void );

	char * GetNickname();

private:
	IMessenger3Ptr messenger3;
	_bstr_t nickname;
};
