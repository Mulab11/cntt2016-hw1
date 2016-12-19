#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;
#include <sstream>

int pl[310], pr[310], pre[310][310];
int f[310][310];

class WolfInZooDivOne
{
public:
	int count(int N, vector<string> inpl, vector<string> inpr)
	{
		stringstream in;
		for(int i = 0; i != (int) inpl.size(); ++i) in << inpl[i];
		in << "  ";
		for(int i = 0; i != (int) inpr.size(); ++i) in << inpr[i];
		int M;
		{
			string instr = in.str();
			M = std::count(instr.begin(), instr.end(), ' ') / 2;
		}
		for(int i = 0; i != M; ++i) in >> pl[i], ++pl[i];
		for(int i = 0; i != M; ++i) in >> pr[i], ++pr[i];
		for(int l = 1; l <= N; ++l)
			for(int r = l + 1; r <= N; ++r)
			{
				int &ret = pre[l][r];
				ret = l - 1;
				for(int k = 0; k != M; ++k)
					if(pl[k] <= l && r <= pr[k])
						ret = min(ret, pl[k] - 1);
			}
		int ans = 1;
		for(int i = 1; i <= N; ++i)
		{
			ans += (f[i][0] = 1);
			for(int j = 1; j != i; ++j)
			{
				(ans += (f[i][j] = f[j][pre[j][i]])) %= mod;
				(f[i][j] += f[i][j - 1]) %= mod;
			}
		}
		return ans;
	}
}	user;