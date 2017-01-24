#include <vector>
#include <string>
using namespace std;
class TheDevice{
public:
	int f(int x){return x>0?x:0;}
	int minimumAdditional(vector <string> plates){
		int ans=0,tmp,cnt[50][2]={0};
		for(int i=0;i<plates.size();i++)
			for(int j=0;j<plates[i].length();j++)cnt[j][plates[i][j]-'0']++;
		for(int i=0;i<plates[0].length();i++)
			if((tmp=f(1-cnt[i][0])+f(2-cnt[i][1]))>ans)ans=tmp;
		return ans;
	}
};
ind_val(int i){return fa[i]==i?0:val[i]^find_val(fa[i]);}
	bool link(int i,int j,int v){ // 连边，返回是否未出现奇环
		v^=find_val(i)^find_val(j);i=find_fa(i);j=find_fa(j);
		if(i==j)return!v;
		if(siz[i]>siz[j]){int t=i;i=j;j=t;}
		fa[opx[opcnt++]=i]=j;siz[j]+=siz[i];val[i]=v;return 1;
	}
	void undo(int t){ // 撤销
		for(int i;opcnt>t;)i=opx[--opcnt],siz[fa[i]]-=siz[i],val[fa[i]=i]=0;
	}
	// 搜索1:枚举所有可能的连边情况，判断是否为二分图
	int list[52],top;
	bool dfs1(int i){
		if(i==top)return 1;
		for(int j=i+1,t;j<top;j++){ // 枚举点list[i]和哪个点连 
			bool flag=1;
			int old=opcnt;
			ex[ecnt]=list[i];ey[ecnt]=t=list[j];
			if(ex[ecnt]>t)ey[ecnt]=ex[ecnt],ex[ecnt]=t;
			for(int k=0;k<ecnt&&flag;k++)if(cross(k,ecnt)&&!link(k,ecnt,1))flag=0; // 出现奇环就不合法
			if(flag){ 
				ecnt++;list[j]=list[i+1];list[i+1]=t;
				if(dfs1(i+2))return 1;
				ecnt--;list[i+1]=list[j];list[j]=t;
			}
			undo(old);
		}
		return 0;
	}
	// 搜索2:枚举每条边的类型，判断是否存在连边方案
	int id[26],type[26],select[26],stype[26];
	bool dfs2(int i){
		if(i==ecnt)return 1;
		for(int c=0,t=select[id[i]],old=opcnt;c<2;c++){
			if(t&&c!=(stype[id[i]]^type[i])||!i&&c)continue;
			if(!t)select[id[i]]=1,stype[id[i]]=c^type[i];
			if(link(ex[i],ex[i]+1,c)&&link(ey[i],ey[i]+1,c)
				&&link(ex[i]+1,ey[i],c?0:(ex[i]^ey[i]^1)%2)&&dfs2(i+1))return 1; // 每条边内同类点必须偶数个 
			if(!t)select[id[i]]=0;undo(old);
		}
		return 0;
	}
	string getPossibility(vector <int> labels){
		for(int i=ecnt=top=opcnt=0;i<labels.size();i++) // 预处理边集
			if(labels[i]==-1)list[top++]=i;
			else for(int j=i+1;j<labels.size();j++)if(labels[i]==labels[j])ex[ecnt]=i,ey[ecnt++]=j;
		init(labels.size());
		for(int i=0;i<ecnt;i++)
			for(int j=i+1;j<ecnt;j++)if(cross(i,j)&&!link(i,j,1))return"IMPOSSIBLE"; // 输入的不合法则退出
		if(top<=12)return dfs1(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索1
		for(int j=0;j<ecnt;j++)id[j]=find_fa(j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索2
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
