#include <iostream>
#include "wallet.h"

bool is_number(std::string_view str);

int main(uint32_t argc, const char** cargv)
{
	Wallet wallet;
	std::string argv[4];
	for (uint32_t i = 0; i < argc; i++)
		argv[i] = cargv[i];

	switch (argc)
	{
		case 2:
		{
			if (argv[1] == "log")
				std::cout << wallet.get_log();
			else if (argv[1] == "overall")
				std::cout << wallet.get_overall();
			else if (argv[1] == "clear")
				wallet.clear();
			else
			{
				std::cout << "Invalid command\n";
				system("PAUSE");
				return EXIT_SUCCESS;
			}
		}
		break;
		case 3: case 4: 
		{
			if (is_number(argv[1]))
			{
				if (argv[2] == "cash" || argv[2] == "card")
					wallet.insert(std::stoi(argv[1]), argv[2], argc == 4 ? argv[3] : "");
				else
					std::cout << "Invalid wallet type\n";
			}
			else
				std::cout << "It's not a number\n";
		}
		break;
	}

	wallet.write();
	return EXIT_SUCCESS;
}

bool is_number(std::string_view str)
{
	std::string_view::iterator iter = str.begin();
	while (iter != str.end() && std::isdigit(*iter))
		iter++;
	return !str.empty() && iter == str.end();
}
