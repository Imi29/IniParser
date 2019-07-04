#include "FileParserFactory.h"


int main()
{
	DH::FileParserFactory factory;
	factory.ParseFile("test1.ini");

	int cntr = 0;
	while (cntr < 5)
	{
		std::string value1 = factory.GetValue("Elso", "Kulcs1");
		std::string value2 = factory.GetValue("Elso", "Kulcs2");
		std::string value3 = factory.GetValue("Elso", "Kulcs3");
		std::string value4 = factory.GetValue("Elso", "Kulcs4");

		std::cout << value1 << std::endl;
		std::cout << value2 << std::endl;
		std::cout << value3 << std::endl;
		std::cout << value4 << std::endl;

		std::string value5 = factory.GetValue("Masodik", "KulcsM1");
		std::string value6 = factory.GetValue("Masodik", "KulcsM2");
		std::string value7 = factory.GetValue("Masodik", "KulcsM3");
		std::string value8 = factory.GetValue("Masodik", "KulcsM4");

		std::cout << value5 << std::endl;
		std::cout << value6 << std::endl;
		std::cout << value7 << std::endl;
		std::cout << value8 << std::endl;

		std::cout << std::endl;

		std::cin.get();
		cntr++;
	}

	return 0;
}