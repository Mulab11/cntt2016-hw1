#include<bits/stdc++.h>
using namespace std;
int n,i,t,f,O=1e9+1;
long long x,m;
class Suminator//模拟
{
    public:
        int findMissing(vector<int> a,int M)
        {
        	for(m=M,n=a.size(),i=n-1;~i;i--){if(a[i]<1)t++;else if(t-->=0)x+=a[i];if(t<0)break;}
        	if(x==m)return 0;
        	for(t=0,i=n-1;~i;i--){if(!a[i])t++;else if(t-->=0)a[i]>0?m-=a[i]:f=1;if(t<0)break;}
        	if(f)return m>0&&m<O?m:-1;
        	return m?-1:1;
        }
};
