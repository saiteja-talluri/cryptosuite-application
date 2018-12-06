#include "bigint.h"
#include <sstream>
#include <map>
using namespace std;
typedef pair<bigint,bigint> pa;

bigint gcd(bigint a,bigint b){
	if(a%b==0)return b;
	else if(b%a==0)return a;
	else{
		return gcd(b,a%b);
	}
}

pa pair1(bigint a,bigint b){
	if(a%b==1)return pa(1,-(a/b));
	pa c=pair1(b,a%b);
	return pa(c.second,c.first-(a/b)*c.second);
}

bigint inverse(bigint a,bigint b){
	if(gcd(a,b)!=1)return -1;
	pa c=pair1(a%b,b);
	bigint t = c.first;
	if(t<0)return t+b;
	else return t;
}