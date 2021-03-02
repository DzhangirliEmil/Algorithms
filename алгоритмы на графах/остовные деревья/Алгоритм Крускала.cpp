/*Шреку необходимо пробраться в башню, чтобы спасти прекрасную принцессу Фиону.
И сейчас его путь лежит через старый полуразвалившийся мост. 
Осёл очень боится упасть с этого моста в лавовую реку под ним и отказывается идти дальше, пока мост не будет полностью починен. 
Шрек не может идти без друга и решил отремонтировать его.
Мост представляет собой поле из n × m клеток, причем некоторые клетки ещё остались целыми. 
У Шрека есть только дощечки размера 1 × 2, установка которых занимает у него a секунд, и 1 × 1, установка которых занимает b секунд. 
Ему необходимо закрыть все пустые клетки, причем только их, не накладывая дощечки друг на друга.

Определите, через какое минимальное количество секунд Шрек и Осёл смогут продолжить свой путь дальше.*/

/*Решение: 
утверждение - в итоговом остове не может быть не специальных рёбер, которые не проходят через вершину с минимальным весом.
Док-во: предположим, что это не так, и такая вершина есть в итоговом остове.
Т.к. это остов, то при убирании этого ребра кол-во компонент связности увеличится.
И так, пусть она соединяет вершины a и b. Тогда найдём минимальную вершину c.
Если c и a лежат в одной компоненте, то ab можно заменить на ca. компонента связности будет одна,
а цена ребра уменшится. если же c лежит с b, то меняем ab на cb, аналогично. То есть мы уменьшили цену остова.
быть не может.
То есть освтов может состоять только из специальных предложений и рёбер, проходящих через минимальную вершину.
На них я и запускаю крускала*/

#include <queue>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::queue;

class DSU {
public:
	DSU(size_t n)
	{
		parents.resize(n);
		ranks.resize(n);
	}

	void MakeSet(size_t x)
	{
		parents[x] = x;
	}

	int Find(size_t x)
	{
		if (parents[x] == x) return x;
		return parents[x] = Find(parents[x]);
	}

	void Unite(size_t x, size_t y)
	{
		x = Find(x);
		y = Find(y);
		if (ranks[x] < ranks[y])
		{
			parents[x] = y;
		}
		else
		{
			parents[y] = x;
			if (ranks[x] == ranks[y])
			{
				++ranks[x];
			}	
		}
	}

private:
	vector<size_t> parents;
	vector<size_t> ranks;
};

struct Edge
{
	Edge(size_t _start, size_t _end, size_t _cost)
	{
		start = _start;
		end = _end;
		cost = _cost;
	}

	int start;
	int end;
	size_t cost;
};

class Compare {
public:
	bool operator() (const Edge& a, const Edge& b) const
	{
		return a.cost > b.cost;
	}
};

size_t CountAnswer(size_t N, size_t M)
{
	std::priority_queue<Edge, vector<Edge>, Compare> edges;
	DSU components(N);

	size_t start, finish, P;
	vector<size_t> a;
	a.resize(N);



	size_t min_index = 0; //индекс минимальной вершины
	for (size_t i = 0; i < N; ++i)
	{
		cin >> a[i];
		if (a[i] <= a[min_index])
		{
			min_index = i;
		}
	}

	//добавляю спецпредложения
	size_t answer = 0;
	for (size_t i = 0; i < M; ++i)
	{
		cin >> start >> finish >> P;
		if (P < a[start - 1] + a[finish - 1])
		{
			edges.push(Edge(start - 1, finish - 1, P));
		}
	}

	//добавляю ребра из минимальной вершины
	for (size_t i = 0; i < N; ++i)
	{
		if (i != min_index) edges.push(Edge(min_index, i, a[min_index] + a[i]));
	}


	//создаю множества
	for (size_t i = 0; i < N; i++)
	{
		components.MakeSet(i);
	}


	size_t edges_added = 0;
	while (edges_added < N - 1)
	{
		Edge present = edges.top();
		edges.pop();

		if (components.Find(present.start) == components.Find(present.end))
		{
			continue;
		}

		++ edges_added;
		components.Unite(present.start, present.end);

		answer += present.cost;
	}

	return answer;
}

int main()
{
	size_t N, M;
	cin >> N >> M;

	cout << CountAnswer(N, M);
}