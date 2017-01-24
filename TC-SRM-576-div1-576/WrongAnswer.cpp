#include <vector>
#include <string>
#define MOD 1000000009
using namespace std;
class TheExperiment{
public:
	int a[310],l[310],r[310],t[310]; // a[i]为前i个数的和，[l[i],r[i])为满足第i~j-1个数的和在[A,B]内且j-i<L的j的区间，t[i]表示i之后的L个数的和是否在[A,B]内
	long long f[310][310][3]; // f[i][j][k]为从[l,n)中取出j个区间(l>=i)，[0,l)状态为k（k=0:空;k=1:不含长度L的区间;k=2:含L的区间）的方案数和
	int countPlacements(vector <string> intensity, int M, int L, int A, int B){
		int n=0;
		for(int i=0;i<intensity.size();i++)
			for(int j=0;j<intensity[i].length();j++)a[++n]=intensity[i][j]-'0';
		for(int i=0;i<n;i++)a[i+1]+=a[i];
		// 预处理区间
		for(int i=0;i<n;i++){
			while(l[i]<=n&&a[l[i]]-a[i]<A)l[i]++;
			while(r[i]<=n&&a[r[i]]-a[i]<=B)r[i]++;
			l[i+1]=l[i];r[i+1]=r[i];
		}
		for(int i=0;i<n;i++){
			if(l[i]>i+L)r[i]=l[i]; // i~i+L-1的和不足A，无法转移
			else if(i+L<r[i])r[i]=i+L,t[i]=1; // 长度L的区间和在[A,B]内，修改区间
		}
		// 转移(i,j,k)
		// 1:不选i，转移到(i+1,j,0)，前提是k不为1
		// 2:用一段区间覆盖i，转移到(i',j-1,k')，当i'-i=L时k'=2，否则k'=1
		long long g[2];
		f[n][0][0]=f[n][0][2]=1;
		for(int i=n-1;i>=0;i--){
			for(int j=0;j<=M;j++){
				for(int k=0;k<2;k++)g[k]=j?(f[l[i]][j-1][k+1]+MOD-f[r[i]][j-1][k+1]+(t[i]?f[i+L][j-1][2]+MOD-f[i+L+1][j-1][2]:0))%MOD:0; // 转移2的方案数
				f[i][j][0]=(f[i+1][j][0]*2+MOD-f[i+2][j][0]+g[0])%MOD;
				f[i][j][1]=(f[i+1][j][1]+g[0])%MOD;
				f[i][j][2]=(f[i+1][j][2]+f[i+1][j][0]+MOD-f[i+2][j][0]+g[1])%MOD;
			}
		}
		return (f[0][M][0]+MOD-f[1][M][0])%MOD;
	}
};
0][M][0]+MOD-f[1][M][0])%MOD;
	}
};
t[0]=1; // U->R
			}
			else if(!sy){
				if(!ty)left_in[sx]=1,!sx||tx>sx+1?left_out[tx]=1:1; // L->L，非第一行且行差不大时转为L->D
				else if(ty==C-1)sx==tx?is_line[sx]=1:left_in[sx]=right_out[tx]=1; // L->R，可能在同一行
				else if(!tx)ans++,left_out[sx]=1; // L->U，转为U->L
				else left_in[sx]=1; // L->D
			}
			else if(sy==C-1){
				if(!ty)right_in[sx]=left_out[tx]=1; // R->L
				else if(ty==C-1)right_in[sx]=1,!sx||tx>sx+1?right_out[tx]=1:1; // R->R，非第一行且行差不大时转为R->D
				else right_in[sx]=1; // R->D
			}
			else if(!sx){
				ans++;
				if(!ty)left_out[tx]=1; // U->L
				else if(ty==C-1)right_out[tx]=1; // U->R
			}
			else if(!ty)left_in[tx]=1; // D->L，转为L->D
			else if(ty==C-1)right_in[tx]=1; // D->R，转为R->D
		}
		return ans+dfs(0,R,0,0);
	}
};
1; // D->R，转为R->D
		}
		return ans+dfs(0,R,0,0);
	}
};
j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // 鎼滅储2
	}
};
1ll*P*(p-l)%MOD;
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
