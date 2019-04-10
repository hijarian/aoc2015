#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

unsigned calc_area(unsigned first_dimension, unsigned second_dimension, unsigned third_dimension)
{
	unsigned first_area = first_dimension * second_dimension;
	unsigned second_area = second_dimension * third_dimension;
	unsigned third_area = third_dimension * first_dimension;

	return 2 * first_area + 2 * second_area + 2 * third_area + std::min({ first_area, second_area, third_area });
}

unsigned calc_length(unsigned first_dimension, unsigned second_dimension, unsigned third_dimension)
{
	unsigned ribbon = 2 * (first_dimension + second_dimension + third_dimension - std::max({ first_dimension, second_dimension, third_dimension }));
	unsigned bow = first_dimension * second_dimension * third_dimension;

	return ribbon + bow;
}


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

	unsigned total_area{};
	unsigned total_length{};

	unsigned first_dimension;
	unsigned second_dimension;
	unsigned third_dimension;

	std::string line;
	while (std::getline(input_file, line))
	{
		std::regex dimensions_regex{ "([0-9]+)x([0-9]+)x([0-9]+)" };
		std::smatch dimensions_regex_match;


		if (!std::regex_match(line, dimensions_regex_match, dimensions_regex))
		{
			std::cerr << "No match for line: " << line << std::endl;
			continue;
		}

		first_dimension = std::stoul(dimensions_regex_match[1]);
		second_dimension = std::stoul(dimensions_regex_match[2]);
		third_dimension = std::stoul(dimensions_regex_match[3]);

		total_area += calc_area(first_dimension, second_dimension, third_dimension);
		total_length += calc_length(first_dimension, second_dimension, third_dimension);
	}

	std::cout << "Total cloth: " << total_area << std::endl;
	std::cout << "Total ribbon: " << total_length << std::endl;

	std::cin.get();

	return 0;
}
