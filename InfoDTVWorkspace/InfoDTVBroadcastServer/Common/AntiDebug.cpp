/*
 * AntiDebug.cpp
 *
 *  Created on: 2009-5-28
 *      Author: victor
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_ether.h>

bool CheckMAC(unsigned int aNetworkCardID,unsigned char aSrcMac[])
{
	struct ifreq ifr;
	int sock;
	unsigned char *ptr;
	int status;
	//string TmpStr="eth"+
	sprintf(ifr.ifr_name,"eth%d",aNetworkCardID);
//	strcpy (ifr.ifr_name , "eth1");
	sock = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock == -1)
	{
		return false;
	}
	status = ioctl (sock, SIOCGIFHWADDR, &ifr);
	if (status < 0)
	{
		close (sock);
		return false;
	}
	ptr =(unsigned char *) ifr.ifr_hwaddr.sa_data;
	if(ptr[0]==aSrcMac[0]&&ptr[1]==aSrcMac[1]
	&&ptr[2]==aSrcMac[2]&&ptr[3]==aSrcMac[3]
   &&ptr[4]==aSrcMac[4]&&ptr[5]==aSrcMac[5])
		return true;
	else
		return false;
}
