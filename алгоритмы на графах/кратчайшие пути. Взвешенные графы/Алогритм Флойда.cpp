/*Рик отправляет Морти в путешествие по N вселенным.
 У него есть список всех существующих однонаправленных телепортов.
Чтобы Морти не потерялся, Рику необходимо узнать, между какими вселенными существуют пути, а между какими нет.
Помогите ему в этом!*/

/*в этой задачке я просто использую алгоритм флойда с оптимищацией при помощи
битовых масок.*/

#include <bitset>
#include <iostream>
#include <string>

using std::bitset;
using std::cin;
using std::cout;
using std::string;


void ChangeMatrix (bitset<1024>* matrix_ways, int m)
{
    for (int k = 0; k < m; ++k)
	{
		for (int i = 0; i < m; i++)
		{
			if (matrix_ways[i][k])
			{
				matrix_ways[i] |= matrix_ways[k];
			}
		}
	}
}

int main()
{
	int m;
	cin >> m;

	bitset<1024>* matrix_ways = new bitset<1024>[m];

	string help_string;
	for (int i = 0; i < m; ++i)
	{
		cin >> help_string;
		for (int j = 0; j < help_string.size(); ++j)
		{
			matrix_ways[i][j] = help_string[j] - '0';
		}
	}

    ChangeMatrix (matrix_ways, m);

	for (int i = 0; i < m; ++i)
	{
		if (i)
		{
			cout << std::endl;
		}
		for (int j = 0; j < m; j++)
		{
			cout << matrix_ways[i][j];
		}
	}
}
