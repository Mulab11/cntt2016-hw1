#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class TheNumberGameDivOne
{
public:
	string find(ll N)
	{
		// 如果是 2 的奇数次幂，或是奇数，挂
		return (N % 2 || (N == (N & -N) && __builtin_ctzll(N) % 2)) ? "Brus" : "John";
	}
}	user;
