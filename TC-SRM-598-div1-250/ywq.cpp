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

int s[310];

struct BinPacking 
{
    int minBins(vector <int> item)
    {
    	int n=item.size();
    	int tmp=n,x=0;
    	for (int i=0;i<n;i++) if (item[i]==100) x++;
    	for (int j=0;j<=x/3;j++)
    	{
    		memset(s,0,sizeof(s));
    		for (int i=0;i<n;i++) s[item[i]]++;
    		int ans=j;s[100]-=j*3;
    		int k=200;
    		for (int i=100;i<=k;i++)
    			while (s[i])
    			{
    				while (i<=k&&(i+k>300||!s[k])) k--;
    				if (i==k&&s[i]==1||i>k) break;
    				s[i]--;s[k]--;ans++;
    			}
    		for (int i=100;i<=300;i++) ans+=s[i];
    		tmp=min(tmp,ans);
    	}
    	return tmp;
    }
};
