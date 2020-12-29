#include "PacketsReader.h"

PacketsReader::PacketsReader(string filePath)
{
    this->_dbFilePath = filePath;
    this->_cursor = 0;
}