#pragma once
#include <WinSock2.h>
#include <Windows.h>

#include <vector>
#include "json.hpp"

using nlohmann::json;
using std::vector;

class ConversationUtils
{
public:
	static void receiveFromSocket(SOCKET sock, char* buff, int length) throw();
	static void sendToSocket(SOCKET sock, vector<unsigned char> data) throw();
	static vector<unsigned char> castBuffToVector(char* buff, int size);
	static json castBinToJson(vector<unsigned char> buff);
	static vector<unsigned char> castJsonToBin(json j);
	static int castByteToInt(vector<unsigned char> buff);
	static vector<unsigned char> castIntToByte(int val, int requiredBytes) throw();
	static vector<unsigned char> buildErrorResponse(std::string errorMsg);
private:
    ConversationUtils() = default;  // beacuse it's a static class
	static const int BITS_IN_BYTE = 8;
	static const int COUNTING_BASE = 256; //pow(2,BITS_IN_BITE)

};