#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

struct node
{
	int x,y,z;
	bool operator <(node a)const {return x<a.x||(x==a.x&&y<a.y);}
}a[55];

int n;
int area[55][55][55];

double calc(int x,int y,int z)
{
	double tmp=double(a[x].z)/1000*double(a[y].z)/1000*double(a[z].z)/1000;
	for (int i=0;i<x;i++) tmp*=double(1000-a[i].z)/1000;
	for (int i=x;i<n;i++)
		if (i!=x&&i!=y&&i!=z)
		{
			int t=area[y][z][x]*area[y][z][i];
			if (t<0||(t==0&&(a[z].x-a[i].x)*(a[y].x-a[i].x)<=0&&(a[z].y-a[i].y)*(a[y].y-a[i].y)<=0)) tmp*=double(1000-a[i].z)/1000;
		}
	return tmp;
}

struct Constellation 
{
    double expectation(vector <int> x, vector <int> y, vector <int> prob)
    {
    	n=x.size();
    	for (int i=0;i<n;i++) {a[i].x=x[i];a[i].y=y[i];a[i].z=prob[i];}
    	sort(a,a+n);
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			for (int k=0;k<n;k++)
    				area[i][j][k]=(a[j].x-a[i].x)*(a[k].y-a[i].y)-(a[j].y-a[i].y)*(a[k].x-a[i].x);
    	double ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=i+1;j<n;j++)
    			for (int k=i+1;k<n;k++)
    				if (area[i][j][k]>0) ans+=calc(i,j,k)*area[i][j][k]/2;
    	return ans;
    }
};
