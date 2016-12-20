#include<bits/stdc++.h>
#define vs vector<string>
using namespace std;
pair<int,int> a[2555];
string I,J,K,L,M,N,O,P;
int i,s,j,k,r,n,R=2555;
class ShoutterDiv1
{
	public:
		int count(vs A,vs B,vs C,vs D,vs E,vs F,vs G,vs H)
		{
			for(;i<A.size();i++)I+=A[i],J+=B[i],K+=C[i],L+=D[i],M+=E[i],N+=F[i],O+=G[i],P+=H[i];
			for(n=I.size(),i=0;i<n;i++)a[i]=make_pair((I[i]-48)*1000+(J[i]-48)*100+(K[i]-48)*10+L[i]-48,(M[i]-48)*1000+(N[i]-48)*100+(O[i]-48)*10+P[i]-48),R=min(R,a[i].second);
			for(sort(a,a+n),i=0;i<n;i++)for(j=0,r=R;j<n;s+=(j<n))
			{
				if(a[i].first<=r)r=max(r,a[i].second);
				for(k=r;j<n&&a[j].first<=k;j++)r=max(r,a[j].second);
				if(j<n&&k==r)return -1;
			}
			return s;
		}
};
