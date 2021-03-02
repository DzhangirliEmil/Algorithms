/* Арсений продолжает спать. Теперь ему снится кроличья ферма на планете Ка-Пэкс.
 Правда, ферма у него так себе — одни кроличьи норы в пустом поле. 
Чтобы её хоть как-то облагородить, 
Арсений решил поставить забор так, чтобы все норки оказались внутри огражденной территории, 
а досок он потратил как можно меньше. 
Помогите Арсению найти длину забора, чтобы он мог уже заказывать стройматериалы!
В первой строке вводится число N. Следующие N строк содержат пары целых чисел x и y — координаты кроличьих нор.
Вывести дно вещественное число — длину забора — с максимально возможной точностью.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <iomanip> 

using std::vector;
using std::sqrt;
using std::cin;
using std::cout;
using std::swap;
using std::stack;

struct Point
{
	Point(long long& x, long long& y) :x(x), y(y) {};
	Point() = default;
	long long x, y;

	long long st_x, st_y;


	bool operator < (const Point& a) const
	{
		if (a.x == st_x && a.y == st_y)
		{
			return false;
		}

		if (x == st_x && y == st_y)
		{
			return true;
		}

		if (((x - st_x)*(a.y - st_y) - (a.x - st_x)*(y - st_y)) == 0)
		{
			return ((x - st_x)*(x - st_x) + (y - st_y)*(y - st_y) < (a.x - st_x)*(a.x - st_x) + (a.y - st_y)*(a.y - st_y));

		}

		else
		{
			return (((x - st_x)*(a.y - st_y) - (a.x - st_x)*(y - st_y)) > 0);
		}
	}
};

long double Dist(Point a, Point b)
{

	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


long double CountDist(long long N)
{
	long long x, y;

	vector<Point> dots(N);

	long long min = 0;

	for (long long i = 0; i < N; ++i)
	{

		cin >> x >> y;
		dots[i].x = x;
		dots[i].y = y;

		if (y <= dots[min].y)
		{
			if (y == dots[min].y)
			{
				if (x < dots[i].x)
				{
					min = i;
				}
			}

			else
			{
				min = i;
			}
		}
	}

	for (long long i = 0; i < N; ++i)
	{
		dots[i].st_x = dots[min].x;
		dots[i].st_y = dots[min].y;
	}

	swap(dots[0], dots[min]);

	std::sort(dots.begin() + 1, dots.end());

	stack<Point> p;
	p.push(dots[0]);
	p.push(dots[1]);

	for (int i = 2; i < N; ++i)
	{
		Point last = p.top();
		p.pop();
		Point pre_last = p.top();
		p.push(last);


		while ((last.x - pre_last.x) * (dots[i].y - last.y) - (dots[i].x - last.x) * (last.y - pre_last.y) <= 0 && p.size() >= 3)
		{
			p.pop();

			last = p.top();
			p.pop();
			pre_last = p.top();
			p.push(last);
		}

		p.push(dots[i]);
	}


	long double res = 0.0;
	Point pred = dots[0];
	while (p.size() != 0)
	{
		res += Dist(pred, p.top());
		pred = p.top();

		p.pop();
	}

	res += Dist(pred, dots[0]);

	return res;
}


int main()
{
	long long N;
	cin >> N;

	cout << std::setprecision(10) << CountDist(N);
}