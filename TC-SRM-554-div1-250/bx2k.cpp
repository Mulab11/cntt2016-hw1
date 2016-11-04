#include<bits/stdc++.h>

class TheBrickTowerEasyDivOne 
{
	public:
		int find(int rc, int rh, int bc, int bh) 
		{
			if(rc==bc)
			{
				if(rh==bh)return rc*2;//去除二式等于三式的情况
				else return rc*3;
			}
			else//a!=b的情况会多出一种
			{
				if(rh==bh)return std::min(rc,bc)*2+1;//去除二式等于三式的情况
				else return std::min(rc,bc)*3+1;
			}
		}
};