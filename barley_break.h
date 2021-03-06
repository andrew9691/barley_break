#ifndef BARLEY_BREAK
#define BARLEY_BREAK

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

class barley_break
{
	std::vector<std::vector<int>> mat;
	std::vector<std::vector<int>> goal_mat = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 0 } };
	int emp_pos_i;
	int emp_pos_j;
	std::vector<char> solution_moves;
	bool solved;

public:
	barley_break()
	{
		mat.resize(4);
		for (int i = 0; i < 4; i++)
			mat[i].resize(4);
	}

	barley_break(std::vector<std::vector<int>> m)
	{
		mat.resize(4);
		for (int i = 0; i < 4; i++)
			mat[i].resize(4);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] = m[i][j];
				if (mat[i][j] == 0)
				{
					emp_pos_i = i;
					emp_pos_j = j;
				}
			}
				
	}

	void solvable_random_fill(int permuts)
	{
		mat = goal_mat;
		emp_pos_i = 3;
		emp_pos_j = 3;

		for (int i = 0; i < permuts; i++)
		{
			int random_permut = rand() % 4;
			switch (random_permut)
			{
			case 0:
				if (emp_pos_i != 3)
				{
					move_down();
					std::cout << "D ";
				}
				else
					i--;
				break;
			case 1:
				if (emp_pos_i != 0)
				{
					move_up();
					std::cout << "U ";
				}
				else
					i--;
				break;
			case 2:
				if (emp_pos_j != 0)
				{
					move_left();
					std::cout << "L ";
				}
				else
					i--;
				break;
			default:
				if (emp_pos_j != 3)
				{
					move_right();
					std::cout << "R ";
				}
				else
					i--;
				break;
			}
		}
		std::cout << std::endl;
	}

	void print()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				if (this->mat[i][j] == 0)
					std::cout << "  ||";
				else if (this->mat[i][j] < 10)
					std::cout << this->mat[i][j] << " ||";
				else
					std::cout << this->mat[i][j] << "||";
			std::cout << std::endl;
		}
	}

	void move_right()
	{
		if (emp_pos_j == 3)
			return;
		std::swap(mat[emp_pos_i][emp_pos_j], mat[emp_pos_i][emp_pos_j + 1]);
		emp_pos_j++;
	}

	void move_left()
	{
		if (emp_pos_j == 0)
			return;
		std::swap(mat[emp_pos_i][emp_pos_j], mat[emp_pos_i][emp_pos_j - 1]);
		emp_pos_j--;
	}

	void move_up()
	{
		if (emp_pos_i == 0)
			return;
		std::swap(mat[emp_pos_i][emp_pos_j], mat[emp_pos_i - 1][emp_pos_j]);
		emp_pos_i--;
	}

	void move_down()
	{
		if (emp_pos_i == 3)
			return;
		std::swap(mat[emp_pos_i][emp_pos_j], mat[emp_pos_i + 1][emp_pos_j]);
		emp_pos_i++;
	}
	
	int manhattan_dist()
	{
		int res = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				int elem_i, elem_j;
				if (mat[i][j])
				{
					elem_i = (mat[i][j] - 1) / 4;
					elem_j = (mat[i][j] - 1) % 4;
				}
				else
					elem_i = elem_j = 3;
				res += (abs(i - elem_i) + abs(j - elem_j));
			}

		return res;
	}

	int linear_conflict()
	{
		int res = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				for (int k = j + 1; k < 4; k++)
					if ((mat[i][j] != 0 ? mat[i][j] : 15) > (mat[i][k] != 0 ? mat[i][k] : 15))
						res += 2;

		return res;
	}

	inline int heuristics()
	{
		return manhattan_dist() + linear_conflict();
	}

	void ida_star()
	{
		solved = false;
		int deepness = heuristics();
		solution_moves = std::vector<char>();
		std::vector<char> possible_moves = std::vector<char>();
		while (!solved)
		{
			std::cout << deepness << " ";
			deepness = search(possible_moves, 0, deepness, '0');
		}
		std::cout << std::endl;
	}

	int search(std::vector<char> possible_moves, int cur_cost, int deepness, char last_move_from)
	{
		int h = heuristics();
		if (h == 0)
		{
			solved = true;
			solution_moves = possible_moves;
			return cur_cost;
		}

		int f = cur_cost + h;
		if (f > deepness)
			return f;

		int min_deep = deepness;
		std::vector<int> exceeded_tresholds;

		if (last_move_from != 'R' && emp_pos_j != 3)
		{
			move_right();
			possible_moves.emplace_back('R');
			exceeded_tresholds.push_back(search(possible_moves, cur_cost + 1, min_deep, 'L'));
			possible_moves.pop_back();
			move_left();
		}
		if (last_move_from != 'L' && emp_pos_j != 0)
		{
			move_left();
			possible_moves.emplace_back('L');
			exceeded_tresholds.push_back(search(possible_moves, cur_cost + 1, min_deep, 'R')); 
			possible_moves.pop_back();
			move_right();
		}
		if (last_move_from != 'D' && emp_pos_i != 3)
		{
			move_down();
			possible_moves.emplace_back('D');
			exceeded_tresholds.push_back(search(possible_moves, cur_cost + 1, min_deep, 'U'));
			possible_moves.pop_back();
			move_up();
		}
		if (last_move_from != 'U' && emp_pos_i != 0)
		{
			move_up();
			possible_moves.emplace_back('U');
			exceeded_tresholds.push_back(search(possible_moves, cur_cost + 1, min_deep, 'D'));
			possible_moves.pop_back();
			move_down();
		}

		int min = exceeded_tresholds[0];
		for (int i = 1; i < exceeded_tresholds.size(); i++)
			min = exceeded_tresholds[i] < min ? exceeded_tresholds[i] : min;

		return min;
	}

	void print_res()
	{
		for (int i = 0; i < solution_moves.size(); i++)
		{
			switch (solution_moves[i])
			{
			case 'L':
				move_left();
				break;
			case 'R':
				move_right();
				break;
			case 'U':
				move_up();
				break;
			default:
				move_down();
			}
		}

		std::cout << "Moves amount: " << solution_moves.size() << std::endl << std::endl;

		print();
	}

	void print_moves()
	{
		for (int i = 0; i < solution_moves.size(); i++)
			std::cout << solution_moves[i] << " ";
		std::cout << std::endl;
	}
};
#endif
