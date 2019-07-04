#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace DH
{
	///<summary>A input file beolvas�s�t v�gz� basic RAII oszt�ly.</summary>
	class FileReader final
	{
	public:
		FileReader(const std::string& filePath);
		~FileReader();

		FileReader(const FileReader&) = delete;
		FileReader(FileReader&&) = delete;

		FileReader& operator=(const FileReader&) = delete;
		FileReader& operator=(FileReader&&) = delete;

		void ReadLine(std::string& fileContent);

		inline bool Eof() const { return m_file.eof(); }

	private:
		std::ifstream m_file;
	};
}