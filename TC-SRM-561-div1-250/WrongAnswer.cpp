#include <vector>
#include <string>
#include <algorithm>
#define INF (1<<30)
using namespace std;
class ICPCBalloons{
public:
	// M[0],...,M[Mcnt-1]为每种M大小的气球个数，L[0],...,L[Lcnt-1]为每种L大小的气球个数
	int n,m,A[15],M[65],Mcnt,Msum,L[65],Lcnt,Lsum,ans;
	int cost(int a,int b){return a>b?0:b-a;}
	// i为已确定题数，Mp和Lp为剩余可分配M和L气球种数，Ms和Ls为剩余M和L气球总个数，c为已重新染色气球数
	void dfs(int i,int Mp,int Lp,int Ms,int Ls,int c){ 
		if(Ms<0||Ls<0)return; // 不能超过总数
		if(!i){c<ans?ans=c:1;return;} // 更新答案
		// 枚举题 i 的气球颜色，用个数最多的一种气球来匹配
		dfs(i-1,Mp-1,Lp,Ms-A[i-1],Ls,c+cost(M[Mp-1],A[i-1]));
		dfs(i-1,Mp,Lp-1,Ms,Ls-A[i-1],c+cost(L[Lp-1],A[i-1]));
	}
	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted){
		// 把气球按大小M和L分为两组，注意补一些0
		n=balloonCount.size();m=maxAccepted.size();Mcnt=Lcnt=m;Msum=Lsum=0;
		for(int i=0;i<m;i++)A[i]=maxAccepted[i],M[i]=L[i]=0;
		for(int i=0;i<n;i++)balloonSize[i]=='M'?Msum+=(M[Mcnt++]=balloonCount[i]):Lsum+=(L[Lcnt++]=balloonCount[i]);
		// 将气球按个数排序，题目按通过数排序
		sort(M,M+Mcnt);sort(L,L+Lcnt);sort(A,A+m);
		// 用DFS枚举每种题目对应气球的颜色，得到答案
		ans=INF;dfs(m,Mcnt,Lcnt,Msum,Lsum,0);return ans==INF?-1:ans;
	}
};
