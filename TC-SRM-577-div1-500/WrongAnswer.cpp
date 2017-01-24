#include <vector>
#include <string>
using namespace std;
class EllysChessboard{
public:
	int minCost(vector <string> board);
};
int n,a[64],b[64],S[16][16],f[15][15][15][15];
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
struct rect{
	int u,d,l,r;
	int sum(){return S[d+1][r+1]-S[d+1][l]-S[u][r+1]+S[u][l];}
	int cost(int i){return max(max(a[i]-u,d-a[i]),max(b[i]-l,r-b[i]));}
	bool inside(int i){return u<=a[i]&&a[i]<=d&&l<=b[i]&&b[i]<=r;}
	rect append(int i,int&c){
		rect p=(rect){min(u,a[i]),max(d,a[i]),min(l,b[i]),max(r,b[i])};
		for(c=i=0;i<n;i++)if(!inside(i)&&p.inside(i))c+=p.cost(i);
		return p;
	}
};
int dfs(rect b){
	if(b.sum()==n)return 0;
	int&s=f[b.u][b.d][b.l][b.r],c;
	if(s)return s-1;
	s=1<<30;
	for(int i=0,t;i<n;i++)if(!b.inside(i))t=dfs(b.append(i,c)),s=min(s,t+c);
	return s++;
}
int EllysChessboard::minCost(vector <string> board){
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(board[i][j]=='#')a[n]=i-j+7,b[n++]=i+j;
	if(n<2)return 0;
	for(int i=0;i<n;i++)S[a[i]+1][b[i]+1]=1;
	for(int i=1;i<=15;i++)
		for(int j=1;j<=15;j++)S[i][j]+=S[i][j-1]+S[i-1][j]-S[i-1][j-1];
	int ans=1<<30;
	for(int i=0;i<n;i++)ans=min(ans,dfs((rect){a[i],a[i],b[i],b[i]}));
	return ans;
}
[i],a[i],b[i],b[i]}));
	return ans;
}
;
			int tot=0,b=Ls[i],flag=1;
			for(int x=0;x<h;x++)for(int y=0;y<w;y++)items[tot++]=make_pair((x*1ll*W+y)%Ls[i],fragment[x][y]);
			sort(items,items+tot);
			for(int l=0,r=0;l<tot&&flag;l=r,b--)
				for(;r<tot&&items[l].first==items[r].first&&flag;r++)items[l].second!=items[r].second?flag=0:1;
			if(flag)ans=(ans+pow(26,b))%MOD;
		}
		return ans;
	}
};
ans=(ans+pow(26,b))%MOD;
		}
		return ans;
	}
};
堑谝恍星倚胁畈淮笫弊狶->D
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
