#include<bits/stdc++.h>
#define LL long long
using namespace std;
int i,j,k,m,v[60];
LL x;
vector<LL> e,s;
class BitwiseAnd
{
	public:
		vector<LL> lexSmallest(vector<LL> a,int n)
		{
			s=a;s.resize(n);m=a.size();
			for(i=0;i<m;i++)for(j=0;j<60;j++)if(a[i]>>j&1)v[j]=1;
			for(i=0;i<m;i++)for(j=i+1;j<m;j++)if(!(a[i]&a[j]))return e;
			for(i=0;i<m;i++)for(j=i+1;j<m;j++)for(k=j+1;k<m;k++)if(a[i]&a[j]&a[k])return e;
			for(i=0;i<m;i++)for(j=i+1;j<m;j++)x=a[i]&a[j],a[i]^=x,a[j]^=x;
			for(i=m;i<n;i++)
			{
				for(j=0;j<m;j++)
				{
					if(!a[j])return e;
					for(k=0;!(a[j]>>k&1);k++);
					a[j]^=1ll<<k;s[i]^=1ll<<k;
				}
				for(j=i+1;j<n;j++)
				{
					for(k=0;k<60&&v[k];k++);
					if(k==60)return e;
					v[k]=1;
					s[j]^=1ll<<k;s[i]^=1ll<<k;
				}
			}
			sort(s.begin(),s.end());
			return s;
		}
};
