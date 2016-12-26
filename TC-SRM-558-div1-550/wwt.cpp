/*
一开始，对于所有P，求出lx,rx，表示最大的lx，满足x[lx]<bx[p]，最小的rx满足x[rx]>bx[p]，那么合法的A,D点的区间就确定了。
接下来，枚举P,Q,求出在左边哪段区间的x满足X在线PQ的左侧，同理可求出右边区间满足x在PQ的右侧。然后左右端点是独立的，
分别统计一下合法的A,B对数和C,D对数，乘起来就好了。
*/
#include <bits/stdc++.h>

using namespace std;

struct node
{
	int x,y;

	node(void){}
	node(int a,int b) : x(a),y(b){}
};

node operator -(const node &a,const node &b) {return node(a.x - b.x,a.y - b.y);}
int operator ^(const node &a,const node &b) {return a.x * b.y - a.y * b.x;}

class Ear
{
public:
	vector<int> rx,bx,by;

	void get_num(vector<string> base,vector<int> &a)
	{
		a.clear();
		string ch = "";
		for(int i = 0;i < base.size();i ++) ch = ch + base[i];
		int v = 0;
		for(int i = 0;i < ch.length();i ++)
		{
			if (ch[i] >= '0' && ch[i] <= '9')
			{
				v = v * 10 + ch[i] - 48;
			} else
			{
				if (v) a.push_back(v);
				v = 0;
			}
		}
		if (v) a.push_back(v);
	}

	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
	{
		get_num(redX,rx),get_num(blueX,bx),get_num(blueY,by);
		sort(rx.begin(),rx.end());
		static int l[505],r[505];
		for(int i = 0;i < bx.size();i ++)
		{
			r[i] = upper_bound(rx.begin(),rx.end(),bx[i]) - rx.begin();
			l[i] = lower_bound(rx.begin(),rx.end(),bx[i]) - rx.begin() - 1;
		}
		long long ans = 0;
		for(int p = 0;p < bx.size();p ++)
			for(int q = 0;q < bx.size();q ++)
				if (by[p] > by[q])
				{
					node pp = node(bx[p],by[p]),pq = node(bx[q],by[q]);
					int lmx = -1,rmi = rx.size();
					for(int i = 0;i < rx.size();i ++)
					{
						node cx = node(rx[i],0);
						if (((pq - cx) ^ (pp - cx)) > 0) lmx = max(lmx,i); //找到在pq左侧的右端
						if (((pq - cx) ^ (pp - cx)) < 0) rmi = min(rmi,i);//找到在pq右侧的左端
					}	
					int lc = 0,rc = 0;
					for(int i = 0;i <= min(l[p],lmx);i ++)//左端合法的C的个数
						lc += l[q] - i;
					for(int i = max(r[p],rmi);i < rx.size();i ++)//合法的D的个数
						rc += i - r[q];
					ans += lc * rc;
				}
		return ans;
	}
};
