#include <vector>
#include <string>
using namespace std;
struct node{node*fa,*ch[26];}nodes[2510],*newnode,*root;
class UndoHistory{
public:
	int minPresses(vector <string> lines){
		root=nodes;newnode=nodes+1;
		int ans=lines.size();
		node*cur=root;
		for(int i=0;i<lines.size();i++){
			node*it=root,*x=it;
			for(int j=0;j<lines[i].length();j++){
				if(!it->ch[lines[i][j]-'a'])newnode->fa=it,it=it->ch[lines[i][j]-'a']=newnode++,ans++;
				else it=x=x->ch[lines[i][j]-'a'];
			}
			if(cur==x->fa)ans++;
			else if(cur!=x)ans+=2;
			cur=it;
		}
		return ans;
	}
};
		return ans;
	}
};
0;i<nx;i++)
			for(int j=0;j<ny;j++)if(w[i][j]>lx[i])lx[i]=w[i][j];
		for(int i=0;i<ny;i++)to[i]=-1,ly[i]=0;
		for(int i=0;i<nx;i++){
			for(int j=0;j<ny;j++)slack[j]=INF;
			for(int d;d=INF;){
				for(int j=0;j<ny;j++)visx[j]=visy[j]=0;
				if(dfs(i))break;
				for(int j=0;j<ny;j++)!visy[j]&&d>slack[j]?d=slack[j]:1;
				for(int j=0;j<nx;j++)visx[j]?lx[j]-=d:1;
				for(int j=0;j<ny;j++)visy[j]?ly[j]+=d:slack[j]-=d;
			}
		}
		int s=0;
		for(int i=0;i<ny;i++)if(to[i]!=-1)s+=w[to[i]][i];
		return s;
	}
}solver;
class DeerInZooDivOne{
public:
	int N,pre[60],pos[60],now;
	struct edge{int to;bool del;edge*rev,*next;}E[110],*ne,*first[60],*fe[60];
	void link(int a,int b){
		*ne=(edge){b,0,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	void dfs(int i,int f){
		pre[i]=now++;
		for(edge*e=first[i];e;e=e->next)if(e->to!=f)fe[e->to]=e,dfs(e->to,i);
		pos[i]=now;
	}
	int f[60][110];
	void calc(int i,int j){
		if(f[i][j])return;
		f[i][j]=1;
		for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del&&ei!=fe[i]->rev)
			for(edge*ej=first[E[j].to];ej;ej=ej->next)if(!ej->del&&ej!=E[j].rev)calc(ei->to,ej-E);
		solver.nx=0;
		for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del&&ei!=fe[i]->rev){
			solver.ny=0;
			for(edge*ej=first[E[j].to];ej;ej=ej->next)if(!ej->del&&ej!=E[j].rev)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
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
