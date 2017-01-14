#include<algorithm>
#include<string>
int n;int temp;
using namespace std;
int f[2555][55][55]={};
int codeforces=1000000007;
class LittleElephantAndPermutationDiv1
{
public:
	int getNumber(int N, int K)
	{
		f[min(N+N,K)][N][0]=N*(N-1);
		f[min(N,K)][N][1]=N;
		for(int k=0;k<=K;k++)
			for(int i=N;i>1;i--)
				for(int j=0;j<=N-i+1;j++)
					if(f[k][i][j])
					{
						int codeforces1=N-i+1-j;
						int codeforces2=N-j-codeforces1*2;
						if(codeforces1)
							f[k][i-1][j+2]=(f[k][i-1][j+2]+1LL*f[k][i][j]*codeforces1*codeforces1)%codeforces;
						if(codeforces2)
							temp=min(k+i-1,K),
							f[temp][i-1][j+1]=(f[temp][i-1][j+1]+1LL*f[k][i][j]*codeforces2)%codeforces;
						if(codeforces2>1)
							temp=min(k+i+i-2,K),
							f[temp][i-1][j]=(f[temp][i-1][j]+1LL*f[k][i][j]*(codeforces2*(codeforces2-1)))%codeforces;
						if(codeforces1&&codeforces2)
							temp=min(k+i-1,K),
							f[temp][i-1][j+1]=(f[temp][i-1][j+1]+1LL*f[k][i][j]*codeforces1*codeforces2*2)%codeforces;
					}
		return f[K][1][N];
	}
};
