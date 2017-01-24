#include <vector>
#include <string>
using namespace std;
class SurveillanceSystem{
public:
	string getContainerInfo(string containers, vector <int> reports, int L){
		int n=containers.length(),ty[110]={0},cnt[110]={0},m[110]={0};
		for(int i=0,r=0,s=0;i+L<=n;i++){ // 求出所有长度为L的区间[i,i+L)的长度ty及每种长度的个数cnt
			while(r<i+L)containers[r++]=='X'?s++:1;
			cnt[ty[i+L]=s+1]++;containers[i]=='X'?s--:1;
		}
		for(int i=0;i<reports.size();i++)m[reports[i]+1]++; // 求出每种report的个数m
		string ans;
		int t[110]={0},ex1=0,ex2=0; // 存每种ty出现的个数t，t>0的个数ex1，t>cnt-m的个数ex2
		for(int i=0,r=0;i<n;i++){
			while(r<i+L)if(m[ty[++r]])++t[ty[r]]==1?ex1++:1,t[ty[r]]==cnt[ty[r]]-m[ty[r]]+1?ex2++:1;
			ans.push_back(ex1?ex2?'+':'?':'-');
			if(m[ty[i+1]])--t[ty[i+1]]==0?ex1--:1,t[ty[i+1]]==cnt[ty[i+1]]-m[ty[i+1]]?ex2--:1;
		}
		return ans;
	}
};
