﻿// This code is part of Pcap_DNSProxy
// A local DNS server based on WinPcap and LibPcap
// Copyright (C) 2012-2016 Chengr28
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#include "Base.h"

#if defined(ENABLE_PCAP)
//Structures
typedef struct _capture_handler_param_
{
	uint16_t   DeviceType;
	char       *Buffer;
	size_t     BufferSize;
}CaptureHandlerParam, CAPTURE_HANDLER_PARAM, *PCaptureHandlerParam, *PCAPTURE_HANDLER_PARAM;

//Global variables
extern CONFIGURATION_TABLE Parameter;
extern GLOBAL_STATUS GlobalRunningStatus;
extern ALTERNATE_SWAP_TABLE AlternateSwapList;
#if defined(ENABLE_LIBSODIUM)
	extern DNSCURVE_CONFIGURATION_TABLE DNSCurveParameter;
#endif
extern std::deque<OUTPUT_PACKET_TABLE> OutputPacketList;
extern std::mutex CaptureLock, OutputPacketListLock;
std::string PcapFilterRules;
std::vector<std::string> PcapRunningList;

//Functions
void __fastcall CaptureFilterRulesInit(
	std::string &FilterRules);
bool __fastcall CaptureModule(
	const pcap_if *pDrive, 
	const bool IsCaptureList);
void CaptureHandler(
	unsigned char *Param, 
	const struct pcap_pkthdr *PacketHeader, 
	const unsigned char *PacketData);
bool __fastcall CaptureNetworkLayer(
	const char *Buffer, 
	const size_t Length, 
	const size_t BufferSize, 
	const uint16_t Protocol);
bool __fastcall CaptureCheck_ICMP(
	const char *Buffer, 
	const size_t Length, 
	const uint16_t Protocol);
bool __fastcall CaptureCheck_TCP(
	const char *Buffer);
bool __fastcall MatchPortToSend(
	const char *Buffer, 
	const size_t Length, 
	const size_t BufferSize, 
	const uint16_t Protocol, 
	const uint16_t Port);
#endif
