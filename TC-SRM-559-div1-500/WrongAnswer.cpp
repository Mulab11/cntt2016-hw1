#include <vector>
#define M1 (siz[c1]==ls[siz[i]]&&siz[c2]==rs[siz[i]])
#define M2 (siz[c1]==rs[siz[i]]&&siz[c2]==ls[siz[i]])
using namespace std;
class HatRack{
public:
	int to[60][3],deg[60],siz[60], // to[i]:i的所有出边 deg[i]:i的度 siz[i]:i的子树大小
		ls[60],rs[60]; // ls[i],rs[i]分别为大小为i的完全二叉树两子树大小
	void getsiz(int i,int f){ // 求所有点的子树大小
		siz[i]=1;
		for(int j=0;j<deg[i];j++)if(to[i][j]!=f)getsiz(to[i][j],i),siz[i]+=siz[to[i][j]];
	}
	long long dfs(int i,int f){ // 求以i为根（f为i父节点）的完全二叉树方案数
		if(siz[i]<3)return 1;
		for(int j1=0,c1;j1<deg[i];j1++)if((c1=to[i][j1])!=f)
			for(int j2=j1+1,c2;j2<deg[i];j2++)if((c2=to[i][j2])!=f)
				return M1||M2?dfs(c1,i)*dfs(c2,i)*(ls[siz[i]]==rs[siz[i]]?2:1):0;
		return 0;
	}
	long long countWays(vector <int> knob1, vector <int> knob2){
		int n=1+knob1.size();
		if(n==2)return 2;
		for(int i=1;i<=n;i++)deg[i]=0;
		for(int i=0,x,y;i<n-1;i++){
			if(deg[x=knob1[i]]>2||deg[y=knob2[i]]>2)return 0; // 度超过3则无解
			to[x][deg[x]++]=y;
			to[y][deg[y]++]=x;
		}
		// 实际上这一步没有必要
		int cnt[4]={0};
		for(int i=1;i<=n;i++)cnt[deg[i]]++;
		if(cnt[1]!=(n+1)/2||cnt[2]!=(n-1)%2+1||cnt[3]!=cnt[1]-2)return 0; // 度的数量错误则无解
		long long ans=0;
		ls[3]=rs[3]=1;
		for(int i=4,j=1;i<=n;i++){ // 预处理ls[i]和rs[i]
			if(i>=4<<j)++j;
			ls[i]=ls[i-1];rs[i]=rs[i-1];
			i<3<<j?++ls[i]:++rs[i];
		}
		for(int i=1;i<=n;i++)if(deg[i]==2) // 枚举根节点
			getsiz(i,0),ans+=dfs(i,0);
		return ans;
	}
};
�利益
				}
				else{
					link(0,P(i,j),U+dec(cost[i][j])),link(P(i,j),1,U); // 偶数格割0表示选，割1表示不选
					for(int d=0,x,y;d<4;d++)
						if((x=i+vx[d])>=0&&x<R&&(y=j+vy[d])>=0&&y<C)link(Q(i,j),P(x,y),INF);
					ans+=dec(benefit[i][j]),link(P(i,j),Q(i,j),dec(benefit[i][j])); // 默认得到利益，如果没被占据则取消利益
				}
			}
		}
		return ans-maxflow();
	}
};
g ans=0,v[56]={0},w[56]={0}; // ans为答案，v为系数，w为初始向量 
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
