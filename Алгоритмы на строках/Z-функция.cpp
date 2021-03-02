/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Z функцией
https://contest.yandex.ru/contest/19772/run-report/45687197/ */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::max;
using std::min;


int GetNextZValue(const vector<int>& z_array, int index, const string& text, const string& subtext, int& left, int& right)
{
	int z_function = max(0, min(right - index, z_array[index - left]));
	while (index + z_function < text.size() && subtext[z_function] == text[index + z_function])
	{
		++z_function;
	}

	if (index + z_function > right)
	{
		left = index;
		right = index + z_function;
	}

	return z_function;
}

vector<int> BuiltZArray(const string& str)
{
	vector<int> z(str.size());

	int left = 0;
	int right = 0;
	for (int i = 1; i < z.size(); ++i)
	{
		z[i] = GetNextZValue(z, i, str, str, left, right);
	}

	return z;
}

vector<int> Answer(const string& pattern, const string& text, const vector<int>& z_array)
{
	int left = 0;
	int right = 0;
	int current_z_func = 0;
	vector<int> answer;

	for (int i = 0; i < text.size(); ++i)
	{
		current_z_func = GetNextZValue(z_array, i, text, pattern, left, right);

		if (current_z_func == pattern.size() - 1)
		{
			answer.push_back(i);
		}
	}

	return answer;
}

void AnswerPrint(vector<int>& ans)
{
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
}

int main()
{
	string text, pattern;
	cin >> text >> pattern;
	text += "#";

	vector<int> z = BuiltZArray(text);
	vector<int> ans = Answer(text, pattern, z);

	AnswerPrint(ans);
}