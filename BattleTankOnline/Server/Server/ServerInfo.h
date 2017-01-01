#define SERVER_INFO_H
#ifdef SERVER_INFO_H
#pragma once

struct ServerInf
{
	int SID;
	int HostID;
	int MapID;
	ServerInf(int sid, int hostID, int mapID);
};
#endif //SERVER_INFO_H