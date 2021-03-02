/*Арсений опять уснул. 
И снова на планете Ка-Пэкс без него никак — два фермера поссорились из-за того, 
что их территории могут перекрываться. Естественно, как самого рассудительного, 
Арсения позвали урегулировать конфликт. Для начала он решил узнать, насколько серьезен конфликт. 
Для этого он решил узнать, пересекаются ли фермы вообще. Помогите Арсению это понять, если известно,
 что каждая ферма представляет собой выпуклый многоугольник.

Формат ввода
Первая строка содержит число N точек первого многоугольника.
 Затем идут N строк с координатами точек первого многоугольника по часовой стрелке (координаты – действительные числа). 
Второй прямоугольник задается аналогично. N, M ≤ 80000.

Формат вывода
Выведите “YES”, если фермы пересекаются, и “NO”, если нет (без кавычек).*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;
using std::swap;

class Point
{
public:
	Point() = default;
	Point(long double   _x, long double   _y) :x(_x), y(_y) {}
	long double x, y;
};

vector<Point> SortVector(vector<Point>& v)
{
	vector<Point> ans(v.size());
	long double   min_number = 0;

	for (long double i = 0; i < v.size(); i++)
	{
		if (v[i].y < v[min_number].y)
		{
			min_number = i;
		}

		else
		{
			if (v[i].y == v[min_number].y)
			{
				if (v[i].x < v[min_number].x)
				{
					min_number = i;
				}
			}
		}
	}

	long double   j = 0;
	for (j = 0; min_number + j < v.size(); ++j)
	{
		ans[j] = v[min_number + j];
	}

	for (long double i = 0; i < min_number; i++)
	{
		ans[j + i] = v[i];
	}

	return ans;
}
void reverse(vector<Point>& v)
{
	for (long double i = 0; i < v.size() / 2; ++i)
	{
		swap(v[i], v[v.size() - 1 - i]);
	}
}

long double VectorProduct(long double   x1, long double   y1, long double   x2, long double   y2)
{
	return x1 * y2 - x2 * y1;
}

long double VectorProductPoints(Point v1, Point v2, Point w1, Point w2)
{
	return VectorProduct(v2.x - v1.x, v2.y - v1.y, w2.x - w1.x, w2.y - w1.y);
}

bool Between(Point a, Point a2, Point b)
{
	if (a2.x == a.x)
	{
		if (b.y <= max(a.y, a2.y) && b.y >= min(a.y, a2.y))
		{
			return true;
		}
		return false;
	}

	else
	{
		if (b.x <= max(a.x, a2.x) && b.x >= min(a.x, a2.x))
		{
			return true;
		}
		return false;
	}
}

bool Crossing(const Point& a, const Point& a2, const Point& b, const Point& b2)
{
	if (VectorProductPoints(a, a2, b, b2) == 0)
	{
		if (VectorProductPoints(a, a2, a, b) == 0)
		{
			if (Between(a, a2, b)) return true;
			if (Between(a, a2, b2)) return true;
			if (Between(b, b2, a)) return true;
			if (Between(b, b2, a2)) return true;
		}

		return false;
	}

	if (VectorProductPoints(a, a2, a, b)*VectorProductPoints(a, a2, a, b2) <= 0)
	{
		if (VectorProductPoints(b, b2, b, a)*VectorProductPoints(b, b2, b, a2) <= 0)
		{
			return true;
		}
	}

	return false;
}


vector<Point> MinkovskiSum(vector<Point> first, vector<Point> second)
{
	reverse(first);
	reverse(second);

	vector<Point> f_mas = SortVector(first);
	vector<Point> s_mas = SortVector(second);

	f_mas.push_back(f_mas[0]);
	s_mas.push_back(s_mas[0]);

	long double j = 0;
	long double i = 0;

	Point help_Point(0, 0);
	vector<Point> ans;

	while (i < f_mas.size() - 1 && j < s_mas.size() - 1)
	{
		help_Point.x = f_mas[i].x + s_mas[j].x;
		help_Point.y = f_mas[i].y + s_mas[j].y;

		ans.push_back(help_Point);
		if (VectorProductPoints(f_mas[i], f_mas[i + 1], s_mas[j], s_mas[j + 1]) > 0)
		{
			++i;
		}

		else
		{
			if (VectorProductPoints(f_mas[i], f_mas[i + 1], s_mas[j], s_mas[j + 1]) < 0)
			{
				++j;
			}

			else
			{
				++i;
				++j;
			}
		}
	}

	return ans;
}

bool Cross(vector<Point> points)
{
	long int Crosses = 0;
	points.push_back(points[0]);

	Point start(0, 0);
	Point end(821, 1313);

	for (long double i = 0; i < points.size(); ++i)
	{
		if (points[i].x == 0 && points[i].y == 0)
		{
			return true;
		}
	}

	for (long double i = 0; i < points.size() - 1; ++i)
	{
		if (Crossing(start, end, points[i], points[i + 1]))
		{
			Crosses++;
		}
	}

	if (Crosses % 2 == 0)
	{
		return false;
	}

	return true;
	
}


int main()
{
	long double n;
	cin >> n;
	vector<Point> first(n);

	long double x, y;
	for (long double i = 0; i < n; ++i)
	{
		cin >> x >> y;
		Point help_point(x, y);
		first[i] = help_point;
	}

	long double m;
	cin >> m;
	vector<Point> second(m);

	for (long double i = 0; i < m; ++i)
	{
		cin >> x >> y;
		Point help_point(-x, -y);
		second[i] = help_point;
	}
	vector<Point> ans = MinkovskiSum(first, second);
	bool are_crossing = Cross(ans);

	if (are_crossing == true)
	{
		cout << "YES";
	}

	else
	{
		cout << "NO";
	}
}