#include <algorithm>
using namespace std;
struct HatRack{
	int n, mmm, sz[51];
	bool e[51][51];
	void fafafa(int u, int v){e[u][v]=e[v][u]=1;}
	// 计算子树size
	void gsz(int u, int ff){
		sz[u]=1;
		for(int v=0;v<n;++v)
			if(e[u][v] && v^ff)gsz(v,u),sz[u]+=sz[v];
	}
	long long gao(int u, int ff, int id){
		mmm=max(mmm,id);
		vector<int> erz;
		for(int v=0;v<n;++v)if(e[u][v] && v^ff)erz.push_back(v);
		// 度数不合法
		if(erz.size()>2)return 0;
		// 叶子
		if(erz.size()==0)return 1;
		// 形态唯一
		if(erz.size()==2 && sz[erz[0]]<sz[erz[1]])swap(erz[0],erz[1]);
		long long ret=1;
		// 各自的答案
		for(int i=0;i<erz.size();++i)ret*=gao(erz[i],u,id*2+i);
		// 左右可交换
		if(erz.size()>1 && sz[erz[0]]==sz[erz[1]])ret*=2;
		return ret;
	}
	long long countWays(vector<int> edge_u, vector<int> edge_v){
		n=edge_u.size()+1;
		if(n==2)return 2;
		for(int i=0;i+1<n;++i)fafafa(--edge_u[i],--edge_v[i]);
		long long ans = 0;
		// 枚举根
		for(int i=0;i<n;++i){
			gsz(i,-1);
			mmm=0;
			long long tmp=gao(i,-1,1);
			// 最大点编号==n意味着编号成功
			if(mmm==n)ans+=tmp;
		}
		return ans;
	}
};