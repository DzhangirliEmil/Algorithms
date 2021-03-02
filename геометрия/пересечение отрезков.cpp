/*Арсений уснул. И приснилась ему планета Ка-Пэкс,
 на которой протекают две реки. 
Эти реки достаточно необычны для землян: они текут строго от одной точки до другой точки напрямую в пространстве 
(так как в сне Арсения планета вовсе не круглая). Арсений решил,
 что он хочет прорыть тоннель между реками. Так как он ленивый,
 то и копать много он не хочет. Помогите Арсению найти, сколько-таки ему придется прорыть*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;


struct Point
{
	Point() = default;
	Point(int _x, int _y): x(_x), y(_y) {}
	int x, y;
};

long double vector_mul(long double x1, long double y1, long double x2, long double y2)
{
	return x1 * y2 - x2 * y1;
}

long double VectorProduct(Point v1, Point v2, Point w1, Point w2)
{
	return vector_mul(v2.x - v1.x, v2.y - v1.y, w2.x - w1.x, w2.y - w1.y);
}

bool Crossing(const Point& a, const Point& a2, const Point& b, const Point& b2)
{
	if (VectorProduct(a, a2, a, b) * VectorProduct(a, a2, a, b2) <= 0)
	{
		if (VectorProduct(b, b2, b, a) * VectorProduct(b, b2, b, a2) <= 0)
		{
			return true;
		}
	}

	return false;
}


int main()
{
	Point start, end;
	int n;

	cin >> start.x >> start.y >> end.x >> end.y >> n;

	int answer = 0;

	Point point_1;
	Point point_2;
	for (int i = 0; i < n; ++i)
	{
		cin >> point_1.x >> point_1.y;
		cin >> point_2.x >> point_2.y;

		if (Crossing(point_1, point_2, start, end)) answer++;
	}

	cout << answer;
}