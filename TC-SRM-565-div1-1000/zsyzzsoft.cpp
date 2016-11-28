#include <algorithm>
#include <map>
using namespace std;
const int p = 1000000009;
class UnknownTree
{
public:
	int n;
	int Solve(int *a, int *b, int *c, int da, int db, int dc) //已知中间点到ABC的距离，求方案数 
	{
		if(da <= 0 || db <= 0 || dc < 0)
			return 0;
		map<pair<int, int>, vector<int> > pos;
		for(int i = 0; i < n; i++)
		{
			long long x = 0;
			int y = 0, d = 0, flag = 0;
			if(a[i] - b[i] == da - db) //在C臂上 
				x = (long long)dc + da + c[i] - a[i], y = c[i], d = dc, flag = -1;
			else if(b[i] - c[i] == db - dc) //在A臂上 
				x = (long long)da + db + a[i] - b[i], y = a[i], d = da, flag = 0;
			else if(c[i] - a[i] == dc - da) //在B臂上 
				x = (long long)db + dc + b[i] - c[i], y = b[i], d = db, flag = 1;
			else
				return 0;
			if(x < 0 || x > d * 2 || x % 2 == 1) //在臂上的位置 
				return 0;
			x /= 2;
			y -= x; //多余部分的长度 
			pos[make_pair(x, flag)].push_back(y);
		}
		int ret = 1;
		for(auto it = pos.begin(); it != pos.end(); ++it)
		{
			vector<int> &vec = it->second;
			sort(vec.begin(), vec.end());
			if(it->first.first && (vec[0] || (vec.size() > 1 && vec[1] == 0)))
				return 0; //臂长大于0，即不与ABC重合时，必须有且仅有一个点恰好在臂上 
			for(int i = 1, j = 0; i < vec.size(); i++)
			{
				if(vec[i - 1] < vec[i])
					j = i - (vec[0] == 0);
				ret = (long long)ret * (j + 1) % p; //计算同一点上分岔的方案数 
			}
		}
		return ret;
	}
	int Tree(int *a, int *b, int *c)//存在一个中心点共同连接着ABC 
	{
		pair<int, int> center(2147483647, -1); //中心点一定是距离之和最短的点 
		for(int i = 0; i < n; i++)
			center = min(center, make_pair(-2000000000 + a[i] + b[i] + c[i], i)); //防止爆int 
		swap(a[0], a[center.second]);
		swap(b[0], b[center.second]);
		swap(c[0], c[center.second]);
		return Solve(a, b, c, a[0], b[0], c[0]);
	}
	long long Line(int *a, int *b, int *c) //ABC形成一条链，C在中间 
	{
		pair<int, int> center(2147483647, -1); //枚举距离C最短的点的相对位置，并计算ABC之间的距离 
		for(int i = 0; i < n; i++)
			center = min(center, make_pair(c[i], i));
		swap(a[0], a[center.second]);
		swap(b[0], b[center.second]);
		swap(c[0], c[center.second]);
		return ((long long)Solve(a, b, c, a[0] - c[0], b[0] - c[0], 0) +
			Solve(a, b, c, a[0] + c[0], b[0] - c[0], 0) +
			Solve(a, b, c, a[0] - c[0], b[0] + c[0], 0) +
			Solve(a, b, c, c[0] - a[0], b[0] - c[0], 0) +
			Solve(a, b, c, a[0] - c[0], c[0] - b[0], 0)) % p;
	}
	int getCount(vector<int> va, vector<int> vb, vector<int> vc)
	{
		n = va.size();
		int *a = &va[0], *b = &vb[0], *c = &vc[0];
		return ((long long)Line(a, b, c) + Line(b, c, a) + Line(c, a, b) + Tree(a, b, c)) % p;
	}
};
