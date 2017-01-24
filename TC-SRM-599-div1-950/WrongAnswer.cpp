#include <vector>
#include <string>
#include <algorithm>
#define MOD 1000000007
using namespace std;
class SimilarNames{
public:
	int n,m,k,ex[8],ey[8],V[16],G[16],popc[1<<16];
	vector<int> ch[51],split[1<<16];
	int f[51][1<<16],g[51][1<<16];
	int calc_sum(int i,int j,int S,int k,int T){
		if(k==split[S].size())return 1ll*dfs_g(i,j-1,T)*dfs_f(ch[i][j-1],S-T)%MOD;
		return(calc_sum(i,j,S,k+1,T)+calc_sum(i,j,S,k+1,T|split[S][k]))%MOD;
	}
	int dfs_g(int i,int j,int S){ // 将点集S加入i的前j个子树（除i外）的方案数
		if(!j)return!S;
		int&s=g[ch[i][j-1]][S];
		if(s)return s-1;
		s=j==1?dfs_f(ch[i][0],S):calc_sum(i,j,S,0,0);
		return s++;
	}
	int dfs_f(int i,int S){ // 将点集S加入i子树的方案数
		int&s=f[i][S];
		if(s)return s-1;
		s=dfs_g(i,ch[i].size(),S);
		for(int j=0;j<m;j++)if((S>>j&1)&&!(G[j]&S))s=(s+dfs_g(i,ch[i].size(),S-(1<<j)))%MOD;
		return s++;
	}
	bool vis[1<<16];
	int fa[16];
	int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
	void init(int S){ // 预处理连通块划分split[S]
		vis[S]=1;
		for(int i=0;i<m;i++)if(S>>i&1)fa[i]=i;
		for(int i=0;i<k;i++)if((S>>ex[i]&1)&&(S>>ey[i]&1))fa[find(ex[i])]=find(ey[i]);
		int RS[m]; // R为连通块根集合
		for(int i=0;i<m;i++)if(S>>i&1)RS[i]=0;
		for(int i=0;i<m;i++)if(S>>i&1)RS[find(i)]|=1<<i;
		for(int i=0;i<m;i++)if((S>>i&1)&&find(i)==i)split[S].push_back(RS[i]);
		for(int i=0;i<m;i++)if((S>>i&1)&&!(G[i]&S)&&!vis[S-(1<<i)])init(S-(1<<i));
	}
	int count(vector <string> names, vector <int> info1, vector <int> info2){
		n=names.size();m=0;k=info1.size();
		// 离散化图中的点集
		for(int i=0;i<k;i++)V[m++]=info1[i],V[m++]=info2[i];
		sort(V,V+m);m=unique(V,V+m)-V;
		for(int i=0;i<m;i++)G[i]=0;
		for(int i=0;i<k;i++)G[ey[i]=lower_bound(V,V+m,info2[i])-V]|=1<<(ex[i]=lower_bound(V,V+m,info1[i])-V);
		// 字符串前缀关系构树
		for(int i=0;i<n;i++){
			int f=n;
			for(int j=0;j<n;j++)if(j!=i&&names[j].length()<names[i].length()&&(f==n||names[j].length()>names[f].length())){
				bool s=1;for(int k=0;k<names[j].length()&&s;k++)if(names[j][k]!=names[i][k])s=0;
				if(s)f=j;
			}
			ch[f].push_back(i);
		}
		// DP
		for(int S=0;S<(1<<m);S++)popc[S]=S?popc[S&(S-1)]+1:0;
		init((1<<m)-1);
		int ans=dfs_g(n,ch[n].size(),(1<<m)-1);
		for(int i=n-m;i;i--)ans=1ll*ans*i%MOD;
		return ans;
	}
};
		for(int i=n-m;i;i--)ans=1ll*ans*i%MOD;
		return ans;
	}
};
p627x5o1A8y5j3i310i010A010V4Z0K054S4S9F263651080X7R7r9G210S010LBP129j0A0x8S5l4I710:6B1I2a60810Y1V472e5K110O310P2m100h9k010F810S5j3C1L6O1O311S2s51000h0y110o1p4f3V24710l0l000m92910y310w1U386D2I21027q1P2o;41r800h4r8s2U010Z021237393f;R2fAi110s1x100a5S232A5Z3D434W;R6T2r8B0n0o210J310i1u1t610n5f;l9r2V210Q310l31000f3k010d5lAo010w110X2440010:3s3J6e0Y201P3s8G5S12910a11000H1G5p0W010a2i:O26152d5a1i2b255a2;5q2T553c8m1n48:10B8c;q0T710H300DAh3F3s757x01086d32422t610A2L00:iAC010o0r0g2n0E40;a410F8sAE2z94277Y:C864B:P2Y;O2Q21CF7d510s0PB00x2Y0734362t110O3T127W5Y1s9y15900;3e0732110m2t066108210p1F4n210S7U000100010D0h9D32340n12610p2:2u010C11000:072:5b010R32D:3J4W1DA00d79FDAD010s2KBi6v0a2U;27j2f210a010t0x10010u2103;C2tA10t353v2O0B510w08:00p7z0f48668k110x91031x700X6G;38W2D1B0V0N;10g6x0M7sDz2REu21000G2::cGb0R58:t0r1h3281013t600042410y0L5W110K010r8H6D210c0w7K410W210S110E0KDi810A7D1l9z053c7C810:4M5m210t178m3V0DDj8G8f4738200H1Q110y5M5011003s1EAD72910c110u385e210O8v2i2l0UA10w01027:Ev111T710S5z4E:h7W2v422U30910e0F9B3u700D6Y7m200Z502o;21l5A3I3N;v7Z21000S2a7m:o310D2N2F010M110F;cEF3H5e331Y:9100M5i0j0O0;4y310m810H3SCi155w310P1n5I310q11041z0A9J9J3T500109510j2x9K3qBN;t2g0s09Bx8L310Y210005100MBG082m7eCn610V0D782B77;N;Q410i9a2F3n5A010s0B9W0M3P31000p0VFpD:91082;FUAH9G0;BmBK0R3s286x2mBI80071S3102810c3Z82110T3e2M310;710e7J9M2p3i010mB10r2cDV010a4C83250G2W9W3R3CB10g395mB33X3s3j4rCy3iA0010x291O3i209;5K710Z352k6b5831000aFW2h:u7cCDAv5I610k2B0:1109I37S336c3K3N;t1E310H051d3e5i910Y7m2N210k0108:;1S110Q410f39300F5M7A2K2Z2c210S19Cu5W:G;J9M1QBG3m7A110u9UDM33:0810y4i3bFq2j310q2f600R564T4Z2I4;010T4B115P8l3u4R910s21000:5i0RDI2gCy510N;I581D9c:p;mK10m010o3n18Db8I256e5DHI00875SGmB2;00R;q3T6Y5l5X410F2D1r3HGC610N2X200u1s39Gv710N7r2eCM:t31000y24C10K410E1F3w310Q:wCz4R:U3d4221000j6q7J5J0108:VE;:jBC5Z1M3;10010o010p28Jy3X1l385VJC02910:1PG00d:S:tB02f6o0CJG196G310q8P814R3J0DQA9C1001024f11DM6G41032x634aIO2H1P8x200R0W110F8105Bi10E10Q210f2b3G;t3G5;563U98D10I1FAmBcE74rFq0N3Y7a4k410q210x175g0N4X:zC94:30010W5J100aCu1106;10q535C506O31000993D10A310A4d3p:V7A9F6K1B;B410C;10K010Y9s7Z210w3C3zD1060l7E3n6s2H740n900L1v210601025W71FU0s06100F1WEb1k210G4q51FZGi5D2aI:EM1x26710UAM00010Q3;0I3f49;10t3FGJ46H00UG:410V9z3K4N1I3T4C810k43EL4v400v;2810m310;2C6N;1092W61DK3N4h9O110Y:mGL0h5O4BA9Bl;;657u0XLP4aD4610I110GE6BQ410a2P1p:83k6v;84105B104C10C310c3:1MEt6w;10H7u3W310y;F1318900i3M0IO0GNJ2910:110g00;:8z9w8LIdAcKW408j2p9A:R1G;Z8E0h;34S3t510:AD9Y4n4VJ10w010mBV6Z4N6q2104GL1S110M0R7R6C9L5109693G3OM00T3IAO8O2JAL3N9i1100EW31FT1831029C2C410I;10g2778Dc7o610rKjLf410:210006;Y510U1x00GF6WEM1l9p:h4y2w110O2X2z9a3o210y08:2209w41054V10010tO8;O1d531eL1Fs37310N3K;l41025FI1;LA0010W1b5N033b5VCS4vKn4V10010w7t600rJs3n;L510G7WES4p5031000u04C10g335p0PNF:LAt1d4r6:7r4uAO9iFnAi5k5XK01u:1Di2:1";
	int read(char c){return c<60?c-48:c<91?c-53:c-59;}
	double minimumPolygon(int L){
		if(L<4||L%2)return-1;
		return read(s[L-3])<<6|read(s[L-4]);
	}
};

	}
};
