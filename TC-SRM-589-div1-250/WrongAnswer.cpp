#include <string>
using namespace std;
class GooseTattarrattatDiv1{
public:
	int fa[26],c[26],s[26],m[26];
	int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
	int getmin(string S){
		for(int i=0;i<26;i++)fa[i]=i,c[i]=s[i]=m[i]=0;
		for(int i=S.length();i--;)c[S[i]-'a']++;
		for(int i=0;i<26;i++)s[i]=m[i]=c[i];
		for(int i=0,j=S.length()-1,fi,fj;i<j;i++,j--)
			if((fi=find(S[i]-'a'))!=(fj=find(S[j]-'a')))fa[fi]=fj,s[fj]+=s[fi],m[fi]>m[fj]?m[fj]=m[fi]:1;
		int ans=0;
		for(int i=0;i<26;i++)if(fa[i]==i)ans+=s[i]-m[i];
		return ans;
	}
};
}
	string check(vector <string> field){
		int R=field.size(),C=field[0].length(),xA,yA,xB,yB;
		for(int x=0;x<R;x++)
			for(int y=0;y<C;y++)field[x][y]=='A'?xA=x,yA=y:field[x][y]=='B'?xB=x,yB=y:1;
		for(int t=0;t<2;t++){
			for(*Q=(item){t?xB:xA,t?yB:yA},H=Q,T=Q+1,vis[Q->x][Q->y]=!t;H<T;up[H->x][H->y]=down[H->x][H->y]=0,H++)
				fe(H->x,H->y)if(vis[dx][dy]==t)vis[T->x=dx][T->y=dy]=!t,(t?DB:DA)[dx][dy]=(t?DB:DA)[H->x][H->y]+1,T++;
			while(H-->Q)fc(H->x,H->y)cmax(down[H->x][H->y],se[H->x][H->y],down[dx][dy]+1);
			for(H=Q;H<T;H++)fc(H->x,H->y)up[dx][dy]=max(up[H->x][H->y],down[H->x][H->y]==down[dx][dy]+1?se[H->x][H->y]:down[H->x][H->y])+1;
		}
		for(int x=0,t=1;x<R;x++)for(int y=0;y<C;y++)if(DA[x][y]-DB[x][y]>1){
			int cnt=up[x][y]>2;
			fc(x,y)if(down[dx][dy]>1)cnt++;
			if(cnt>2)return "Bob wins";
		}
		return "Alice wins";
	}
};
return "Alice wins";
	}
};
r[i]*(long long)(l[i]-p);
			if(r[i]<l[i]&&p<l[i])ans--;
		}
		return ans;
	}
};
0;i<n;i++){
			solver.link(i*9+1,0,0);
			for(int j=2;j<=9;j++)solver.link(i*9+j,i*9+j-1,0);
		}
		int s[12],l=0;
		for(int i=0;i<courseInfo.size();i++)
			for(int j=0,x;j<courseInfo[i].length();j++)
				(x=courseInfo[i][j])==' '?add(s),l=0:s[l++]=x;
		add(s);
		return solver.solve();
	}
};
es[y][2]);
			}
		}
		return ans;
	}
};
ej=first[E[j].to];ej;ej=ej->next)if(!ej->del&&ej!=E[j].rev)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
			solver.nx++;
		}
		f[i][j]+=solver.match();
	}
	int getmax(vector <int> a, vector <int> b){
		N=a.size()+1;ne=E;
		for(int i=0;i<N-1;i++)link(a[i],b[i]);
		now=0;dfs(0,-1);
		int ans=0,tmp;
		for(int i=1;i<N;i++){
			fe[i]->del=fe[i]->rev->del=1;
			memset(f,0,sizeof(f));
			for(int j=0;j<N;j++)if(pre[j]<pre[i]||pre[j]>=pos[i]){
				for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del)
					for(edge*ej=first[j];ej;ej=ej->next)if(!ej->del)calc(ei->to,ej-E);
				solver.nx=0;
				for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del){
					solver.ny=0;
					for(edge*ej=first[j];ej;ej=ej->next)if(!ej->del)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
					solver.nx++;
				}
				if((tmp=1+solver.match())>ans)ans=tmp;
			}
			fe[i]->del=fe[i]->rev->del=0;
		}
		return ans;
	}
};
ver.match())>ans)ans=tmp;
			}
			fe[i]->del=fe[i]->rev->del=0;
		}
		return ans;
	}
};
ep+1,ff);
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
