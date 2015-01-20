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