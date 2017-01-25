#include <vector>
#include <string>
using namespace std;
class DisjointSemicircles{
public:
	int ex[26],ey[26],ecnt, // 边集
		fa[52],siz[52],val[52],opx[630],opcnt; // 带权并查集
	void init(int n){for(int i=0;i<=n;i++)fa[i]=i,siz[i]=1,val[i]=0;}
	bool cross(int i,int j){return ex[i]<ex[j]?ex[j]<ey[i]&&ey[i]<ey[j]:ex[i]<ey[j]&&ey[j]<ey[i];}
	int find_fa(int i){return fa[i]==i?i:find_fa(fa[i]);}
	int find_val(int i){return fa[i]==i?0:val[i]^find_val(fa[i]);}
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
