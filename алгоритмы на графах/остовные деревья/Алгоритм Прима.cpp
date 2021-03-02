/*Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно. 
Следующие m строк содержат описание ребер по одному на строке. 
Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100 000).
n ≤ 5 000, m ≤ 100 000.
Граф является связным.

Найти минимальный вес остовного дерева*/

/*Решение - применяем к нашему графу алгоритм прима.  В начале запихаем в очередь с приоритетом все
ребра первой вершины, отметим первую вершину как посещенную. Будем вытаскивать из очереди ребро,
оно будет иметь мин вес среди всех доступных из нашего остовного дерева ребер. Если вершина, в которую оно ведёт, уже ранее была посещаема, то мы игнорим ребро.
Иначе добавляем ребро и вершину в наше остовное дерево, отмечаем вершину как добалвенную и добавляем в очередь все исходящие из рассматриваемой вершины ребра.*/

#include <queue>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::queue;

struct Edge
{
	Edge(int _end, int _cost)
	{
		end = _end;
		cost = _cost;
	}

	int end;
	int cost;
};

class Compare {
public:
	bool operator() (const Edge& a, const Edge& b) const
	{
		return a.cost > b.cost;
	}
};

int CountAnswer(int N, int M)
{
	std::priority_queue<Edge, vector<Edge>, Compare> nods;
	vector<bool> used;

	vector<vector<Edge> > elements;
	elements.resize(N);
	used.resize(N);

	int start, finish, P;

	int answer = 0;
	for (size_t i = 0; i < M; ++i)
	{
		cin >> start >> finish >> P;
		if (start == finish) continue;
		elements[start - 1].push_back(Edge(finish - 1, P));
		elements[finish - 1].push_back(Edge(start - 1, P));
	}

	used[0] = true;
	for (Edge neighbour : elements[0])
	{
		nods.push(neighbour);
	}

	int vertexes_visited = 1;

	while (vertexes_visited < N && nods.size() > 0)
	{
		Edge present = nods.top();
		nods.pop();

		if (used[present.end] == true) continue;
		answer += present.cost;
		vertexes_visited++;
		used[present.end] = true;

		for (Edge neighbour_of_present : elements[present.end])
		{
			if (used[neighbour_of_present.end] == false)
			{
				nods.push(neighbour_of_present);
			}
		}
	}

	return answer;
}

int main()
{
	int N, M;
	cin >> N >> M;

	cout << CountAnswer(N, M);
}