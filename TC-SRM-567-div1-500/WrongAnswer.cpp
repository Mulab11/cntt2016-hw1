// FST:问题考虑不周到，没注意到若干轮之后原本非最优的会变成最优
#include <vector>
#include <string>
using namespace std;
class StringGame{
public:
	vector <int> getWinningStrings(vector <string> S){
		int cnt[50][26]={0};
		vector<int> ans;
		for(int i=0;i<S.size();i++)
			for(int j=0;j<S[i].length();j++)cnt[i][S[i][j]-'a']++;
		for(int i=0;i<S.size();i++){
			long long A=(1ll<<S.size())-1;
			int P[26],tot=26;
			for(int j=0;j<26;j++)P[j]=j;
			for(int j=0;j<tot&&A!=1ll<<i;j++){
				int m=0;
				for(int k=0;A>>k;k++)if((A>>k&1)&&cnt[k][P[j]]>m)m=cnt[k][P[j]];
				if(cnt[i][P[j]]==m){
					for(int k=0;A>>k;k++)if((A>>k&1)&&cnt[k][P[j]]<m)A-=1ll<<k;
					P[j]=P[--tot];j=-1;
				}
			}
			if(A==1ll<<i)ans.push_back(i);
		}
		return ans;
	}
};
1,double x2,double y2,double x3,double y3){ // 三角形有向面积*2
		return x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
	}
	bool inside(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y){ // 判断(x,y)是否在三角形内
		return fabs(area(x1,y1,x2,y2,x,y))+fabs(area(x2,y2,x3,y3,x,y))+fabs(area(x3,y3,x1,y1,x,y))-fabs(area(x1,y1,x2,y2,x3,y3))<1e-13;
	}
	int countWays(int n, int radius, vector <int> x, vector <int> y, string color){
		// 预处理
		double PI=acos(-1),xi,yi,xj,yj;
		int ex[128][2]={0};
		for(int i=0;xi=cos(2*PI*i/n),yi=sin(2*PI*i/n),i<n;i++)
			for(int j=i+1;xj=cos(2*PI*j/n),yj=sin(2*PI*j/n),j<n;j++)
				for(int k=0;k<x.size();k++)
					inside(1,0,xi,yi,xj,yj,x[k]*1.0/radius,y[k]*1.0/radius)?cnt[i][j]++,cnt[j][i]--:1,
					ex[color[k]][area(xi,yi,xj,yj,x[k]*1.0/radius,y[k]*1.0/radius)>0]=i*n+j,ex[color[k]][0]==i*n+j&&ex[color[k]][1]==i*n+j?cut[i][j]=1:1;
		int sum=cnt[n-1][0];
		for(int i=1;i<n;i++)sum+=cnt[i-1][i];
		if(sum<x.size())return 0; // 判掉无解的情况
		// DP
		for(int l=n-2;l>=0;l--){
			for(int r=l+1;r<n;r++){
				// 1:l~r只有一条边，要求k=0且l l+1 r-1 r多边形内没有点
				f[l][r][0]=l+1==r||!poly(l,l+1,r-1,r)?l+1<r-1?g[l+1][r-1]:1:0;
				f[l][r][1]=0;
				// 2:l~r有多条边，枚举l的下一个点i，要求l l+1 i-1 i多边形内没有点
				for(int i=l+1;i<r;i++)if(!cut[l][i]&&(l+1==i||!poly(l,l+1,i-1,i))){
					long long t=l+1<i-1?g[l+1][i-1]:1;
					f[l][r][0]=(f[l][r][0]+t*f[i][r][0])%MOD;
					f[l][r][1]=(f[l][r][1]+t*f[i][r][!poly(l,i,r)])%MOD;
				}
				g[l][r]=l+1<r?poly(l,l+1,r)?0:g[l+1][r]:1;
				for(int i=l+1;i<=r;i++){
					if(!cut[l][i]&&(i==r||!poly(l,i,i+1,r)))g[l][r]=(g[l][r]+1ll*f[l][i][1]*(i+1<r?g[i+1][r]:1))%MOD;
				}
			}
		}
		return g[0][n-1];
	}
};
};
=1ll*P*(p-l)%MOD;
				}
			}
			ans=(ans+P)%MOD;
		}
		return ans; 
	}
};

			for(edge*e=first[i];e;e=e->next){
				if(siz[e->to]==n-k)dfs2(e->to,i,dep+1,ff*fv[e->to]%MOD);
			}
		}
		else for(edge*e=first[i];e;e=e->next)
			if(e->to!=fa)dfs2(e->to,i,dep+1,ff);
	}
	int getCount(vector <int> edge1, vector <int> edge2, int k){
		this->n=edge1.size()+1;this->k=k;ne=E;ans=0;
		for(int i=0;i<edge1.size();i++)link(edge1[i],edge2[i]),link(edge2[i],edge1[i]);
		init();
		if(k==1)return fac[n];
		if(2*k>n){
			init(0,-1);
			dfs1(0,-1,1);
			return ans*fac[2*k-n]%MOD*fac[n-k]%MOD*fac[n-k]%MOD;
		}
		for(int i=0;i<n;i++){
			init(i,-1);
			dfs2(i,-1,0,inv[k]);
		}
		return ans*fac[k]%MOD*fac[k]%MOD;
	}
};
