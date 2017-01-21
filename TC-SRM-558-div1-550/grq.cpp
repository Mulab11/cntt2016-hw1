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

const int N=355;

struct node{
	int x,y;
}a[N],b[N],c[N],g[N];
int n,m,px,py,cnt[10005];

int get(int *a,vector<string> S){
	string s="";
	for(int i=0;i<S.size();i++) s=s+S[i];
	int n=0,m=s.length();
	for(int i=0;i<m;i++){
		if(s[i]!='-'&&(s[i]<'0'||s[i]>'9')) continue;
		++n;a[n]=0;
		while(i<m&&s[i]>='0'&&s[i]<='9') a[n]=a[n]*10+s[i++]-'0';
	}
	return n;
}
bool operator < (node a,node b){
	return (a.x-px)*(b.y-py)>(b.x-px)*(a.y-py);
}
node operator - (node a,node b){
	a.x-=b.x;a.y-=b.y;
	return a;
}
int operator * (node a,node b){
	return a.x*b.y-a.y*b.x;
}

class Ear{
public:
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){
		int tmp[N];
		n=get(tmp,redX);
		sort(tmp+1,tmp+n+1);
		for(int i=1;i<=n;i++) a[i]=(node){tmp[i],0};
		
		m=get(tmp,blueX);
		for(int i=1;i<=m;i++) b[i].x=tmp[i];
		get(tmp,blueY);
		for(int i=1;i<=m;i++) b[i].y=tmp[i];
//		for(int i=1;i<=m;i++) printf("%d %d\n",b[i].x,b[i].y);
//---------------------------read-------------------------
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++) cnt[a[i].x]++;
		for(int i=1;i<=10000;i++) cnt[i]+=cnt[i-1];
		ll ans=0;
		for(int i=1;i<=m;i++){
			int k=0;
			for(int j=1;j<=m;j++)
				if(i!=j&&b[j].y<b[i].y) g[++k]=b[j];
//			debug(k);
			px=b[i].x;py=b[i].y;
			sort(g+1,g+k+1);
			for(int l=1;l<=n;l++){
				if(a[l].x>=b[i].x) continue;
				int s=0,t=0,sum=0,res=0;
				for(int j=1;j<=k;j++)
					if((g[j]-a[l])*(b[i]-a[l])>0) c[++s]=g[j];
//				if(k) printf("%d %d %d\n",i,l,s);
				if(!s) continue;
				for(int r=l+1;r<=n;r++){
					while(t<s&&(c[t+1]-a[r])*(b[i]-a[r])<0){
						++t;
						sum+=cnt[c[t].x-1]-cnt[a[l].x];
						res+=(ll)(cnt[c[t].x-1]-cnt[a[l].x])*(cnt[a[r].x-1]-cnt[c[t].x]);
//						if(i==3) debug(res);
					}
					if(a[r].x>b[i].x) ans+=res;
					res+=sum;
				}
			}
//			debug(ans);
		}
		return ans;
	}
};
