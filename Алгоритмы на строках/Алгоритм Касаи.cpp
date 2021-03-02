/*Заданы две строки s, t и целое число k.
Рассмотрим множество всех таких непустых строк, которые встречаются как подстроки в s и t одновременно.
Найдите k-ую в лексикографическом порядке строку из этого множества.*/
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;


long long TwoInDegree(const long long& degree)
{
	return 1 << degree;
}

void EqualVectors(vector<long long>& vec1, vector<long long>& vec2)
{
	for (long long i = 0; i < vec1.size(); ++i)
	{
		vec1[i] = vec2[i];
	}
}

vector<long long> BuildLcp(const vector<long long>& suf_mas, const string& str)
{
	vector<long long> lcp(suf_mas.size());
	vector<long long> upside_down_suf(suf_mas.size());

	for (long long i = 0; i < suf_mas.size(); ++i)
	{
		upside_down_suf[suf_mas[i]] = i;
	}

	long long k = 0;
	for (long long i = 0; i < suf_mas.size(); ++i)
	{
		if (k > 0)
		{
			--k;
		}

		if (upside_down_suf[i] != suf_mas.size() - 1)
		{
			long long j = suf_mas[1 + upside_down_suf[i]];

			while (i + k < suf_mas.size() && j + k < suf_mas.size() && str[i + k] == str[j + k])
			{
				++k;
			}
			lcp[upside_down_suf[i]] = k;
		}

		else
		{
			lcp[suf_mas.size() - 1] = -1;
			k = 0;
		}
	}

	return lcp;
}

vector<long long> BuildSufMas(const string& str)
{
	long long size = str.size();

	vector<long long> suf_mas(size);
	vector<long long> classes(size);

	long long class_numbers = 1;
	vector<long long> symbols(257);


	for (auto symbol : str)
	{
		symbols[symbol] ++;
	}

	for (long long i = 1; i < 257; ++i)
	{
		symbols[i] += symbols[i - 1];
	}

	for (long long i = 0; i < size; ++i)
	{
		symbols[str[i]] -= 1;
		suf_mas[symbols[str[i]]] = i;
	}


	for (long long i = 1; i < size; ++i)
	{
		if ((str[suf_mas[i - 1]] != str[suf_mas[i]]))
		{
			class_numbers += 1;
		}

		classes[suf_mas[i]] = class_numbers - 1;
	}

	long long sdvig_size = 1;
	vector<long long> new_suf_mas(size);
	vector<long long> new_classes(size);

	for (long long d = 0; TwoInDegree(d) < str.size(); ++d)
	{
		sdvig_size = TwoInDegree(d);
		for (long long i = 0; i < size; ++i)
		{
			new_suf_mas[i] = suf_mas[i] - sdvig_size;

			if (new_suf_mas[i] < 0)
			{
				new_suf_mas[i] += size;
			}
		}

		vector<long long> class_alphabet(class_numbers);
		for (long long i = 0; i < size; ++i)
		{
			class_alphabet[classes[new_suf_mas[i]]] += 1;
		}

		for (long long i = 1; i < class_numbers; ++i)
		{
			class_alphabet[i] += class_alphabet[i - 1];
		}

		for (long long i = size - 1; i >= 0; --i)
		{
			class_alphabet[classes[new_suf_mas[i]]] -= 1;
			suf_mas[class_alphabet[classes[new_suf_mas[i]]]] = new_suf_mas[i];
		}

		new_classes[suf_mas[0]] = 0;

		class_numbers = 1;

		for (long long i = 1; i < size; ++i)
		{
			if (classes[(suf_mas[i - 1] + sdvig_size) % size] != classes[(suf_mas[i] + sdvig_size) % size]
				|| classes[suf_mas[i - 1]] != classes[suf_mas[i]])
			{
				class_numbers += 1;
			}

			new_classes[suf_mas[i]] = class_numbers - 1;
		}

		EqualVectors(classes, new_classes);
	}

	return suf_mas;
}

string CountAnswer(const vector<long long>& suf_mas, const vector<long long>& lcp, const string a, long long k, const string& needed)
{
	string ans;

	long long min_common_part = 0;
	long long size = a.size();
	long long extra_length = 0;

	for (long long i = 0; i < suf_mas.size() - 1; ++i)
	{
		if ((lcp[i] > 0) && (suf_mas[i] - size) * (suf_mas[i + 1] - size) < 0)
		{
			extra_length = (lcp[i] - min_common_part > 0 ? lcp[i] - min_common_part : 0);

			if (extra_length < k)
			{
				min_common_part = lcp[i];
				k -= extra_length;
			}
			else
			{
				ans = needed.substr(suf_mas[i], k + min_common_part);
				break;

			}
		}
		else
		{
			if (min_common_part >= lcp[i])
			{
				min_common_part = lcp[i];
			}
		}
	}

	return ans;
}

void PrintAnswer(const string& answer)
{
	if (answer.size() == 0)
	{
		cout << -1;
	}

	else
	{
		cout << answer;
	}
}

int main()
{
	string str1, str2;
	long long k;
	cin >> str1 >> str2;
	cin >> k;

	string help_string = str1 + '#' + str2 + '$';
	vector<long long> suf_mas = BuildSufMas(help_string);
	vector<long long> lcp = BuildLcp(suf_mas, help_string);

	string answer = CountAnswer(suf_mas, lcp, str1, k, help_string);
	PrintAnswer(answer);
}