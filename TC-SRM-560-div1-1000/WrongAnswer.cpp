#include <vector>
#include <string>
using namespace std;
class BoundedOptimization{
public:
	int n,Max,lb[13],ub[13],k[13][13],ty[13],del[13];
	double x[13],ans;
	void dfs(int i,int cnt,int sum){
		if(!cnt&&sum<0)return;
		if(i==n){
			double s=0;
			for(i=n;i--;){
				if(!ty[i]){
					if(lb[i]*cnt<=sum+cnt*del[i]&&sum+cnt*del[i]<=ub[i]*cnt)x[i]=sum*1.0/cnt+del[i];
					else return;
				}
				for(int j=n;--j>i;)k[i][j]?s+=x[i]*x[j]:1;
			}
			if(s>ans)ans=s;return;
		}
		for(ty[i]=0;ty[i]<3;ty[i]++){
			if(!ty[i]){
				del[i]=0;
				int s=sum;
				bool flag=1;
				for(int j=i,t;j--;){
					if(k[i][j]&&ty[j])s-=(t=ty[j]==1?lb[j]:ub[j]),del[i]+=t;
					if(!k[i][j]&&!ty[j])flag=0;
				}
				if(flag)dfs(i+1,cnt+1,s);
				for(int j=i;j--;){
					if(k[i][j]&&ty[j])del[i]+=ty[j]==1?lb[j]:ub[j];
				}
			}
			else{
				int*t=ty[i]==1?lb:ub,s=sum-t[i];
				for(int j=i;j--;)if(k[i][j]&&!ty[j])s-=t[i],del[j]+=t[i];
				x[i]=t[i];dfs(i+1,cnt,s);
				for(int j=i;j--;)if(k[i][j]&&!ty[j])del[j]-=t[i];
			}
		}
	}
	double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum){
		n=lowerBound.size();
		for(int i=0,l='+',c;i<expr.size();i++)
			for(int j=0;j<expr[i].length();j++)(c=expr[i][j])!='+'&&l!='+'?k[c-'a'][l-'a']=k[l-'a'][c-'a']=1:1,l=c;
		int sum=0;
		for(int i=0;i<n;i++)lb[i]=lowerBound[i],sum+=(ub[i]=upperBound[i]);
		if(maxSum>=sum){
			sum=0;
			for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)
				sum+=k[i][j]*upperBound[i]*upperBound[j];
			return sum;
		}
		dfs(0,0,maxSum);
		return ans;
	}
};
