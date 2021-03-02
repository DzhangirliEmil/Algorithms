/*Рик и Морти снова бороздят просторы вселенных, но решили ограничиться только теми, номера которых меньше M.
Они могут телепортироваться из вселенной с номером z во вселенную (z+1) mod M за a бутылок лимонада
 или во вселенную (z2+1) mod M за b бутылок лимонада.
  Рик и Морти хотят добраться из вселенной с номером x во вселенную с номером y.
  Сколько бутылок лимонада отдаст Рик за такое путешествие, если он хочет потратить их как можно меньше? */

/*решение - в задаче использую алгоритм Дейкстры с маленькой модернизацией.
Всех соседей уже рассмотренных вершин я запихиваю в приоритетную очередь. Когда я извлекаю минимум из приоритетной очереди, то проверяю, вытаскивал ли его ранее.
Если вытаскивал, то забиваю и иду дальше. Если не вытаскивал, то делаю с ним все необходимые операции
а потом отмечаю, что его использовал.
Всё остальное как в Дейкстре*/

#include <iostream>
#include <vector>
#include <queue>

const size_t infinity = 2000000000;

using std::vector;
using std::cout;
using std::cin;

struct Nod
{
	Nod(size_t name_, size_t _way)
	{
		name = name_;
		way = _way;
	}

	size_t name;
	size_t way;
};

class Compare {
public:
	bool operator() (const Nod& a, const Nod& b) const
	{
		return a.way > b.way;
	}
};

struct Sosed
{
	Sosed(size_t _nomber, size_t _cost)
	{
		cost = _cost;
		nomber = _nomber;
	}

	size_t nomber = 0;
	size_t cost = 0;
};

long long Minimum(const size_t& a, const size_t& b)
{
	if (a < b) return a;
	return b;

}

int CountAnswer(size_t a, size_t b, size_t M, size_t x, size_t y)
{
    std::priority_queue<Nod, vector<Nod>, Compare> nods;

	vector<bool> used;
	vector<size_t> ways;
	used.resize(M);
	ways.resize(M);

	for (int i = 0; i < M; ++i)
	{
		used[i] = false;
		ways[i] = infinity;
	}

	ways[x] = 0;

	for (int i = 0; i < M; ++i)
	{
		if (i == x) nods.push(Nod(i, 0));
		else nods.push(Nod(i, infinity));
	}

	vector<vector<Sosed> > elements;
	elements.resize(M);

	elements[0].push_back(Sosed(1, Minimum(a, b)));

	for (size_t i = 1; i < elements.size(); ++i)
	{
		elements[i].push_back(Sosed((i + 1) % M, a));
		elements[i].push_back(Sosed((i*i + 1) % M, b));
	}

	size_t answer;


	while (nods.empty() == false)
	{
		Nod present = nods.top();
		nods.pop();


		if (present.name == y)
		{
			answer = present.way;
			break;
		}
		if (used[present.name] == true) continue;
		used[present.name] = true;

		for (Sosed sosed_of_present : elements[present.name])
		{
			if (used[sosed_of_present.nomber] == false)
			{

				ways[sosed_of_present.nomber] = Minimum(ways[sosed_of_present.nomber], ways[present.name] + sosed_of_present.cost);
				nods.push(Nod(sosed_of_present.nomber, ways[sosed_of_present.nomber]));
			}
		}
	}

	return answer;
}

int main()
{
	size_t a, b, M, x, y;

	cin >> a >> b >> M >> x >> y;

	cout << CountAnswer (a, b, M, x, y);
}
