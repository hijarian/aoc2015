#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <set>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Please provide path to input file" << std::endl;
		exit(1);
	}

	std::ifstream input_file(argv[1]);

	if (!input_file.is_open())
	{
		std::cerr << "File has not been opened!" << std::endl;
		exit(2);
	}


	std::string line;
	while (std::getline(input_file, line))
	{
		// TODO
	}

	std::cin.get();

	return 0;
}
