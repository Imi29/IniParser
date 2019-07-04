#include "IniParser.h"

using namespace DH;

constexpr char TRIM_CHARACTER		= ' ';
constexpr char COMMENT_CHARACTER1	= ';';
constexpr char COMMENT_CHARACTER2	= '#';

void IniParser::ParseFile(const std::string& filePath)
{
	FileReader fileReader(filePath);
	while (!fileReader.Eof())
	{
		fileReader.ReadLine(*m_Content);
		if (!m_Content->empty()) { SplitLine(); }
	}
}

void IniParser::TrimContent(std::string& content)
{
	if (content.empty()) { return; }

	std::size_t first = content.find_first_not_of(TRIM_CHARACTER);
	std::size_t last  = content.find_last_not_of(TRIM_CHARACTER);

	content = std::move(content.substr(first, (last - first + 1)));
}

bool IniParser::IsSection() const
{
	return m_Content->find('[') != std::string::npos && m_Content->rfind(']') != std::string::npos;
}

bool IniParser::IsKeyValuePair() const
{
	return m_Content->find(m_KeyValueSeparator) != std::string::npos;
}

bool IniParser::IsComment() const
{
	return !m_Content->empty() && (m_Content->at(0) != COMMENT_CHARACTER1 || m_Content->at(0) != COMMENT_CHARACTER2);
}

inline void IniParser::InsertSectionToContainer()
{
	m_Content->erase(m_Content->cbegin(), m_Content->cbegin() + 1);
	m_Content->erase(m_Content->cend() - 1, m_Content->cend());

	m_entry[*m_Content] = std::map<KEY, VALUE>();
	m_CurrentSection = *m_Content;
}

inline void IniParser::InsertKeyValueToContainer()
{
	const int separatorPosition = m_Content->find(m_KeyValueSeparator);

	std::string key = std::move(m_Content->substr(0, separatorPosition));
	if (key.empty()) 
	{ 
		std::cerr << "Invalid file. Key cannot be empty.\nPress enter to exit" << std::endl;
		std::cin.get();
		exit(2);
	}

	TrimContent(key);

	std::string value = std::move(m_Content->substr(separatorPosition + 1, m_Content->length() - 1));
	TrimContent(value);

	m_entry[m_CurrentSection][key] = value;
}

void IniParser::SplitLine()
{
	TrimContent(*m_Content);

	if (IsSection())
	{
		InsertSectionToContainer();
	}
	else if (m_CurrentSection.length() > 0 && IsKeyValuePair())
	{
		InsertKeyValueToContainer();
	}
	else if (!IsComment())
	{
		std::cerr << "Invalid file. Invalid line found.\nPress enter to exit" << std::endl;
		std::cin.get();
		exit(3);
	}
}

std::string IniParser::GetValue(const std::string& section, const std::string& key)
{
	return m_entry[section][key];
}