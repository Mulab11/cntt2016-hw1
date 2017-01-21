#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

ll s[105];

ll get(vi tmp,int k){
	for(int i=0;i<tmp.size();i++)
		if(tmp[i]==-1) tmp[i]=k;
	int top=50;
	memset(s,0,sizeof(s));
	for(int i=0;i<tmp.size();i++)
		if(tmp[i]==0) s[top-1]+=s[top],top--;
		else s[++top]=tmp[i];
	return s[top];
}

class Suminator{
public:
	int findMissing(vector <int> program, int wantedResult){
		vi a=program;
		if(get(a,0)==wantedResult) return 0;
		ll l=get(a,1),r=get(a,2);
		printf("%lld %lld\n",l,r);
		if(l==wantedResult) return 1;
		if(r==l||l>wantedResult) return -1;
		return wantedResult-l+1;
	}
};
