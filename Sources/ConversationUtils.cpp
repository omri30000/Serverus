#include "../Headers/ConversationUtils.h"
#include "JsonResponsePacketSerializer.h"
#include "ErrorResponse.h"
#include <iostream>
/*
This function gets input of length bytes from the socket
Input:sock: The socket with the client
	  buff -> pointer to the dest buffer
	  length ->num of bytes to read
Output:None
*/
void ConversationUtils::receiveFromSocket(SOCKET sock, char* buff, int length) throw()
{
	int res = 0;
	if (length <= 0)
		return;
	try
	{
		res = recv(sock, buff,length, 0);
	}
	catch (std::exception e)
	{
		std::string s = "Socket had been closed";
		s += std::to_string(sock);
		throw std::exception(s.c_str());
	}

	if (res == INVALID_SOCKET || length != res)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sock);
		throw std::exception(s.c_str());
	}

}

void ConversationUtils::sendToSocket(SOCKET sock, vector<unsigned char> data) throw()
{
	int res = 0;
	try 
	{
		char* response = (char*)&(data[0]); //from vector<unsigned char> to char *
		res = send(sock, response, data.size(), 0);

	}
	catch (std::exception er)
	{
		throw er;
	}

	if (res == SOCKET_ERROR || data.size() != res)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sock);
		throw std::exception(s.c_str());
	}
}

/*
This function casts bson to json object
Input:buff -> bson as binary buff
Output:json object
*/
json ConversationUtils::castBinToJson(vector<unsigned char> buff)
{
	std::string s(buff.begin(), buff.end());
	return json::from_bson(buff);
}


/*
This function casts json to bson as binary buffer
Input:j -> json object
Output:binary buffer
*/
vector<unsigned char> ConversationUtils::castJsonToBin(json j)
{
	return json::to_bson(j);
}

/*
This function converts from binary to integer value
For Example:0111 ==> 7
Input : bin - vector of chars: the value in binary
Output:The integer value
*/
int ConversationUtils::castByteToInt(vector<unsigned char> buff)
{
	int val = 0;
	int size = buff.size();

	for (int i = 0; i < size; i++)
	{
		val += pow(COUNTING_BASE, size - i - 1) * buff[i];
	}
	return val;
}


/*
This function casts char* of to vector of unsigned chars
Input:buff -> the buffer as char*
	  size -> the size of the buffer
Output:vector of bytes
*/
vector<unsigned char> ConversationUtils::castBuffToVector(char* buff, int size)
{
	return std::vector<unsigned char>(buff, buff + size);
}

/*
the function will get a decimal integer and cast into 4 bytes integer that will fit the 'bytes' object
EXAMPLE : 400 -- > 0 - 0 - 1 - 90 // 256 --> 0-0-1-0 // 1000 --> 0-0-3-232
FutureIdea: create recursive function instead
*/
vector<unsigned char> ConversationUtils::castIntToByte(int val, int requiredBytes) throw()
{
	int index = 0;
	vector<unsigned char> result;
	result.resize(requiredBytes);

	if (val > std::pow(2, (requiredBytes * BITS_IN_BYTE)))
	{
		throw std::exception("Number is to Big!");
	}


	for (size_t i = 0; i < requiredBytes; i++)
	{
		result[requiredBytes - 1 - index] = val % COUNTING_BASE;
		val = (int)(val / COUNTING_BASE);
		index += 1;
	}

	return result;
}
/*
This function creates an Errors response and encocde it.
Input:errMsg -> the message Error
Output: The encoded response :vector<unsigned char>
*/
vector<unsigned char> ConversationUtils::buildErrorResponse(std::string errorMsg)
{
	ErrorResponse er(errorMsg);
	return JsonResponsePacketSerializer::serializeResponse((Response*)&er);
}

