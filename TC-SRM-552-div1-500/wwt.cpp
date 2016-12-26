/*
两个矩阵(x,y,x1,y1),(x2,y2,x3,y3)不重叠，必然满足x1<x2或x>x3或y1 < y2或y > y3，我们考虑第一种情况，其他对称翻转一下都能做，
我们可以暴力枚举矩阵，然后把这个矩阵的信息记录在x1上，当枚举到x时，把所有x1<x的情况都考虑一下贡献即可（维护一个前缀max）。
*/
#include <bits/stdc++.h>

using namespace std;

const char str[2] = {'L','P'};

class FoxAndFlowerShopDivOne
{
public:
	int calc(int s[][35],int l,int r,int i,int j)
	{
		return s[r + 1][j + 1] - s[l][j + 1] - s[r + 1][i] + s[l][i]; //子矩阵和
	}

	int work(vector<string> &a,int maxi)
	{
		static int f[1805],sav[35][1805],s[2][35][35];
		memset(f,200,sizeof f);
		memset(sav,200,sizeof sav);
		int tmp = -1,n = a.size(),m = a[0].length();
		for(int x = 0;x < 2;x ++)
			for(int i = 1;i <= n;i ++)
				for(int j = 1;j <= m;j ++)
					s[x][i][j] = s[x][i - 1][j] + s[x][i][j - 1] - s[x][i - 1][j - 1] + (a[i - 1][j - 1] == str[x]); //二维前缀和
		for(int l = 0;l < n;l ++)
		{
			static int cur[1805];
			memset(cur,200,sizeof cur);
			for(int r = l;r < n;r ++)
				for(int i = 0;i < m;i ++)
					for(int j = i;j < m;j ++)
					{
						int l_c = calc(s[0],l,r,i,j),p_c = calc(s[1],l,r,i,j),po = l_c - p_c + 900; //+900:避免下标<0
						cur[po] = max(cur[po],l_c + p_c);
						sav[r][po] = max(sav[r][po],l_c + p_c);
					}
			for(int i = 0;i <= 1800;i ++)
				if (cur[i] >= 0)
					for(int j = max(0,1800 - maxi - i);j <= min(1800,1800 + maxi - i);j ++)
						if (f[j] >= 0) tmp = max(tmp,cur[i] + f[j]); //更新答案，合并
			for(int i = 0;i <= 1800;i ++)
				f[i] = max(f[i],sav[l][i]); //前缀max
		}
		return tmp;
	}

	int theMaxFlowers(vector<string> flowers,int maxDiff)
	{
		int ans = work(flowers,maxDiff);
		vector<string> els;
		int n = flowers.size(),m = flowers[0].length();
		for(int j = 0;j < m;j ++)
		{
			string a = "";
			for(int i = 0;i < n;i ++) a = a + flowers[i][j];
			els.push_back(a);
		}		
		ans = max(ans,work(els,maxDiff));
		return ans;
	}
};
