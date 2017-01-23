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

const double pi=acos(-1);
const int N=55;
struct comp{double a,b;};
comp operator + (comp a,comp b){return (comp){a.a+b.a,a.b+b.b};}
comp operator - (comp a,comp b){return (comp){a.a-b.a,a.b-b.b};}
comp operator - (comp a){return (comp){-a.a,-a.b};}
comp operator * (comp a,comp b){return (comp){a.a*b.a-a.b*b.b,a.b*b.a+b.b*a.a};}
comp sqrt(comp a){
	double r=sqrt(sqr(a.a)+sqr(a.b));
	return (comp){sqrt(r)*cos(atan2(a.b,a.a)/2),sqrt(r)*sin(atan2(a.b,a.a)/2)};
}

class SplittingFoxes2 {
    public:
    vi ans,now;
	comp w[N][2],a[N],b[N],tmp[N];
	int n;
	ll mul[N];
	void dft(comp *a,int n,int p){
		for(int i=0;i<n;i++) tmp[i]=a[i];
		for(int i=0;i<n;i++){
			comp wn=w[i][p],now=(comp){1,0};
			a[i]=(comp){0,0};
			for(int j=0;j<n;j++,now=now*wn) a[i]=a[i]+tmp[j]*now;
		}
	}
	bool check(vi a){
		for(int i=0;i<n;i++) if(now[i]<0) return 0;
	//	debuge;
		memset(mul,0,sizeof(mul));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				mul[(i+j)%n]+=(ll)now[i]*now[j];
		for(int i=0;i<n;i++) if(mul[i]!=a[i]) return 0;
		return 1;
	}
    vector<int> getPattern(vector<int> amount) {
        n=amount.size();
//		debug(n);
		for(int i=0;i<n;i++) a[i]=(comp){amount[i],0};
		comp wn=(comp){cos(pi*2/(double)n),sin(pi*2/(double)n)};
		w[0][0]=(comp){1,0};
		for(int i=1;i<=n;i++) w[i][0]=w[i-1][0]*wn;
		for(int i=0;i<=n;i++) w[i][1]=w[n-i][0];
		dft(a,n,0);ans.clear();
//		debug(a[0].a);
		ans.pb(-1);
		for(int i=0;i<(1<<n/2+1);i++){
			for(int j=0;j<=n/2;j++)
				if(i&(1<<j)) b[j]=b[n-j]=sqrt(a[j]); else b[j]=b[n-j]=-sqrt(a[j]);
			dft(b,n,1);now.clear();
			for(int j=0;j<n;j++) now.pb((int)(b[j].a/(double)n+0.5));
			if(check(amount)){if(ans[0]==-1) ans=now; else ans=min(ans,now);}
		}
		return ans;
    }
};
