#pragma once

#include "FileReader.h"

///<summary>
/// A parser-ek absztrakt �soszt�lya. Minden key-value parser-nek ebb�l az oszt�lyb�l kell sz�rmaznia.
///</summary>

namespace DH
{
	class BaseParser
	{
	public:
		BaseParser();
		virtual ~BaseParser();

		BaseParser(const BaseParser&) = delete;
		BaseParser(BaseParser&&) = delete;

		BaseParser& operator=(const BaseParser&&) = delete;
		BaseParser& operator=(BaseParser&&) = delete;

		///<summary>Parser specifikus a f�jlok elemz�se.</summary>
		///<params>filePath: az input file</params>
		virtual void ParseFile(const std::string& filePath) = 0;

		///<summary>Parser specifikus a f�jl egy sor�nak felbont�sa kulcs-�rt�k p�rra.</summary>
		virtual void SplitLine() = 0;

		///<summary>
		/// Parser specifikus, hogy a t�rol�j�nak hogy adja vissza egy section-h�z tartoz� kulcs �rt�k�t.
		///</summary>
		virtual std::string GetValue(const std::string& section, const std::string& key) = 0;

		char GetKeyValueSeparator() const;
		void SetKeyValueSeparator(char separator);

		///<summary>
		/// Az egyes sorokban a kulcsokat az �rt�kt�l elv�laszt� alap�rtelmezett karakter.
		///</summary>
		static const char DEFAULT_SEPARATOR;

	protected:
		std::string*   m_Content;
		char m_KeyValueSeparator;
	};
}