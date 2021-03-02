/*Задано дерево с корнем, содержащее (1 ≤ n ≤ 100 000) вершин, пронумерованных от 0 до n-1.
Требуется ответить на m (1 ≤ m ≤ 10 000 000) запросов о наименьшем общем предке для пары вершин.
Запросы генерируются следующим образом. Заданы числа a1, a2 и числа x, y и z.
Числа a3, ..., a2m генерируются следующим образом: ai = (x ⋅ ai-2 + y ⋅ ai-1 + z) mod n.
Первый запрос имеет вид (a1, a2). Если ответ на i-1-й запрос равен v, то i-й запрос имеет вид ((a2i-1 + v) mod n, a2i).

Для решения задачи можно использовать метод двоичного подъёма.*/

/*Решение - ну я и использую метод двоичного подъема :)*/


#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

class LCA
{
public:
	LCA(const vector<int>& parents_)
	{
		log_size = Log(parents_.size());
		parents.resize(parents_.size());

		time_in.resize(parents_.size());
		time_out.resize(parents_.size());

		for (int i = 0; i < parents.size(); ++i)
		{
			parents[i].resize(log_size + 1);
		}

		children.resize(parents_.size());
		for (int i = 1; i < parents_.size(); ++i)
		{
			children[parents_[i]].push_back(i);
		}

		dfs(0, 0);
	}

	int Lca(int left, const int& right)
	{
		if (Upper(left, right))
		{
			return left;
		}

		if (Upper(right, left))
		{
			return right;
		}

		for (int i = log_size; i >= 0; --i)
		{
			if (!Upper(parents[left][i], right))
			{
				left = parents[left][i];
			}

		}

		return parents[left][0];
	}
private:
	vector<vector<int>> parents;
	vector<vector<int>> children;

	int help_time = 0;
	int log_size;
	vector<int> time_in, time_out;

	int Log(const int& n)
	{
		int answer = 1;
		while ((1 << answer) <= n)  ++answer;
		return answer;
	}

	void dfs(const int& vertex, const int& current_parrent)
	{
		time_in[vertex] = ++help_time;
		parents[vertex][0] = current_parrent;

		for (int i = 1; i <= log_size; ++i)
		{
			parents[vertex][i] = parents[parents[vertex][i - 1]][i - 1];
		}

		for (int child : children[vertex])
		{
			if (child != current_parrent)
			{
				dfs(child, vertex);
			}
		}
		time_out[vertex] = ++help_time;
	}

	bool Upper(const int& first, const int& second)
	{
		return ((time_out[first] >= time_out[second]) && (time_in[first] <= time_in[second]));
	}
};

int main()
{
	int n, a1, a2;
	long x, y, z;

	long m;

	cin >> n >> m;

	vector<int> parents(n);

	parents[0] = 0;
	for (int i = 1; i < n; ++i)
	{
		cin >> parents[i];
	}

	LCA tree(parents);

	cin >> a1 >> a2 >> x >> y >> z;

	long long first = a1;
	long long second = a2;

	long answer = tree.Lca(a1, a2);
	long sum = answer;

	for (long i = 1; i < m; ++i)
	{
		first = (first*x + second * y + z) % n;
		second = (second*x + first * y + z) % n;

		answer = tree.Lca((first + answer) % n, second);
		sum += answer;
	}

	cout << sum;
}