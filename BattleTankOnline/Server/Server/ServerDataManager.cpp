#include "ServerDataManager.h"
#include "ServerManager.h"
#include "ConfigsManager.h"
#include "ServerTimeManager.h"

ServerDataManager* ServerDataManager::_instance = 0;

ServerDataManager* ServerDataManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new ServerDataManager();
	}
	return _instance;
}
ServerDataManager::ServerDataManager()
{
	DataBuffer[0] = new char[20480];
	PushIndex[0] = PopIndex[0] = 0;
	DataBuffer[1] = new char[20480];
	PushIndex[1] = PopIndex[1] = 0;
	DataCount[0] = DataCount[1] = 0;
	MaxDataBufferSize = ConfigsManager::Instance()->GetIntConfig(ConfigName::MAX_HOLDING_DATA_SIZE);
}
ServerDataManager::~ServerDataManager()
{

}

void ServerDataManager::PushBack(char* buffer,int length)
{
	int current = 0;
	int bIndex = 0;
	while (buffer[current] != '\0' && current < length)
	{
		if (head)
		{
			if (buffer[current] == '0')
			{
				bIndex = 0;
			}
			else
			{
				bIndex = 1;
			}
			current++;
			head = false;
		}

		DataBuffer[bIndex][PushIndex[bIndex]] = buffer[current];
		if (DataBuffer[bIndex][PushIndex[bIndex]] == '$')
		{
			DataCount[bIndex] += 1;
			head = true;
		}


		// +1
		PushIndex[bIndex] ++;
		current ++;
		if (PushIndex[bIndex] >= MaxDataBufferSize)
		{
			PushIndex[bIndex] = 0;
		}
	}
}
char* ServerDataManager::PopFront()
{
	char* datareturn = new char[DATA_BUFSIZE];
	int bIndex;
	
	if (CurrentBuffer == 0)
	{
		if (DataCount[0] > 0)
			CurrentBuffer = 1;
		else if (DataCount[1] > 0)
			CurrentBuffer = 0;
		else
		{
			CurrentBuffer = 0;
			datareturn[0] = '\0';
			return datareturn;
		}
	}
	else 
	{
		if (DataCount[1] > 0)
			CurrentBuffer = 0;
		else if (DataCount[0] > 0)
			CurrentBuffer = 1;
		else
		{
			CurrentBuffer = 1;
			datareturn[0] = '\0';
			return datareturn;
		}
	}
	bIndex = 1-CurrentBuffer;
	int current = 0;
	while (DataBuffer[bIndex][PopIndex[bIndex]] != '$')
	{
		datareturn[current] = DataBuffer[bIndex][PopIndex[bIndex]];
		PopIndex[bIndex]++;
		current++;

		if (PopIndex[bIndex] >= MaxDataBufferSize)
		{
			PopIndex[bIndex] = 0;
		}
		if (DataBuffer[bIndex][PopIndex[bIndex]] == '$')
		{
			DataCount[bIndex] -= 1;
		}
	}
	PopIndex[bIndex]++;
	datareturn[current] = '\0';
	return datareturn;
}

void ServerDataManager::Run()
{
	while (ServerManager::Instance()->State != ServerState::STOP)
	{
		if (ServerManager::Instance()->State > 0)
		{
			//if (ServerTimeManager::Instance()->ExecuteFrameCount > ConfigsManager::Instance()->GetIntConfig(ConfigName::CLIENT_STEP))
			{
				ServerTimeManager::Instance()->ExecuteFrameCount = 0;
				try
				{

					string currentData = PopFront();
					while (currentData != "")
					{
						vector<string> decode = StringHelper::split(currentData, ",");
						int uid = Helper::GetInt(decode, 1);
						Client* client = ClientManager::Instance()->GetClient(uid);
						client->Receive(currentData);
						if (Helper::GetString(decode, 0) == "JoinServer")
						{
							Server* server = ServerManager::Instance()->GetServer(Helper::GetInt(decode, 3));
							server->Join(uid);
							client->SID = server->SID;
						}
						currentData = PopFront();
					}
					ServerManager::Instance()->ServerExecute();
				}
				catch (const std::exception&)
				{
					printf("Error!!");
				}
			}			
		}
		//ServerTimeManager::Instance()->ServerThreadSleep();
		ServerTimeManager::Instance()->ThreadSleep(1);
	}
}
