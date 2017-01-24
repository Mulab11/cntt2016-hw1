#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Ear{
public:
	int R,B,rx[310],bx[310],by[310];
	void read(vector<string> s,int&n,int*a){
		n=*a=0;
		for(int i=0;i<s.size();i++)for(int j=0;j<s[i].length();j++){
			if(s[i][j]==' ')a[++n]=0;
			else a[n]=a[n]*10+s[i][j]-'0';
		}
		n++;
	}
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){
		read(redX,R,rx);
		read(blueX,B,bx);
		read(blueY,B,by);
		long long ans=0;
		sort(rx,rx+R);
		for(int i=0;i<B;i++){
			int l1=std::lower_bound(rx,rx+R,bx[i])-rx,r1=rx+R-upper_bound(rx,rx+R,bx[i]),l2,r2;
			for(int j=0;j<B;j++)if(by[j]>by[i]){
				if(bx[j]>bx[i])l2=lower_bound(rx,rx+R,bx[i]-by[i]*(bx[j]-bx[i])/(by[j]-by[i]))-rx,r2=rx+R-upper_bound(rx,rx+R,bx[j]);
				else l2=lower_bound(rx,rx+R,bx[j])-rx,r2=rx+R-upper_bound(rx,rx+R,bx[i]+by[i]*(bx[i]-bx[j])/(by[j]-by[i]));
				ans+=l2*(2*l1-l2-1ll)*r2*(2*r1-r2-1ll)/4;
			}
		}
		return ans;
	}
};
�果不改变决策就会不独立（t=x），就改变决策
				}
				else if((a[i]>>j&1)!=(t>>j&1))t^=a[l]; // j这一位不为空，用a[l]消使得t和x这一位相同
			}
			ans+=x; // 将最大的可选的x加入答案
			for(int j=0;j<i;j++)if((a[i]^a[j])<a[i])a[i]^=a[j]; // 前面部分消元
			for(int j=i;j&&a[j-1]<a[j];j--)t=a[j],a[j]=a[j-1],a[j-1]=t;
		}
		return ans;
	}
};
 i=n;i--;)for(int j=n;--j>i;)
				if(bridges[i][j]!='X')solver.link(i+2,j+2,bridges[i][j]=='N'?1<<30:2,bridges[i][j]=='N'?1<<30:2);
			if(solver.maxflow()<an+bn<<1)return"No";
		}
		return"Yes";
	}
};
n+bn<<1)return"No";
		}
		return"Yes";
	}
};
.a[P(s,j)][P(t,j-d)]=(A.a[P(s,j)][P(t,j-d)]+p)%MOD;
		}
		else for(to[i]=0;to[i]<=m;to[i]++){
			if(to[i]==m)c?dfs(s,i+1,m+1,c-1,p*c%MOD,k),1:1;
			else dfs(s,i+1,m,c,p,k);
		}
	}
	int find(int C, int K, long long H){
		// 构造矩阵 
		A.N=M.N=S.N=7*(K+1);
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)dfs(s,0,spl[s][3]+1,C-spl[s][3]-1,1,K);
		// 计算答案
		solve(H);
		long long ans=0,v[56]={0},w[56]={0}; // ans为答案，v为系数，w为初始向量 
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C){
			v[s]=rot[s];
			for(int i=0;i<=spl[s][3];i++)(v[s]*=C-i)%=MOD;
			w[P(s,dig[s])]=1;
		}
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)
			for(int k=0;k<=K;k++)
				for(int i=0;i<A.N;i++)(ans+=S.a[P(s,k)][i]*w[i]%MOD*v[s])%=MOD;
		return ans; 
	}
};
ight;
	}
};
�的一层
		if(cur!=-1)for(int i=0;i<N;i++)if(rest>>i&1){
			L[++top]=1<<i;
			for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			top--;
		}
		// i放同一层
		for(int i=cur+1;i<N;i++)if(rest>>i&1){
			L[top]|=1<<i;
			if(top)for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			else G[i]=0,cnt+=count_graph(i,rest-(1<<i));
			L[top]-=1<<i;
		}
		return cnt;
	}
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays){
		N=blockTypes.size();Min=minWays;Max=maxWays;
		for(int i=0;i<N;i++)cnt[i]=blockTypes[i],G[i]=0;
		*L=top=0;
		return count_graph(-1,(1<<N)-1);
	}
};
