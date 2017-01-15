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

int n,l,r,m;
ll f[40];
string s,w;

ll dfs(int k,ll t,int z)
{
	if (t==0) //the intersection is empty
	{
		bool ok=0;
		for (int i=k;i<n;i++) if (f[i]!=-1) ok=1;
		if (!ok) return z; else return 0;
	}
	if (k>=n)
	{
		ll s=1;
		while (t) {if (t&1) s<<=1;t>>=1;}
		return s*z;
	}
	ll s=dfs(k+1,t,z);
	if (f[k]!=-1) s+=dfs(k+1,t&f[k],-z);
	return s;
}

struct MapGuessing 
{
    long long countPatterns(string goal, vector <string> code)
    {
    	n=goal.size();s="";
    	for (int i=0;i<code.size();i++) s+=code[i];
    	m=s.size();
    	int k=0;l=0;r=0;
    	for (int i=0;i<m;i++)
    	{
    		if (s[i]=='<') k--;
    		if (s[i]=='>') k++;
    		l=min(l,k);r=max(r,k);
    	}
    	for (int i=0;i<n;i++)
    	{
    		w=goal;
    		if (i+l>=0&&i+r<n)
    		{
    			int k=i;ll t=0;f[i]=0;
    			for (int j=0;j<m;j++)
    			{
    				if (s[j]=='<') k--;
    				if (s[j]=='>') k++;
    				if (s[j]=='0'||s[j]=='1')
    				{
    					t|=(1ll<<k);
    					bool ok=1;w[k]=s[j];
    					for (int p=0;p<n;p++) if (w[p]!=goal[p]) ok=0;
    					if (ok) f[i]=t;//all the positions after operations are the same as goal
    				}
    			}
    		}
    		else
    			f[i]=-1;
    	}
    	return dfs(0,(1ll<<n)-1,-1)+(1ll<<n);
    }
};
