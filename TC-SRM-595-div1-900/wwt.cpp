#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

struct node
{
	double x,y;

	node(void){}
	node(double a,double b) : x(a),y(b){}

	double len()
	{
		return x * x + y * y;
	}
}p[maxn];

node operator +(const node &a,const node &b) {return node(a.x + b.x,a.y + b.y);}
node operator -(const node &a,const node &b) {return node(a.x - b.x,a.y - b.y);}
double operator ^(const node &a,const node &b) {return a.x * b.y - a.y * b.x;}
double operator *(const node &a,const node &b) {return a.x * b.x + a.y * b.y;}

class Constellation
{
public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob)
	{
		int n = x.size();
		for(int i = 0;i < n;i ++) p[i] = node(x[i],y[i]);
		double ans = 0;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++) //考虑向量p_i -> p_j的贡献
				if (i != j)
				{
					double prb = prob[i] * 1.0 * prob[j] / 1000000.0;//首先这两个点要能被看见
					for(int k = 0;k < n;k ++)
						if (i != k && j != k)
						{
							double pb = prob[k] / 1000.0;
							node pk = p[k] - p[i],pj = p[j] - p[i];
							if ((pk ^ pj) > 0) prb *= 1 - pb; else//假如存在一个点k，使得他存在时p_i->p_j不可能在凸包上，那么这个点不能存在
							{
								if (((pk ^ pj) == 0) && (pk * pj < 0 || pk.len() > pj.len())) prb *= 1 - pb;
							}
						}
					ans += prb * (p[i] ^ p[j]); //p_i -> p_j会贡献的期望面积
				}
		return ans / 2.0;
	}
};
