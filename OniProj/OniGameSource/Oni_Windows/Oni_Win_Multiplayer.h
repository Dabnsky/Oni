// Oni_Win_Multiplayer.h
// Header for multiplayer dialog callbacks

#ifndef ONI_WIN_MULTIPLAYER_H
#define ONI_WIN_MULTIPLAYER_H

#include "BFW.h"
#include "BFW_WindowManager.h"

UUtBool OWrMPHost_Callback(WMtDialog *inDialog, WMtMessage inMessage, UUtUns32 inParam1, UUtUns32 inParam2);
UUtBool OWrMPJoin_Callback(WMtDialog *inDialog, WMtMessage inMessage, UUtUns32 inParam1, UUtUns32 inParam2);

#endif // ONI_WIN_MULTIPLAYER_H
