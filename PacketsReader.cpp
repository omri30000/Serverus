#include "PacketsReader.h"

PacketsReader::PacketsReader(string filePath)
{
    this->_dbFilePath = filePath;
    this->_cursor = 0;
}

string PacketsReader::getHostMac()
{
    string s = this->execTerminalCommand("ifconfig | grep ether");

    s = s.substr(s.find("ether") + 6, 17);

    return s;
}

string PacketsReader::execTerminalCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}