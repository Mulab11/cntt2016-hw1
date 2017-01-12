#include <bits/stdc++.h>

using namespace std;

double f[70005],g[70005],s[70005];

class TriangleXor {
public:
	int theArea(int W) {
		double w=W,ret=0;
		for(int a=W;a>=0;--a){//枚举x轴上的长度 
			f[a]=(w-a+1)*w/(a+w)*0.5*w;//算总面积 
			g[a]=f[a]-f[a+1]-s[a+1];//算当前这层的面积 
			s[a]=s[a+1]+g[a];//之前的面积并 
			if(!(a&1))ret+=g[a];//奇数次 
		}
		return int(ret);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
