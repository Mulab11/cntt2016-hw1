// BEGIN CUT HERE

// END CUT HERE
#line 5 "ConvexPolygonGame.cpp"
#include <bits/stdc++.h>
#define ll long long
#define eps (1e-7)

using namespace std;


class ConvexPolygonGame{
	inline double calc(int x0,int y0,int x1,int y1,int x){
		return 1.0*(y1-y0)*(x-x0)/(x1-x0)+y0;
	}
	int n;
	bool check(vector <int> x, vector <int> y){
		int cnt=0,L=x[0],R=x[0];
		for (int i=1;i<n;++i)
			L=min(L,x[i]),R=max(R,x[i]);
		bool flag=0;
		int x0=0,y0=0,x1=0,y1=0;
		for (int i=L;i<=R;++i){
			int u=-1,v=-1;
			for (int j=0;j<n;++j)
				if ((x[j]<=i&&x[j+1]>=i)||(x[j+1]<=i&&x[j]>=i)){
					v=u;u=j;
					if (x[j]==x[j+1]){v=n;break;}
					if (j<n-1&&x[j+1]!=x[j+2]&&x[j+1]==i) ++j;
				}
			double l,r;
			if (v==-1) continue;
			if (v<n)
				l=calc(x[u],y[u],x[u+1],y[u+1],i),
				r=calc(x[v],y[v],x[v+1],y[v+1],i);
			else
				l=y[u],r=y[u+1],v=u;
			if (l>r) swap(l,r),swap(u,v);
			if (x[u]==i||x[u+1]==i) ++l;
			if (x[v]==i||x[v+1]==i) --r;
			u=ceil(l-eps);v=floor(r+eps);
//			printf("x:%d   %.3f %.3f\n",i,l,r);
			if (u<v){
				flag=1;
				if ((cnt+=2)>2) return 1;
			}
			if (u==v){
				if (flag) return 1;
				if (cnt==0) x0=i,y0=u,++cnt;
				else if (cnt==1) x1=i,y1=u,++cnt;
				else if (((ll)i-x0)*(u-y1)!=((ll)i-x1)*(u-y0)) return 1;
			}
		}
		return 0;
	}
	public:
	string winner(vector <int> X, vector <int> Y){
		n=X.size();
		X.push_back(X[0]);
		Y.push_back(Y[0]);
		return check(X,Y)?"Masha":"Petya";
	}
};

//this is for test
/*
int main(){
	ConvexPolygonGame test;
	vector<int> a,b;
	a.push_back(0);
	a.push_back(10);
	a.push_back(10);
	a.push_back(0);

	b.push_back(0);
	b.push_back(0);
	b.push_back(10);
	b.push_back(10);
	cout<<test.winner(a,b)<<endl;
//	test.run_test(-1);
	return 0;
}
*/
//test end
