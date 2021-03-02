#include "iostream"
#include "vector"
#include "string"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::ostream;
using std::istream;
using std::to_string;

class BigInteger
{
public:
	BigInteger() = default;
	friend istream& operator >> (std::istream &in, BigInteger &bigint);
	friend ostream& operator << (std::ostream &out, const BigInteger &bigint);
	friend BigInteger operator - (const BigInteger& bigint);
	friend bool operator == (const BigInteger& left, const BigInteger& right);
	friend bool operator < (const BigInteger& left, const BigInteger& right);
	friend bool operator > (const BigInteger& left, const BigInteger& right);
	friend bool operator <= (const BigInteger& left, const BigInteger& right);
	friend bool operator >= (const BigInteger& left, const BigInteger& right);
	friend bool operator != (const BigInteger& left, const BigInteger& right);

	friend BigInteger operator *(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator +(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator -(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator /(const BigInteger& left, const BigInteger& right);

	friend BigInteger operator %(const BigInteger& left, const BigInteger& right);

	BigInteger(string a)
	{
		SetBigInt(a);
	}

	BigInteger& operator -=(const BigInteger& value)
	{
		return *this = (*this - value);
	}

	BigInteger& operator +=(const BigInteger& value)
	{
		return *this = (*this + value);
	}

	BigInteger& operator *=(const BigInteger& value)
	{
		return *this = (*this * value);
	}

	BigInteger& operator /=(const BigInteger& value)
	{
		return *this = (*this / value);
	}
	BigInteger& operator %=(const BigInteger& value)
	{
		return *this = (*this % value);
	}
	BigInteger operator ++() {
		return (*this += BigInteger(1));
	}
	BigInteger operator --() {
		return (*this -= BigInteger(1));
	}
	BigInteger operator ++(int) {
		*this += 1;
		return *this - BigInteger(1);
	}
	BigInteger operator --(int) {
		*this -= 1;
		return *this + BigInteger(1);
	}

	explicit operator bool() const
	{
		for (unsigned int i = 0; i < digits.size(); ++i)
		{
			if (digits[i] != 0)
			{
				return true;
			}

			return false;
		}

		return true;
	}


	std::vector<long long> digits;
	bool is_negative = false;

	string toString()
	{
		string str;

		if (is_negative && !(digits.size() == 1 && digits[0] == 0)) str += "-";


		if (digits.size() != 0) str += to_string(digits[digits.size() - 1]);
		for (int i = digits.size() - 2; i >= 0; --i)
		{
			for (unsigned int j = 0; j < 9 - to_string(digits[i]).size(); j++) str += "0";
			str += to_string(digits[i]);
		}

		return str;
	}

	void change_sign()
	{
		if (digits.size() == 1 && digits[0] == 0)
		{
			is_negative = false;
		}
		else
		{
			if (is_negative == true) is_negative = false;
			else is_negative = true;
		}

	}

	BigInteger& operator = (const BigInteger& right)
	{
		if (this == &right) {
			return *this;
		}

		is_negative = right.is_negative;
		digits = right.digits;

		return *this;
	}

	long long base = 1000000000;
	int base_int = 1000000000;


	void SetBigInt(string str)
	{
		if (str[0] == '-')
		{
			is_negative = true;
			str = str.substr(1);
		}


		for (int i = str.length(); i > 0; i -= 9)
		{
			if (i < 9)
			{
				this->digits.push_back(atoi(str.substr(0, i).c_str()));
			}

			else
			{
				this->digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
			}
		}
	}

	BigInteger(long long number)
	{
		do {
			//cout << number;
			this->digits.push_back(number % base);
			number /= base;

		} while (number != 0);
	}

	BigInteger return_first_part(unsigned int n) const
	{
		BigInteger result;

		if (n > digits.size() - 1) n = digits.size();
		for (unsigned int i = 0; i < n; ++i)
		{
			result.digits.push_back(this->digits[i]);
		}

		if (result.digits.size() == 0) result.digits.push_back(0);
		return result;
	}
	BigInteger return_second_part(unsigned int n) const
	{
		BigInteger result;
		if (n > digits.size() - 1) n = digits.size();
		for (unsigned int i = n; i < this->digits.size(); ++i)
		{
			result.digits.push_back(this->digits[i]);
		}
		if (result.digits.size() == 0) result.digits.push_back(0);

		return result;
	}
	BigInteger step(int step) const
	{
		BigInteger answer;

		if (step == 0)
		{
			return BigInteger(1);
		}

		for (int i = 0; i < step; ++i) answer.digits.push_back(0);
		for (unsigned int i = 0; i < this->digits.size(); ++i)
		{
			answer.digits.push_back(this->digits[i]);
		}

		return answer;
	}

	BigInteger karacuba(const BigInteger& left, const BigInteger& right) const
	{
		unsigned int max = left.digits.size();

		if (right.digits.size() > max)
		{
			max = right.digits.size();
		}

		if (max == 1)
		{
			long long help = left.digits[0] * right.digits[0];
			return BigInteger(help);
		}

		unsigned int helpchislo = max / 2;

		BigInteger r_left = left.return_first_part(helpchislo);
		BigInteger l_left = left.return_second_part(helpchislo);

		BigInteger r_right = right.return_first_part(helpchislo);
		BigInteger l_right = right.return_second_part(helpchislo);

		BigInteger a = l_left * l_right;

		BigInteger b = r_left * r_right;

		BigInteger c = (l_left + r_left) * (l_right + r_right);

		return (a.step(helpchislo * 2) + (c - b - a).step(helpchislo) + b);
	}
};

BigInteger operator %(const BigInteger& left, const BigInteger& right)
{
	BigInteger helpchislo = left / right;
	BigInteger answer = left - helpchislo * right;

	if (answer.is_negative != left.is_negative)
	{
		if (answer.is_negative == true) answer += right;
		else answer -= right;
	}

	return answer;
}

BigInteger divide_by_2(BigInteger number)
{
	int flag = 0;
	long long help;
	if (number.digits[number.digits.size() - 1] % 2 == 1) flag = 1;
	number.digits[number.digits.size() - 1] /= 2;

	for (int i = number.digits.size() - 2; i > -1; --i)
	{
		help = number.digits[i];
		number.digits[i] /= 2;
		if (flag == 1)
		{
			number.digits[i] += 500000000;
		}

		if (help % 2 == 1) flag = 1;
		else flag = 0;
	}

	return number;
}

istream& operator >> (std::istream& in, BigInteger &bigint)
{
	string str;
	in >> str;
	bigint.SetBigInt(str);

	return in;
}

bool operator ==(const BigInteger& left, const BigInteger& right)
{
	if (left.is_negative != right.is_negative) return false;
	if (left.digits.size() != right.digits.size()) return false;

	for (unsigned int i = 0; i < left.digits.size(); ++i)
	{
		if (left.digits[i] != right.digits[i]) return false;
	}

	return true;
}

bool operator < (const BigInteger& left, const BigInteger& right)
{
	if (left == right) return false;

	if (left.is_negative != right.is_negative)
	{
		return (left.is_negative > right.is_negative);
	}

	if (left.is_negative == true) return ((-right) < (-left));

	if (left.digits.size() == right.digits.size())
	{
		for (int i = left.digits.size() - 1; i >= 0; --i)
		{
			if (left.digits[i] != right.digits[i]) return left.digits[i] < right.digits[i];
		}
	}
	//
	else
	{
		return (left.digits.size() < right.digits.size());
	}

	return 0;
}

bool operator != (const BigInteger& left, const BigInteger& right)
{
	return !(left == right);
}

bool operator <=(const BigInteger& left, const BigInteger& right)
{
	return (left < right || left == right);
}

bool operator >(const BigInteger& left, const BigInteger& right)
{
	return !(left <= right);
}

bool operator >=(const BigInteger& left, const BigInteger& right)
{
	return !(left < right);
}

ostream& operator << (std::ostream &out, const BigInteger &bigint)
{
	BigInteger ans = bigint;

	out << ans.toString();
	return out;
}


BigInteger operator - (const BigInteger& bigint)
{
	BigInteger copyInt = bigint;
	copyInt.change_sign();

	return copyInt;
}

BigInteger operator +(const BigInteger& left, const BigInteger& right)
{
	if (left.is_negative == true)
	{
		if (right.is_negative == true) return (-(-left + (-right)));
		else return right - (-left);
	}

	else if (right.is_negative == true) return left - (-right);

	BigInteger sum;

	int zanimalka = 0;
	for (unsigned int i = 0; (i < left.digits.size()) || (i < right.digits.size()) || (zanimalka == 1); ++i)
	{
		sum.digits.push_back(0);
		sum.digits[i] += zanimalka;

		if (i < left.digits.size()) sum.digits[i] += left.digits[i];
		if (i < right.digits.size()) sum.digits[i] += right.digits[i];

		if (sum.digits[i] >= left.base)
		{
			zanimalka = 1;
			sum.digits[i] -= left.base;
		}

		else
		{
			zanimalka = 0;
		}
	}

	for (int i = sum.digits.size() - 1; i > 0 && sum.digits[i] == 0; --i)
	{
		sum.digits.pop_back();
	}

	return sum;
}
BigInteger operator - (const BigInteger& left, const BigInteger& right)
{
	if (right.is_negative == true)
	{

		return left + (-right);
	}

	if (left.is_negative == true)
	{

		return -(-left + right);
	}

	if (left < right)
	{
		return -(right - left);
	}



	int zanimalka = 0;
	BigInteger dif;

	for (unsigned int i = 0; ((i < left.digits.size()) || (zanimalka == 1)); ++i)
	{
		dif.digits.push_back(0);
		if (i < left.digits.size()) dif.digits[i] += left.digits[i];
		if (i < right.digits.size()) dif.digits[i] -= right.digits[i];

		dif.digits[i] -= zanimalka;

		if (dif.digits[i] < 0)
		{
			zanimalka = 1;
			dif.digits[i] += dif.base;
		}

		else
		{
			zanimalka = 0;
		}
	}

	for (int i = dif.digits.size() - 1; i > 0 && dif.digits[i] == 0; i--)
	{
		dif.digits.pop_back();
	}

	return dif;
}
BigInteger operator *(const BigInteger& left, const BigInteger& right)
{
	BigInteger res;
	if (right == BigInteger(0) || left == BigInteger(0)) return BigInteger(0);
	res = left.karacuba(left, right);
	if (left.is_negative != right.is_negative)  res.is_negative = true;

	for (int i = res.digits.size() - 1; i > 0 && res.digits[i] == 0; i--)
	{
		res.digits.pop_back();
	}

	return res;
}
BigInteger operator / (const BigInteger& delimoe, const BigInteger& delitel)
{
	if (delitel == BigInteger(1)) return delimoe;

	if (delimoe.is_negative == true)
	{
		if (delitel.is_negative == true)
		{
			return (-delimoe) / (-delitel);
		}

		else
		{
			BigInteger answer = -((-delimoe) / delitel);
			return answer;
		}
	}

	else
	{
		if (delitel.is_negative == true)
		{
			BigInteger answer = -(delimoe / (-delitel));

			return answer;
		}
	}

	BigInteger left(0);
	BigInteger right = delimoe;


	BigInteger mid;
	BigInteger helpchislo;

	while ((right - left) != BigInteger(1))
	{
		mid = divide_by_2(right + left);
		helpchislo = mid * delitel;

		if (helpchislo < delimoe)
		{
			left = mid;
		}

		if (helpchislo == delimoe) return mid;

		if (helpchislo > delimoe)
		{
			right = mid;
		}
	}

	for (int i = left.digits.size() - 1; i > 0 && left.digits[i] == 0; i--)
	{
		left.digits.pop_back();
	}

	return left;
}
//////////////////////////////////////////////////////////////////////
class Rational
{
public:
	Rational() = default;
	Rational(const int& a)
	{
		if (a < 0)
		{
			chislitel = -BigInteger(a);
			is_negative = true;
		}

		else
		{
			chislitel = BigInteger(a);
		}

	}
	Rational(const BigInteger& a)
	{
		if (a < BigInteger(0))
		{
			chislitel = -BigInteger(a);
			is_negative = true;
		}

		else
		{
			chislitel = BigInteger(a);
		}
	}

	void sokrati()
	{
		BigInteger delitel = NOD(chislitel, znaminatel);

		if (delitel != BigInteger(1))
		{
			chislitel /= delitel;
			znaminatel /= delitel;
		}

	}

	explicit operator double()
	{
		return stod(asDecimal(30));
	}

	friend Rational operator - (const Rational& bigint);
	friend bool operator == (const Rational& left, const Rational& right);
	friend bool operator < (const Rational& left, const Rational& right);
	friend bool operator > (const Rational& left, const Rational& right);
	friend bool operator <= (const Rational& left, const Rational& right);
	friend bool operator >= (const Rational& left, const Rational& right);
	friend bool operator != (const Rational& left, const Rational& right);



	friend Rational operator *(const Rational& left, const Rational& right);
	friend Rational operator +(const Rational& left, const Rational& right);
	friend Rational operator -(const Rational& left, const Rational& right);
	friend Rational operator /(const Rational& left, const Rational& right);


	Rational& operator -=(const Rational& value)
	{
		return *this = (*this - value);
	}

	Rational& operator +=(const Rational& value)
	{
		return *this = (*this + value);
	}

	Rational& operator *=(const Rational& value)
	{
		return *this = (*this * value);
	}

	Rational& operator /=(const Rational& value)
	{
		return *this = (*this / value);
	}

	Rational operator ++() {
		return (*this += Rational(1));
	}

	Rational operator --() {
		return (*this -= Rational(1));
	}

	Rational operator ++(int) {
		*this += 1;
		return *this - Rational(1);
	}

	Rational operator --(int) {
		*this -= 1;
		return *this + Rational(1);
	}

	void change_sign()
	{
		if (is_negative == true) is_negative = false;
		else is_negative = true;
	}

	string toString()
	{
		string answer;
		if (is_negative == true) answer += "-";

		sokrati();
		answer += chislitel.toString();
		if (znaminatel != BigInteger(1))
		{
			answer += "/";
			answer += znaminatel.toString();
		}

		return answer;

	}

	string asDecimal(size_t precision = 0)
	{
		BigInteger ans = chislitel / znaminatel;
		BigInteger after_drop(10);
		for (unsigned int i = 0; i < precision - 1; ++i) after_drop *= BigInteger(10);

		string a;
		if (is_negative == true) a += "-";

		a += ans.toString();
		if (precision == 0) return a;

		ans = chislitel % znaminatel;
		ans *= after_drop;
		ans /= znaminatel;
		if (ans != BigInteger(0))
		{
			a += ".";
			a += ans.toString();
		}

		return a;
	}

private:
	BigInteger chislitel = 1;
	BigInteger znaminatel = 1;
	bool is_negative = false;

	BigInteger NOD(BigInteger a, BigInteger b)
	{
		while (a > BigInteger(0) && b > BigInteger(0))
		{
			if (a > b)
			{
				a %= b;
			}


			else
			{
				b %= a;
			}

		}
		return a + b;
	}
};

bool operator ==(const Rational& left, const Rational& right)
{
	if (left.chislitel == right.chislitel && left.znaminatel == right.znaminatel && left.is_negative == right.is_negative)
	{
		return true;
	}

	return false;
}

bool operator < (const Rational& left, const Rational& right)
{
	if (left.is_negative != right.is_negative)
	{
		if (left.is_negative == true) return false;
		else return true;
	}

	return left.chislitel*right.znaminatel < right.chislitel*left.znaminatel;
}

Rational operator +(const Rational& left, const Rational& right)
{
	Rational ans(0);
	ans.chislitel = left.chislitel*right.znaminatel + left.znaminatel*right.chislitel;

	if (ans.chislitel.is_negative == true)
	{
		ans.is_negative = true;
		ans.chislitel.change_sign();
	}

	ans.sokrati();
	return ans;
}

Rational operator - (const Rational& left, const Rational& right)
{
	return left + (-right);
}

Rational operator *(const Rational& left, const Rational& right)
{
	Rational ans(0);
	ans.chislitel = left.chislitel*right.chislitel;
	ans.znaminatel = left.znaminatel*right.znaminatel;

	ans.sokrati();
	if (ans.znaminatel.is_negative == true)
	{
		ans.znaminatel.is_negative = false;
		ans.change_sign();
	}

	return ans;
}

Rational operator /(const Rational& delimoe, const Rational& delitel)
{
	Rational ans;
	ans.chislitel = delimoe.chislitel*delitel.znaminatel;
	ans.znaminatel = delimoe.znaminatel*delitel.chislitel;

	ans.sokrati();
	if (ans.znaminatel.is_negative == true)
	{
		ans.znaminatel.is_negative = false;
		ans.change_sign();
	}

	if (ans.chislitel.is_negative == true)
	{
		ans.chislitel.is_negative = false;
		ans.change_sign();
	}


	return ans;
}

bool operator != (const Rational& left, const Rational& right)
{
	return !(left == right);
}
bool operator <=(const Rational& left, const Rational& right)
{
	return (left < right || left == right);
}
bool operator >(const Rational& left, const Rational& right)
{
	return !(left <= right);
}
bool operator >=(const Rational& left, const Rational& right)
{
	return !(left < right);
}
Rational operator - (const Rational& bigint)
{
	Rational copyInt = bigint;
	copyInt.change_sign();

	return copyInt;
}


int main()
{
	BigInteger a, b;
	cin >> a >> b;

	cout << a * b / b + a - a % 1010;
}