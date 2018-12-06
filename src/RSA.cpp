#include <iostream>
#include "bigint.h"
#include "dislog.cpp"
#include <utility>
using namespace std;

bigint encryption(bigint m,bigint e,bigint n)
{
	return exp(m,e,n);
}


bigint decryption(bigint c,bigint e,bigint p,bigint q)
{
	bigint d=inverse(e,(p-1)*(q-1));
	return exp(c,e,p*q);
}

