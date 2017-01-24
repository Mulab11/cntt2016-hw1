#include <vector>
#include <string>
#include <algorithm>
#define MOD 1000000009
using namespace std;
class CharacterBoard{
public:
	int W,P[100010],Ls[400010],t[50],pcnt,lcnt,cnt;
	long long p[50];
	bool vis[100010];
	void dfs(int i,long long s){
		if(s>W)return;
		if(i==cnt){Ls[lcnt++]=s;return;}
		for(int j=0;j<=t[i];j++)dfs(i+1,s),s*=p[i];
	}
	long long pow(long long a,int n){int num=1;for(;n;n>>=1)n%2?num=num*a%MOD:1,a=a*a%MOD;return num;}
	int countGenerators(vector <string> fragment, int W, int i0, int j0){
		int w=fragment[0].length(),h=fragment.size();this->W=W;
		for(int i=2;i<=100000;i++){
			if(!vis[i])P[pcnt++]=i;
			for(int j=0;j<pcnt&&1ll*i*P[j]<=100000;j++){
				vis[i*P[j]]=1;
				if(i%P[j]==0)break;
			}
		}
		for(int i=1;i<w;i++)Ls[lcnt++]=i;
		for(int i=1;i<h;i++){
			for(int j=-w+1;j<w;j++){
				long long X=1ll*i*W+j;cnt=0;
				for(int k=0;k<pcnt&&1ll*P[k]*P[k]<=X;k++)if(X%P[k]==0){
					p[cnt]=P[k];t[cnt]=0;
					while(X%P[k]==0)X/=P[k],t[cnt]++;
					cnt++;
				}
				if(X>1)p[cnt]=X,t[cnt++]=1;
				dfs(0,1);
			}
		}
		sort(Ls,Ls+lcnt);
		lcnt=unique(Ls,Ls+lcnt)-Ls;
		int ans=(pow(26,W)-1)*pow(25,MOD-2)%MOD*pow(26,MOD-w*h)%MOD;
		for(int i=0;i<lcnt;i++){
			ans=(ans+MOD-pow(26,Ls[i]-w*h+MOD-1))%MOD;
			pair<int,char> items[101];
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
