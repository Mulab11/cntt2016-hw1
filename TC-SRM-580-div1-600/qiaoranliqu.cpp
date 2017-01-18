#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,st,ed,ans;
struct Node{
		int l,r;
}A[N];
inline int cmp(Node a,Node b)
{
	return a.l<b.l;
}
int work(int x)
{
	  int l=0,now=ed,f=0,ans=0;
	  for (;now<st;) //设当前能覆盖的最右端点是now,选取一个向右延伸最多的段,如果一旦能覆盖x的时候,将x选进去 
	  {
			if (!f&&now>=A[x].l)
			{
				 now=max(now,A[x].r);
				 f=1;
			}
			else 
			{
				int Max=now;
				while (l<n&&A[l].l<=now)
						Max=max(Max,A[l].r),++l;
				if (Max==now) return -1;
				++ans; now=Max;
			}
	  }
	  return ans;
}
class ShoutterDiv1{
	public:
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)
	{
			string S1000,S100,S10,S1,T1000,T100,T10,T1; //本题读入非常麻烦 
			for (i=0;i<(int)s1000.size();++i) S1000+=s1000[i];
			for (i=0;i<(int)s100.size();++i) S100+=s100[i];
			for (i=0;i<(int)s10.size();++i) S10+=s10[i];
			for (i=0;i<(int)s1.size();++i) S1+=s1[i]; 
			for (i=0;i<(int)t1000.size();++i) T1000+=t1000[i];
			for (i=0;i<(int)t100.size();++i) T100+=t100[i];
			for (i=0;i<(int)t10.size();++i) T10+=t10[i];
			for (i=0;i<(int)t1.size();++i) T1+=t1[i]; 
			n=(int)S1000.size();
			ed=100000000;
			for (i=0;i<n;++i)
				A[i]=(Node){(S1000[i]-'0')*1000+(S100[i]-'0')*100+(S10[i]-'0')*10+S1[i],
							(T1000[i]-'0')*1000+(T100[i]-'0')*100+(T10[i]-'0')*10+T1[i]},
				ed=min(ed,A[i].r),st=max(st,A[i].l);  //事实上,我们要求的是选取最少的连续的段,使得其覆盖[min{R[i]},max{L[i]}]. 
			sort(A,A+n,cmp);
			for (i=0;i<n;++i) 
			ans+=work(i);
			return max(-1,ans);
	}
}MRT;

int main()
{
	 cout<<MRT.count({"22", "2"},
{"00", "0"},
{"11", "1"},
{"21", "4"},
{"22", "2"},
{"00", "0"},
{"11", "1"},
{"43", "6"});
}
