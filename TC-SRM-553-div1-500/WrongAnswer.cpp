#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class TwoConvexShapes{
public:
	int N,M,L0[60],R0[60],L1[60],R1[60],f[60][60][4][4][3],rev[4]={0,2,1,3};
	bool check(int i,int j,int s){ // 判断分界是否合法
		if(!s)return!j&&!R1[i];
		if(s==3)return!j&&!R0[i];
		if(!j||j>=M)return 0;
		if(s==2)return R0[i]<=j&&j<=L1[i];
		return R1[i]<=j&&j<=L0[i];
	}
	// 已确定前i行，第i行分界线不超过j，第i行类型type，可调整方向dir，已出现状态ex，求方案数
	// type[0]:(i,0)的字符，type[1]:(i,M-1)的字符
	// dir[0]:能否左移，dir[1]:能否右移
	// ex[0]:是否出现01，ex[1]:是否出现10
	int F(int i,int j,int type,int dir,int ex){
		int&s=f[i][j][type][dir][ex];
		if(s)return s-1;
		if(type%2!=type/2%2&&j>1)(s+=F(i,j-1,type,dir,ex))%=MOD; // 分界线在j左侧
		if(!check(i,j,type))return s++; // 分界线在j不合法
		// 统计分界线在j的转移方案数
		if(i==N-1){s=(s+1)%MOD;return s++;} // 最后一行，方案唯一
		for(int to=0;to<4;to++){ // 向type=to转移
			if(to==1||to==2){ // 整行颜色不同（1: 10; 2: 01）
				if(ex!=to){
					if(type==to){
						(s+=F(i+1,j,to,dir,3-to)-F(i+1,j-1,to,dir,3-to))%=MOD; // 分界线不变
						if(dir%2)(s+=F(i+1,j-1,to,dir&1,3-to))%=MOD; // 分界线左移
						if(dir/2)(s+=F(i+1,M-1,to,dir&2,3-to)-F(i+1,j,to,dir&2,3-to))%=MOD; // 分界线右移
						if(s<0)s+=MOD;
					}
					else if(((type^to^3)&dir)==(type^to^3))(s+=F(i+1,M-1,to,dir&(type^to^3),3-to))%=MOD; // 当前整行颜色相同，只需判方向转移到所有状态
				}
			}
			else if(((type^to)&dir)==(type^to))(s+=F(i+1,0,to,dir&(rev[type]^to^3),ex))%=MOD; // 整行颜色相同，只需判方向
		}
		return s++;
	}
	int countWays(vector <string> grid){
		N=grid.size();M=grid[0].length();
		for(int i=0;i<N;i++){
			for(L0[i]=0;L0[i]<M&&grid[i][L0[i]]!='B';L0[i]++);
			for(L1[i]=0;L1[i]<M&&grid[i][L1[i]]!='W';L1[i]++);
			for(R0[i]=M;R0[i]&&grid[i][R0[i]-1]!='B';R0[i]--);
			for(R1[i]=M;R1[i]&&grid[i][R1[i]-1]!='W';R1[i]--);
		}
		int ans=F(0,0,0,3,0); // 00
		(ans+=F(0,M-1,1,3,2))%=MOD; // 10
		(ans+=F(0,M-1,2,3,1))%=MOD; // 01
		(ans+=F(0,0,3,3,0))%=MOD; // 11
		return ans;
	}
};
