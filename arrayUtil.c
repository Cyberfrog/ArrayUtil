#include "arrayUtil.h"
#include <stdlib.h>
int areEqual(ArrayUtil a, ArrayUtil b){
	int i;
	int maxLength = a.length<=b.length?(b.length*a.typeSize):(a.length*a.typeSize);
	for(i=0;i<maxLength;i++){
		if(((char*) a.base)[i]!=((char*)b.base)[i]){
			return 0;
		}
	}
	return 1;	
}

ArrayUtil create(int typeSize, int length){
	ArrayUtil au;
	au.base = calloc(length,typeSize);
	au.typeSize=typeSize;
	au.length =length;
	return au;
}
