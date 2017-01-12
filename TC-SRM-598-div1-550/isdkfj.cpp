#include <bits/stdc++.h>

using namespace std;


class FoxAndFencing {
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
		if(d-mov1<=rng1)return "Ciel";//一步能干掉 
		if(d+mov1-mov2<=rng2)return "Liss";//退一步也会死 
		if(mov1>mov2){
			if(mov2+rng2+1+mov2-mov1<=rng1)return "Ciel";//走到最近的不被干掉的地方 
			return "Draw";
		}else if(mov1<mov2){
			if(mov1+rng1+1+mov1-mov2<=rng2)return "Liss";//走到最近的不被干掉的地方 
			return "Draw";
		}else return "Draw";//谁都打不死谁 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
