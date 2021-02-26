#include <stdio.h>
#include <Light.h>

#define TEST_ACTIVATED         1
#define TEST_NOT_ACTIVATED     0

typedef struct
{
  unsigned char functionName[40];
  int (*pf)(void);
  unsigned char run;
} T_testFunction;


/* Test function prototype (test_main.h) */
int TEST_Light_init(void);
int TEST_Light_order_LightOff(void);
int TEST_Light_order_LightOn(void);
int TEST_Light_order_LightReverseState(void);
int TEST_LightOutputSet(void);
int TEST_LightOutputReset(void);

/* Test configuration (test_cfg.c) */
unsigned char TEST_module[50] = "Light";

T_testFunction test_list_config[]=
{
  /* Unit tests*/
  {"Light_init",                    TEST_Light_init,                    TEST_ACTIVATED     },
  {"Light_order_LightOff",          TEST_Light_order_LightOff,          TEST_ACTIVATED     },
  {"Light_order_LightOn",           TEST_Light_order_LightOn,           TEST_ACTIVATED     },
  {"Light_order_LightReverseState", TEST_Light_order_LightReverseState, TEST_ACTIVATED     },
  {"LightOutputSet",                TEST_LightOutputSet,                TEST_NOT_ACTIVATED },
  {"LightOutputReset",              TEST_LightOutputReset,              TEST_NOT_ACTIVATED }

  /* Integration tests */
/*  {"Integration test: TeleInfo_Integration", TEST_TeleInfo_Integration}, */
};


/* Test variables declaration (test_cfg.h) */
#define TEST_LIST_CONFIG_SIZE ((unsigned int)(sizeof(test_list_config)/sizeof(T_testFunction)))

/* Test (test.h)*/
#define TST_RET_OK    0
#define TST_RET_N_OK  1
unsigned int errorNum;

/* Test (test.c)*/
int testStringFill(int *strPtr, int *string)
{
  unsigned char strSize = sizeof(string);
  unsigned char i;

  for(i=0; i<strSize; i++)
  {
    strPtr[i] = string[i];
  }
  return 0;
}

void assert(int check, char *str)
{
  if(check == 0)
  {
    printf("  Error: %s\n", str);
    errorNum++;
  }
}

void assert_cmp(unsigned int val1, unsigned int val2, char *str)
{
  if(val1 != val2)
  {
    printf("  Error: %s (%d!=%d)\n", str, val1, val2);
    errorNum++;
  }
}

void TEST_init(void)
{
  errorNum=0;
}

unsigned int TEST_finish(void)
{
  return errorNum;
}

unsigned char tst_cmp(unsigned char *a, unsigned char *b, unsigned char len)
{
  for(unsigned char i=0; i<len; i++)
  {
    if(*a++ != *b++)
    {
      assert(0, "cmp fail\n");
      return TST_RET_N_OK;
    }
  }
  return TST_RET_OK;
}

unsigned char tst_set(unsigned char *a, unsigned char *b, unsigned char len)
{
  for(unsigned char i=0; i<len; i++)
  {
    *a = *b;
    a++;
    b++;
  }
  return TST_RET_OK;
}


unsigned int assert_error;
unsigned char assert_testName[100];

void assert_init(unsigned char testName[100], unsigned char testCaseNum)
{
  assert_error=0;
  printf("Executing test: %s__%d... \t", testName, testCaseNum);
  for(int i=0; i<100; i++)
  {
    assert_testName[i] = testName[i];
  }
}

void assert_end(void)
{
  if( assert_error == 0)
  {
    printf("%s- TEST PASSED!\n", assert_testName );
  }
  else
  {
    printf("\n %s - TEST FAILED: %d errors\n", assert_testName, assert_error);
  }
}

/********************************************************/

#define TST_LIGHT_NUM 1
int TEST_Light_init(void)
{
  /*int result=-1;*/
  int i;
  TEST_init();

  /* Init */
  Light_Init();

  for(i=0; i<TST_LIGHT_NUM; i++)
  {
    assert(LightState[i].state == 0, "Invalid init state");
    assert(LightState[i].order == 0, "Invalid init order");
    assert(LightState[i].timer_val == 0, "Invalid init timer value");
  }

  return TEST_finish();
}


int TEST_Light_order_LightOff(void)
{
  /*int result=-1;*/
  unsigned char tst_ret;


  // GPIO_TypeDef* Test_GPIO_Port;
  // T_LightConfig Test_Config = {
  //                               Test_GPIO_Port, 
  //                               0, /* Pin */
  //                               0b10000000, /* Active, not dimmable; no timer, not ledStrip */
  //                               0, /* brightness default value */
  //                               0  /* timer default value */
  //                             };

  TEST_init();

  LightState[0].state = 255;
  LightState[0].order = 255;
  LightState[0].brightness_last = 255;
  LightState[0].timer_val = 255;

  /* Init */
  Light_Init();

  tst_ret = Light_order_LightOff(0);

  assert(LightState[0].state == 0, "Invalid state");
  assert(LightState[0].order == 0, "Invalid order");
  assert(LightState[0].brightness_last == 255, "Invalid brightness");
  assert(LightState[0].timer_val == 0, "Invalid timer value");
  assert(tst_ret == 0, "Invalid return value");

  return TEST_finish();
}

int TEST_Light_order_LightOn(void)
{
  /*int result=-1;*/
  unsigned char tst_ret;
  TEST_init();

  /* Init */
  Light_Init();

  LightState[0].state = 127;
  LightState[0].order = 127;
  LightState[0].brightness_last = 0;
  LightState[0].timer_val = 0;

  tst_ret = Light_order_LightOn(0);

  assert(LightState[0].state == 255, "Invalid state");
  assert(LightState[0].order == 127, "Invalid order");
  assert(LightState[0].brightness_last == 127, "Invalid brightness");
  assert(LightState[0].timer_val == 0, "Invalid timer value");
  assert(tst_ret == 0, "Invalid return value");

  return TEST_finish();
}


int TEST_Light_order_LightReverseState(void)
{
  /*int result=-1;*/
  unsigned char tst_ret;

  TEST_init();

  /* Init */
  Light_Init();

  T_LightState * Test_Light = &LightState[0];

  /* Set some values */
  Test_Light->state = 127;
  Test_Light->order = 127;
  Test_Light->brightness_last = 0;
  Test_Light->timer_val = 127;

  /* Mid brightness to Off */
  tst_ret = Light_order_LightReverseState(0);

  assert(Test_Light->state == 0, "Step1 - Invalid state");
  assert(Test_Light->order == 127, "Step1 - Invalid order");
  assert(Test_Light->brightness_last == 127, "Step1 - Invalid brightness");
  assert(Test_Light->timer_val == 127, "Step1 - Invalid timer value");
  assert(tst_ret == 0, "Invalid return value");

  /* Off to On */
  tst_ret = Light_order_LightReverseState(0);

  assert(Test_Light->state == 255, "Step2 - Invalid state");
  assert(Test_Light->order == 127, "Step2 - Invalid order");
  assert(Test_Light->brightness_last == 127, "Step2 - Invalid brightness");
  assert(Test_Light->timer_val == 127, "Step2 - Invalid timer value");
  assert(tst_ret == 0, "Invalid return value");

  /* On to Off */
  tst_ret = Light_order_LightReverseState(0);

  assert(Test_Light->state == 0, "Step3 - Invalid state");
  assert(Test_Light->order == 127, "Step3 - Invalid order");
  assert(Test_Light->brightness_last == 127, "Step3 - Invalid brightness");
  assert(Test_Light->timer_val == 127, "Step3 - Invalid timer value");
  assert(tst_ret == 0, "Invalid return value");

  return TEST_finish();
}


int TEST_LightOutputSet(void)
{
  /*int result=-1;*/
  unsigned char tst_ret;

  TEST_init();

  /* Init */
  Light_Init();

//unsigned char LightOutputSet(unsigned char LightId)

  return TEST_finish();
}

int TEST_LightOutputReset(void)
{
  /*int result=-1;*/
  unsigned char tst_ret;

  TEST_init();

  /* Init */
  Light_Init();

//unsigned char LightOutputReset(unsigned char LightId)

  return TEST_finish();
}




/********************************************************/







/************************************************
 *
 *   MAIN TESTS
 *
 *************************************************/
int main(void)
{
  int ret[TEST_LIST_CONFIG_SIZE];
  unsigned int test_passed=0, test_failed=0, test_notrun=0;
  
  printf("Module: %s\n", TEST_module);
  printf("Test sequence begin\n");
  printf("-------------------\n");

  for(unsigned int i=0; i<TEST_LIST_CONFIG_SIZE; i++)
  {
    printf("Executing test: %s\n", test_list_config[i].functionName);
    if(test_list_config[i].run)
    {
      ret[i] = (test_list_config[i].pf)();
    }
    else 
    {
      ret[i] = -1;
    }
    printf("End of test: %s - ", test_list_config[i].functionName);

    if(ret[i] == 0)
    {
      printf("PASSED\n");
    }
    else if(ret[i] >= 1)
    {
      printf("FAILED\n");
    }
    else
    {
      printf("NOT EXECUTED\n");
    }
  }
  printf("-------------------\n");
  printf("Test sequence end  \n\n");

  printf("------Sum Up-------\n");
  for(unsigned int i=0; i<TEST_LIST_CONFIG_SIZE; i++)
  {
    if(ret[i] == 0)
    {
      test_passed++;
      printf("[v] TEST %s: passed\n", test_list_config[i].functionName);
    }
    else if(ret[i] >= 1)
    {
      test_failed++;
      printf("[x] TEST %s: failed\n", test_list_config[i].functionName);
    }
    else
    {
      test_notrun++;
      printf("[u] TEST %s: not executed\n", test_list_config[i].functionName);
    }
    
  }
  printf("%d failed - %d passed - %d unexecuted - total: %d tests\n", test_failed, test_passed, test_notrun, test_passed+test_failed+test_notrun);
  printf("-------------------\n");

  return test_failed;
}
