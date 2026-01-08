#include "sorting.h"
#include <unity.h>

void setUp(){

}

void tearDown(){

}


void test_insertion_sort(){
  int samples[] = {9,8,7,6,5,4,3,2,1,0};
  insertion_sort(samples, 10);
  for(int i = 0; i<10; i++){
    TEST_ASSERT_EQUAL(i, samples[i]);
  }
}

void test_insertion_sort_single(){
  int samples[] = {5};
  insertion_sort(samples, 1);
  TEST_ASSERT_EQUAL(5, samples[0]);
}

void test_insertion_sort_already_sorted(){
  int samples[] = {1,2,3,4,5};
  insertion_sort(samples, 5);
  for(int i = 0; i < 5; i++){
    TEST_ASSERT_EQUAL(i+1, samples[i]);
  }
}

void app_main(){
  UNITY_BEGIN();
  RUN_TEST(test_insertion_sort);
  RUN_TEST(test_insertion_sort_single);
  RUN_TEST(test_insertion_sort_already_sorted);
  UNITY_END();
}