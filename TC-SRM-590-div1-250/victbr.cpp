#include <bits/stdc++.h>
using namespace std;

class FoxAndChess{
	public:
		string ableToMove(string begin, string target){
			int n = begin.size(),i = 0,j = 0;
			bool flag = 1;
			while (i < n && j < n){
				if (begin[i] == '.') i++;
				else if (target[j] == '.') j++;
				else{
					if (begin[i] != target[j]) {flag = 0;break;}//棋子不对应 
					if (begin[i] == 'L' && i < j) {flag = 0;break;}
					if (begin[i] == 'R' && i > j) {flag = 0;break;}
					i++;j++;
				}
			}
			while (i < n && begin[i] == '.') i++;
			while (j < n && target[j] == '.') j++;
			
			if (i != j) flag = 0;//i!=j说明其中一个串跑完了另一个串还没跑完，所以两个串棋子个数不等。
			
			if (flag) return "Possible";
			else return "Impossible"; 
		}
};
