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

ll f[55];

struct XorAndSum 
{
    long long maxSum(vector<long long> number)
    {
    	int n=number.size(),k=0;
        //Gaussian elimination
    	for (int i=60;i>=0;i--)
    	{
    		for (int j=k;j<n;j++)
    			if (number[j]&(1ll<<i))
    			{
    				swap(number[j],number[k]);
    				for (int p=k+1;p<n;p++) if (number[p]&(1ll<<i)) number[p]^=number[k];
    				f[k++]=1ll<<i;
    				break;
    			}
    	}
    	for (int i=k-1;i>0;i--)
    		for (int j=0;j<i;j++)
    			if (number[j]&f[i]) number[j]^=number[i];
    	for (int i=1;i<k;i++) number[0]^=number[i];
        for (int i=1;i<n;i++) number[i]^=number[0];
        ll ans=0;
        for (int i=0;i<n;i++) ans+=number[i];
        return ans;
    }
};
