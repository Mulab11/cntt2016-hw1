#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;

class PastingPaintingDivOne
{
	private:
	int mp[300], n, m;//n * m board
	int f[55][55];//f[i][j]: min k where clipboard[i + k][j + k] is not '.'
	vector <long long> force(vector<string> clipboard, int T)//for debug
	{
		mp['R'] = 0, mp['G'] = 1, mp['B'] = 2;
		vector <long long> ans(3, 0);
		char a[200][200];
		memset(a, '.', sizeof(a));
		n = clipboard.size(), m = clipboard[0].size();
		for(int k = 0; k < T; k++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
				{
					if(clipboard[i][j] == '.')
						continue;
					if(a[k + i][k + j] != '.')
						ans[mp[a[k + i][k + j]]]--;
					ans[mp[a[k + i][k + j] = clipboard[i][j]]]++;
				}
		return ans;
	}
	public:
	vector<long long> countColors(vector<string> clipboard, int T)
	{
		mp['R'] = 0, mp['G'] = 1, mp['B'] = 2;//map "RGB" to "012"
		vector <long long> ans(3, 0);
		const int minnm = min(T, min(n = clipboard.size(), m = clipboard[0].size()));
		string now(n + m - 1, '.');
		/*
		   .
		   . -> now
		....
		*/
		for(int i = 0; i < minnm; i++)//calculate the effect of the last min(T,n,m) steps to string "now"
		{
			for(int j = 0; j < m - i; j++)
				if(clipboard[n - i - 1][j] != '.')
					now[i + j] = clipboard[n - i - 1][j];
			for(int j = 0; j < n - i - 1; j++)
				if(clipboard[j][m - i - 1] != '.')
					now[n + m - 2 - i - j] = clipboard[j][m - i - 1];
			for(int j = 0; j < n + m - 1; j++)
				if(now[j] != '.')
					ans[mp[now[j]]]++;
			/*
			e.g. if the clipboard is
			..G
			R..
			BG.
			then string "now" is
			"BG..G" after i = 0,
			"BR..G" after i = 1,
			"BR..G" after i = 2.
			*/
		}
		for(int j = 0; j < n + m - 1; j++)
			if(now[j] != '.')
				ans[mp[now[j]]] += T - minnm;
		/*
		e.g. if the clipboard is
		..G
		R..
		BG.
		and T = 3, the result is
		..G  
		R..G 
		BR..G
		 BR..
		  BG.
		we've got the answer of
		  G  
		  .G 
		BR..G
		 BR..
		  BG.
		so now we should calculate the answer of
		..
		R.
		*/
		memset(f, 31, sizeof(f));
		for(int i = n - 2; i >= 0; i--)
			for(int j = m - 2; j >= 0; j--)
				f[i][j] = clipboard[i][j] == '.' ? f[i + 1][j + 1] + 1 : 0;
		for(int i = 0; i < n - 1; i++)
			for(int j = 0; j < m - 1; j++)
			{
				int tmp = min(min(i, j), T - 1);
				if((tmp -= f[i - tmp][j - tmp]) >= 0)//tmp = max k < T where clipboard[i - k][j - k] is not '.'
					ans[mp[clipboard[i - tmp][j - tmp]]]++;
			}
		return ans;
	}
};

