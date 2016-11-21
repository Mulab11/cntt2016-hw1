#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class BoundedOptimization{
	static const int maxn=13;
	int n;
	bool map[maxn][maxn],sel[maxn],check[1<<maxn];
	int val[maxn],use[maxn],A[maxn],bound[maxn][2];
	double ans;
	
	public:
	double maxValue(vector<string> expr, vector<int> lowerBound,
	vector<int> upperBound, int maxSum){
		
		n=lowerBound.size();
		string s;
		for (auto &x:expr) s+=x;
		
		int ll=s.length();
		for(int i=0;i<ll;){
			int a=s[i]-'a';
			if (i+1<ll&&s[i+1]=='+'){
				++sel[a];
				i+=2;
			}
			else{
				int b=s[i+1]-'a';
				map[a][b]=map[b][a]=true;
				i+=3;
			}
		}
		for (int i=0;i<n;++i){
			bound[i][0]=lowerBound[i];
			bound[i][1]=upperBound[i];
		}
		check[0]=true;
		for (int i=1;i<(1<<n);++i){
			for (int j=0;j<n;++j) if (i&(1<<j)){
				if(check[i^(1<<j)]){
					check[i]=true;
					for (int k=j+1;k<n;++k) if (i&(1<<k)){
						if (!map[j][k]){
							check[i]=false;
							break;
						}
					}
				}
				else check[i]=false;
				break;
			}
		}
		int all=(1<<n)-1;
		for (int i=0;i<(1<<n);++i) if (check[all^i]){
//			printf("i=%d\n",i);
			for (int t=i;;t=(t-1)&i){
//				printf("t=%d\n",t);
				int cnt=0,sum=0;
				for (int k=0;k<n;++k) if (t&(1<<k)) sum+=(val[k]=bound[k][0]);
				else if (i&(1<<k)) sum+=(val[k]=bound[k][1]);
				else{
					val[k]=-1;
					use[cnt++]=k;
				}
				if (i==all&&t==all){
					double tt=0;
					for (int a=0;a<n;++a){
						if (sel[a]) tt+=val[a];
						for (int b=a+1;b<n;++b) if (map[a][b]) tt+=val[a]*val[b];
					}
					ans=max(ans,tt);
					continue;
				}
//				if (i==4&&t==4) printf("sum=%d\n",sum);
				if (sum>=maxSum){
					if (t==0) break;
					continue;
				}
				double tmp=0;
				for (int j=0;j<cnt;++j){
					A[j]=0;
					for (int x=0;x<n;++x) if (map[use[j]][x]&&val[x]!=-1) A[j]+=val[x];
					if (sel[use[j]]) ++A[j];
					tmp+=A[j];
				}
				tmp=(maxSum-sum-tmp)/cnt;
//				if (i==5&&t==5) printf("tmp=%lf\n",tmp);
				
				double now=0;
				
				for (int j=0;j<n;++j) if (val[j]!=-1){
					if (sel[j]) now+=val[j];
					for (int k=j+1;k<n;++k) if (map[j][k]&&val[k]!=-1) now+=val[j]*val[k];
				}
//				if (i==5&&t==5) printf("now=%lf\n",now);
				for (int j=0;j<cnt;++j){
					double x=A[j]+tmp;
					if (x>bound[use[j]][1]||x<bound[use[j]][0]){
						now=-1e18;
						break;
					}
//					if (i==5&&t==5) printf("A[%d]=%d,x=%lf\n",j,A[j],x);
					now+=x*(A[j]+0.5*(maxSum-sum-x));
//					if (i==5&&t==5) printf("now=%lf\n",now);
				}
				ans=max(ans,now);
//				if (i==5&&t==5) printf("%lf, ans=%lf\n",now,ans);
				if (t==0) break;
			}
		}
		return ans;
	}
};
