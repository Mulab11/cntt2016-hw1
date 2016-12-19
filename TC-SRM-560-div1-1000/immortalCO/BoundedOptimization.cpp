#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

int N, v[13];
bool e[13][13];
double x[13];
vector<int> lll, rrr;

class BoundedOptimization
{
	double calc()
	{
		double ans = 0;
		for(int i = 0; i != N; ++i)
			for(int j = i + 1; j != N; ++j)
				if(e[i][j]) ans += x[i] * x[j];
		return ans;
	}
public:
	double maxValue(vector<string> inp, vector<int> ll, vector<int> rr, int sum)
	{
		lll = ll;
		rrr = rr;
		N = ll.size();
		string E;
		for(int i = 0; i != (int) inp.size(); ++i) E += inp[i];
		for(int i = 0; i < (int) E.size(); i += 3)
			e[E[i] - 'a'][E[i + 1] - 'a'] = 
			e[E[i + 1] - 'a'][E[i] - 'a'] = 1;
		srand(2341);
		// 随机出一个解
		for(int i = 0; i != N; ++i) sum -= ll[i], v[i] = i;
		random_shuffle(v, v + N);
		for(int i = 0; i != N; ++i) 
		{
			sum -= (x[v[i]] = min(sum, rr[v[i]] - ll[v[i]]));
			x[v[i]] += ll[v[i]];
		}
		// 每次随机两个位置，然后假设它们的和不变，调整为最优
		double ans = 0;
		for(int T = 0; T <= 5000000; )
		{
			int p = rand() % N, q = rand() % N;
			if(p == q) continue;
			const double s = x[p] + x[q];
			const double l = max((double) ll[p], s - rr[q]), r = min((double) rr[p], s - ll[q]);
			// 求出新的 x 的系数
			double a = 0, b = 0;
			for(int i = 0; i != N; ++i)
			{
				if(e[p][i] && q != i) a += x[i];
				if(e[q][i] && p != i) b += x[i];
			}
			double nx;
			if(T % 100000)
			{
				if(e[p][q]) 
				{
					nx = (a - b + s) / 2;
					if(nx > r) nx = r; if(nx < l) nx = l;
				}
				else nx = (a < b) ? l : r;
			}
			else 
			{
				ans = max(ans, calc());
				nx = l + (r - l) * (rand() % (1000001)) / 1000000;
			}
			x[p] = nx;
			x[q] = s - nx;
			++T;
		}
		return ans;
	}
}	user;