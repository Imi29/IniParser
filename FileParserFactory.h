#pragma once

#include <chrono>
#include <thread>
#include <sys/stat.h>

#include "IniParser.h"
#include "FileReader.h"

///<summary>
/// FileParser osztály Gyártó tervezési minta alapján. Különbözõ kulcs-érték párokat tartalmazó fájlok parse-olására bõvíthetõ.
/// Minden kapcsolódó osztályban le van tiltva a copy constructor, és az értékadó operátor az egyszerûség kedvéért.
///</summary>

namespace DH
{
	class FileParserFactory final
	{
	public:
		/// <summary>Minden member változót default nullára inicializálunk.</summary>
		FileParserFactory();

		/// <summary>A file polling thread itt várja be a main thread-et, mielõtt megszûnne.</summary>
		~FileParserFactory();


		FileParserFactory(const FileParserFactory&) = delete;
		FileParserFactory(FileParserFactory&&) = delete;

		FileParserFactory& operator=(const FileParserFactory&) = delete;
		FileParserFactory& operator=(FileParserFactory&&) = delete;

		/// <summary>
		/// Fájlok parse-olását végzõ metódus. Az input fájl kiterjesztése alapján eldönti, hogy milyen parser-t kell létrehoznia.
		/// Ha nem talál a kiterjesztésnek megfelelõ parser-t, akkor leáll a program.
		/// Itt bõvíthetõ más parser-ekkel a Gyártó minta, például lehetne még .sys, .cfg, .conf parser is.
		/// A metódus egy külön thread-et indít a file változásának vizsgálatára.
		/// Ha nincs megfelelõ értelmezõ, a program terminál.
		///</summary>
		/// <params>filePath: az input fájl helye</params>
		void ParseFile(const std::string& filePath);

		/// <summary>
		/// A fájl válozását vizsgálja. Megnézi, hogy mikor lett utoljára írva a file.
		/// Ha módosult a korábbi vizsgálathoz képest, akkor újra beolvassa a fájlt, majd fel parse-olja.
		///</summary>
		void FilePolling();

		/// <summary>Visszaadja a file-ból beolvasott (section, key) rendezett párhoz tartozó értéket</summary>
		/// <params>
		/// section: melyik szekció
		/// key:	 melyik kulcs
		/// </params>
		/// <returns>(section;key) rendezett párhoz tartozó érték</returns>
		std::string GetValue(const std::string& section, const std::string& key) const;

		/// <summary>Meghatározza az input file kiterjesztését. Ha nem talál kiterjesztést, üres string-et ad vissza.</summary>
		/// <returns>Az input file kiterjesztése.</returns>
		std::string GetExtension(const std::string& filePath) const;


	private:
		BaseParser*		m_parser;
		std::string		m_FilePath;
		struct stat		m_fileStat;
		bool			m_KillFilePollingthread;
		std::thread		m_FilePollingthread;
	};
}