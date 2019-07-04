#pragma once

#include <map>

#include "ParserBase.h"

namespace DH
{
	typedef std::string SECTION;
	typedef std::string KEY;
	typedef std::string VALUE;

	typedef std::map<SECTION, std::map<KEY, VALUE>> INIMAP;

	///<summary>Az ini file-ok elemzését végzõ osztály.</summary>
	class IniParser : public BaseParser
	{
	public:
		IniParser() = default;
		~IniParser() = default;

		IniParser(const IniParser&) = delete;
		IniParser(IniParser&&) = delete;

		IniParser& operator=(const IniParser&) = delete;
		IniParser& operator=(IniParser&&) = delete;

		///<summary>Beolvassa a fájlt, majd fel is bontja kulcs-érték párokra.</summary>
		///<params>Beolvassa a fájlt, majd fel is bontja kulcs-érték párokra.</params>
		virtual void ParseFile(const std::string& filePath) override;

		///<summary>
		/// Egy kiolvasott sorról eldönti, hogy section, vagy key-value pár-e.
		/// Minden esetben trim-eli a kiolvasott sort.
		/// Csak akkor fogadja el section-nek, ha a sor '[', ']' karakterek között van. A név nélküli, vagy üres section megengedett.
		/// Ha késõbb egy már létezõ section-t talál felülírja a korábbit.
		/// Üres kulcsok nem megendettek.
		/// Ha se nem section, se nem kulcs, akkor megvizsgálja, hogy komment-e, ha nem komment, érvénytelen a file.
		/// A kommenteknek külön sorban kell lenniük.
		///</summary>
		virtual void SplitLine() override;

		///<summary>Visszaadja az adott section-höz és key-hez tartozó értéket.</summary>
		virtual std::string GetValue(const std::string& section, const std::string& key) override;

		///<summary>Trim-eli a kapott sort.</summary>
		///<params>content: az ini file egy sora</params>
		void TrimContent(std::string& content);

		///<summary>Eldönti, hogy az adott sor érvényes section-e.</summary>
		bool IsSection() const;

		///<summary>Eldönti a separator alapján, hogy az adott sor érvényes kulcs-érték pár-e.</summary>
		bool IsKeyValuePair() const;

		///<summary>Eldönti, hogy az adott sor komment-e.</summary>
		bool IsComment() const;

		///<summary>Elmenti a kiolvasott section-t a tárolójába.</summary>
		inline void InsertSectionToContainer();

		///<summary>Elmenti a kiolvasott key-value párt a tárolójába.</summary>
		inline void InsertKeyValueToContainer();

	private:

		INIMAP  m_entry;
		SECTION m_CurrentSection;

	};
}