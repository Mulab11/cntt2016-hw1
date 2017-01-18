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
inline int cmp(int a,int b)
{
		return a>b;
}
int i,j,m,n,p,k,R,ratings[N];
class EllysRoomAssignmentsDiv1{
	public:
	double getAverage(vector <string> rst)
	{
		string s; for (i=0;i<(int)rst.size();++i) s+=rst[i];
		s+=" ";
		for (i=0;i<(int)s.length();i=j+1)
		{
				int now=0;
				for (j=i;s[j]!=' ';++j) now=now*10+s[j]-'0';
				ratings[n++]=now;
		}
		int goal=ratings[0],ID;
		sort(ratings,ratings+n,cmp);
		for (i=0;i<n;++i) if (ratings[i]==goal) ID=i;
		int R=(n+19)/20;
		vector<double> v;
		for (i=0;i<n;i=j) //枚举每组被加入的人,如果本人在里面,那么rating确定,否则rating就是所有人的平均值 
		{
			 j=min(i+R,n);
			 if (i<=ID&&ID<j) v.pb(ratings[ID]);
			 else 
			 {
			 		double s=0;
			 		for (k=i;k<j;++k) s+=ratings[k];
			 		v.pb(s/(j-i));
			 }
		}
		double gg=0;
		for (i=0;i<(int)v.size();++i) gg+=v[i];  
		int T=n/R;
		if (n%R==0) return gg/T;
		else 
		if (ID/R==T) return gg/(T+1); //如果本人在最后一组里,那么一定是有T+1个人. 
		else  //分本人是否在一个拥有(T+1)个人的房间讨论 
		{
			double p1=(n%R)/(double)R; 
        	double p2=1-p1;      
       		return p1*(gg/(T+1))+p2*(gg-v[T])/T;
    	}
	}
}MRT;

int main()
{
	cout<<MRT.getAverage({"1924 1242 1213 1217 2399 1777 2201 2301 1683 2045 ", "1396 2363 1560 2185 1496 2244 2117 2207 2098 1319 ",
 "2216 1223 1256 2359 2394 1572 2151 2191 2147 2253 ", "1633 2217 2211 1591 1310 1209 1430 1445 1988 2030 ",
 "1947 1202 1203"});
}
