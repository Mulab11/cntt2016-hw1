#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;
const int maxl=5005;
vector<PII>edge[maxl/2];
int sqr(int x){return x*x;}

/*
奇数无解
偶数判一下矩形，然后判一下三角形
三角形的话大不了打表就好了
*/

class FindPolygons{
public:
	double minimumPolygon(int L){
		if (L&1) return -1;
		rep(i,0,L/2) rep(j,i,L/2){
			int xb=int(sqrt(i*i+j*j));
			if (xb>=L/2) break;
			if (sqr(xb)==i*i+j*j) edge[j].pb(mk(i,xb));
		}
		int ret=-1;
		rep(i,1,L/2) rep(j,i,L/2){
			rep(k,0,edge[i].size()-1) rep(l,0,edge[j].size()-1){
				int xb1=edge[i][k].sc,xb2=edge[j][l].sc,v,sq;
				if (i*edge[j][l].fs!=j*edge[i][k].fs){
					v=sqr(abs(i-j))+sqr(abs(edge[i][k].fs-edge[j][l].fs));
					sq=floor(sqrt(v));
					if (sqr(sq)==v&&sq+xb1+xb2==L){
						if (ret==-1||max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2))<ret){
							ret=max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2));
						}
					}
					v=sqr(abs(i+j))+sqr(abs(edge[i][k].fs+edge[j][l].fs));
					sq=floor(sqrt(v));
					if (sqr(sq)==v&&sq+xb1+xb2==L){
						if (ret==-1||max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2))<ret){
							ret=max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2));
						}
					}
				}
				if ((i||j)&&(edge[i][k].fs||edge[j][k].fs)){
					v=sqr(abs(i-j))+sqr(abs(edge[i][k].fs+edge[j][l].fs));
					sq=floor(sqrt(v));
					if (sqr(sq)==v&&sq+xb1+xb2==L){
						if (ret==-1||max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2))<ret){
							ret=max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2));
						}
					}
					v=sqr(abs(i+j))+sqr(abs(edge[i][k].fs-edge[j][l].fs));
					sq=floor(sqrt(v));
					if (sqr(sq)==v&&sq+xb1+xb2==L){
						if (ret==-1||max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2))<ret){
							ret=max(sq,max(xb1,xb2))-min(sq,min(xb1,xb2));
						}
					}
				}
			}
		}
		if (ret!=-1) return ret;
		if (L<=2) return -1;
		return (L/2)%2;
	}
};
