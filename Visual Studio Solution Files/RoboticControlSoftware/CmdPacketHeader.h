/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing a CmdPacketHeader structure for the PktDef structure
*/

#ifndef PROJECT_CMDPACKET_HEADER_H
#define PROJECT_CMDPACKET_HEADER_H

namespace MilestoneOne {
	struct CmdPacketHeader
	{
	private:
	public:
		ui PktCount;		// Value that is incremented constantly each time a packet is transmitted between the client and robot
		uc Drive : 1;		// Set to 1 if the command is a DRIVE command
		uc Status : 1;		// Set to 1 if the response packet is sensor telemetry
		uc Sleep : 1;		// Set to 1 if the command is a SLEEP command
		uc Arm : 1;			// Set to 1 if the command is an ARM command
		uc Claw : 1;		// Set to 1 if the command is a CLAW command
		uc Ack : 1;			/* Set to 1 if the command is an acknowledgement packet. Behaviour as follows:
								After receiving a DRIVE, ARM, CLAW or SLEEP command, the robot will
								send a STATUS command with ACK set to 1 as well at the bit corresponding to the command
								also set to 1
							*/
		uc Padding : 2;
		uc Length;			// Contains the total number of bytes in the body of the packet

		CmdPacketHeader()
		{
			PktCount = 6;
			Drive = 1;
			Status = 1;
			Sleep = 1;
			Arm = 1;
			Claw = 1;
			Ack = 1;
			Padding = 1;
			Length = 1;
		}
	};
}
#endif

/*
	To be noted: DRIVE, ARM, CLAW and SLEEP flags should never be set at the same time. The ACK flag should always be set
	with a corresponding command flag (one of the above).
*/