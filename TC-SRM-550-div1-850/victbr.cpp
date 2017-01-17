#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = 1e9+7;


int add(int x,int y){
	x += y;
	while (x >= mod) x -= mod;
	return x;
};
struct Matrix{
	int a[145][145];
};
struct Ans{
	int a[145];
};
Matrix operator * (const Matrix &a,const Matrix &b){
	Matrix c;
	memset(c.a,0,sizeof(c.a));
	for (int i = 0;i < 145;i++)
		for (int j = 0;j < 145;j++)
			for (int k = 0;k < 145;k++)
				c.a[i][j] = add(c.a[i][j],(ll)a.a[i][k]*b.a[k][j]%mod);
	return c;
};
Ans operator * (const Ans &a,const Matrix &b){
	Ans c;
	memset(c.a,0,sizeof(c.a));
	for (int i = 0;i < 145;i++)
		for (int j = 0;j < 145;j++)
			c.a[i] = add(c.a[i],(ll)a.a[j]*b.a[j][i]%mod);
	return c;
};



class ConversionMachine{
	public:
		ll val;//最少花费可能超过longlong 
		int n,m,step,s1,s2;
		Matrix A;
		Ans F;
		int countAll(string word1, string word2, vector <int> costs, int maxCost){
			n = word1.size();
			for (int i = 0;i < n;i++){
				if (word1[i] == 'a' && word2[i] == 'b') {val += costs[0];step++;s1++;}
				if (word1[i] == 'a' && word2[i] == 'c') {val += costs[0];val += costs[1];step+=2;s2++;}
				if (word1[i] == 'b' && word2[i] == 'a') {val += costs[1];val += costs[2];step+=2;s2++;}
				if (word1[i] == 'b' && word2[i] == 'c') {val += costs[1];step++;s1++;}
				if (word1[i] == 'c' && word2[i] == 'a') {val += costs[2];step++;s1++;}
				if (word1[i] == 'c' && word2[i] == 'b') {val += costs[2];val += costs[0];step+=2;s2++;}
			}
			for (int i = 0;i <= n;i++)
				for (int j = 0;i+j <= n;j++){
					if (i != 0) A.a[i*12+j][i*12-12+j] = i;
					if (j != 0) A.a[i*12+j][i*12+j-1+12] = j;
					if (i+j < n) A.a[i*12+j][i*12+j+1] = n-i-j;
				}
			A.a[0][144] = 1;
			A.a[144][144] = 1;
			
			if (val > maxCost) return 0;
			step += (maxCost-val)/(costs[0]+costs[1]+costs[2])*3;
			F.a[s1*12+s2] = 1;
			
			step++;//step次后a[144]中为前step-1次的和，故需再做一次。 
			while (step){
				if (step&1) F = F * A;
				A = A * A;
				step >>= 1;
			}
			
			return F.a[144];	
		}
};
