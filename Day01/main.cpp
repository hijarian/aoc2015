#include <iostream>
#include <fstream>
#include <string>

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

	int basement_position{};
	int position{0};
	int sum{};
	char input{};
	while (input_file.get(input))
	{
		++position;
		std::cout << position << ": " << input << ": " << sum;

		if (input == '(')
		{
			++sum;
			std::cout << " +1 = " << sum << std::endl;
		}
		if (input == ')')
		{
			--sum;
			std::cout << " -1 = " << sum << std::endl;
		}
		if (sum == -1 && basement_position == 0)
		{
			basement_position = position;
		}
	}

	std::cout << "Final floor: " << sum << std::endl;
	std::cout << "First basement visit position: " << basement_position << std::endl;
	std::cin.get();
}