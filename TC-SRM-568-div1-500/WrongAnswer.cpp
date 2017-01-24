#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class EqualSums{
public:
	int count(vector <string> board){
		int N=board.size();
		for(int c=0,r1,r2;c<N;c++){
			for(r1=0;r1<board.size()&&board[r1][c]=='-';r1++);
			for(r2=r1+1;r2<board.size()&&board[r2][c]=='-';r2++);
			if(r2<board.size()){
				int p=r1,q=r2;
				if(board[r1][c]>board[r2][c])p=r2,q=r1;
				char a=board[p][c],b=board[q][c];
				for(int i=0;i<N;i++){
					char&x=board[p][i],&y=board[q][i];
					if(x!='-'&&y!='-'&&x-y!=a-b)return 0;
					if(x=='-'&&y!='-'&&(x=y+a-b)<'0')return 0;
				}
				board[q]=board[board.size()-1];board.pop_back();c--;
			}
		}
		int a[51],pre=1,pos[51],n=0,ans;
		for(int i=0;i<board.size();i++){
			int m=20;
			for(int j=0;j<N;j++)if(board[i][j]!='-'&&board[i][j]-'0'<m)m=board[i][j]-'0';
			a[n++]=m;
		}
		pos[n-1]=1;for(int i=n-1;i;i--)pos[i-1]=1ll*pos[i]*(a[i]+1)%MOD;
		ans=pos[0];for(int i=1;i<n;i++)ans=(ans+1ll*pre*pos[i]%MOD*a[0])%MOD,pre=1ll*pre*a[i]%MOD;
		return ans;
	}
};
s[j]));
			cmax(hr,h[j]-diff(R[i],pos[j]));
			cmax(hrr,h[j]-diff(R[i]+1,pos[j]));
		}
		int pl=L[i],pr=R[i];
		cmax(pl,hr-h[i]+R[i]+1);
		cmin(pr,h[i]+L[i]-hl-1);
		if(L[i])cmax(pl,h[i]+L[i]-hll-1);
		if(R[i]<W-1)cmin(pr,hrr-h[i]+R[i]+1);
		for(p=pl;p<=pr;p++)s=(s+dfs(i-1,!L[i]&&R[i]==W-1?i:m))%MOD;
		if(m==i+1)f[m][pos[m]]=s+1;
		return s;
	}
	int countPlacements(vector <int> heights, vector <string> visibility){
		N=heights.size();W=visibility[0].length();
		for(int i=0;i<N;i++){
			h[i]=heights[i];
			for(L[i]=0;L[i]<W&&visibility[i][L[i]]=='-';L[i]++);
			for(R[i]=W-1;R[i]>=0&&visibility[i][R[i]]=='-';R[i]--);
		}
		return dfs(N-1,99);
	}
};
t[i][j]=1:1;
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
