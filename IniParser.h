#pragma once

#include <map>

#include "ParserBase.h"

namespace DH
{
	typedef std::string SECTION;
	typedef std::string KEY;
	typedef std::string VALUE;

	typedef std::map<SECTION, std::map<KEY, VALUE>> INIMAP;

	///<summary>Az ini file-ok elemz�s�t v�gz� oszt�ly.</summary>
	class IniParser : public BaseParser
	{
	public:
		IniParser() = default;
		~IniParser() = default;

		IniParser(const IniParser&) = delete;
		IniParser(IniParser&&) = delete;

		IniParser& operator=(const IniParser&) = delete;
		IniParser& operator=(IniParser&&) = delete;

		///<summary>Beolvassa a f�jlt, majd fel is bontja kulcs-�rt�k p�rokra.</summary>
		///<params>Beolvassa a f�jlt, majd fel is bontja kulcs-�rt�k p�rokra.</params>
		virtual void ParseFile(const std::string& filePath) override;

		///<summary>
		/// Egy kiolvasott sorr�l eld�nti, hogy section, vagy key-value p�r-e.
		/// Minden esetben trim-eli a kiolvasott sort.
		/// Csak akkor fogadja el section-nek, ha a sor '[', ']' karakterek k�z�tt van. A n�v n�lk�li, vagy �res section megengedett.
		/// Ha k�s�bb egy m�r l�tez� section-t tal�l fel�l�rja a kor�bbit.
		/// �res kulcsok nem megendettek.
		/// Ha se nem section, se nem kulcs, akkor megvizsg�lja, hogy komment-e, ha nem komment, �rv�nytelen a file.
		/// A kommenteknek k�l�n sorban kell lenni�k.
		///</summary>
		virtual void SplitLine() override;

		///<summary>Visszaadja az adott section-h�z �s key-hez tartoz� �rt�ket.</summary>
		virtual std::string GetValue(const std::string& section, const std::string& key) override;

		///<summary>Trim-eli a kapott sort.</summary>
		///<params>content: az ini file egy sora</params>
		void TrimContent(std::string& content);

		///<summary>Eld�nti, hogy az adott sor �rv�nyes section-e.</summary>
		bool IsSection() const;

		///<summary>Eld�nti a separator alapj�n, hogy az adott sor �rv�nyes kulcs-�rt�k p�r-e.</summary>
		bool IsKeyValuePair() const;

		///<summary>Eld�nti, hogy az adott sor komment-e.</summary>
		bool IsComment() const;

		///<summary>Elmenti a kiolvasott section-t a t�rol�j�ba.</summary>
		inline void InsertSectionToContainer();

		///<summary>Elmenti a kiolvasott key-value p�rt a t�rol�j�ba.</summary>
		inline void InsertKeyValueToContainer();

	private:

		INIMAP  m_entry;
		SECTION m_CurrentSection;

	};
}