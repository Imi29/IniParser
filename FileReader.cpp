#include "FileReader.h"

using namespace DH;

FileReader::FileReader(const std::string& filePath)
{	
	m_file.open(filePath, std::ifstream::in);

	if (!m_file.is_open())
	{
		std::cerr << "Unable to open file: " << filePath << "\nPress Enter to exit." << std::endl;
		std::cin.get();
		exit(1);
	}
}

FileReader::~FileReader()
{
	m_file.close();
}

void FileReader::ReadLine(std::string& line)
{
	std::getline(m_file, line);
}
