#include "arrayUtil.h"
#include <stdlib.h>
#include <string.h>
int areEqual(ArrayUtil a, ArrayUtil b){
	int i;
	int byteLength = a.length*a.typeSize;
	byte_ptr a_bytes = a.base, b_bytes = b.base;
	if(a.length != b.length||a.typeSize != b.typeSize){
		return 0;
	}
	for(i = 0;i < byteLength;i++){
		if(a_bytes[i] != b_bytes[i]){
			return 0;
		}
	}
	return 1;	
}

ArrayUtil create(int typeSize, int length){
	return	(ArrayUtil){calloc(length,typeSize),typeSize,length}; 
}

ArrayUtil resize(ArrayUtil util, int length){
	int i,index;
	byte_ptr base;
	int newLength = length*util.typeSize;
	int byteLength =util.length*util.typeSize;	
	int diff = (length-util.length)*util.typeSize;

	util.base = realloc(util.base,newLength);
	util.length = length;
	base = (byte_ptr)util.base;

	for(i = 0;i < diff;i++){
		index = i+byteLength;
		base[index] = 0;
	}
	return util;
} 

int findIndex(ArrayUtil util, void* element){
	int i;
	int sub_i = 0;
	int subByteLength = util.typeSize; 
	int byteLength = util.length*util.typeSize;
	byte_ptr bytes = (byte_ptr)util.base;
	byte_ptr subByte = (byte_ptr)element;

	for (i = 0;i < (byteLength);i++){
	
		if(sub_i > 0 && bytes[i] != subByte[sub_i]){
			sub_i = 0;
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
}

void* findFirst(ArrayUtil util, MatchFunc* match, void* hint){
	int i;
	void * item = malloc(util.typeSize);
	for (i=0;i<util.length;i++){
		
		memcpy(item,&(util.base[i*util.typeSize]),util.typeSize);
		
		if(match(hint,item)){
			return item;
		}
	}
	return 0;
}

void* findLast(ArrayUtil util, MatchFunc* match, void* hint){
	int i;
	void * item = malloc(util.typeSize);
	for (i = (util.length-1);i >= 0;i--){
		
		memcpy(item,&(util.base[(i*util.typeSize)]),util.typeSize);
		
		if(match(hint,item)){
			return item;
		}
	}
	return 0;
}
int count(ArrayUtil util, MatchFunc* match, void* hint){
	int i;
	int counter = 0;
	void * item = malloc(util.typeSize);
	for (i = 0;i < util.length;i++){

		memcpy(item,&(util.base[(i*util.typeSize)]),util.typeSize);

		if(match(hint,item)){
			counter++;
		}
	}
	return counter;
}

int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems ){
	int i;
	int counter = 0;
	void * item = malloc(util.typeSize);
	for (i = 0;i < util.length;i++){

		memcpy(item,&(util.base[(i*util.typeSize)]),util.typeSize);
	
		if(match(hint,item)){
			memcpy(&((*destination)[counter*util.typeSize]),item,util.typeSize);
			counter++;
		}

		if(counter==maxItems){
			return counter;
		}
	
	}
	return counter;
}
