// ======================================================================
#ifndef NM_WS_UDP_H
#define NM_WS_UDP_H

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <Winsock2.h>
#include <ws2tcpip.h>
#include "BFW.h"
#include "BFW_NetworkManager.h"

// ======================================================================
// prototypes
// ======================================================================
char*
NMrWS_AddressToString(
	const NMtNetAddress			*inNetAddress);

UUtError
NMrWS_UDP_Initialize(
	void);

void
NMrWS_UDP_Terminate(
	void);

// ======================================================================
#endif /* NM_WS_UDP_H */
