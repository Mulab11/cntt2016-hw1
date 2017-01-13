#include<bits/stdc++.h>
#define P(x) sort(x.begin(),x.end())
using namespace std;
vector<int> b[2];
int i,j,S[2],s[2],r=-1,t,k[2],n,m;
class ICPCBalloons
{
	public:
		int minRepaintings(vector<int> w,string c,vector<int> a)
		{
			for(n=w.size(),m=a.size();i<n;i++)b[c[i]=='M'].push_back(w[i]),S[c[i]=='M']+=w[i];
			for(P(a),P(b[0]),P(b[1]),i=0;i<1<<m;i++)
			{
				for(s[0]=s[1]=j=0;j<m;j++)s[i>>j&1]+=a[j];
				for(k[0]=b[0].size(),k[1]=b[1].size(),t=s[0]+s[1],j=m-1;~j;j--)if(k[i>>j&1])t-=min(b[i>>j&1][--k[i>>j&1]],a[j]);
				if(S[0]>=s[0]&&S[1]>=s[1]&&(r<0||t<r))r=t;
			}
			return r;
		}
};
