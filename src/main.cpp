#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <utility>
#include "bigint.h"

using namespace std;

typedef pair<bigint,bigint> pa;

/* Modular Addition */
bigint add(bigint a,bigint b,bigint c){
	bigint temp=(a+b)%c;
	return temp;
}

/* Modular Multiplication */
bigint mult(bigint a,bigint b,bigint c){
	bigint temp=(a*b)%c;
	return temp;
}

/* Min */
bigint min(bigint a,bigint b){
	if(a<b)return a;
	else return b;
}

/* Modular Exponentiation */
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

/* GCD */
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

/* Modular Inverse */
bigint inverse(bigint a,bigint b){
	if(gcd(a,b)!=1)return -1;
	pa c=pair1(a%b,b);
	bigint t = c.first;
	if(t<0)return t+b;
	else return t;
}

/* Discrete Logarithm */
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

bool rabinMiller(bigint n){
     bigint s = n-1;
     bigint t = 0;
     while (s%2 == 0)
     {
         s = s/2;
         t=t+1;
     }
     int k=0;
     while (k<128){
         bigint v = exp((bigint)rand()%(n-2)+2,s,n) ;
         if (v!=1)
         {
             bigint i=0;
             while (v != (n-1))
             {
                 if (i == t-1)
                     return false;
                 else
                 {
                     i = i+1;
                     v = (v*v)%n;
              	 }
             } 
     	 }
     	 k+=2;
     	}
     return true;
}

/* RSA Encryption */
bigint encryption(bigint m,bigint e,bigint n)
{
	return exp(m,e,n);
}

/* RSA Decryption */
bigint decryption(bigint c,bigint e,bigint p,bigint q)
{
	bigint d=inverse(e,(p-1)*(q-1));
	return exp(c,e,p*q);
}

/* Prime fields */
struct primefield{
    bigint x,y;
    primefield add(bigint p,bigint a,bigint b)
    {
        bigint m;primefield C;
        m=((b-y)*inverse((a-x).abs(),p))%p;
        if (a-x<0)m=-m;
        C.x=(((m%p)*(m%p)-x%p-a%p)%p+p)%p;
        C.y=((-y%p+(m%p)*(x%p-C.x%p))%p+p)%p;
        return C;
    }
};

struct primefield1{
    bigint x,y;
    bigint a,b; //a,b in X^3+aX+b
    primefield1 doubling(bigint p)
    {
        bigint m;primefield1 C;
        m=((bigint(3)*x%p*x%p+a%p)*inverse(bigint(2)*y.abs()%p,p));
        if (y<0)m=-m;
        C.x=(((m%p)*(m%p)-x%p-x%p)%p+p)%p;
        C.y=((-y%p+(m%p)*(x%p-C.x%p))%p+p)%p;
        return C;
    }
};

int main(){
	int n;
	while(true){
		cout<< "Choose one of them and type the serial no. and press Enter" <<endl;
		cout<<"0.To exit" << endl
			<<"1.Modulo Addition"<<endl
			<<"2.Modulo Multiplication"<<endl
			<<"3.Modulo Exponentiation"<<endl
			<<"4.GCD"<<endl
			<<"5.Inverse Modulo"<<endl
			<<"6.Discrete Logarithm"<<endl
			<<"7.ECS over prime field to find A+B over Fp"<<endl
			<<"8.ECS over prime field to find 2*A over Fp"<<endl
			<<"9.RSA Encryption"<<endl
			<<"10.RSA Decryption"<<endl;
		cout << endl;
		cin>>n;
		if(n==0) break;
		if(n==1){bigint a,b,c;
			cout<<"Enter a,b,c in given sequence to get a+b mod c"<<endl;
			cin>>a>>b>>c;
			cout<<add(a,b,c)<<endl;
		}
		if(n==2){bigint a,b,c;
		cout<<"Enter a,b,c in given sequence to get a*b mod c"<<endl;
			cin>>a>>b>>c;
			cout<<mult(a,b,c)<<endl;
		}

		if(n==3){long long int a,b,c;
		cout<<"Enter a,b,c in given sequence to get a^b mod c"<<endl;
			cin>>a>>b>>c;
			cout<<exp(a,b,c)<<endl;
		}
		if(n==4){bigint a,b;
		cout<<"Enter a,b in given sequence to get gcd(a,b)"<<endl;
			cin>>a>>b;
			cout<<gcd(a,b)<<endl;
		}
		if(n==5){bigint a,b;
		cout<<"enter a,b in given sequence to get a inverse mod b"<<endl;
			cin>>a>>b;
			cout<<inverse(a,b)<<endl;
		}
		if(n==6){bigint a,b,c;
		cout<<"Enter a,b,c in given sequence to get x in a^x=b(modc)"<<endl;
			cin>>a>>b>>c;
			cout<<dlog(a,b,c)<<endl;
		}
		if(n==7){
			cout<<"Enter prime p, A.x, A.y, B.x, B.y to calculate A+B "<<endl;
			primefield A,B;
			bigint p;//prime
			cin>>p>>A.x>>A.y>>B.x>>B.y;
			cout<<"("<<(A.add(p,B.x,B.y)).x<<", "<<(A.add(p,B.x,B.y)).y<<")"<<endl;
		}
		if(n==8){
			cout<<"Enter  prime p, A.x, A.y, a where a = coefficient of x in X^3+aX+b to calculate 2A "<<endl;
			primefield1 A;
			bigint p; //prime
			cin>>p>>A.x>>A.y>>A.a; //if A.x,A.y,a are known then b can be calculated 
			cout<<"("<<A.doubling(p).x<<" ,"<<A.doubling(p).y<<")"<<endl;
		}
		if(n==9){
			bigint a,b,c;
			cout<<"Enter m,e,n in given sequence to get RSA encrypted message"<<endl;
			cin>>a>>b>>c;
			cout<<encryption(a,b,c)<<endl;	
		}
		if(n==10){
			bigint a,b,c,d;
			cout<<"Enter c,e,p,q in given sequence to get RSA decrypted message"<<endl;
			cin>>a>>b>>c>>d;
			cout<<decryption(a,b,c,d)<<endl;
		}
		cout << endl;
	}
	cout << "Thanks for using our application\n";
	return 0;
}