#include<cstdio>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class CharacterBoard{
	private:
		static const int maxn=110,mod=1000000009;
		typedef pair<long long,char> pl;
		typedef map<int,char>::iterator mit;
		int n,m;
		pl nod[maxn];
		set<int> use;
		map<int, char> mp;
		long long power(long long a,int b){
			long long ret=1;
			while(b){
				if (b&1) ret=ret*a%mod;
				b>>=1;
				a=a*a%mod;
			}
			return ret;
		}
	public:
		int countGenerators(vector <string> s, int W, int i0, int j0){
			n=s.size();
			m=s[0].size();
			for (int i=1-n;i<n;++i)
			for (int j=1-m;j<m;++j){
				long long tmp=(long long)W*i+j;
				if (tmp<0) continue;
				for (int k=1;k<=W&&1ll*k*k<=tmp;++k) if (tmp%k==0){
					long long t=tmp/k;
					use.insert(k);
					if (t<=W&&t!=k) use.insert(t);
				}
			}
			long long ans=0;
			if (W>=n*m) ans=(power(26,W-n*m+1)-1+mod)*power(25,mod-2)%mod;
//			cout<<ans<<endl;
//			cout<<use.size()<<endl;
			for (auto a:use){
				mp.clear();
				bool fl=false;
				for (int i=0;i<n&&!fl;++i)
				for (int j=0;j<m&&!fl;++j){
					int t=((long long)W*(i+i0)+j+j0)%a;
					mit it=mp.find(t);
//					if (a==5) printf("%d,%d -> %d  %c\n",i+i0,j+j0,t,s[i][j]);
					if (it!=mp.end()){
						if (it->second!=s[i][j]) fl=true;
					}
					else mp[t]=s[i][j];
				}
//				printf("check %d, fl=%d \n",a,fl?1:0);
				ans=(ans+(fl?0:power(26,a-mp.size())))%mod;
				if (a>=n*m) ans=(ans-power(26,a-n*m)+mod)%mod;
			}
			return ans;
		}
};
