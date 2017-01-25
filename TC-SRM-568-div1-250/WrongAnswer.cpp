#include <vector>
using namespace std;
class BallsSeparating{
public:
	void cmin(int&a,int b){b<a?a=b:1;}
	int minOperations(vector <int> red, vector <int> green, vector <int> blue){
		if(red.size()<3)return -1;
		int f[2][8];
		for(int i=0;i<8;i++)f[0][i]=i?1<<30:0,f[1][i]=1<<30;
		for(int i=0;i<red.size();i++){
			int a[3]={green[i]+blue[i],blue[i]+red[i],red[i]+green[i]};
			for(int j=0;j<8;j++)for(int k=0;k<3;k++)cmin(f[1][j|1<<k],f[0][j]+a[k]);
			for(int j=0;j<8;j++)f[0][j]=f[1][j],f[1][j]=1<<30;
		}
		return f[0][7];
	}
};
