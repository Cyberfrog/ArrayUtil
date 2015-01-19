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