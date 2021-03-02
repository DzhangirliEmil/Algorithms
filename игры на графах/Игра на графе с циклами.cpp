/*Два игрока играют в настольную игру. Игровое поле представляет собой квадратный лабиринт, 
8× 8 клеток. В некоторых клетках располагаются стенки. Один игрок управляет фишкой-терминатором, 
а второй — фишкой-беглецом. Игроки ходят по очереди, ходы пропускать нельзя
 (гарантируется, что ход всегда возможен). За один ход игрок может переместить
 свою фишку в любую из свободных клеток, расположенных рядом с исходной по горизонтали,
 вертикали или по диагонали (то есть ходом короля).
 Терминатор, кроме того, может стрелять в беглеца ракетами. 
Выстрел идет по прямой в любом направлении по горизонтали, вертикали или диагонали.
 Если беглец оказывается на линии выстрела терминатора и не прикрыт стенками,
 то терминатор незамедлительно делает выстрел (вне зависимости от того, чей ход),
 и беглец проигрывает. Начальное положение фишек задано. Первый ход делает беглец. 
Он выигрывает, если сделает ход с восьмой строки за пределы игрового поля,
 так как остальные границы поля окружены стенками.

Вопрос задачи: может ли беглец выиграть при оптимальной игре обеих сторон?

Формат ввода
Во входном файле задано игровое поле. Свободная клетка обозначена цифрой 0, а клетка со стенкой — цифрой 1. Клетка, в которой находится беглец, обозначена цифрой 2, а клетка с терминатором — цифрой 3.

Формат вывода
В выходной файл выведите число 1, если беглец выигрывает, и -1 — в противном случае.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using std::vector;
using std::unordered_map;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::string;


const int field_size = 8;

struct situation
{
	int man_x, man_y;
	int rob_x, rob_y;
	int turn = 0;

	int loose = -1;
	int degree;

	int get_hash()
	{
		return turn * 10000 + rob_y * 1000 + rob_x * 100 + man_y * 10 + man_x;
	}

	vector<int> neighbour;
};

bool IsLoose(int array[field_size][field_size], situation sit)
{
	if (sit.man_x == sit.rob_x && sit.rob_y == sit.man_y)
	{
		return true;
	}
	if (sit.man_x == sit.rob_x)
	{
		bool is_wall = false;
		for (int i = min(sit.man_y, sit.rob_y) + 1; i < max(sit.man_y, sit.rob_y); i++)
		{
			if (array[sit.man_x][i] == 1)
			{
				is_wall = true;
				break;
			}
		}

		if (is_wall == false)
		{
			return true;
		}
	}

	if (sit.man_y == sit.rob_y)
	{
		bool is_wall = false;
		for (int i = min(sit.man_x, sit.rob_x) + 1; i < max(sit.man_x, sit.rob_x); i++)
		{
			if (array[i][sit.man_y] == 1)
			{
				is_wall = true;
			}
		}

		if (is_wall == false)
		{
			return true;
		}
	}

	if (abs(sit.man_x - sit.rob_x) == abs(sit.man_y - sit.rob_y))
	{
		bool is_wall = false;

		int k = (sit.man_x - sit.rob_x)*(sit.man_y - sit.rob_y);
		if (k > 0)
		{
			for (int i = 0; i < abs(sit.man_y - sit.rob_y); ++i)
			{
				if (array[min(sit.man_x, sit.rob_x) + i][min(sit.man_y, sit.rob_y) + i] == 1)
				{
					is_wall = true;
					break;
				}
			}
		}

		else
		{
			for (int i = 0; i < abs(sit.man_y - sit.rob_y); ++i)
			{
				if (array[min(sit.man_x, sit.rob_x) + i][max(sit.man_y, sit.rob_y) - i] == 1)
				{
					is_wall = true;
					break;
				}
			}
		}


		if (is_wall == false)
		{
			return true;
		}
	}

	return false;
}
vector<int> GetNeighbours(int array[field_size][field_size], situation sit)
{
	vector<int> answer;
	int x, y;
	if (sit.turn == 1)
	{
		x = sit.man_x;
		y = sit.man_y;
	}

	else
	{
		x = sit.rob_x;
		y = sit.rob_y;
	}

	int delta_x[8] = { 1,  1,  1,  0,  0, -1, -1, -1 };
	int delta_y[8] = { 1,  0, -1,  1, -1,  0,  1, -1 };

	for (int i = 0; i < 8; ++i)
	{
		if (x + delta_x[i] >= 0 && x + delta_x[i] < field_size)
		{
			if (y + delta_y[i] >= 0 && y + delta_y[i] < field_size)
			{
				if (array[x + delta_x[i]][y + delta_y[i]] == 0)
				{
					if (sit.turn == 0)
					{
						int neighbour = 10000 + 1000 * (y + delta_y[i]) + 100 * (x + delta_x[i]) + sit.man_y * 10 + sit.man_x;
						answer.push_back(neighbour);
					}

					else
					{
						int neighbour = 1000 * sit.rob_y + 100 * sit.rob_x + 10 * (y + delta_y[i]) + x + delta_x[i];
						answer.push_back(neighbour);
					}
				}
			}
		}
	}

	return answer;
}

void Dfs(unordered_map<int, situation>& s, int array[field_size][field_size], situation sit)
{
	if (s[sit.get_hash()].loose == -1)
	{
		s[sit.get_hash()].loose = -2;
	}

	for (int connected_vertex : s[sit.get_hash()].neighbour)
	{
		if (s[connected_vertex].loose == -1)
		{
			if (s[sit.get_hash()].loose == 1)
			{
				s[connected_vertex].loose = 0;
			}

			else
			{
				if (--s[connected_vertex].degree == 0)
				{
					s[connected_vertex].loose = 1;
				}

				else
				{
					continue;
				}
			}

			Dfs(s, array, s[connected_vertex]);
		}
	}
}

bool GetAnswer(string helpstr[field_size])
{
	int array[field_size][field_size];
	unordered_map<int, situation> s;
	situation start;
	for (int i = 0; i < field_size; ++i)
	{
		for (int j = 0; j < field_size; ++j)
		{
			array[i][j] = helpstr[j][i] - '0';

			if (array[i][j] == 2)
			{
				start.man_x = i;
				start.man_y = j;
				start.turn = 0;

				array[i][j] = 0;
			}

			if (array[i][j] == 3)
			{
				start.rob_x = i;
				start.rob_y = j;

				array[i][j] = 0;
			}
		}
	}

	situation sit;


	for (int m1 = 0; m1 < field_size; ++m1)
	{
		for (int m2 = 0; m2 < field_size; ++m2)
		{
			for (int r1 = 0; r1 < field_size; ++r1)
			{
				for (int r2 = 0; r2 < field_size; ++r2)
				{
					if (array[m1][m2] == 0 && array[r1][r2] == 0)
					{
						situation n;
						n.man_x = m1;
						n.man_y = m2;
						n.rob_x = r1;
						n.rob_y = r2;

						n.turn = 0;
						n.neighbour = GetNeighbours(array, n);
						n.degree = 0;
						if (n.man_y == field_size - 1) n.loose = 0;
						if (IsLoose(array, n)) n.loose = 1;
						s[n.get_hash()] = n;


						n.loose = -1;
						n.turn = 1;


						n.neighbour = GetNeighbours(array, n);
						n.degree = 0;
						if (IsLoose(array, n))
						{
							n.loose = 0;
						}

						s[n.get_hash()] = n;
					}
				}
			}
		}
	}



	for (auto& elem : s)
	{
		for (int connected_vertexdi : elem.second.neighbour)
		{
			s[connected_vertexdi].degree++;
		}
	}

	vector<situation> win_vertexes;
	for (auto t : s)
	{
		if (t.second.loose >= 0)
		{
			win_vertexes.push_back(t.second);
		}
	}

	for (auto t : win_vertexes)
	{
		Dfs(s, array, t);
	}

	if (s[start.get_hash()].loose == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	string helpstr[field_size];

	for (int i = 0; i < field_size; ++i)
	{
		cin >> helpstr[i];
	}

	bool win = GetAnswer(helpstr);

	if (win)
	{
		cout << 1;
	}
	else
	{
		cout << -1;
	}

}