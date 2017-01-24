#include <vector>
#include <string>
#define MOD 1000000009
using namespace std;
class Mountains{
public:
	int N,W,h[15],L[15],R[15],pos[15],f[15][55],a[55];
	int diff(int a,int b){return a>b?a-b:b-a;}
	void cmin(int&a,int b){b<a?a=b:1;}
	void cmax(int&a,int b){b>a?a=b:1;}
	int dfs(int i,int m){ // 求放置0~i有多少种方案，m为上一个覆盖整个区间的位置
		if(i<0)return 1;
		if(m==i+1&&f[m][pos[m]])return f[m][pos[m]]-1;
		int&p=pos[i],s=0;
		if(R[i]<0){ // i被完全覆盖，统计有多少个覆盖i的点
			for(int j=i+1;j<=m&&j<N;j++)if(h[j]>=h[i]){
				int l=pos[j]-h[j]+h[i],r=pos[j]+h[j]-h[i]+1;
				cmax(l,0);cmin(r,W);a[l]++;a[r]--;
			}
			for(int j=0;j<W;a[j+1]+=a[j],a[j++]=0)if(a[j])s++,p=j;
			if(s)s=1ll*s*dfs(i-1,m)%MOD; // 搜索剩下部分
			if(m==i+1)f[m][pos[m]]=s+1;
			return s;
		}
		int hl=0,hll=0,hr=0,hrr=0; // hl,hll,hr,hrr分别为L[i],L[i]-1,R[i],R[i]+1当前高度
		for(int j=i+1;j<=m&&j<N;j++){
			cmax(hl,h[j]-diff(L[i],pos[j]));
			cmax(hll,h[j]-diff(L[i]-1,pos[j]));
			cmax(hr,h[j]-diff(R[i],pos[j]));
			cmax(hrr,h[j]-diff(R[i]+1,pos[j]));
		}
		int pl=L[i],pr=R[i];
		cmax(pl,hr-h[i]+R[i]+1);
		cmin(pr,h[i]+L[i]-hl-1);
		if(L[i])cmax(pl,h[i]+L[i]-hll-1);
		if(R[i]<W-1)cmin(pr,hrr-h[i]+R[i]+1);
		for(p=pl;p<=pr;p++)s=(s+dfs(i-1,!L[i]&&R[i]==W-1?i:m))%MOD;
		if(m==i+1)f[m][pos[m]]=s+1;
		return s;
	}
	int countPlacements(vector <int> heights, vector <string> visibility){
		N=heights.size();W=visibility[0].length();
		for(int i=0;i<N;i++){
			h[i]=heights[i];
			for(L[i]=0;L[i]<W&&visibility[i][L[i]]=='-';L[i]++);
			for(R[i]=W-1;R[i]>=0&&visibility[i][R[i]]=='-';R[i]--);
		}
		return dfs(N-1,99);
	}
};
