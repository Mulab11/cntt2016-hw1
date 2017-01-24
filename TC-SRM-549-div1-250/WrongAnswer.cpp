#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class PointyWizardHats{
public:
	struct item{int t,h,r;bool operator<(const item&it)const{int x=h*it.r-r*it.h;return x?x>0:t>it.t;}}a[110];
	multiset<int> S;
	int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius){
		int n=0,ans=0;
		for(int i=0;i<topHeight.size();i++)a[n++]=(item){0,topHeight[i],topRadius[i]};
		for(int i=0;i<bottomHeight.size();i++)a[n++]=(item){1,bottomHeight[i],bottomRadius[i]};
		sort(a,a+n);
		multiset<int>::iterator it;
		for(int i=0;i<n;i++){
			if(a[i].t){
				it=S.lower_bound(a[i].r);
				if(it!=S.begin())S.erase(--it),ans++;
			}
			else S.insert(a[i].r);
		}
		return ans;
	}
};
[n3][k])return f[n][n2][n3][k]-1;
		ll&s=f[n][n2][n3][k];
		if(n3){ // 有3-连通块
			s=C[C[n][2]+n*3][k]; // 图的总个数
			for(int x=0;x<n;x++) // 减去不连通图个数
				for(int y=0;y<=k;y++)
					(s-=C[n][x]*F(x,0,1,0,y)%MOD*C[C[n-x][2]][k-y])%=MOD; // (x,1,y)\(n-x,0,k-y) 的图个数
		}
		else if(n2){ // 没有3-连通块但有2-连通块
			s=C[C[n][2]+n*n2*2+4*C[n2][2]][k]; // 图的总个数
			for(int x=0;x<=n;x++) // 减去不连通图个数
				for(int x2=0;x2<n2&&x+x2+1<n+n2;x2++)
					for(int y=0;y<=k;y++)
						(s-=C[n][x]*C[n2-1][x2]%MOD*F(x,x2+1,0,0,y)%MOD*C[C[n-x][2]+(n-x)*(n2-x2-1)*2][k-y])%=MOD; // (x,x2+1,y)\(n-x,n2-x2-1,k-y) 的图个数
		}
		else{ // 只有1-连通块
			s=C[C[n][2]][k]; // 图的总个数
			for(int x=0;x<n;x++) // 减去不连通图个数
				for(int y=0;y<=k;y++)
					(s-=C[n-1][x]*F(x+1,0,0,0,y)%MOD*C[C[n-x-1][2]][k-y])%=MOD; // (x+1,y)\(n-x-1,k-y) 的图个数
		}
		if(s<0)s+=MOD;
		return s++;
	}
	int howMany(int N, int M, int K){
		for(int i=0;i<=N*N;i++)
			for(int j=*C[i]=1;j<=i&&j<=K;j++)
				C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		return F(N-M,0,0,M,K);
	}
};
