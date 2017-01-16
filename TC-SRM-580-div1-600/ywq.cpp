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
int s[2510],t[2510],a[2510],b[2510],dp[2510][2510],g[2510][2510],L[2510],R[2510];

struct ShoutterDiv1 
{
    int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)
    {
    	int n=0;
    	for (int i=0;i<s1000.size();i++)
    		for (int j=0;j<s1000[i].size();j++)
    		{
    			s[n]=s[n]*10+s1000[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<s100.size();i++)
    		for (int j=0;j<s100[i].size();j++)
    		{
    			s[n]=s[n]*10+s100[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<s10.size();i++)
    		for (int j=0;j<s10[i].size();j++)
    		{
    			s[n]=s[n]*10+s10[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<s1.size();i++)
    		for (int j=0;j<s1[i].size();j++)
    		{
    			s[n]=s[n]*10+s1[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<t1000.size();i++)
    		for (int j=0;j<t1000[i].size();j++)
    		{
    			t[n]=t[n]*10+t1000[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<t100.size();i++)
    		for (int j=0;j<t100[i].size();j++)
    		{
    			t[n]=t[n]*10+t100[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<t10.size();i++)
    		for (int j=0;j<t10[i].size();j++)
    		{
    			t[n]=t[n]*10+t10[i][j]-'0';
    			n++;
    		}
    	n=0;
    	for (int i=0;i<t1.size();i++)
    		for (int j=0;j<t1[i].size();j++)
    		{
    			t[n]=t[n]*10+t1[i][j]-'0';
    			n++;
    		}
    	for (int i=0;i<n;i++) {a[i]=s[i];b[i]=t[i];}
    	sort(a,a+n);int m1=1;
    	for (int i=1;i<n;i++) if (a[i]!=a[i-1]) a[m1++]=a[i];
    	sort(b,b+n);int m2=1;
    	for (int i=1;i<n;i++) if (b[i]!=b[i-1]) b[m2++]=b[i];
    	for (int i=0;i<n;i++)
    	{
    		s[i]=lower_bound(a,a+m1,s[i])-a;
    		t[i]=lower_bound(b,b+m2,t[i])-b;
    	}
    	int mi=t[0],ma=s[0];
    	for (int i=1;i<n;i++)
    	{
    		mi=min(mi,t[i]);ma=max(ma,s[i]);
    	}
    	for (int i=0;i<n;i++) g[s[i]][t[i]]=-1;
    	for (int i=0;i<m1;i++)
    	{
    		L[i]=i;
    		for (int j=0;j<n;j++)
    			if (b[t[j]]>=a[i]) L[i]=min(L[i],s[j]);
    	}
    	for (int i=0;i<m2;i++)
    	{
    		R[i]=i;
    		for (int j=0;j<n;j++)
    			if (a[s[j]]<=b[i]) R[i]=max(R[i],t[j]);
    	}
    	for (int p=0;p<m1;p++)
    		for (int q=m2-1;q>=0;q--)
    		{
    			int tmp=inf;
    			if (p) tmp=min(g[p-1][q],tmp);
    			if (q+1<m2) tmp=min(g[p][q+1],tmp);
    			if (a[p]>b[q]) break;
    			if (a[p]<=b[mi]&&b[q]>=a[ma]) 
    			{
    				dp[p][q]=0;
    				if (g[p][q]==-1) g[p][q]=0; else g[p][q]=tmp;
    				continue;
    			}
    			dp[p][q]=inf;
    			dp[p][q]=min(min(min(dp[L[p]][q],dp[p][R[q]]),tmp)+1,dp[p][q]);
    			if (g[p][q]==-1) g[p][q]=min(dp[p][q],tmp); else g[p][q]=tmp;
    		}
    	int ans=0;
    	for (int i=0;i<n;i++)
    	{
    		if (dp[s[i]][t[i]]==inf) return -1;
    		ans+=dp[s[i]][t[i]];
    	}
    	return ans;
    }
};
