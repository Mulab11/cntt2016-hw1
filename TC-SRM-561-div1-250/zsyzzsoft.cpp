#include <algorithm>
using namespace std;
int Cmp(int a, int b)
{
	return a > b;
}
class ICPCBalloons
{
public:
	int minRepaintings(vector<int> count, string sz, vector<int> goal)
	{
		int n = goal.size(), m = count.size(), suma = 0, sumb = 0, sum = 0;
		for(int i = 0; i < n; i++)
			sum += goal[i];
		vector<int> a, b;
		for(int i = 0; i < m; i++)
			a.push_back(sz[i] == 'M' ? count[i] : 0), b.push_back(sz[i] == 'L' ? count[i] : 0);
		sort(a.begin(), a.end(), Cmp); //按大小分开排序 
		sort(b.begin(), b.end(), Cmp);
		for(int i = 0; i < m; i++)
			suma += a[i], sumb += b[i];
		int ans = -1;
		for(int i = 0; i < 1 << n; i++) //枚举大小 
		{
			vector<int> va, vb;
			int sa = 0, sb = 0;
			for(int j = 0; j < n; j++)
				va.push_back((i >> j) % 2 == 0 ? goal[j] : 0), vb.push_back((i >> j) % 2 == 1 ? goal[j] : 0);
			sort(va.begin(), va.end(), Cmp);
			sort(vb.begin(), vb.end(), Cmp);
			int match = 0;
			for(int j = 0; j < n; j++)
				sa += va[j], sb += vb[j];
			for(int j = 0; j < n && j < m; j++) //不用改颜色的数量 
				match += min(va[j], a[j]) + min(vb[j], b[j]);
			if(sa <= suma && sb <= sumb) //总数够用 
				ans = max(ans, match);
		}
		return ans < 0 ? -1 : sum - ans;
	}
};
