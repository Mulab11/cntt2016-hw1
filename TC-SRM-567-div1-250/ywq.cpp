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

int s[100010];

struct TheSquareRootDilemma 
{
    int countPairs(int N, int M)
    {
    	int ans=0;s[0]=0;
    	for (int j=1;j<=M;j++)
    	{
    		s[j]=s[j-1];
    		int x=sqrt(j+0.5);
    		if (x*x==j) s[j]++;
    	}
        //s[i]=[sqrt(i)]
    	for (int i=1;i<=N;i++)
    	{
    		int t=i,p=1;
    		for (int j=2;j*j<=t;j++)
    			if (t%j==0)
    			{
    				bool k=0;
    				while (t%j==0) {t/=j;k^=1;}
    				if (k) p*=j;
    			}
    		p*=t;
    		ans+=s[M/p];
    	}
    	return ans;
    }
};
