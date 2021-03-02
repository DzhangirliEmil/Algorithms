/*Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.
Для решения задачи используйте структуру данных Sparse Table. 
Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных O(log n).*/

/*решение - завожу спарс табличку, и буду хранить 2 объекта на интервалах - минимум и второй минимум. 
Функция все требуемым свойствам удовлетворяет.*/

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

struct Minims
{
	Minims() = default;
	Minims(long long number_1, long long number_2, const vector<long long>& mas)
	{
		if (mas[number_1] < mas[number_2])
		{
			minimum = mas[number_1];
			second_minimum = mas[number_2];
		}

		else
		{
			minimum = mas[number_2];
			second_minimum = mas[number_1];
		}
	}

	Minims(Minims min_1, Minims min_2)
	{
		if (min_1.minimum < min_2.minimum)
		{
			minimum = min_1.minimum;

			if (((min_2.minimum < min_1.second_minimum) || (min_1.second_minimum == min_1.minimum))
				&& (min_2.minimum != min_1.minimum))
			{
				second_minimum = min_2.minimum;
			}
			else if ((min_1.second_minimum <= min_2.second_minimum) && (min_1.second_minimum != min_1.minimum))
			{
				second_minimum = min_1.second_minimum;
			}

			else
			{
				second_minimum = min_2.second_minimum;
			}
		}

		else 
		{
			minimum = min_2.minimum;

			if ((min_1.minimum != min_2.minimum) && ((min_1.minimum < min_2.second_minimum) || (min_2.second_minimum == min_2.minimum)))
			{
				second_minimum = min_1.minimum;
			}
			else if ((min_2.second_minimum != min_2.minimum) && (min_2.second_minimum <= min_1.second_minimum))
			{
				second_minimum = min_2.second_minimum;
			}
			else 
			{
				second_minimum = min_1.second_minimum;
			}
		}
	}
	long long minimum;
	long long second_minimum;
};

void CreateSparceTable(vector<vector<Minims>>& sparce_table, vector<long long> degree, long long N, long long y_size, vector<long long> mas)
{
	sparce_table.resize(N);
	for (long long i = 0; i < sparce_table.size(); ++i)
	{
		sparce_table[i].resize(y_size);
	}


	for (long long i = 0; i < N - 1; ++i)
	{
		sparce_table[i][1] = Minims(i, i + 1, mas);
	}

	for (long long j = 2; j < y_size; ++j)
	{
		for (long long i = 0; i + degree[j] <= N; i++)
		{
			sparce_table[i][j] = Minims(sparce_table[i][j - 1], sparce_table[i + degree[j - 1]][j - 1]);
		}
	}
}

long long lg(long long chislo)
{
	if (chislo == 1)
	{
		return 0;
	}

	else
	{
		return lg(chislo / 2) + 1;
	}
}


int main()
{
	long long N, M;

	cin >> N >> M;

	vector<long long> mas;
	mas.resize(N);

	for (long long i = 0; i < N; ++i)
	{
		cin >> mas[i];
	}

	long long y_size = lg(N) + 1;

	vector<long long> degree;
	degree.push_back(1);
	for (long long i = 1; i < N; i++)
	{
		degree.push_back(degree[degree.size() - 1] * 2);
	}

	vector<long long> logarifms(N + 1);
	for (long long i = 1; i < N + 1; ++i)
	{
		logarifms[i] = lg(i);
	}

	vector<vector<Minims>> sparce_table;
	CreateSparceTable(sparce_table, degree, N, y_size, mas);
	

	long long left, right, j;


	for (long long i = 0; i < M; i++)
	{
		cin >> left >> right;
		--left; --right;

		j = logarifms[right - left + 1];

		Minims answer(sparce_table[left][j], sparce_table[right - degree[j] + 1][j]);

		cout << answer.second_minimum << "\n";
	}
}