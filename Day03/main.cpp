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

	std::pair<int, int> current_position_single_santa{ 0, 0 };
	std::set<std::pair<int, int>> visited_positions_single_santa{ std::make_pair(0, 0) };

	bool is_santa_turn{ true };
	std::pair<int, int> current_position_santa{ 0, 0 };
	std::pair<int, int> current_position_robo{ 0, 0 };
	std::set<std::pair<int, int>> visited_positions_santa_robo{ std::make_pair(0, 0) };

	char input;
	while (input_file.get(input))
	{
		if (input == '^')
		{
			++current_position_single_santa.second;
			if (is_santa_turn)
			{
				++current_position_santa.second;
			}
			else
			{
				++current_position_robo.second;
			}
		}
		if (input == '>')
		{
			++current_position_single_santa.first;
			if (is_santa_turn)
			{
				++current_position_santa.first;
			}
			else
			{
				++current_position_robo.first;
			}
		}
		if (input == '<')
		{
			--current_position_single_santa.first;
			if (is_santa_turn)
			{
				--current_position_santa.first;
			}
			else
			{
				--current_position_robo.first;
			}
		}
		if (input == 'v')
		{
			--current_position_single_santa.second;
			if (is_santa_turn)
			{
				--current_position_santa.second;
			}
			else
			{
				--current_position_robo.second;
			}
		}
		//std::cout << input << ": " << current_position_single_santa.first << " " << current_position_single_santa.second << std::endl;
		visited_positions_single_santa.insert(current_position_single_santa);

		if (is_santa_turn)
		{
			visited_positions_santa_robo.insert(current_position_santa);
			//std::cout << input << ": S " << current_position_santa.first << " " << current_position_santa.second << std::endl;
		}
		else
		{
			visited_positions_santa_robo.insert(current_position_robo);
			//std::cout << input << ": R " << current_position_robo.first << " " << current_position_robo.second << std::endl;
		}
		is_santa_turn = !is_santa_turn;
	}

	std::cout << "Single Santa visited houses: " << visited_positions_single_santa.size() << std::endl;

	std::cout << "Santa with Robo-Santa visited houses: " << visited_positions_santa_robo.size() << std::endl;

	std::cin.get();

	return 0;
}
