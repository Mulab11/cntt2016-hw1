#include <vector>
#include <string>
#include <cstring>
using namespace std;
class TheTilesDivOne{
public:
	struct edge{int to,cap;edge*rev,*next;}E[13824],*ne,*first[3456],*cur[3456];
	void link(int a,int b,int d=1){
		*ne=(edge){b,d,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,!d,ne-1,first[b]};first[b]=ne++;
	}
	int Q[3456],D[3456];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;
			if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
			f+=dfs(0,1<<30);
		}
	}
	int P[48][48];
	bool ex(int i,int j){return i>=0&&j>=0&&P[i][j];}
	int find(vector <string> board){
		int R=board.size(),C=board[0].length(),tot=2;ne=E;
		memset(first,0,sizeof(first));memset(P,0,sizeof(P));
		for(int i=0;i<R;i++)for(int j=(i+1)%2;j<C;j+=2)if(board[i][j]!='X')
			i%2?link(0,tot):link(tot,1),P[i][j]=tot++;
		for(int i=0;i<R;i++)for(int j=i%2;j<C;j+=2)if(board[i][j]!='X'){
			if(ex(i,j-1))link(P[i][j-1],tot,j%2);
			if(ex(i,j+1))link(P[i][j+1],tot,j%2);
			tot++;link(tot-1,tot,j%2);
			if(ex(i-1,j))link(tot,P[i-1][j],j%2);
			if(ex(i+1,j))link(tot,P[i+1][j],j%2);
			tot++;
		}
		return maxflow();
	}
};
++;
				if(!sy)left_out[0]=1; // U->L
				else if(sy==C-1)right_out[0]=1; // U->R
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
