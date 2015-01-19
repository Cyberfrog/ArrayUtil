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
ArrayUtil resize(ArrayUtil util, int length){
	int i;
	int diff = (length-util.length)*util.typeSize;
	util.base = realloc(util.base, (length*util.typeSize));
	for(i=0;i<diff;i++){
		((char*)util.base)[i+(util.length*util.typeSize)]=0;
	}
	util.length = length;
	return util;
} 
int findIndex(ArrayUtil util, void* element){
	int i;
	int sub_i =0;
	int subByteLength =util.typeSize/(int)sizeof(char); 
	char * bytes = (char *)util.base;
	char * subByte =(char *)element;
	int byteLength =util.length*util.typeSize;
	for (i=0;i<(byteLength);i++){
		if(sub_i>0&&bytes[i]!=subByte[sub_i]){
			sub_i =0;
		}
		if(bytes[i]==subByte[sub_i]){
			sub_i++;
			if(sub_i==subByteLength){
				return (i/util.typeSize);
			}
		}
		
	}
	return -1;
}

