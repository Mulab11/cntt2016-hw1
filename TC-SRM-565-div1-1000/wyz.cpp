// BEGIN CUT HERE

// END CUT HERE
#line 5 "UnknownTree.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000009
#define pb push_back

using namespace std;

typedef map<int,vector<int> > map0;

map0 mp[3];
vector<int> _d[3];
void Clear(){
	for (int i=0;i<3;++i)mp[i].clear(),_d[i].clear();
	for (int i=0;i<3;++i) _d[i].pb(0);
}
int calc(vector<int> &_a){
	sort(_a.begin(),_a.end());
	if (_a[0]!=0) return 0;
	int ret=1;
	int j=0;
	for (int i=1;i<_a.size();++i){
		while (_a[j]<_a[i]) ++j;
		ret=1LL*ret*j%P;
	}
	return ret;
}

#define inc(x,y) if(((x)+=(y))>=P)(x)-=P;

class UnknownTree{
	int ans;
	int n;
	void work0(vector<int> &A,vector<int> &B,vector<int> &C){
		for (int k=0;k<n;++k){
			Clear();
			int da=A[k],db=B[k],dc=C[k];
			bool valid=1;
			for (int i=0;valid&&i<n;++i){
				map0::iterator it;
				if (B[i]-A[i]==db+da&&C[i]-A[i]==dc+da) _d[0].pb(A[i]);
				else if (A[i]-B[i]==da+db&&C[i]-B[i]==dc+db)_d[1].pb(B[i]);
				else if (A[i]-C[i]==da+dc&&B[i]-C[i]==db+dc)_d[2].pb(C[i]);
				else{
					int dltA=A[i]-da,dltB=B[i]-db,dltC=C[i]-dc;
					int id=-1,key,v;
					if (dltB==dltC&&(dltB+dltA)%2==0&&(key=(dltB-dltA)/2)>=0&&(v=(dltB+dltA)/2)>=0)
						id=0;
					if (dltA==dltC&&(dltA+dltB)%2==0&&(key=(dltA-dltB)/2)>=0&&(v=(dltA+dltB)/2)>=0)
						id=1;
					if (dltA==dltB&&(dltA+dltC)%2==0&&(key=(dltA-dltC)/2)>=0&&(v=(dltA+dltC)/2)>=0)
						id=2;
					if (id<0){valid=0;break;}
					
//					printf("[qwq]%d %d %d %d\n",i,id,key,v);
					it=mp[id].find(key);
					if (it==mp[id].end()){
						vector<int> tmp;tmp.pb(v);
						mp[id].insert(make_pair(key,tmp));
					}
					else (it->second).pb(v);
				}
			}
//			printf("k=%d   is valid?%d\n",k,valid);
			if (!valid) continue;
			int res=1;
			for (int i=0;i<3;++i) res=1LL*res*calc(_d[i])%P;
			for (int i=0;i<3;++i)
				for (map0::iterator it=mp[i].begin();it!=mp[i].end();++it)
					res=1LL*res*calc(it->second)%P;
			inc(ans,res);
//			printf("Y:%d %d\n",k,res);
		}
	}
	void work1_solve(vector<int> &A,vector<int> &B,vector<int> &C,int ab,int cb){
//		printf("%d %d   before:%d\n",ab,cb,ans);
		Clear();
		bool valid=(ab>0&&cb>0);
		for (int i=0;valid&&i<n;++i){
			map0::iterator it;
			if (A[i]-ab==B[i]&&C[i]-cb==B[i]) _d[1].pb(B[i]);
			else if (C[i]==A[i]+ab+cb&&B[i]==A[i]+ab)_d[0].pb(A[i]);
			else if (A[i]==C[i]+cb+ab&&B[i]==C[i]+cb)_d[2].pb(C[i]);
			else{
				int dltA=A[i]-ab,dltC=C[i]-cb;
				int id=-1,key,v;
				if (dltC==B[i]&&(B[i]+dltA)%2==0&&(key=(B[i]-dltA)/2)>=0&&(v=(B[i]+dltA)/2)>=0)
					id=0;
				if (dltA==B[i]&&(B[i]+dltC)%2==0&&(key=(B[i]-dltC)/2)>=0&&(v=(B[i]+dltC)/2)>=0)
					id=1;
				if (id<0){valid=0;break;}
				
				it=mp[id].find(key);
				if (it==mp[id].end()){
					vector<int> tmp;tmp.pb(v);
					mp[id].insert(make_pair(key,tmp));
				}
				else (it->second).pb(v);
//				if (ab==1&&cb==3&&i==2) printf("%d\n",id);
			}
		}
		if (!valid) return;
		int res=1;
		for (int i=0;i<3;++i) res=1LL*res*calc(_d[i])%P;
		for (int i=0;i<2;++i)
			for (map0::iterator it=mp[i].begin();it!=mp[i].end();++it)
				res=1LL*res*calc(it->second)%P;
		inc(ans,res);
//		printf("%d %d res:%d\n",ab,cb,res);
//		printf("after:%d\n",ans);
	}
	void work1(vector<int> &A,vector<int> &B,vector<int> &C){
		int k=0;
		for (int i=1;i<n;++i) if (B[i]<B[k]) k=i;
		work1_solve(A,B,C,A[k]-B[k],C[k]-B[k]);
//		printf("[qaq]%d\n",ans);
		work1_solve(A,B,C,A[k]+B[k],C[k]-B[k]);
		work1_solve(C,B,A,C[k]+B[k],A[k]-B[k]);
//		printf("[qaq]%d\n",ans);
		work1_solve(A,B,C,B[k]-A[k],C[k]-B[k]);
		work1_solve(C,B,A,B[k]-C[k],A[k]-B[k]);
//		printf("[qaq]%d\n",ans);
	}
	
	public:
	int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC){
		n=distancesA.size();
		ans=0;
		work0(distancesA,distancesB,distancesC);
//		printf("%d\n",ans);
		work1(distancesA,distancesB,distancesC);
//		printf("%d\n",ans);
		work1(distancesB,distancesC,distancesA);
//		printf("%d\n",ans);
		work1(distancesC,distancesA,distancesB);
//		printf("%d\n",ans);
		return ans;
	}
};
