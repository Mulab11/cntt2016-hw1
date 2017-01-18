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

#define N 55
#define M 200005
#define seed 23333
#define Mo 1000000009

using namespace std;
int i,j,m,n,p,k,A[N],B[N],C[N],ans;
vector<pair<int,int> >va,vb,vc;
vector<int>v;
void jia(int &x,int y)
{
		x+=y; if (x>=Mo) x-=Mo;
}
int cal(vector<int> v) //给出一堆deep,算可能的森林数量 
{
		int i,sum=1,cur=0;
		for (i=0;i<(int)v.size();++i) if (v[i]==0) ++cur;
		if (cur!=1) return 0;
		for (i=0;i<(int)v.size();++i)
			if (v[i]!=0)
		{
				int now=0; 
				for (j=0;j<(int)v.size();++j) 
					if (v[j]<v[i]) ++now;
				sum=1ll*sum*now%Mo;
		} 
		return sum;
}
map<int,vector<int> >mp;
map<int,vector<int> >::iterator it;
int work(vector<pair<int,int> > v)
{
		int i,sum=1;
		mp.clear();
		for (i=0;i<(int)v.size();++i)	mp[v[i].fi].pb(v[i].se); 
		for (it=mp.begin();it!=mp.end();++it) sum=1ll*sum*cal(it->se)%Mo;
		return sum;
}
int Center(int x)
{
	int i;
	va.clear(); vb.clear(); vc.clear(); v.clear();
	va.pb(mk(0,0)); vb.pb(mk(0,0)); vc.pb(mk(0,0)); v.pb(0);
	for (i=0;i<n;++i)
		if (x!=i)
		{
				int f=0;
				if (A[i]-A[x]==B[i]-B[x]&&B[i]-B[x]==C[i]-C[x]&&A[i]-A[x]>0) //在中心点的子树里 
				{
					v.pb(A[i]);
					f=1;
				}
				if (f) continue;
				if (B[i]-B[x]==C[i]-C[x]&&B[i]-B[x]>0) //这个点在A所在的分支里 
				{
						int now=A[i]+B[i]-B[x]-A[x];
						if (now%2==0&&now>=0)
						{
								now/=2;
								if (A[i]-now>=0&&A[i]-now<A[x])
								 va.pb(mk(A[i]-now,now)),f=1;
						}
				}
				if (A[i]-A[x]==C[i]-C[x]&&A[i]-A[x]>0) //in B
				{
						int now=B[i]+A[i]-A[x]-B[x];
						if (now%2==0&&now>=0)
						{
								now/=2;
								if (B[i]-now>=0&&B[i]-now<B[x])
								 vb.pb(mk(B[i]-now,now)),f=1;
						}
				}
				if (B[i]-B[x]==A[i]-A[x]&&B[i]-B[x]>0) //in C
				{
						int now=C[i]+B[i]-B[x]-C[x];
						if (now%2==0&&now>=0)
						{
								now/=2;
								if (C[i]-now>=0&&C[i]-now<C[x])
								 vc.pb(mk(C[i]-now,now)),f=1;
						}
				}
				if (f) continue;	
				return 0;		
		}
		return 1ll*cal(v)*work(va)%Mo*work(vb)%Mo*work(vc)%Mo;
}
int Line(int *A,int *B,int *C)
{
		set<pair<int,int> >st; st.clear();
		set<pair<int,int> >::iterator it;
		int i;
		for (i=0;i<n;++i) //找各种可能的两条长度 
		{
				st.insert(mk(A[i]-B[i],C[i]-B[i]));
				st.insert(mk(B[i]-A[i],C[i]-B[i]));
				st.insert(mk(A[i]-B[i],B[i]-C[i]));
				st.insert(mk(A[i]+B[i],C[i]-B[i])); 
				st.insert(mk(A[i]-B[i],B[i]+C[i]));
		}
		int sum=0;
		for (it=st.begin();it!=st.end();++it) //枚举所有情况进行判断 
		{	
		    	int a=it->fi,b=it->se;
		    	if (a<=0||b<=0) continue;
		    	if (a==2&&b==3)
		    	 a=2;
				va.clear(); vb.clear(); va.pb(mk(0,0)); vb.pb(mk(0,0)); v.clear(); v.pb(0);
				for (i=0;i<n;++i) //利用与情况一相似的方法判断在哪个位置 
				{
						int f=0;
						if (A[i]-a==B[i]&&C[i]-b==B[i]) v.pb(B[i]),f=1;
						if (f) continue;
						if (C[i]-b==B[i])
						{
							int now=A[i]+B[i]-a;
							if (now%2==0)
							{
							   	now/=2;
							   	if (now>=0)
							   	{
							   			if (A[i]-now>=0&&A[i]-now<a)  va.pb(mk(A[i]-now,now)),f=1;
							   	}
							}
						}
						if (A[i]-a==B[i])
						{
							 int now=B[i]+C[i]-b;
							 if (now%2==0)
							 {
							 	now/=2;
							 	if (now>=0)
							 	{
							 		   if (C[i]-now>=0&&C[i]-now<b) vb.pb(mk(C[i]-now,now)),f=1;
							 	}
							 }
						}
						if (!f) break;
				}
				if (i!=n) continue;
				int ll=sum;
				jia(sum,1ll*cal(v)*work(va)%Mo*work(vb)%Mo); 
		}
		return sum;
}
class UnknownTree{
	public:
		int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC)
		{
				n=distancesA.size();
				for (i=0;i<n;++i) A[i]=distancesA[i],B[i]=distancesB[i],C[i]=distancesC[i];
				for (i=0;i<n;++i) jia(ans,Center(i)); //枚举i作为中心 
				jia(ans,Line(A,B,C));
				jia(ans,Line(B,A,C));
				jia(ans,Line(A,C,B));
				return ans;
		}
}MRT;
int main()
{
		cout<<MRT.getCount({1, 1, 1, 3, 1, 2, 1}, {3, 3, 3, 5, 3, 4, 3}, {2, 2, 2, 4, 2, 3, 2});
}
