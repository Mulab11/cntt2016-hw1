#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double eps=1e-12;
const double eps2=1e-12;

struct point{
	long double x,y;
	point(long double a=0,long double b=0):x(a),y(b){};
	point operator + (const point &a)const{return point (x+a.x,y+a.y);}
	point operator - (const point &a)const{return point (x-a.x,y-a.y);}
	long double operator * (const point &a)const{return x*a.x+y*a.y;}
	long double operator ^ (const point &a)const{return x*a.y-y*a.x;}
	friend long double dist(const point &a){
		return sqrt(a.x*a.x+a.y*a.y);
	}
};

struct nod{
	point cent;
	long double r,mn,mx;
};

class CandyOnDisk{
	private:
		static const int maxn=55;
		bool vis[maxn];
		nod rec[maxn];
		long double ned[maxn];
		point S,T;
		int n;
		queue<int> q;
		bool check(int a,int b){
			long double mn=-1000,mx=-1000;
			long double d=dist(rec[a].cent-rec[b].cent);
			if (d>rec[a].mx+rec[b].r+eps) return false;
			if (d+rec[b].r<rec[a].mn-eps) return false;
			if (d>=rec[a].mx){
				mx=min(rec[b].r,d+rec[a].mx);
				mn=d-rec[a].mx;
				if (mn>rec[b].mn-eps&&mx<rec[b].mx+eps) return false;
				if (rec[b].mn>mn+eps2) rec[b].mn=mn;
				if (rec[b].mx<mx-eps2) rec[b].mx=mx;
				return true;
			}
			else if (d>=rec[a].mn){
				bool ret=false;
				if (rec[a].mn-eps<0){
					/*
					b->mx+d;
					a->mx+2d;
					a->mx+3d;
					*/
					int k=min((int)(rec[a].r-rec[a].mx)/d,(int)(rec[b].r-rec[a].mx)/d);
					if (k>0){
						if (k&1){
							mx=rec[a].mx+k*d;
							if (rec[b].mx<mx||rec[b].mn>eps){
								rec[b].mx=max(rec[b].mx,mx);
								rec[b].mn=0;
								ret=true;
							}
						}
						else{
							mx=rec[a].mx+k*d;
							if (rec[a].mx<mx){
								rec[a].mx=mx;
								if (!vis[a]){
									vis[a]=true;
									q.push(a);
								}
							}
						}
					}
				}
				mx=min(rec[b].r,d+rec[a].mx);
				mn=0;
				if (mn>rec[b].mn-eps&&mx<rec[b].mx+eps) return ret;
				if (rec[b].mn>mn+eps2) rec[b].mn=mn;
				if (rec[b].mx<mx-eps2) rec[b].mx=mx;
				return true;
			}
			else{
				bool ret=false;
				if (rec[a].mn-d<rec[b].r){
					/*
					b->mn-d;
					a->mn-2d;
					a->mn-3d;
					*/
					int k=(int)rec[a].mn/d;
					if (k>0){
						if (k&1){
							mn=rec[a].mn-k*d;
							if (rec[b].mn>mn){
								rec[b].mn=mn;
								ret=true;
							}
						}
						else{
							mn=rec[a].mn-k*d;
							if (rec[a].mn>mn){
								rec[a].mn=mn;
								if (!vis[a]){
									vis[a]=true;
									q.push(a);
								}
							}
						}
					}
				}
				mn=rec[a].mn-d;
				mx=min(rec[b].r,rec[a].mx+d);
				if (mn>rec[b].mn-eps&&mx<rec[b].mx+eps) return ret;
				if (rec[b].mn>mn+eps2) rec[b].mn=mn;
				if (rec[b].mx<mx-eps2) rec[b].mx=mx;
				return true;
			}
		}
	public:
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
		n=x.size();
		for (int i=0;i<n;++i){
			rec[i].cent=point(x[i],y[i]);
			rec[i].r=r[i];
			rec[i].mn=rec[i].mx=-1000;
		}
		S=point (sx,sy);
		T=point (tx,ty);
//		printf("T=(%Lf , %Lf)\n",T.x,T.y);
		for (int i=0;i<n;++i){
			long double d=dist(T-rec[i].cent);
			if (d<=rec[i].r+eps) ned[i]=d;
			else ned[i]=-10000000;
		}
		if (dist(S-T)<eps2) return "YES";
		for (int i=0;i<n;++i){
			long double d=dist(S-rec[i].cent);
			if (d<=rec[i].r+eps){
				rec[i].mn=rec[i].mx=d;
				q.push(i);
				vis[i]=true;
			}
		}
		while(!q.empty()){
			int u=q.front();
//			printf("%d: [ %.10Lf , %.10Lf ] need %.10Lf\n",u,rec[u].mn,rec[u].mx,ned[u]);
			if (ned[u]>=rec[u].mn-eps&&ned[u]<=rec[u].mx+eps) return "YES";
			q.pop();
			vis[u]=false;
			for (int i=0;i<n;++i) if (i!=u) if (check(u,i)){
				if (ned[i]>=rec[i].mn-eps&&ned[i]<=rec[i].mx+eps) return "YES";
				if (!vis[i]){
					vis[i]=true;
					q.push(i);
				}
			}
//			system("pause");
		}
		return "NO";
	}
};
