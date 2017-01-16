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

int s[55],ans[55],d[55],a[55];

struct SurveillanceSystem 
{
    string getContainerInfo(string containers, vector <int> reports, int L)
    {
    	int n=containers.size();
    	s[0]=0;
    	for (int i=1;i<=n;i++) s[i]=s[i-1]+(containers[i-1]=='X');
    	int m=reports.size();
    	sort(reports.begin(),reports.end());
    	int j=0;
    	while (j<m)
    	{
    		int k=j;
    		while (k<m&&reports[k]==reports[j]) k++;
    		int cnt=0;
    		for (int i=L;i<=n;i++) if (s[i]-s[i-L]==reports[j]) a[++cnt]=i-L+1;
    		memset(d,0,sizeof(d));
    		for (int i=1;i<=cnt;i++)
    			{
    				d[a[i]]++;d[a[i]+L]--;
    			}
    		for (int i=1;i<=n;i++)
    		{
    			d[i]+=d[i-1];
    			if (cnt-d[i]<k-j) ans[i]=2; else if (d[i]) ans[i]=max(ans[i],1);
    		}
    		j=k;
    	}
    	string ss="";
    	for (int i=1;i<=n;i++)
    	{
    		if (!ans[i]) ss+='-';
    		if (ans[i]==1) ss+='?';
    		if (ans[i]==2) ss+='+';
    	}
    	return ss;
    }
};
