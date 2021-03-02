/*Рику необходимо попасть на межвселенную конференцию.
 За каждую телепортацию он платит бутылками лимонада, поэтому хочет потратить их на дорогу как можно меньше (он же всё-таки на конференцию едет!).
 Однако после K перелетов подряд Рика начинает сильно тошнить, и он ложится спать на день.
 Ему известны все существующие телепортации. Теперь Рик хочет найти путь (наименьший по стоимости в бутылках лимонада),
 учитывая, что телепортация не занимает времени, а до конференции осталось 10 минут (то есть он может совершить не более K перелетов)!*/

 /*решение. тут я использую обычный алгоритм Беллмана — Форда, но теперь обрываюсь на k-ом шаге и в нужной ячейке получаю ответ,
 ведь в них храняться минимальный вес пути с кол-вом рёбер не больше k на катом шаге */

#include <iostream>
#include <vector>

const size_t infinite = 2000000000000;

using std::vector;
using std::cin;
using std::cout;

struct Vertex {
	Vertex(int _number, int _cost)
	{
		number = _number;
		cost = _cost;
	}

	int number;
	int cost;
};

int TaskAnswer(int N, int M, int K, int S, int F)
{
    --S;
	--F;

	int v1, v2, cost;

	vector<vector<Vertex> > neighbour;
	neighbour.resize(N);

	vector<long long> ways;
	ways.resize(N);

	for (int i = 0; i < N; ++i)
	{
		ways[i] = infinite;
	}

	for (int i = 0; i < M; ++i)
	{
		cin >> v1 >> v2 >> cost;
		neighbour[v2 - 1].push_back(Vertex(v1 - 1, cost));

		if (v1 - 1 == S)
		{
			ways[v2 - 1] = cost;
		}
	}

	for (int i = 0; i < K - 1; ++i)
	{
		for (int j = 0; j < ways.size(); ++j)
		{
			for (int f = 0; f < neighbour[j].size(); f++)
			{
				if (ways[neighbour[j][f].number] + neighbour[j][f].cost < ways[j])
				{
					ways[j] = ways[neighbour[j][f].number] + neighbour[j][f].cost;
				}

			}
		}
	}

	if (ways[F] == infinite)
	{
		return -1;
	}

	return ways[F];
}

int main()
{
	int N, M, K, S, F;

	cin >> N >> M >> K >> S >> F;

    cout << TaskAnswer (N, M, K, S, F);
}
