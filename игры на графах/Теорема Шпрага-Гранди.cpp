/*Штирлиц и Мюллер стреляют по очереди. В очереди n человек,
 стоящих друг за другом. Каждым выстрелом убивается один из стоящих.
 Кроме того, если у кого-то из стоящих в очереди убиты все его соседи, 
то этот человек в ужасе убегает. Проигрывает тот, кто не может ходить.
 Первым стреляет Штирлиц. Требуется определить, кто выиграет при оптимальной игре обеих сторон,
 и если победителем будет Штирлиц, то найти все возможные первые ходы, ведущие к его победе.

Формат ввода
Входной файл содержит единственное число n (2≤ n≤ 5 000) — количество человек в очереди.

Формат вывода
Если выигрывает Мюллер, выходной файл должен состоять из единственного слова Mueller.
 Иначе в первой строке необходимо вывести слово Schtirlitz, а в последующих строках — номера людей в очереди,
 которых мог бы первым ходом убить Штирлиц для достижения своей победы. 
Номера необходимо выводить в порядке возрастания.*/

/*Задачу решаю через теорему Шпрага-Гранди.
В качестве функции Шпрага-Гранди выстпает текущая длина ширенги людей*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int mex(vector<int>& xor_f)
{
	vector<int> numbers(xor_f.size(), -1);

	for (int i = 0; i < xor_f.size(); ++i)
	{
		if (xor_f[i] < xor_f.size())
		{
			numbers[xor_f[i]] = 1;
		}
	}

	int answer = -1;
	for (int i = 0; i < xor_f.size(); ++i)
	{
		if (numbers[i] == -1)
		{
			answer = i;
			break;
		}
	}

	if (answer == -1)
	{
		answer = xor_f.size();
	}

	return answer;
}


int count_func(vector<int>& func, int n)
{
	if (func[n] != -1)
	{
		return func[n];
	}

	vector<int> xor_f;
	xor_f.push_back(count_func(func, n - 1));
	xor_f.push_back(count_func(func, n - 2));
	for (int i = 2; i <= n - 3; i++)
	{
		xor_f.push_back(count_func(func, i) ^ count_func(func, n - i - 1));
	}
	func[n] = mex(xor_f);

	return func[n];
}

vector<int> whom_to_kill(vector<int>& func)
{
	vector<int> ans;
	int size = func.size() - 1;

	if (func[size - 1] == 0)
	{
		ans.push_back(1);
	}

	if (func[size - 2] == 0)
	{
		ans.push_back(2);
	}

	for (int i = 2; i + 3 <= size; i++)
	{
		if ((func[i] ^ func[size - i - 1]) == 0)
		{
			ans.push_back(i + 1);
		}
	}

	if (func[size - 2] == 0)
	{
		ans.push_back(size - 1);
	}

	if (func[size - 1] == 0)
	{
		ans.push_back(size);
	}

	return ans;
}

void print_vector(vector<int> dead)
{
	for (auto i : dead)
	{
		cout << i << endl;
	}
}

void print_answer(vector<int>& func, int res)
{
	if (res != 0)
	{
		cout << "Schtirlitz" << endl;

		if (func.size() == 3) cout << 1 << endl << 2;
		else
		{
			if (func.size() == 4)
			{
				cout << 2;
			}

			else
			{
				print_vector(whom_to_kill(func));
			}
		}
	}
	else
	{
		cout << "Mueller";
	}
}

int main()
{
	int n;
	cin >> n;

	vector<int> func(n + 1, -1);

	func[0] = 0;
	if (n >= 2) func[2] = 1;
	if (n >= 3) func[3] = 2;
	if (n >= 4) func[4] = 0;

	int res = count_func(func, n);

	print_answer(func, res);
}