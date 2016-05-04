// ARPLayer.h: interface for the CARPLayer class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLayer.h"
#include "EthernetLayer.h"
#include "IPLayer.h"
#include "NILayer.h"
#include <list>
#include <pcap.h>
#include <Packet32.h>

class CARPLayer : public CBaseLayer
{
private:
	inline void		ResetHeader( );

public:
	CARPLayer(char* pName);
	virtual ~CARPLayer(void);

	typedef struct _ARP_HEADER
	{
		unsigned short arpHardwareType;
		unsigned short arpProtocolType;
		unsigned char arpHardwareAddrSize;
		unsigned char arpProtocolAddrSize;
		unsigned short arpOperationType;
		unsigned char arpSenderHardwareAddress[6];
		unsigned char arpSenderIPAddress[4];
		unsigned char arpTargetHardwareAddress[6];
		unsigned char arpTargetIPAddress[4];
		unsigned char arpData[ARP_DATA_SIZE];

	} ARP_HEADER, *LPARP_HEADER;

	typedef struct _ARP_CACHE_RECORD
	{
		unsigned char arpInterface[6];
		unsigned char ipAddress[4];
		unsigned char ethernetAddress[6];
		BOOL isComplete;
	} ARP_CACHE_RECORD, *LPARP_CACHE_RECORD;

	void setARPOperationType(unsigned char operationType);
	void setSenderIPAddress(unsigned char* senderIP);
	void setSenderHardwareAddress(unsigned char* senderHard);
	void setTargetIPAddress(unsigned char* targetIP);
	void setTargetHardwareAddress(unsigned char* targetHard);

	BOOL Send(unsigned char* ppayload, int length);
	BOOL Receive(unsigned char* ppayload);

protected:
	ARP_HEADER arpHeader;
	list<ARP_CACHE_RECORD> arpCacheTable;
	LPADAPTER adapter;
};
