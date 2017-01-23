#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

class IncrementAndDoubling{
public:
	int getMin(vector<int> desiredArray){
		int ans=0,maxx=0;
		for(int i=0;i<desiredArray.size();i++){
			int t=desiredArray[i],len=0;
			if(!t) continue;
			while(t){
				if(t&1) ans++;//计算1的个数 
				len++;t>>=1;
			} 
			maxx=max(maxx,len-1);//计算最大的长度 
		}
		return ans+maxx;
	}
};
