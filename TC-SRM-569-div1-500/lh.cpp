#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheJediTest{
	static const int maxn=30;
	int num[maxn],fr[maxn],n;
	
	public:
		int minimumSupervisors(vector<int> students, int K){
			int ans=0;
			n=students.size();
			for (int i=0;i<n;++i) num[i+2]=students[i];
			n+=2;
			for (int i=2;i<n;++i){
				int g=(fr[i-1]+num[i-1]+num[i])%K,giv=0;
				if (g<=num[i-1]+num[i]){
					if (num[i]>=g){
						giv+=num[i]-g;
						num[i]=g;
					}
					else{
						fr[i]=g-num[i];
						num[i-1]-=fr[i];
					}
				}
				else giv+=num[i],num[i]=0;
				num[i-1]+=giv;
				int tmp=num[i-1]/K;
				fr[i]+=tmp*K;
				num[i-1]-=tmp*K;
			}
			for (int i=2;i<n;++i) ans+=(num[i]+fr[i]+K-1)/K;
			return ans;
		}
};
