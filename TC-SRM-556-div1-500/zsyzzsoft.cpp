#include <algorithm>
using namespace std;
class LeftRightDigitsGame2
{
public:
	int n;
	string f[50][50][3];
	int Cmp(char a, char b)
	{
		return a < b ? 0 : a > b ? 2 : 1;
	}
	string Min(string &a, const string &b)
	{
		if(b.length() > 1)
			a = a.empty() ? b : min(a, b);
		return a;
	}
	string minNumber(string digits, string bound)
	{
		n = digits.size();
		if(n == 1)
			return digits[0] >= bound[0] ? digits : "";
		for(int i = 0; i < n; i++)
			f[i][i][Cmp(digits[0], bound[i])] = digits[0];
		for(int d = 1; d < n; d++)
		{
			for(int i = 0, j = d; j < n; i++, j++)
			{
				Min(f[i][j][0], f[i][j - 1][0] + digits[d]); //放到右边 
				Min(f[i][j][Cmp(digits[d], bound[j])], f[i][j - 1][1] + digits[d]);
				Min(f[i][j][2], f[i][j - 1][2] + digits[d]);
				int cmp = Cmp(digits[d], bound[i]);
				Min(f[i][j][cmp / 2 * 2], string(&digits[d], 1) + f[i + 1][j][0]); //放到左边 
				Min(f[i][j][cmp], string(&digits[d], 1) + f[i + 1][j][1]);
				Min(f[i][j][(cmp + 1) / 2 * 2], string(&digits[d], 1) + f[i + 1][j][2]);
			}
		}
		return Min(f[0][n - 1][1], f[0][n - 1][2]);
	}
};
