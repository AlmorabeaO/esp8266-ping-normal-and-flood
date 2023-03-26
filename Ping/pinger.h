#ifndef __MyPinger__
#ifndef __ORIGINAL_PINGER__
#define __MyPinger__
#include "IPAddress.h"
extern "C"
{
  #include <lwip/raw.h>
  #include <user_interface.h>
}
#endif __ORIGINAL_PINGER__

void PingAttack(IPAddress ip, int packetId=0xADDE, int echoPayloadLen = 32);

#endif __MyPinger__
