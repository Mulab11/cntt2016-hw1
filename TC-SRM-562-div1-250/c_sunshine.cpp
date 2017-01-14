#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class PastingPaintingDivOne
{
	public:
	LL cnt[256];
	char s[555][555];
	vector<string> g;
	
	void paste(int x,int y)//paste a pattern whose left-upper corner is at (x,y).
	{
		for(int i=0;i<g.size();i++)
			for(int j=0;j<g[0].size();j++)
				if(g[i][j]!='.')
				{
					//Maintain the number of this color of cells.
					cnt[s[x+i][y+j]]--;
					s[x+i][y+j]=g[i][j];
					cnt[g[i][j]]++;
				}
	}
	
	vector<LL> countColors(vector<string> clipboard,int T)
	{
		memset(s,'.',sizeof(s));
		g=clipboard;
		vector<LL> ans;
		//We can prove the numbers of colors or cells must form an arithmetic progression
		//when pasting more than 100 times.
		if(T<=120)
		{
			for(int i=0;i<T;i++)
				paste(i,i);
		}
		else
		{
			for(int i=0;i<100;i++)
				paste(i,i);
			LL cR,cG,cB;
			cR=cnt['R'];
			cG=cnt['G'];
			cB=cnt['B'];
			paste(100,100);
			//s[T]=(s[101]-s[100])*(T-100) since T > 100 and s[100..T] is an arithmetic progression.
			cnt['R']=cR+((LL)cnt['R']-cR)*(T-100);
			cnt['G']=cG+((LL)cnt['G']-cG)*(T-100);
			cnt['B']=cB+((LL)cnt['B']-cB)*(T-100);
		}
		ans.push_back(cnt['R']);
		ans.push_back(cnt['G']);
		ans.push_back(cnt['B']);
		return ans;
	}
};

