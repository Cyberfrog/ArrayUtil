#include "expr_assert.h"
#include "arrayUtil.h"
void test_areEqual_returns_1_when_content_of_both_array_are_same(){
	int marks1[] ={1,2,3,4,5};
	int marks2[] ={1,2,3,4,5};
	int result;
	ArrayUtil au1,au2 ;
	au1.base = marks1;
	au1.typeSize=sizeof(int);
	au1.length = 5;
	au2.base = marks2;
	au2.typeSize=sizeof(int);
	au2.length = 5;
	result = areEqual(au1,au2);
	assertEqual(result, 1);
} 

void test_areEqual_returns_0_when_content_of_both_array_are_not_same(){
	int marks1[] ={1,2,3,4,5};
	int marks2[] ={1,2,4,4,3};
	int result;
	ArrayUtil au1,au2 ;
	au1.base = marks1;
	au1.typeSize=sizeof(int);
	au1.length = 5;
	au2.base = marks2;
	au2.typeSize=sizeof(int);
	au2.length = 5;
	result = areEqual(au1,au2);
	assertEqual(result, 0);
}
void test_creat_returns_new_ArraUtil_of_specified_size_and_length_and_set_all_element_to_zero(){
	int i;
	ArrayUtil au = create(sizeof(int),5);
	assertEqual(au.length,5);
	assertEqual(au.typeSize,sizeof(int));
	for(i=0;i<au.length;i++){
		assertEqual(((int *)au.base)[i],0);
	}

}
void test_ArrayUtil_has_previous_element_and_sets_new_element_to_zero_after_resizing_to_large_size(){
	int i;
	ArrayUtil au = create(sizeof(int),3);
	ArrayUtil au1;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	au1 =  resize(au,5);
	assertEqual(au1.length, 5);
	assertEqual(((int *)au1.base)[0],101);
	assertEqual(((int *)au1.base)[1],99);
	assertEqual(((int *)au1.base)[2],66);
	assertEqual(((int *)au1.base)[3],0);
	assertEqual(((int *)au1.base)[3],0);

}
void test_ArrayUtil_has_previous_element_after_resizing_to_less_size(){
	int i;
	ArrayUtil au = create(sizeof(int),5);
	ArrayUtil au1;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=666;
	((int *)au.base)[4]=99;
	au1 =  resize(au,3);
	assertEqual(au1.length, 3);
	assertEqual(((int *)au1.base)[0],101);
	assertEqual(((int *)au1.base)[1],99);
	assertEqual(((int *)au1.base)[2],66);
}
void test_findIndex_retruns_index_of_given_element_in_array(){
	int i,index;
	int x=66;
	ArrayUtil au = create(sizeof(int),4);
	ArrayUtil au1;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=666;
	index = findIndex(au, &x);
	assertEqual(index,2);
}
void test_findIndex_retruns_minus_1_given_element_is_not_present_in_array(){
	int i,index;
	int x=0;
	ArrayUtil au = create(sizeof(int),4);
	ArrayUtil au1;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=666;
	index = findIndex(au, &x);
	assertEqual(index,-1);
}


void test_findIndex_retruns_index_of_match_char_in_present_in_array(){
	int index;
	char  x='h';
	ArrayUtil au = create(sizeof(char),4);
	ArrayUtil au1;
	((char *)au.base)[0]='a';
	((char *)au.base)[1]='b';
	((char *)au.base)[2]='h';
	((char *)au.base)[3]='g';
	index = findIndex(au, &x);
	assertEqual(index,2);
}
void test_findIndex_retruns_first_index_of_given_element_in_array(){
	int i,index;
	int x=66;
	ArrayUtil au = create(sizeof(int),6);
	ArrayUtil au1;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=66;
	((int *)au.base)[4]=66;
	((int *)au.base)[5]=66;

	index = findIndex(au, &x);
	assertEqual(index,2);
}

void test_dispose_free_the_array(){
	ArrayUtil au = create(sizeof(int),6);
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=66;
	((int *)au.base)[4]=66;
	((int *)au.base)[5]=66;
	dispose(au);
	// assertEqual(au.length,0);
	// assertEqual(au.typeSize,0);
	// assert((int*)au.base==0);
}

int isEven(void *hint,void *item){
	return (*((int*)item)%2)==0;
}
void test_findFirst_retruns_first_even_number_from_array(){
	ArrayUtil au = create(sizeof(int),6);
	int *firstIndex;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=77;
	((int *)au.base)[4]=2;
	((int *)au.base)[5]=4;
	firstIndex=(int*)findFirst(au,isEven,0);
 	assertEqual(*firstIndex,66);
}

int lessthan(void *hint,void *item ){
	return *((int *)item)<*((int *)hint);
}

void test_findFirst_retruns_first_lessthan_10_number_from_array(){
	ArrayUtil au = create(sizeof(int),6);
	int *firstIndex;
	int hint =10;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=77;
	((int *)au.base)[4]=2;
	((int *)au.base)[5]=4;
	firstIndex=(int*)findFirst(au,lessthan,&hint);
 	assertEqual(*firstIndex,2);
}
void test_findFirst_retruns_null_if_non_of_array_element_matches(){
	ArrayUtil au = create(sizeof(int),6);
	int *firstIndex;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=11;
	((int *)au.base)[3]=13;
	((int *)au.base)[4]=13;
	((int *)au.base)[5]=21;
	firstIndex=(int*)findFirst(au,isEven,0);
 	assertEqual((int)firstIndex,0);
}
void test_findLast_retruns_Last_even_number_from_array(){
	ArrayUtil au = create(sizeof(int),6);
	int *firstIndex;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=77;
	((int *)au.base)[4]=2;
	((int *)au.base)[5]=4;
	firstIndex=(int*)findLast(au,isEven,0);
 	assertEqual(*firstIndex,4);
}
void test_findLast_retruns_last_lessthan_10_number_from_array(){
	ArrayUtil au = create(sizeof(int),6);
	int *firstIndex;
	int hint =10;
	((int *)au.base)[0]=1;
	((int *)au.base)[1]=2;
	((int *)au.base)[2]=3;
	((int *)au.base)[3]=88;
	((int *)au.base)[4]=35;
	((int *)au.base)[5]=12;
	firstIndex=(int*)findLast(au,lessthan,&hint);
 	assertEqual(*firstIndex,3);
}
void test_findLast_retruns_null_if_non_of_array_element_matches(){
	ArrayUtil au = create(sizeof(int),6);
	int *firstIndex;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=11;
	((int *)au.base)[3]=13;
	((int *)au.base)[4]=13;
	((int *)au.base)[5]=21;
	firstIndex=(int*)findLast(au,isEven,0);
 	assertEqual((int)firstIndex,0);
}
void test_count_retruns_count_of_even_number_from_array(){
	ArrayUtil au = create(sizeof(int),6);
	int c;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=66;
	((int *)au.base)[3]=77;
	((int *)au.base)[4]=2;
	((int *)au.base)[5]=4;
	c=count(au,isEven,0);
 	assertEqual(c,3);
}
void test_count_retruns_count_of_lessthan_10_number_from_array(){
	ArrayUtil au = create(sizeof(int),6);
	int c;
	int hint =10;
	((int *)au.base)[0]=1;
	((int *)au.base)[1]=2;
	((int *)au.base)[2]=3;
	((int *)au.base)[3]=88;
	((int *)au.base)[4]=35;
	((int *)au.base)[5]=9;
	c=count(au,lessthan,&hint);
 	assertEqual(c,4);
}
void test_count_retruns_0_if_non_of_array_element_matches(){
	ArrayUtil au = create(sizeof(int),6);
	int c;
	((int *)au.base)[0]=101;
	((int *)au.base)[1]=99;
	((int *)au.base)[2]=11;
	((int *)au.base)[3]=13;
	((int *)au.base)[4]=13;
	((int *)au.base)[5]=21;
	c=count(au,isEven,0);
 	assertEqual((int)c,0);
}