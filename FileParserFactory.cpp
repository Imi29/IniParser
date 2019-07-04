#include "FileParserFactory.h"

using namespace DH;

FileParserFactory::FileParserFactory() :
	m_parser(nullptr), m_FilePath(""), m_fileStat({0}), m_KillFilePollingthread(false)
{
}

FileParserFactory::~FileParserFactory()
{
	delete m_parser;
	m_parser = nullptr;

	m_KillFilePollingthread = true;
	m_FilePollingthread.join();
}

void FileParserFactory::ParseFile(const std::string& filePath)
{
	stat(filePath.c_str(), &m_fileStat);
	m_FilePath = filePath;

	const std::string ext = std::move(GetExtension(filePath));
	if (ext == "ini") { m_parser = new IniParser; }
	else
	{
		std::cerr << "There is no proper parser.\nPress Enter to exit." << std::endl;
		std::cin.get();
		exit(0);
	}

	m_FilePollingthread = std::thread(&FileParserFactory::FilePolling, this);
	m_parser->ParseFile(filePath);	
}

void FileParserFactory::FilePolling()
{
	struct stat localFileStat;
	while (!m_KillFilePollingthread)
	{		
		stat(m_FilePath.c_str(), &localFileStat);
		if (localFileStat.st_mtime > m_fileStat.st_mtime)
		{
			m_fileStat = localFileStat;
			m_parser->ParseFile(m_FilePath);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

std::string FileParserFactory::GetValue(const std::string& section, const std::string& key) const
{
	return m_parser->GetValue(section, key);
}

std::string FileParserFactory::GetExtension(const std::string& filePath) const
{
	int ind = filePath.length() - 1;
	std::string ext = "";
	while (ind >= 0 && filePath[ind] != '.') { ind--; }

	while (ind < static_cast<int>(filePath.length() - 1))
	{
		ind++;
		ext += filePath[ind];
	}

	return ext;
}
