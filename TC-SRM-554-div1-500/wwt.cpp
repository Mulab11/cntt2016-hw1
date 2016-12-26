/*
注意到有序的排肯定是最优的，字典序最小的话就逐位确定，计算接下来的最优值是否等于原来的最优值即可。
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> a;

bool cmp(int x,int y) {return a[x] < a[y];}


class TheBrickTowerMediumDivOne
{
public:
	vector<int> find(vector<int> h)
	{
		a = h;
		int n = h.size(),mp = 0,sum = 0;
		for(int i = 0;i < n;i ++)
		{
			if (a[i] < a[mp]) mp = i;
			sum += a[i];
		}
		sum -= a[mp];
		static int ch[55];
		memset(ch,0,sizeof ch);
		vector<int> p;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (!ch[j])
				{
					ch[j] = 1;
					static int els[55],pc[55];
					int cnt = 0;
					for(int k = 0;k < n;k ++)
						if (!ch[k]) els[cnt ++] = k; //剩下的还没放的位置
					sort(els,els + cnt,cmp); //贪心，按a递增来排
					for(int k = 0;k < i;k ++) pc[k] = p[k];
					pc[i] = j;
					for(int k = 0;k < cnt;k ++) pc[i + k + 1] = els[k];
					int v = 0;
					for(int k = 0;k < n - 1;k ++)
						v += max(a[pc[k]],a[pc[k + 1]]); //算最优下的权值
					if (v == sum) {p.push_back(j);break;}
					ch[j] = 0;						
				}
		return p;
	}
};
