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
	char* bytes = (char*)util.base;
	char* subByte =(char*)element;
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
void dispose(ArrayUtil util){
	free(util.base);
	util.base=0;
	util.length=0;
	util.typeSize=0;
}

void* findFirst(ArrayUtil util, MatchFunc* match, void* hint){
	int i,sub_i;
	void * item = malloc(util.typeSize);
	for (i=0;i<util.length;i++){
		for(sub_i=0;sub_i<util.typeSize;sub_i++){
			((char*)item)[sub_i] = ((char*)util.base)[(i*util.typeSize)+sub_i];
		}
		if(match(hint,item)){
			return item;
		}
	}
	return 0;
}

void* findLast(ArrayUtil util, MatchFunc* match, void* hint){
	int i,sub_i;
	int lastIndex =-1;
	void * item = malloc(util.typeSize);
	for (i=(util.length-1);i>=0;i--){
		for(sub_i=(util.typeSize-1);sub_i>=0;sub_i--){
			((char*)item)[sub_i] = ((char*)util.base)[(i*util.typeSize)+sub_i];
		}
		if(match(hint,item)){
		 return item;
		}
	}
	return 0;
}
int count(ArrayUtil util, MatchFunc* match, void* hint){
	int i,sub_i;
	int c=0;
	void * item = malloc(util.typeSize);
	for (i=0;i<util.length;i++){
		for(sub_i=0;sub_i<util.typeSize;sub_i++){
			((char*)item)[sub_i] = ((char*)util.base)[(i*util.typeSize)+sub_i];
		}
		if(match(hint,item)){
			c++;
		}
	}
	return c;
}

int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems ){
	int i,sub_i;
	int counter=0;
	void * item = malloc(util.typeSize);
	for (i=0;i<util.length;i++){
		for(sub_i=0;sub_i<util.typeSize;sub_i++){
			((char*)item)[sub_i] = ((char*)util.base)[(i*util.typeSize)+sub_i];
		}
		if(match(hint,item)){
			for(sub_i=0;sub_i<util.typeSize;sub_i++){
				((char*)*destination)[sub_i+(counter*util.typeSize)] = ((char*)item)[sub_i];
			}
			counter++;
		}
		if(counter==maxItems){
			return counter;
		}
	
	}
	return counter;
}
