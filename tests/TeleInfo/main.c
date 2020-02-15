#include <stdio.h>
#include "teleinfo.h"


int TEST_teleinfo_rawByte_receive(void);
int TEST_TIC_CRC(void);

typedef struct
{
  unsigned char functionName[30];
  int (*pf)(void);
} T_testFunction;

T_testFunction test_list_config[]=
{
//    {"teleinfo_rawByte_receive", TEST_teleinfo_rawByte_receive},
    {"TIC_CRC", TEST_TIC_CRC},
};
#define TEST_LIST_CONFIG_SIZE (sizeof(test_list_config)/sizeof(T_testFunction))

/************************************************
 *
 *
 *************************************************/
int TEST_teleinfo_rawByte_receive(void)
{
  int result=-1;
  //result = teleinfo_rawByte_receive();
  return result;
}

typedef struct
{
  unsigned char string[30];
  unsigned char expectedResult;
} T_TIC_CRC;

int TEST_TIC_CRC(void)
{
  int result=0;
  unsigned char ret;
  T_TIC_CRC test_table[]=
  {
    {"test_string", 'V'},
    {"ADCO 030022261629 8\r\n", '8'},
    {"HCHC 035047226 # CR LF", '#'},
    //LF ADCO space 0 30022261629 space 8 CR 
 {"\xa\x41\x44\x43\x4f\x20\x30\x33\x30\x30\x32\x32\x32\x36\x31\x36\x32\x39\x20\x38\xd", '8'},
  };
 
  for(int j=0; j<4; j++)
  {
    ret = TIC_CRC(test_table[j].string);
 
    printf("  expected value: %d, result: %d\n", test_table[j].expectedResult, ret);
 
    if(ret != test_table[j].expectedResult)
      result = 1;
  }
  return result;
}



int main(void)
{
  unsigned int ret[TEST_LIST_CONFIG_SIZE];

  printf("Test sequence begin\n");
  printf("-------------------\n");

  for(int i=0; i<TEST_LIST_CONFIG_SIZE; i++)
  {
    printf("Executing test: %s\n", test_list_config[i].functionName);
    ret[i] = (test_list_config[i].pf)();
    if(ret[i] == 0)
    {
      printf("TEST %s: passed", test_list_config[i].functionName);
    }
    else
    {
      printf("TEST %s: failed", test_list_config[i].functionName);
    }

    printf(" - end of test\n"); 
  }
  printf("-------------------\n");
  printf("Test sequence end  \n\n");

  printf("------Sum Up-------\n");
  for(int i=0; i<TEST_LIST_CONFIG_SIZE; i++)
  {
    if(ret[i] == 0)
    {
      printf("[v] TEST %s: passed\n", test_list_config[i].functionName);
    }
    else
    {
      printf("[x] TEST %s: failed\n", test_list_config[i].functionName);
    }
  }
  printf("-------------------\n");
  return 0;
}




