#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class ArcadeManao{
public:
	vector<int> ex[60],ey[60];
	int fa[2510];
	int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
	int shortestLadder(vector <string> level, int coinRow, int coinColumn){
		int N=level.size(),M=level[0].length();
		for(int i=0;i<N*M;i++)fa[i]=i;
		for(int i=0;i<M;i++){
			int l=0;while(l<N&&level[l][i]!='X')l++;
			if(i<M-1&&level[l][i+1]=='X')fa[find(l*M+i+1)]=find(l*M+i);
			if(l<N)for(int j=l+1;j<N;j++)if(level[j][i]=='X'){
				ex[j-l].push_back(l*M+i);
				ey[j-l].push_back(j*M+i);
				l=j;if(i<M-1&&level[l][i+1]=='X')fa[find(l*M+i+1)]=find(l*M+i);
			}
		}
		for(int i=0;;i++){
			for(int j=0;j<ex[i].size();j++)fa[find(ex[i][j])]=find(ey[i][j]);
			if(find((N-1)*M)==find((coinRow-1)*M+coinColumn-1))return i;
		}
	}
};
1))return i;
		}
	}
};
=dfs(0,1<<30);
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
