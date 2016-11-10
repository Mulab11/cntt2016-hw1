#include<cstdio>
#include<string>
#include<vector>
#include<cstring>

const int MAXN(55),MAXV(MAXN*MAXN),MAXE(MAXV*4),INF((1<<30)-1);
const int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};

class BoardPainting{
private:
	
	int n,m,S,T;//行数/列数/源点/汇点
	
	int id[MAXN][MAXN];//原图中每个点的编号，0代表不是点
	
	struct edge{
		int y,next,rem;
	}e[MAXE<<1];
	inline int rev(int i){//返回i的反向边
		if(i&1)return i+1;
		else return i-1;
	}
	int head[MAXV],ecnt;
	inline void connect(int x,int y){//连一条从x到y流量为1的边
		e[++ecnt]=(edge){y,head[x],1};head[x]=ecnt;
		e[++ecnt]=(edge){x,head[y],0};head[y]=ecnt;
	}
	
	//以下为最大流算法dinic
	int lev[MAXV];
	bool make_level(){
		static int que[MAXV],fro,rear;
		memset(lev,0,sizeof lev);
		for(lev[que[fro=rear=0]=S]=1;fro<=rear;fro++)
			for(int x=que[fro],i=head[x],y;i;i=e[i].next)
				if(e[i].rem&&!lev[y=e[i].y])
					lev[que[++rear]=y]=lev[x]+1;
		return lev[T];
	}
	
	int dinic(int x,int pf){
		if(x==T)return pf;
		int nf=0;
		for(int i=head[x],y;i;i=e[i].next)
			if(e[i].rem&&lev[y=e[i].y]==lev[x]+1){
				int d=dinic(y,std::min(e[i].rem,pf-nf));
				e[i].rem-=d;e[rev(i)].rem+=d;
				if((nf+=d)==pf)
					break;
			}
		if(!nf)lev[x]=0;
		return nf;
	}
	
	int max_flow(){
		int ans=0;
		while(make_level())
			ans+=dinic(S,INF);
		return ans;
	}
	int min_cut(){//最小割=最大流
		return max_flow();
	}
	
public:
	int minimalSteps(std::vector<std::string> map){
		n=map.size(),m=map[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(map[i][j]=='#')
					id[i+1][j+1]=++T;//给点编号
		T++;//汇点编号为最大点编号+1
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)if(id[i][j])
				for(int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if(id[x][y])
						connect(id[i][j],id[x][y]);
					else if(k&1)
						connect(id[i][j],T);
					else connect(S,id[i][j]);
				}//建图
		return min_cut()>>1;//返回流网络最小割的一半
	}
};

/*

BoardPainting test;
#define FILE "boardpainting"
#define gc() getchar()
std::vector<std::string> map;
void init(){
	char c=gc();
	do{
		std::string s;
		while(c!='"')
			c=gc();
		c=gc();
		while(c!='"')
			s=s+c,c=gc();
		c=gc();
		map.push_back(s);
	}while(c!='}');
}
int main(){
	freopen(FILE".in","r",stdin);
	freopen(FILE".out","w",stdout);
	init();
	printf("%d\n",test.minimalSteps(map));
	return 0;
}
*/
