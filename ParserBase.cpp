#include "ParserBase.h"

using namespace DH;

const char BaseParser::DEFAULT_SEPARATOR = '=';

BaseParser::BaseParser() :
	m_Content(new std::string), m_KeyValueSeparator(DEFAULT_SEPARATOR)
{
}

BaseParser::~BaseParser()
{
	delete m_Content;
	m_Content = nullptr;
}

char BaseParser::GetKeyValueSeparator() const
{
	return m_KeyValueSeparator;
}

void BaseParser::SetKeyValueSeparator(char separator)
{
	m_KeyValueSeparator = separator;
}
