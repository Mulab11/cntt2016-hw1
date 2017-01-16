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

string s;

struct TheSwapsDivOne 
{
    double find(vector <string> sequence, int k)
    {
    	s="";
    	for (int i=0;i<sequence.size();i++) s+=sequence[i];
    	int n=s.size();double f[2];
    	f[0]=1;f[1]=0;
    	for (int i=1;i<=k;i++)
    	{
    		double t=f[0]*(n-2)/n+f[1]/(n*(n-1)/2);
    		f[1]=f[0]*2/n+f[1]*(1-1.0/(n*(n-1)/2));
			f[0]=t;
		}
		int sum=0;
		for (int i=0;i<n;i++) sum+=s[i]-'0';
		double ans=0;
		for (int i=0;i<n;i++)
			ans=ans+(f[0]*(s[i]-'0')+f[1]*(sum-(s[i]-'0'))/(n-1))*(double(i+1)*(n-i)*2/n/(n+1));
		return ans;
    }
};
