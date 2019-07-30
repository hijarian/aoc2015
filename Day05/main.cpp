#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <set>

bool is_nice_old(std::string input)
{
	bool has_three_vowels{ false };
	bool has_double_letters{ false };
	bool does_not_have_prohibited_syllables{ false };

	unsigned vowels_count{ 0 };
	char previous_character{ 0 };
	for (char character : input)
	{
		if (character == 'a' || character == 'o' || character == 'e' || character == 'u' || character == 'i')
		{
			++vowels_count;
		}
		if (character == previous_character)
		{
			has_double_letters = true;
		}

		if ((previous_character == 'a' && character == 'b')
			|| (previous_character == 'c' && character == 'd')
			|| (previous_character == 'p' && character == 'q')
			|| (previous_character == 'x' && character == 'y'))
		{
			return false;
		}

		previous_character = character;
	}
	has_three_vowels = vowels_count > 2;

	return has_three_vowels && has_double_letters;
}

bool is_nice_new(std::string input)
{
	if (input.length() < 4) {
		return false;
	}

	bool has_two_pairs{ false };
	char first_char;
	char second_char;
	char third_char;
	char fourth_char;
	for (unsigned first_pair_counter = 0; first_pair_counter < input.length() - 2; ++first_pair_counter)
	{
		first_char = input[first_pair_counter];
		second_char = input[first_pair_counter + 1];
		for (unsigned second_pair_counter = first_pair_counter + 2; second_pair_counter < input.length(); ++second_pair_counter)
		{
			third_char = input[second_pair_counter];
			fourth_char = input[second_pair_counter + 1];

			if (first_char == third_char && second_char == fourth_char)
			{
				has_two_pairs = true;
				goto next_check;
			}
		}
	}
next_check:
	bool has_letter_in_between{ false };
	for (unsigned counter = 0; counter < input.length() - 2; ++counter)
	{
		if (input[counter] == input[counter + 2])
		{
			has_letter_in_between = true;
			break;
		}
	}
	return has_two_pairs && has_letter_in_between;
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

	unsigned nice_strings_count_old{ 0 };
	unsigned nice_strings_count_new{ 0 };
	std::string line;
	while (std::getline(input_file, line))
	{
		if (is_nice_old(line))
		{
			++nice_strings_count_old;
		}
		if (is_nice_new(line))
		{
			++nice_strings_count_new;
		}
	}

	std::cout << "qjhvhtzxzqqjkmpb:  " << is_nice_new("qjhvhtzxzqqjkmpb") << std::endl;
	std::cout << "xxyxx:  " << is_nice_new("xxyxx") << std::endl;
	std::cout << "uurcxstgmygtbstg:  " << is_nice_new("uurcxstgmygtbstg") << std::endl;
	std::cout << "ieodomkazucvgmuy:  " << is_nice_new("ieodomkazucvgmuy") << std::endl;
	std::cout << "Nice strings count (old method): " << nice_strings_count_old << std::endl;
	std::cout << "Nice strings count (new method): " << nice_strings_count_new << std::endl;

	std::cin.get();

	return 0;
}
