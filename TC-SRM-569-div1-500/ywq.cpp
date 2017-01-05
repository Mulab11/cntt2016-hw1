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

const int inf=2000000000;

int a[25],b[25];

struct TheJediTest 
{
    int minimumSupervisors(vector <int> students, int K)
    {
    	int n=students.size(),ans=inf;
    	for (int i=0;i<(1<<(n-1));i++)
    	{
    		for (int j=0;j<n;j++) a[j]=students[j];
    		memset(b,0,sizeof(b));
    		for (int j=0;j<n-1;j++)
    			if (i&(1<<j))
    			{
    				b[j+1]=a[j];a[j]=0;
    			}
    			else
    			{
    				int t=min(a[j+1],(K-(a[j]+b[j])%K)%K);
    				a[j]+=t;a[j+1]-=t;
    			}
    		int tmp=0;
    		for (int j=0;j<n;j++) tmp+=(a[j]+b[j]+K-1)/K;
    		ans=min(ans,tmp);
    	}
    	return ans;
    }
};
