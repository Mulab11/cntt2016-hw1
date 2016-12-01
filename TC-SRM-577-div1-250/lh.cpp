#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

class EllysRoomAssignmentsDiv1{
	static const int maxn=1000;
	int num[maxn],n;
	static bool cmp(int a,int b){
		return a>b;
	}
	__float128 C(int a,int b){
		if (a<b) return 0;
		__float128 ret=1;
		int now=1;
		for (int i=b+1;i<=a;++i){
			ret*=i;
			if (now<=a-b) ret/=now++;
		}
		while (now<=a-b) ret/=now++;
		return ret;
	}
	
	public:
		double getAverage(vector<string> ratings){
			stringstream tmp;
			for (auto &i:ratings) tmp<<i;
			n=0;
			while(tmp>>num[n++]);
			--n;
			int tt=num[0];
			sort(num,num+n,cmp);
			tt=lower_bound(num,num+n,tt,cmp)-num;
			int R=(n+19)/20;
			if (n%R==0){
				printf("R=%d\n",R);
				double ans=0;
				for (int st=0;st<n;){
					int ed=st+R;
					if (tt>=st&&tt<ed){
						printf("tt=%d,num=%d,ans=%lf\n",tt,num[tt],ans);
						ans+=num[tt];
						printf("ans=%lf\n",ans);
					}
					else{
						for (int i=st;i<ed;++i){
							ans+=1.0/R*num[i];
							printf("+=%lf\n",1.0/R*num[i]);
						}
					}
					printf("st=%d,num=%d,ans=%lf\n",st,num[st],ans);
					st=ed;
				}
				return ans/(n/R);
			}
			else{
				double ans=0;
				int st;
				for (st=0;st<n;){
					int ed=st+R;
					if (ed>n) break;
					if (tt>=st&&tt<ed) ans+=num[tt];
					else{
						for (int i=st;i<ed;++i) ans+=1.0/R*num[i];
					}
					st=ed;
				}
				if (tt>=st) return (ans+num[tt])/(n/R+1);
				double tmp1,tmp2;
				tmp1=ans*C(R-1,n-st)/C(R,n-st)/(n/R);
				tmp2=ans*(1-C(R-1,n-st)/C(R,n-st));
				double ff=(1-C(R-1,n-st)/C(R,n-st))/(n-st);
				for (int i=st;i<n;++i) tmp2+=ff*num[i];
				return tmp1+tmp2/(n/R+1);
			}
		}
};
