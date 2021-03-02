/* ООО "Новые Железные Дороги" поручило вам разработать систему бронирования билетов на новый маршрут поезда дальнего следования. 
Маршрут проходит через N станций, занумерованных от 0 до N-1. Вместимость поезда ограничена.
В систему бронирования последовательно приходят запросы от пассажиров с указанием номера начальной и конечной станции,
а также количество билетов, которые пассажир хочет приобрести.
Требуемая скорость обработки каждого запроса - O(log n)*/

/*Решение - завожу дерево отрезков на массиве из промежутков.
В промежутках храню кол-во зарезервированных билетов, в дереве отрезков храню максимумы
на промежутках. Тогда бронировать можно - если максимум заполненности на промежутке
+ кол-во билетов не больше максимальной вместимости поезда*/

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

class TrainSystem
{
public:
	TrainSystem(const vector<int>& mas, const int& train)
	{
		tree.resize(4 * mas.size());
		train_size = train;
		Build(mas, 1, 0, mas.size() - 1);
		mas_size = mas.size();
	}

	bool Bronirovanie(const int& begin, const int& end, const int& number)
	{
		if (More(1, 0, mas_size - 1, begin, end) + number > train_size)
		{
			return false;
		}

		else
		{
			Bron(1, 0, mas_size - 1, begin, end, number);

			return true;
		}
	}
private:

	struct Nod
	{
		int tickets_start;
		int adding;
	};

	vector<Nod> tree;
	int train_size;
	int mas_size;

	void Build(const vector<int>& mas, const int& vertex, const int& tree_left, const int& tree_right)
	{
		if (tree_left == tree_right)
		{
			tree[vertex].tickets_start = mas[tree_left];
		}
			
		else 
		{
			int middle = (tree_left + tree_right) / 2;
			Build(mas, vertex * 2, tree_left, middle);
			Build(mas, vertex * 2 + 1, middle + 1, tree_right);
			tree[vertex].tickets_start = Maximum(tree[vertex * 2].tickets_start, tree[vertex * 2 + 1].tickets_start);
		}
	}

	int More(const int& vertex, const int& tree_left, const int& tree_right, const int& left, const int& right) 
	{
		if (left > right)
		{
			return -1;
		}
			
		if (left == tree_left && right == tree_right)
		{
			return tree[vertex].tickets_start + tree[vertex].adding;
		}
			
		else
		{
			int middle = (tree_left + tree_right) / 2;
			return Maximum(More(vertex * 2, tree_left, middle, left, Minimum(right, middle)),
				           More(vertex * 2 + 1, middle + 1, tree_right, Maximum(left, middle + 1), right)) + tree[vertex].adding;
		}
		
	}

	void Bron(const int& vertex, const int& tree_left, const int& tree_right, const int& left, const int& right, const int& add)
	{
		if (left > right)
		{
			return;
		}
			
		if (left == tree_left && tree_right == right)
		{
			tree[vertex].adding += add;
		}
			
		else 
		{
			int middle = (tree_left + tree_right) / 2;
			Bron(vertex * 2, tree_left, middle, left, Minimum(right, middle), add);
			Bron(vertex * 2 + 1, middle + 1, tree_right, Maximum(left, middle + 1), right, add);

			tree[vertex].tickets_start = Maximum(tree[vertex * 2].tickets_start + tree[vertex * 2].adding,
							                tree[vertex * 2 + 1].tickets_start + tree[vertex * 2 + 1].adding);
		}
	}

	int Minimum(int a, int b)
	{
		if (a < b) return a;
		return b;
	}

	int Maximum(int a, int b)
	{
		if (a > b) return a;
		return b;
	}
};


int main()
{
	int N;
	cin >> N;
	vector<int> station_intervals;

	int zagruzka;
	for (int i = 0; i < N - 1; i++)
	{
		cin >> zagruzka;
		station_intervals.push_back(zagruzka);
	}

	int train_size, k;

	cin >> train_size >> k;

	TrainSystem stations(station_intervals, train_size);

	vector<int> errors;
	int begin, end, number;

	for (int i = 0; i < k; i++)
	{
		cin >> begin >> end >> number;

		if (!stations.Bronirovanie(begin, end - 1, number))
		{
			errors.push_back(i);
		}
	}

	for (int i = 0; i < errors.size(); i++)
	{
		cout << errors[i] << " ";
	}
}