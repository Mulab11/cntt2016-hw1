#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;



class PenguinEmperor{
	private:
		static const int maxn=355,mod=1000000007;
		static int n;
		static long long tmp[maxn];
		
		void MOD(long long &a){if (a>=mod) a-=mod;}
		struct mt{
			long long a[maxn];
			long long& operator [](int x){return a[x];}
			mt(){
				memset(a,0,sizeof(a));
				a[0]=1;
				return;
			}
			void add(int t,int cnt){
				memcpy(tmp,a,sizeof(long long)*n);
				memset(a,0,sizeof(long long)*n);
				for (int i=0;i<n;++i) a[(i+t)%n]=(tmp[i]*cnt)%mod;
				if (t!=0&&n-t!=t){
					t=n-t;
					for (int i=0;i<n;++i) a[(i+t)%n]=(a[(i+t)%n]+tmp[i]*cnt)%mod;
				}
				return;
			}
			void merge(mt x){
				memset(tmp,0,sizeof(long long)*n);
				for (int i=0;i<n;++i){
					for (int j=0;j<n;++j) tmp[(j+i)%n]=(tmp[(i+j)%n]+a[j]*x[i])%mod;
				}
				memcpy(a,tmp,sizeof(long long)*n);
				return;
			}
		}tr,ans;
		
	public: 
		int countJourneys(int num, long long T){
			n=num;
			if (T<n){
				for (int i=1;i<=T;++i){
					ans.add(i%n,1);
//					printf("i=%d:",i);
//					ans.print();
				}
			}
			else{
				for (int i=1;i<n;++i) tr.add(i,1);
//				tr.print();
				long long a=T/n;
				while(a){
					if (a&1) ans.merge(tr);
					tr.merge(tr);
					a>>=1;
				}
				T%=n;
				for (int i=1;i<=T;++i) ans.add(i,1);
			}
			return ans[0];
		}
};

int PenguinEmperor::n;
long long PenguinEmperor::tmp[maxn];
