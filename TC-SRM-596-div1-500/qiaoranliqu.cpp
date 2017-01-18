	#include<cstdio>
	#include<algorithm>
	#include<cstring>
	#include<iostream>
	#include<vector>
	#include<set>
	#include<map>
	#include<bitset>
	
	#define ls (t<<1)
	#define rs ((t<<1)+1)
	#define mid ((l+r)>>1)
	#define fi first
	#define se second
	#define mk make_pair
	
	#define N 55
	#define M 200005
	#define seed 23333
	#define Mo 998244353
	
	using namespace std;
	long long A[N],Sum[60],k;
	set<int>st[N];
	class BitwiseAnd{
	public:
	vector<long long> lexSmallest(vector<long long> v,int n)
	{
		    int i,j; vector<long long> ans; ans.clear(); 
		    for (i=0;i<v.size();++i)
			{
			      long long j=v[i];
			      for (k=0;j;j/=2,++k) if (j&1) { Sum[k]++,st[i].insert(k); }
			}
			for (i=0;i<(int)v.size();++i)
			  for (j=i+1;j<(int)v.size();++j)
			     if ((v[i]&v[j])==0) return ans;
			for (i=0;i<60;++i) if (Sum[i]>2) return ans;
			int rest=n-v.size();
			for (i=0;i<v.size();++i) ans.push_back(v[i]);
			for (i=1;i<=rest;++i)
	        {
			       for (j=i+1;j<=rest;++j)
				   {
				        for (k=0;k<60;++k) if (Sum[k]==0) break;
						if (k==60) { ans.clear(); return ans; }
					    A[i]+=1ll<<k;
						A[j]+=1ll<<k;
						Sum[k]=2;
				   }
				   for (j=0;j<(int)v.size();++j)
				   {
				   	     while (st[j].size())
				   	     {
				   	     	   int x=*st[j].begin();
				   	     	   if (Sum[x]==2) st[j].erase(st[j].begin());
				   	     	   else break;
				   	     }
				   	     if (!st[j].size()) { ans.clear(); return ans; }
						 int x=*st[j].begin();
						 st[j].erase(x);
						 A[i]+=1ll<<x;
				   }
				   ans.push_back(A[i]);
		    }
		    sort(ans.begin(),ans.end());
		    return ans;
	}
	};

