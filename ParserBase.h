#pragma once

#include "FileReader.h"

///<summary>
/// A parser-ek absztrakt õsosztálya. Minden key-value parser-nek ebbõl az osztályból kell származnia.
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

		///<summary>Parser specifikus a fájlok elemzése.</summary>
		///<params>filePath: az input file</params>
		virtual void ParseFile(const std::string& filePath) = 0;

		///<summary>Parser specifikus a fájl egy sorának felbontása kulcs-érték párra.</summary>
		virtual void SplitLine() = 0;

		///<summary>
		/// Parser specifikus, hogy a tárolójának hogy adja vissza egy section-höz tartozó kulcs értékét.
		///</summary>
		virtual std::string GetValue(const std::string& section, const std::string& key) = 0;

		char GetKeyValueSeparator() const;
		void SetKeyValueSeparator(char separator);

		///<summary>
		/// Az egyes sorokban a kulcsokat az értéktõl elválasztó alapértelmezett karakter.
		///</summary>
		static const char DEFAULT_SEPARATOR;

	protected:
		std::string*   m_Content;
		char m_KeyValueSeparator;
	};
}