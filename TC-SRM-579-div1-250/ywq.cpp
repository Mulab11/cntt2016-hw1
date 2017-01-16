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

int l[55];

struct UndoHistory 
{
    int minPresses(vector <string> lines)
    {
    	int n=lines.size();
    	int ans=l[0]=lines[0].size();
    	ans++;
    	for (int i=1;i<n;i++)
    	{
    		int ma=0;l[i]=lines[i].size();
    		for (int j=0;j<i;j++)
    			for (int k=0;k<l[i]&&k<l[j]&&lines[i][k]==lines[j][k];k++)
    				ma=max(ma,k+1);
    		if (l[i-1]<=l[i])
    		{
    			bool ok=1;
    			for (int j=0;j<l[i-1];j++) if (lines[i][j]!=lines[i-1][j]) ok=0;
    			if (ok) ma=max(ma,l[i-1]+2);
    		}
    		ans+=l[i]-ma+3;
    	}
    	return ans;
    }
};
