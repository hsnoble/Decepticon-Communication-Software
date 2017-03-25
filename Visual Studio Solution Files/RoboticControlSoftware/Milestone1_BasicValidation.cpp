#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "PktDef.h"

using namespace std;

int main()
{
	MilestoneOne::MotorBody DriveCmd;
	DriveCmd.Direction = MilestoneOne::FORWARD;
	DriveCmd.Duration = 20;

	MilestoneOne::PktDef TestPkt;
	char *ptr;

	cout << sizeof(MilestoneOne::CmdPacketHeader);
	cout << endl << sizeof(MilestoneOne::CmdPacket);
	cout << endl << sizeof(MilestoneOne::CmdPacket::Tail);

	//Testing the PktDef creation interface based on user input
	TestPkt.SetCmd(MilestoneOne::DRIVE);
	TestPkt.SetBodyData((char *)&DriveCmd, 2);
	TestPkt.SetPktCount(1);
	TestPkt.CalcCRC();
	ptr = TestPkt.GenPacket();

	cout << showbase
		<< internal
		<< setfill('0');

	for (int x = 0; x < (int)TestPkt.GetLength(); x++)
		cout << hex << setw(4) << (unsigned int)*(ptr++) << ", ";

	cout << endl;
	TestPkt.SetCmd(MilestoneOne::ACK);
	TestPkt.CalcCRC();
	ptr = TestPkt.GenPacket();

	for (int x = 0; x < (int)TestPkt.GetLength(); x++)
		cout << hex << setw(4) << (unsigned int)*(ptr++) << ", ";

	cout << endl << noshowbase << dec;

	//Testing the PktDef creation interface based on an RxBuffer of RAW Data
	char buffer[9] = { 0x02, 0x00, 0x00, 0x00, 0x02, 0x09, 0x11, 0x24, 0x08 };
	MilestoneOne::PktDef RxPkt(buffer);
	cout << "CommandID:  " << RxPkt.GetCmd() << endl;
	cout << "PktCount:   " << RxPkt.GetPktCount() << endl;
	cout << "Pkt Length: " << RxPkt.GetLength() << endl;
	cout << "Body Data: " << endl;

	ptr = RxPkt.GetBodyData();
	cout << showbase << hex;
	cout << "Byte 1 " << (int)*ptr++ << endl;
	cout << "Byte 2 " << (int)*ptr << endl;

	//Testing the PktDef CRC Calculation
	
	//Test #1 -- Validation of a Correct CRC Calculation
	char CRCGoodTest[9] = { 0x02, 0x00, 0x00, 0x00, 0x02, 0x09, 0x11, 0x24, 0x08 };
	bool Result = RxPkt.CheckCRC(CRCGoodTest, 9);
	if (Result)
		cout << "CRC Test #1 -- PASSED" << endl;
	else
		cout << "CRC Test #1 -- FAILED" << endl;

	//Test #2 -- Validation of an Incorrect CRC Calculation
	char CRCBadTest[9] = { 0x02, 0x00, 0x00, 0x00, 0x02, 0x09, 0x11, 0x24, 0x17 };
	Result = RxPkt.CheckCRC(CRCBadTest, 9);
	if (Result)
		cout << "CRC Test #1 -- FAILED" << endl;
	else
		cout << "CRC Test #1 -- PASSED" << endl;

	return 1;
}
