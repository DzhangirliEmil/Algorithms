/*Шреку необходимо пробраться в башню, чтобы спасти прекрасную принцессу Фиону.
И сейчас его путь лежит через старый полуразвалившийся мост. 
Осёл очень боится упасть с этого моста в лавовую реку под ним и отказывается идти дальше, 
пока мост не будет полностью починен. Шрек не может идти без друга и решил отремонтировать его.

Мост представляет собой поле из n × m клеток, 
причем некоторые клетки ещё остались целыми.
У Шрека есть только дощечки размера 1 × 2, установка которых занимает у него a секунд, и 1 × 1,
установка которых занимает b секунд. Ему необходимо закрыть все пустые клетки, причем только их, не накладывая дощечки друг на друга.

Определите, через какое минимальное количество секунд Шрек и Осёл смогут продолжить свой путь дальше.*/

/*Решение - пусть пустые клетки - вершины некого графа, ребра - тот факт, что
клетки соседи (то есть можно поставить плитку 2*1). То есть ребра не могут быть смежными,
ибо плитки не должны пересекаться.
Очевидно, что граф двудольный. К примеру, можно сделать чёрнобелую покраску.
Черные не имеют грань с белыми, и наоборот.
И так, если выгодно ставить одинарные плитки, их и поставим. Иначе надо максимизировать плитки 2*1.
То есть найти максимальное кол-во паросочетаний в графе. Что я и делаю при помощи алгоритма Куна*/

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

void Fill(vector<int>& mas, int filling)
{
	for (int i = 0; i < mas.size(); i++)
	{
		mas[i] = filling;
	}
}

void Fill(vector<bool>& mas, int filling)
{
	for (int i = 0; i < mas.size(); i++)
	{
		mas[i] = filling;
	}
}

bool dfs(int vertex, vector<bool>& used, vector<vector<int>>& neighbours, vector<int>& matching)
{
	if (used[vertex] == true)
	{
		return false;
	}

	used[vertex] = true;

	for (int to : neighbours[vertex])
	{
		if (matching[to] == -1 or dfs(matching[to], used, neighbours, matching))
		{
			matching[to] = vertex;
			return true;
		}
	}

	return false;
}

int Solution(int n, int m, int a, int b)
{
	vector<vector<int>> most;
	most.resize(n);
	for (int i = 0; i < most.size(); ++i)most[i].resize(m);

	string help_string;

	int empty = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> help_string;

		for (int j = 0; j < help_string.size(); j++)
		{
			if (help_string[j] == '*')
			{
				most[i][j] = empty;
				empty++;
			}
			else
			{
				most[i][j] = -1;
			}
		}
	}

	if (2 * b <= a)
	{
		cout << empty * b;
	}

	else
	{
		vector<bool> used;
		used.resize(empty);

		vector<vector<int>> neighbours;
		neighbours.resize(empty);

		vector<int> matching;
		matching.resize(empty);


		for (int i = 0; i < n - 1; ++i)
		{
			for (int j = 0; j < m; ++j)
			{

				if (most[i][j] != -1)
				{
					if (most[i + 1][j] != -1)
					{
						neighbours[most[i][j]].push_back(most[i + 1][j]);
						neighbours[most[i + 1][j]].push_back(most[i][j]);
					}
				}

			}
		}
		for (int j = 0; j < m - 1; ++j)
		{
			for (int i = 0; i < n; ++i)
			{
				if (most[i][j] != -1)
				{
					if (most[i][j + 1] != -1)
					{
						neighbours[most[i][j]].push_back(most[i][j + 1]);
						neighbours[most[i][j + 1]].push_back(most[i][j]);
					}
				}
			}
		}

		Fill(matching, -1);

		for (int i = 0; i < empty; ++i)
		{
			Fill(used, false);
			dfs(i, used, neighbours, matching);
		}

		int a_plitki = 0;
		for (int i = 0; i < empty; ++i)
		{
			if (matching[i] != -1)
			{
				a_plitki++;
			}
		}

		a_plitki /= 2;

		int b_plitki = empty - a_plitki * 2;

		return (b_plitki*b + a_plitki * a);
	}
}



int main()
{
	int n, m;
	int a, b;

	cin >> n >> m >> a >> b;

	cout << solution(n, m, a, b);
}