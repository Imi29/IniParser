#pragma once

#include <chrono>
#include <thread>
#include <sys/stat.h>

#include "IniParser.h"
#include "FileReader.h"

///<summary>
/// FileParser oszt�ly Gy�rt� tervez�si minta alapj�n. K�l�nb�z� kulcs-�rt�k p�rokat tartalmaz� f�jlok parse-ol�s�ra b�v�thet�.
/// Minden kapcsol�d� oszt�lyban le van tiltva a copy constructor, �s az �rt�kad� oper�tor az egyszer�s�g kedv��rt.
///</summary>

namespace DH
{
	class FileParserFactory final
	{
	public:
		/// <summary>Minden member v�ltoz�t default null�ra inicializ�lunk.</summary>
		FileParserFactory();

		/// <summary>A file polling thread itt v�rja be a main thread-et, miel�tt megsz�nne.</summary>
		~FileParserFactory();


		FileParserFactory(const FileParserFactory&) = delete;
		FileParserFactory(FileParserFactory&&) = delete;

		FileParserFactory& operator=(const FileParserFactory&) = delete;
		FileParserFactory& operator=(FileParserFactory&&) = delete;

		/// <summary>
		/// F�jlok parse-ol�s�t v�gz� met�dus. Az input f�jl kiterjeszt�se alapj�n eld�nti, hogy milyen parser-t kell l�trehoznia.
		/// Ha nem tal�l a kiterjeszt�snek megfelel� parser-t, akkor le�ll a program.
		/// Itt b�v�thet� m�s parser-ekkel a Gy�rt� minta, p�ld�ul lehetne m�g .sys, .cfg, .conf parser is.
		/// A met�dus egy k�l�n thread-et ind�t a file v�ltoz�s�nak vizsg�lat�ra.
		/// Ha nincs megfelel� �rtelmez�, a program termin�l.
		///</summary>
		/// <params>filePath: az input f�jl helye</params>
		void ParseFile(const std::string& filePath);

		/// <summary>
		/// A f�jl v�loz�s�t vizsg�lja. Megn�zi, hogy mikor lett utolj�ra �rva a file.
		/// Ha m�dosult a kor�bbi vizsg�lathoz k�pest, akkor �jra beolvassa a f�jlt, majd fel parse-olja.
		///</summary>
		void FilePolling();

		/// <summary>Visszaadja a file-b�l beolvasott (section, key) rendezett p�rhoz tartoz� �rt�ket</summary>
		/// <params>
		/// section: melyik szekci�
		/// key:	 melyik kulcs
		/// </params>
		/// <returns>(section;key) rendezett p�rhoz tartoz� �rt�k</returns>
		std::string GetValue(const std::string& section, const std::string& key) const;

		/// <summary>Meghat�rozza az input file kiterjeszt�s�t. Ha nem tal�l kiterjeszt�st, �res string-et ad vissza.</summary>
		/// <returns>Az input file kiterjeszt�se.</returns>
		std::string GetExtension(const std::string& filePath) const;


	private:
		BaseParser*		m_parser;
		std::string		m_FilePath;
		struct stat		m_fileStat;
		bool			m_KillFilePollingthread;
		std::thread		m_FilePollingthread;
	};
}