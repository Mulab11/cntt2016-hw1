#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class SurveillanceSystem
{
	static const int maxn=100;
	int sum[maxn];
	int rec[maxn][maxn],cnt[maxn],cr[maxn];
	char res[maxn];
	public:
		string getContainerInfo(string arr,vector<int> num,int L)
		{
			memset(sum,0,sizeof(sum));
			memset(rec,0,sizeof(rec));
			memset(cnt,0,sizeof(cnt));
			memset(res,0,sizeof(res));
			int n=arr.length();
			for (int i=0;i<n;++i) sum[i+1]=sum[i]+((arr[i]=='X')?1:0);
			for (int i=L;i<=n;++i){
				int k=sum[i]-sum[i-L];
				rec[k][cnt[k]++]=i;
				//if (k==1) printf("xx %d\n",i);
			}
			for (auto &i :num) ++cr[i];
			
			for (int i=1;i<=n;++i){
				for (int j=0;j<=n;++j){
					int a=0;
					for (int k=0;k<cnt[j];++k) if (rec[j][k]>=i&&rec[j][k]-L<i) ++a;
					//printf("i=%d,j=%d,a=%d,cnt=%d,cr=%d\n",i,j,a,cnt[j],cr[j]);
					if (a==0) continue;
					if (a+cr[j]>cnt[j]) res[i]='+';
					else if (cr[j]>0&&res[i]==0) res[i]='?';
				}
				if (res[i]==0) res[i]='-';
			}
			res[n+1]='\0';
			return res+1;
		}
};