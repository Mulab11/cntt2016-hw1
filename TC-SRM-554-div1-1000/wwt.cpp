/*
注意到每一层转移到下一层时只与这一层的颜色相同状态有关，bell(4)=15，那么总状态只有15*8种，转移矩阵暴力搞，然后矩阵快速幂即可。注意模数。
*/
#include <bits/stdc++.h>

using namespace std;

const int mo = 1234567891;

struct mat
{
	int a[125][125],n;

	int* operator[](int x)
	{
		return a[x];
	}

	void init()
	{
		n = 121;
		memset(a,0,sizeof a);
	}

	void set_I()
	{
		for(int i = 0;i < n;i ++) a[i][i] = 1;
	}
};

mat operator *(mat &a,mat &b)
{
	mat tmp;
	tmp.init();
	for(int i = 0;i < a.n;i ++)
		for(int k = 0;k < a.n;k ++)
			if (a[i][k])
				for(int j = 0;j < a.n;j ++)
					if (b[k][j])
						tmp[i][j] = (tmp[i][j] + a[i][k] * 1ll * b[k][j]) % mo;
	return tmp;
}

class TheBrickTowerHardDivOne
{
public:
	mat trans,fir;
	int sta[20][5],bel[5],tot,__c,cur;

	void dfs_sta(int n,int m)
	{
		if (n == 4)
		{
			++ tot;
			for(int i = 0;i < 4;i ++) sta[tot - 1][i] = bel[i];
			sta[tot - 1][4] = m;
			return;
		}
		for(int i = 0;i < m;i ++) bel[n] = i,dfs_sta(n + 1,m);
		bel[n] = m,dfs_sta(n + 1,m + 1);
	}

	void get_trans(int n,int m) //找到颜色集合到另一个颜色集合转移的方案数
	{
		if (n == 4)
		{
			int coef = 1;
			for(int i = sta[cur][4];i < m;i ++) //这种集合下的方案数
				coef = (coef * 1ll * (__c - i)) % mo;
			static int ns[4];
			ns[0] = 0;
			int nm = 1,nxt;
			for(int i = 1;i < 4;i ++)//重标号
			{
				bool get = 0;
				for(int j = 0;j < i;j ++) if (bel[i] == bel[j]) {ns[i] = ns[j];get = 1;break;}
				if (!get) ns[i] = nm ++; 
			}
			for(int i = 0;i < tot;i ++)
			{
				bool eq = 1;
				for(int j = 0;j < 4;j ++) if (ns[j] != sta[i][j]) {eq = 0;break;}
				if (eq) {nxt = i;break;}
			}
			int bonus = 0; //相同的对数
			for(int i = 0;i < 4;i ++)
				if (bel[i] == sta[cur][i]) ++ bonus;//上下层
			for(int i = 0;i < 4;i ++)
				if (bel[i] == bel[(i + 1) % 4]) ++ bonus;//同一层
			for(int k = 0;k < 8;k ++)
				if (k + bonus > 7) break; else
					trans[k * tot + cur][(k + bonus) * tot + nxt] = (coef + 0ll + trans[k * tot + cur][(k + bonus) * tot + nxt]) % mo;
			return;
		}
		for(int i = 0;i < m;i ++) bel[n] = i,get_trans(n + 1,m);
		bel[n] = m,get_trans(n + 1,m + 1);
	}

	int find(int C, int K,long long H)
	{
		__c = C;
		trans.init();fir.init();
		dfs_sta(0,0);
		for(int i = 0;i < tot;i ++)
		{
			int bonus = 0,bas = 1;
			for(int j = 0;j < sta[i][4];j ++) bas = bas * 1ll * (__c - j) % mo;
			for(int j = 0;j < 4;j ++)
				if (sta[i][j] == sta[i][(j + 1) % 4]) ++ bonus;
			fir[0][bonus * tot + i] = bas; //第一层的方案
		}
		for(int i = 0;i < tot;i ++)
		{
			cur = i;
			get_trans(0,sta[i][4]);
		}
		for(int k = 0;k < (K + 1) * tot;k ++)
			trans[k][8 * tot] = 1;
		trans[8 * tot][8 * tot] = 1;
		for(;H;H >>= 1)
		{
			if (H & 1) fir = fir * trans;
			trans = trans * trans;
		}
		return fir[0][8 * tot];
	}
};
