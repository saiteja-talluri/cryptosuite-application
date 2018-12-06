#include <iostream>
#include <cmath>
#include <cstdlib>
#include "bigint.h"
#include "modexp.cpp"
#include <map>
using namespace std;
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