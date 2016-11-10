#include <vector>
#include <string>
using namespace std;
class Orienteering{
public:
	int Qx[2510],Qy[2510],fa[2510],siz[2510],Gx[2510],Gy[2510],Gcnt,Dis[52][52],D[310][310],vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
	double select(int a,int b,int K){ // C(a,K)/C(a+b,K)
		double ans=1;
		for(int i=0;i<K;i++)ans=ans*(a-i)/(a+b-i);
		return ans;
	}
	bool cmp(int i1,int j1,int i2,int j2){ // 比较(i1,j1)和(i2,j2)的距离，相同则比较点编号的字典序
		if(D[i1][j1]!=D[i2][j2])return D[i1][j1]<D[i2][j2];
		if(i1>j1){int t=i1;i1=j1;j1=t;}
		if(i1!=i2)return i1>i2;
		return j1>j2;
	}
	double expectedLength(vector <string> field, int K){
		int n=field.size(),m=field[0].length();
		double ans=0;
		// 计算必经边数的期望
		for(int x=0;x<n;x++)for(int y=0;y<m;y++)if(field[x][y]=='*'){
			// 从每个checkpoint出发广度优先遍历（BFS）
			// 求出所有checkpoint之间的距离
			Gx[Gcnt]=x;Gy[Gcnt]=y;
			for(int i=0;i<n;i++)for(int j=0;j<m;j++)Dis[i][j]=0;
			int head=0,tail=1;
			Qx[0]=x;Qy[0]=y;Dis[x][y]=1;
			for(;head<tail;head++){
				for(int d=0;d<4;d++){
					int dx=Qx[head]+vx[d],dy=Qy[head]+vy[d];
					if(dx>=0&&dx<n&&dy>=0&&dy<m&&!Dis[dx][dy]&&field[dx][dy]!='#')Qx[tail]=dx,Qy[tail++]=dy,Dis[dx][dy]=Dis[Qx[head]][Qy[head]]+1,!Gcnt?fa[tail-1]=head:1;
				}
			}
			if(!Gcnt){
				// 第一次BFS时，计算必经边数的期望
				// siz[i]为子树内checkpoint个数
				while(head--)field[Qx[head]][Qy[head]]=='*'?++siz[head]:1,head?siz[fa[head]]+=siz[head]:1;
				// 对每个非根节点，答案加上该边与父节点的连边在某两个checkpoint间路径的概率
				for(head=tail-1;head;head--)ans+=1-select(siz[head],siz[0]-siz[head],K)-select(siz[0]-siz[head],siz[head],K);
			}
			for(int i=0;i<Gcnt;i++)D[Gcnt][i]=D[i][Gcnt]=Dis[Gx[i]][Gy[i]]-1;
			Gcnt++;
		}
		ans*=2;
		// 计算最远点对距离的期望
		for(int i=0;i<Gcnt;i++)for(int j=i+1;j<Gcnt;j++){ // 枚举最远点对 i,j
			int v=0;
			for(int l=0;l<Gcnt;l++)if(l!=i&&l!=j&&cmp(l,i,i,j)&&cmp(l,j,i,j))v++; // 统计到i,j距离小于D[i][j]的点数v
			ans-=D[i][j]*(K-1.0)*K/(Gcnt-1.0)/Gcnt*select(v,Gcnt-v-2,K-2); // i,j为最远点对的概率
		}
		return ans;
	}
};
