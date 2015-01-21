#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdlib.h>
#include <string.h>
ArrayUtil util1,util2;
typedef struct Student{
	int rollno;
	float age;
} student;

void test_areEqual_returns_1_when_content_of_both_array_are_same(){
	int result;
	util1=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};
	util2=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};

	result = areEqual(util1,util2);
	assertEqual(result, 1);
} 

void test_areEqual_returns_0_when_content_of_both_array_are_not_same(){
	int result;
	util1=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};
	util2=(ArrayUtil){(int[]){1,2,4,3,5},sizeof(int),5};

	result = areEqual(util1,util2);
	assertEqual(result, 0);
}
// -------------------------------------areEqual(char)--------------------------------------------------------------
void test_areEqual_returns_1_when_content_of_both_char_array_are_same_(){
	int result;
	util1=(ArrayUtil){(char[]){'q','w','e','r','t'},sizeof(char),5};
	util2=(ArrayUtil){(char[]){'q','w','e','r','t'},sizeof(char),5};

	result = areEqual(util1,util2);
	assertEqual(result, 1);
} 
void test_areEqual_returns_0_when_content_of_both_char_array_are_not_same(){
	int result;
	util1=(ArrayUtil){(char[]){'q','w','e','r','t'},sizeof(char),5};
	util2=(ArrayUtil){(char[]){'Q','w','E','t','r'},sizeof(char),5};

	result = areEqual(util1,util2);
	assertEqual(result, 0);
} 

// void test_areEqual_returns_0_when_content_of_both_string_array_are_not_same(){
// 	int result;
// 	char *string[]={"ask","ask","ask","ask","ask"};
// 	char *string1[]={"ask","ask"};
// 	printf("----%p %p  %p %s\n",string,string1 ,string1[0],string1[2] );
// 	util1=(ArrayUtil){string,sizeof(char *),5};
// 	util2=(ArrayUtil){string1,sizeof(char *),5};

// 	result = areEqual(util1,util2);
// 	assertEqual(result, 0);
// } 
// -------------------------------------areEqual(float)--------------------------------------------------------------
void test_areEqual_returns_1_when_content_of_both_float_array_are_same_(){
	int result;
	util1=(ArrayUtil){(float[]){3.1,5.2,3.2,5.4,0.2},sizeof(float),5};
	util2=(ArrayUtil){(float[]){3.1,5.2,3.2,5.4,0.2},sizeof(float),5};

	result = areEqual(util1,util2);
	assertEqual(result, 1);
} 
void test_areEqual_returns_0_when_content_of_both_float_array_are_not_same(){
	int result;
	util1=(ArrayUtil){(float[]){3.1,5.2,3.2,5.4,0.2},sizeof(float),5};
	util2=(ArrayUtil){(float[]){3.2,5.4,3.1,5.2,4.2},sizeof(float),5};

	result = areEqual(util1,util2);
	assertEqual(result, 0);
} 

// -------------------------------------areEqual(double)--------------------------------------------------------------

void test_areEqual_returns_1_when_content_of_both_double_array_are_same_(){
	int result;
	util1=(ArrayUtil){(double[]){333.1,3335.2},sizeof(double),2};
	util2=(ArrayUtil){(double[]){333.1,3335.2},sizeof(double),2};

	result = areEqual(util1,util2);
	assertEqual(result, 1);
} 
void test_areEqual_returns_0_when_content_of_both_double_array_are_not_same(){	
	int result;
	util1=(ArrayUtil){(double[]){333.1,3335.2},sizeof(double),2};
	util2=(ArrayUtil){(double[]){3.2,5.4},sizeof(double),2};

	result = areEqual(util1,util2);
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
void test_create_Structures_with_all_fields_NULL(){
	student temp = {0,0.0};
	student Student[1] = {temp};
	ArrayUtil expected = {Student,sizeof(student),1};
	util1 = create(sizeof(student),1);	
	assert(areEqual(expected,util1));
};
void test_resize_sets_new_elements_to_zero_in_double(){
	double expectedArray[] = {1.0,0.0};
	ArrayUtil b = {expectedArray,sizeof(double),2};
	util1 = create(sizeof(double),1);
	((double*)util1.base)[0] = 1.0;
	util1 = resize(util1, 2);
	assert(areEqual(b, util1));
}
void test_resize_sets_new_elements_to_NULL(){
	String blank = '\0';
	String expectedArray[] = {"digs",blank};
	String name[] = {"digs"};
	ArrayUtil b = {expectedArray,sizeof(String),2};
	util1 = create(sizeof(String),1);
	memcpy(util1.base, name, sizeof(String)*1);
	util1 = resize(util1, 2);
	assert(areEqual(b, util1));
};
void test_ArrayUtil_has_previous_element_and_sets_new_element_to_zero_after_resizing_to_large_size(){
	util1 =create(sizeof(int),1);
	util2 =(ArrayUtil){(int[]){101,0,0},sizeof(int),3};
	((int *)util1.base)[0] =101;
	assert(areEqual(util2,resize(util1,3)));
	
}
void test_ArrayUtil_has_previous_element_after_resizing_to_less_size(){
	util1= create(sizeof(int),3);
	util2=(ArrayUtil){(int[]){101},sizeof(int),1};
	((int *)util1.base)[0]=101;
	((int *)util1.base)[1]=99;
	((int *)util1.base)[2]=66;
	util1 = resize(util1,1);
	assert(areEqual(util1,util2));
}
void test_findIndex_retruns_index_of_given_element_in_array(){
	int x=4;
	util1 = (ArrayUtil){(int[]){260,4,66,666},sizeof(int),4};
	assertEqual(findIndex(util1, &x),1);
}
void test_findIndex_retruns_minus_1_given_element_is_not_present_in_array(){
	int x=4;
	util1 = (ArrayUtil){(int[]){101,99,66,666},sizeof(int),4};
	assertEqual(findIndex(util1, &x),-1);
}


void test_findIndex_retruns_index_of_match_char_in_present_in_array(){
	char x='h';
	util1 = (ArrayUtil){(char[]){'a','b','h','g'},sizeof(char),4};
	assertEqual(findIndex(util1, &x),2);
}

void test_findIndex_retruns_first_index_of_given_element_in_array(){
	int x=66;
	util1 = (ArrayUtil){(int[]){101,66,66,66},sizeof(int),4};
	assertEqual(findIndex(util1, &x),1);
}

void test_dispose_free_the_array(){
	util1 = create(sizeof(int),6);
	dispose(util1);
	assert(util1.base==(char*)malloc(1));
	free(util1.base);
}

int isEven(void *hint,void *item){
	return (*((int*)item)%2)==0;
}
void test_findFirst_retruns_first_even_number_from_array(){
	util1 = (ArrayUtil){(int[]){101,99,66,77,2,4},sizeof(int),6};
 	assertEqual(*(int*)findFirst(util1,isEven,0),66);
}

int lessthan(void *hint,void *item ){
	return *((int *)item)<*((int *)hint);
}

void test_findFirst_retruns_first_lessthan_10_number_from_array(){
	int hint=10;
	util1 = (ArrayUtil){(int[]){101,99,66,77,2,4},sizeof(int),6};
 	assertEqual(*(int*)findFirst(util1,lessthan,&hint),2);
}

void test_findFirst_retruns_null_if_non_of_array_element_matches(){
	util1 = (ArrayUtil){(int[]){101,99,11},sizeof(int),3};
 	assert(findFirst(util1,isEven,0)==NULL);

}
void test_findLast_retruns_Last_even_number_from_array(){
	util1 = (ArrayUtil){(int[]){101,99,66,77,2,4},sizeof(int),6};
 	assertEqual(*(int*)findLast(util1,isEven,0),4);
}

void test_findLast_retruns_last_lessthan_10_number_from_array(){
	int hint =10;
	util1 = (ArrayUtil){(int[]){1,2,3,88,35,12},sizeof(int),6};
 	assertEqual(*(int*)findLast(util1,lessthan,&hint),3);
}

void test_findLast_retruns_null_if_non_of_array_element_matches(){
	util1 = (ArrayUtil){(int[]){101,99,11},sizeof(int),3};
 	assert(findLast(util1,isEven,0)==NULL);

}
void test_count_retruns_count_of_even_number_from_array(){
	util1 = (ArrayUtil){(int[]){101,99,66,77,2,4},sizeof(int),6};
 	assertEqual(count(util1, isEven, 0), 3);
}
void test_count_retruns_count_of_lessthan_10_number_from_array(){
	int hint=10;
	util1 = (ArrayUtil){(int[]){1,2,3,77,99,4},sizeof(int),6};
 	assertEqual(count(util1, lessthan, &hint), 4);
}
void test_count_retruns_0_if_non_of_array_element_matches(){
	util1 = (ArrayUtil){(int[]){101,99,11,77},sizeof(int),4};
 	assertEqual(count(util1, isEven, 0), 0);
}
void test_filter_populate_destination_array_with_evenNumbers(){
	int maxItem=6;
	int *evens =(int *)malloc(sizeof(int)*maxItem);
	util1 = (ArrayUtil){(int[]){101,22,12,13},sizeof(int),4};
		
 	assertEqual(filter(util1,isEven,0,(void**)&evens,maxItem),2);
 	assertEqual(evens[0],22);
 	assertEqual(evens[1],12);
}
void test_filter_populate_destination_array_until_hits_max_size_and_return_no_element_added_to_id(){
	int maxItem=2;
	int *evens =(int *)malloc(sizeof(int)*maxItem);
	util1 = (ArrayUtil){(int[]){101,22,12,14},sizeof(int),4};		

 	assertEqual(filter(util1,isEven,0,(void**)&evens,maxItem),2);
 	assertEqual(evens[0],22);
 	assertEqual(evens[1],12);

}

void multiplyBy(void* hint, void* sourceItem, void* destinationItem){
	*(int*)destinationItem = *(int*)sourceItem * *(int*)(hint);
}

void test_map_converts_each_element_source_array_and_put_it_to_destination_array(){
	int hint =10;
	ArrayUtil expected={(int[]){10,20,30,40,50},sizeof(int),5};
	util1=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};
	util2 =create(sizeof(int),5);
	
	map(util1,util2,multiplyBy,&hint);
	assert(areEqual(expected, util2));
}

void add10(void* index, void* item){
 	((int*)util2.base)[*(int*)index] =  *(int*)item+10;
 	(*(int*)index)++; 	
}

void test_forEach_call_add_function_with_each_element_in_array (){
	int hint = 0;
	ArrayUtil expected={(int[]){11,12,13,14,15},sizeof(int),5};
	util1=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};
	util2= create(sizeof(int), 5);
	
	forEach(util1,add10,&hint);
	assert(areEqual(expected, util2));
}

void* add(void* hint, void* previousItem, void* item){
 	int *a = (int*)malloc(sizeof(int));
 	*a = *(int*)previousItem + *(int*)item;
 	return a;
}

void test_reduce_call_add_function_with_each_element_in_array_and_retruns_last_call_value (){
	int hint = 0,initVlaue=0;
	int *result; 
	util1=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};
	
	result = (int *)reduce(util1,add,&hint,&initVlaue);
	assertEqual(*result, 15);
}