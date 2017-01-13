#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int inf=1000000000;

int a[52];
bool exist[26];

struct NextAndPrev 
{
    int getMinimum(int nextCost, int prevCost, string start, string goal)
    {
    	if (start==goal) return 0;
    	memset(a,-1,sizeof(a));
    	for (int i=0;i<start.size();i++)
    		if (a[start[i]-'a']==-1)
    			a[start[i]-'a']=goal[i]-'a';
    		else
    			if (a[start[i]-'a']!=goal[i]-'a') return -1;
    	memset(exist,0,sizeof(exist));
    	for (int i=0;i<goal.size();i++) exist[goal[i]-'a']=1;
    	bool ok=1;
    	for (int i=0;i<26;i++) if (!exist[i]) ok=0;
    	if (ok) return -1;
    	int ans=inf;
    	for (int i=0;i<26;i++)
    	{
    		a[26+i]=a[i];
    		bool ok=1;
    		for (int j=i;j<26+i;j++)
    			for (int k=j+1;k<26+i;k++)
    				if (a[j]!=-1&&a[k]!=-1&&a[j]>a[k]) ok=0;
    		if (!ok) continue;
    		for (int t=-1;t<=2;t++)
    		{
    			int tmp=0;
    			for (int j=0;j<26;j++)
    				if (exist[j])
    				{
    					int mi=52,ma=-1;
    					for (int k=i;k<26+i;k++) if (a[k]==j) {mi=min(mi,k);ma=max(ma,k);}
    					tmp+=prevCost*max(ma-j-t*26,0)+nextCost*max(j+t*26-mi,0);
    				}
    			if (tmp==5) return t;
    			ans=min(ans,tmp);
    		}
    	}
    	if (ans==inf) return -1; else return ans;
    }
};
