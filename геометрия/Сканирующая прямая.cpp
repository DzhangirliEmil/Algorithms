/*Арсений открыл эзотерический салон в свои снах на планете Ка-Пэкс.
 У Арсения всё будет хорошо. А вот у его клиентов — не факт. 
Если хотя бы какие-нибудь их палочки в гадании "Мокусо Дзэй" пересеклись,
 то день точно сложится удачно. А если нет — то стоит ждать беды. 
Чтобы точнее сказать, что конкретно пойдет хорошо в этот день, нужно знать, 
какие именно палочки пересекаются.
 Помогите Арсению узнать, как пройдет день у его клиентов.

Формат ввода
Палочка представляется как отрезок прямой.
 В первой строке входного файла записано число N — количество палочек в гадании. 
Следующие N строк содержат описания палочек:
 (i + 1)-я строка содержит координаты концов i-й палочки — целые числа x1, y1, x2, y2.

Формат вывода
В первой строке выходного файла выведите слово "YES", 
если день сложится удачно. 
Вторая строка должна содержать числа i и j — номера палочек, 
которые пересекаются. Если день пройдет плохо, 
выведите в единственной строке выходного файла "NO".*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>


using std::cin;
using std::cout;
using std::vector;
using std::swap;
using std::endl;
using std::min;
using std::max;
using std::set;


struct Point
{
	Point() = default;
	Point(long double _x, long double _y, long double _neighbour_x, long double _neighbour_y)
	{

		x = _x;
		y = _y;
		neighbour_x = _neighbour_x;
		neighbour_y = _neighbour_y;
	}

	long double GetY(long double coord) const
	{
		if (abs(coord - neighbour_x) == 0)  return y;
		return y + (neighbour_y - y) * (coord - x) / (neighbour_x - x);
	}

	int vstav = 0;

	int64_t nomber;
	long double x, y;
	long double neighbour_x, neighbour_y;
};

long double VectorProduct(long double x1, long double y1, long double x2, long double y2)
{
	return x1 * y2 - x2 * y1;
}

long double VectorProductPoints(Point v1, Point v2, Point w1, Point w2)
{
	return VectorProduct(v2.x - v1.x, v2.y - v1.y, w2.x - w1.x, w2.y - w1.y);
}

bool between(Point a, Point a2, Point b)
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


bool crossing(const Point& a, const Point& b)
{
	Point a2(a.neighbour_x, a.neighbour_y, a.x, a.y);
	Point b2(b.neighbour_x, b.neighbour_y, b.x, b.y);


	if (VectorProductPoints(a, a2, b, b2) == 0)
	{
		if (VectorProductPoints(a, a2, a, b) == 0)
		{
			if (between(a, a2, b)) return true;
			if (between(a, a2, b2)) return true;
			if (between(b, b2, a)) return true;
			if (between(b, b2, a2)) return true;
		}

		return false;
	}

	if (VectorProductPoints(a, a2, a, b) * VectorProductPoints(a, a2, a, b2) <= 0)
	{
		if (VectorProductPoints(b, b2, b, a) * VectorProductPoints(b, b2, b, a2) <= 0)
		{
			return true;
		}
	}

	return false;
}




bool less_x(const Point& a, const Point b)
{
	if (a.x != b.x)
	{
		return a.x < b.x;
	}
	return a.vstav < b.vstav;
}

struct comp
{
	bool operator() (const Point &a, const Point &b) const
	{
		if (a.nomber == b.nomber)
		{
			return false;
		}

		long double x = max(min(a.x, a.neighbour_x), min(b.x, b.neighbour_x));

		if (a.GetY(x) == b.GetY(x))
		{
			return a.nomber < b.nomber;
		}

		return a.GetY(x) < b.GetY(x);
	}
};


bool cros(vector<Point> Points, long long int& a, long long int& b)
{
	sort(Points.begin(), Points.end(), less_x);
	for (int64_t i = 0; i < Points.size() - 1; ++i)
	{
		if (Points[i].x == Points[i + 1].x && Points[i].y == Points[i + 1].y)
		{
			if (Points[i].nomber != Points[i + 1].nomber)
			{

				if (Points[i].nomber < Points[i + 1].nomber) a = Points[i].nomber, b = Points[i + 1].nomber;
				else b = Points[i].nomber, a = Points[i + 1].nomber;

				return true;
			}
		}
	}


	vector<int64_t> added(Points.size()/2);
	set<Point, comp> scan_line;


	for (Point p : Points)
	{
		if (added[p.nomber - 1] == 0)
		{
			scan_line.insert(p);

			added[p.nomber - 1] = 1;

			auto st = scan_line.find(p);
			auto neighbour_niz = st;
			auto neighbour_verh = st;

			if (neighbour_niz != scan_line.begin())
			{
				neighbour_niz--;

				if (crossing(*neighbour_niz, *st))
				{

					if (neighbour_niz->nomber < st->nomber) a = neighbour_niz->nomber, b = st->nomber;
					else  b = neighbour_niz->nomber, a = st->nomber;
					return true;
				}
			}

			neighbour_verh++;
			if (neighbour_verh != scan_line.end())
			{
				if (crossing(*neighbour_verh, *st))
				{

					if (neighbour_verh->nomber < st->nomber) a = neighbour_verh->nomber, b = st->nomber;
					else b = neighbour_verh->nomber, a = st->nomber;

					return true;

				}
			}
		}


		else
		{
			Point neighboured(p.neighbour_x, p.neighbour_y, p.x, p.y);
			neighboured.nomber = p.nomber;

			auto st = scan_line.find(neighboured);


			auto neighbour_niz = st;
			auto neighbour_verh = st;

			if (neighbour_niz != scan_line.begin())
			{
				neighbour_niz--;
				if (crossing(*neighbour_niz, *st))
				{
					if (neighbour_niz->nomber < st->nomber) a = neighbour_niz->nomber, b = st->nomber;
					else  b = st->nomber, a = neighbour_niz->nomber;

					return true;
				}
			}

			neighbour_verh++;
			if (neighbour_verh != scan_line.end())
			{
				if (crossing(*neighbour_verh, *st))
				{
					if (neighbour_verh->nomber < st->nomber) a = neighbour_verh->nomber, b = st->nomber;
					else b = st->nomber, a = neighbour_verh->nomber;

					return true;
				}
			}

			scan_line.erase(st);
		}
	}

	return false;
}


int main()
{
	int64_t n;
	cin >> n;

	long double x1, y1, x2, y2;

	vector<Point> Points;
	for (int64_t i = 1; i <= n; ++i)
	{
		cin >> x1 >> y1 >> x2 >> y2;

		Point start(x1, y1, x2, y2);
		Point end(x2, y2, x1, y1);

		if (x1 != x2)
		{
			if (x1 < x2)
			{
				start.vstav = 0;
				end.vstav = 1;
			}

			else
			{
				start.vstav = 1;
				end.vstav = 0;
			}
		}
		else
		{
			start.vstav = 1;
			end.vstav = 0;
		}
		start.nomber = i;
		end.nomber = i;

		Points.push_back(start);
		Points.push_back(end);
	}

	long long a, b;
	bool ans = cros(Points, a, b);

	if (ans == true)
	{
		cout << "YES" << endl;
		cout << a << " " << b;
	}

	else
	{
		cout << "NO";
	}
	
}