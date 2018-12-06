#include "bigint.h"
#include "gcd&inverse.cpp"
#include <sstream>
#include <map>
using namespace std;
typedef pair<bigint,bigint> pa;

bigint min(bigint a,bigint b){
	if(a<b)return a;
	else return b;
}

bigint mult(bigint a,bigint b,bigint c){
	bigint temp=(a*b)%c;
	return temp;
}

bigint inverse(bigint a,bigint b){
	if(gcd(a,b)!=1)return -1;
	pa c=pair1(a%b,b);
	bigint t = c.first;
	if(t<0)return t+b;
	else return t;
}

bigint exp(bigint a,bigint k,bigint c){
	if(k==0)return 1;
	if(k==1)return a%c;
	else if(k%2==0){
		bigint temp=exp(a,k/2,c);
		return (temp*temp)%c;
	}
	else{
		bigint temp=exp(a,(k-1)/2,c);
		return ((((a%c)*temp)%c)*temp)%c;
	}
}

bigint dlog(bigint a,bigint b,bigint c){
	bigint i=1,k=0;
	while(true){
		if(i*i>=c){
			k=i;
			break;
		}
		i=i+1;
	}
	map<bigint,bigint>m;
	map<bigint,bigint>::iterator it;
	for(bigint i=1;i<=k;i=i+1){
		m[exp(a,i,c)]=i;
	}
	bigint r=0;
	bigint ai=inverse(a,c);
	bigint ans=c;
	while(r*k<=c){
		bigint t=mult(b,exp(ai,r*k,c),c);
		it=m.find(t);
		if(it!=m.end()){
			bigint s=it->second;
			ans=s+r*k;
			break;
		}
		r=r+1;
	}
	if(ans==c){return -1;}
	return ans;
}