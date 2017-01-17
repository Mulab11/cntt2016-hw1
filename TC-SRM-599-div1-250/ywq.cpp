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

int c[50];

struct BigFatInteger 
{
    int minOperations(int A, int B)
    {
    	int p=0;
    	for (int i=2;i*i<=A;i++)
    		if (A%i==0)
    		{
    			c[++p]=0;
    			while (A%i==0) {c[p]++;A/=i;}
    		}
    	if (A>1) c[++p]=1;
    	int ans=p,ma=0;
    	for (int i=1;i<=p;i++) ma=max(ma,c[i]);
    	ma*=B;ma--;
    	while (ma) {ans++;ma>>=1;}
    	return ans;
    }
};
