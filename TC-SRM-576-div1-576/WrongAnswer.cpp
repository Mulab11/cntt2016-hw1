#include <vector>
#include <string>
#define MOD 1000000009
using namespace std;
class TheExperiment{
public:
	int a[310],l[310],r[310],t[310]; // a[i]为前i个数的和，[l[i],r[i])为满足第i~j-1个数的和在[A,B]内且j-i<L的j的区间，t[i]表示i之后的L个数的和是否在[A,B]内
	long long f[310][310][3]; // f[i][j][k]为从[l,n)中取出j个区间(l>=i)，[0,l)状态为k（k=0:空;k=1:不含长度L的区间;k=2:含L的区间）的方案数和
	int countPlacements(vector <string> intensity, int M, int L, int A, int B){
		int n=0;
		for(int i=0;i<intensity.size();i++)
			for(int j=0;j<intensity[i].length();j++)a[++n]=intensity[i][j]-'0';
		for(int i=0;i<n;i++)a[i+1]+=a[i];
		// 预处理区间
		for(int i=0;i<n;i++){
			while(l[i]<=n&&a[l[i]]-a[i]<A)l[i]++;
			while(r[i]<=n&&a[r[i]]-a[i]<=B)r[i]++;
			l[i+1]=l[i];r[i+1]=r[i];
		}
		for(int i=0;i<n;i++){
			if(l[i]>i+L)r[i]=l[i]; // i~i+L-1的和不足A，无法转移
			else if(i+L<r[i])r[i]=i+L,t[i]=1; // 长度L的区间和在[A,B]内，修改区间
		}
		// 转移(i,j,k)
		// 1:不选i，转移到(i+1,j,0)，前提是k不为1
		// 2:用一段区间覆盖i，转移到(i',j-1,k')，当i'-i=L时k'=2，否则k'=1
		long long g[2];
		f[n][0][0]=f[n][0][2]=1;
		for(int i=n-1;i>=0;i--){
			for(int j=0;j<=M;j++){
				for(int k=0;k<2;k++)g[k]=j?(f[l[i]][j-1][k+1]+MOD-f[r[i]][j-1][k+1]+(t[i]?f[i+L][j-1][2]+MOD-f[i+L+1][j-1][2]:0))%MOD:0; // 转移2的方案数
				f[i][j][0]=(f[i+1][j][0]*2+MOD-f[i+2][j][0]+g[0])%MOD;
				f[i][j][1]=(f[i+1][j][1]+g[0])%MOD;
				f[i][j][2]=(f[i+1][j][2]+f[i+1][j][0]+MOD-f[i+2][j][0]+g[1])%MOD;
			}
		}
		return (f[0][M][0]+MOD-f[1][M][0])%MOD;
	}
};
