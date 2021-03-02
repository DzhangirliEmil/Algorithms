/*Для заданной строки s длины n (1 ≤ n ≤ 105) требуется подсчитать число пар (i, j), 1 ≤ i < j ≤ n, таких что подстрока s[i..j] является палиндромом.*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::min;

vector<long long> SetPalMas(const string& str, int odd)
{
	vector<long long> odd_pal(str.size());

	long long left = 0;
	long long right = -1;

	long long biggest_dist = 0;

	long long i = 0;

	while (i < str.size())
	{
		if (i > right)
		{
			biggest_dist = 0;
		}

		else
		{
			biggest_dist = min(right - i + 1, odd_pal[left + right - i + odd]);
		}

		while (i - biggest_dist >= 1 && i + biggest_dist < str.size() && str[i + biggest_dist + 1 - odd] == str[i - biggest_dist - 1])
		{
			++biggest_dist;
		}

		odd_pal[i] = biggest_dist;

		if (i + biggest_dist - 1 > right)
		{
			left = i - biggest_dist + 1 - odd;
			right = i + biggest_dist - 1;
		}

		++i;

	}

	return odd_pal;
}


size_t AnswerCount(const vector<long long>& not_odd_pal, const vector<long long>& odd_pal)
{

	size_t answer = 0;

	for (int i = 0; i < not_odd_pal.size(); ++i)
	{
		answer += odd_pal[i];
		answer += not_odd_pal[i];

	}

	return answer;
}

int main()
{
	string str;
	cin >> str;

	vector<long long> odd_pal = SetPalMas(str, 1);
	vector<long long> not_odd_pal = SetPalMas(str, 0);

	cout << AnswerCount(not_odd_pal, odd_pal);
}