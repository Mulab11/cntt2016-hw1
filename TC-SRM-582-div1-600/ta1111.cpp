#include <bits/stdc++.h>
using namespace std;

class ColorfulBuilding {
	public:
		int count(vector <string> color1, vector <string> color2, int L);
};

typedef long long LL;
const int N = 1296 + 10;
const int MO = 1e9 + 9;

int  n, tot, 
	 jc[N], f[N][N], val[N][N], col[N], sum[N], inv[N];
map < int, int > T;

void Add( int &x, int y ) {
	x += y;
	if( x >= MO ) x -= MO;
}

int MI(LL a, LL b,LL c)
 {  
  LL ret = 1;  
  while(b > 0) {  
    if(b & 1) ret = ret * a % c;  
    b >>= 1; a = a * a % c;  
  }  
  return (int) ret;  
}  


int ColorfulBuilding :: count(vector <string> color1, vector <string> color2, int L)
{
	string s1="",s2="";
	int l1 = color1.size(), l2 = color2.size();
	for( int i = 0; i < l1; ++i ) s1 += color1[i];
	for( int i = 0; i < l2; ++i ) s2 += color2[i];
	n = s1.length();
	
	for( int i = 0; i < n; ++i ) { // Hash 一下， 把两种颜色变成一种 
		int t = s1[i] * 256 + s2[i];
		if( T[t] == 0 ) T[t] = ++tot;
		col[i+1] = T[t];
	}
	
	jc[0] = 1; inv[0] = 1; 
	for( int i = 1; i <= n; ++i ) jc[i] = 1ll*jc[i-1]*i % MO, inv[i] = 1ll * inv[i-1] * MI( i, MO-2, MO ) % MO; //预处理阶乘和逆元 


	for( int i = 1; i <= n; ++i ) 
		for( int j = 1; j <= i && j <= L; ++j )
		{
			int tmp;
			if( j == 1 ) { // 特殊处理 f[i][1] 等于放在第一个位置时的方案 + 与前面相同颜色位置构成一段不产生颜色变换区域的方案 
				tmp = 1ll * jc[n-1] * inv[n-i] % MO;
				Add( tmp, 1ll * val[col[i]][j] * inv[n-i]%MO );
			}
			else {
				tmp = sum[j-1] - val[col[i]][j-1];  // 在之前 j-1 个颜色中把 i 放最后构成 j 个颜色 再减掉同色的情况 
				if( tmp < 0 ) tmp += MO;
				Add( tmp, val[col[i]][j] );  // 之前已经构成了的j种颜色的情况，且最后与此时同色 
				tmp = ( 1ll * tmp * inv[n-i] ) % MO;
			}
			f[i][j] = tmp;
			if( i < n ) {
				tmp = 1ll * f[i][j] * jc[n-i-1] %MO; // 更新和 
				Add( sum[j], tmp );
				Add( val[col[i]][j], tmp );
			}
		}
	return f[n][L];
}