#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

string A = "Ciel";
string B = "Liss";
string N = "Draw";

class FoxAndFencing
{
public:
	string WhoCanWin(int a, int b, int c, int d, int e)
	{
		// 刚开始就赢了/输了
		if(e <= a + c) return A;
		if(e + a <= b + d) return B;
		if(a == b) return N; // 这样能不断朝一个方向移动，挂
		// 后面才赢得
		if(a > b) 	{if(a + c > b * 2 + d) return A;}
		else	 	{if(b + d > a * 2 + c) return B;}
		return N;
	}
}	user;
