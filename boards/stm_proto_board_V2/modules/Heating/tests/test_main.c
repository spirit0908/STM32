#include <stdio.h>
#include "Heating.h"


typedef struct
{
  unsigned char functionName[40];
  int (*pf)(void);
  unsigned char run;
} T_testFunction;


int TEST_Heating_Init(void);
int TEST_Heating_mainfunction(void);

/* Test configuration (test_cfg.c) */
unsigned char TEST_module[50] = "Heating";

T_testFunction test_list_config[]=
{
  /* Unit tests*/
  {"Heating_Init", TEST_Heating_Init, 1},
  {"Heating_mainfunction", TEST_Heating_mainfunction, 1},

  /* Integration tests*/
//  {"Integration test: TeleInfo_Integration", TEST_TeleInfo_Integration},
};

#define TEST_LIST_CONFIG_SIZE (sizeof(test_list_config)/sizeof(T_testFunction))

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

unsigned int errorNum;
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

int TEST_TIC_FillInInfo(void)
{
  int result=-1;
  TEST_init();

  return TEST_finish();
}



#define TST_HEATING_MODE_OFF                           0
#define TST_HEATING_MODE_NORMAL                        1
#define TST_HEATING_MODE_ECO                           2
#define TST_HEATING_MODE_CONFORT                       3
#define TST_HEATING_MODE_FROST                         4
#define TST_HEATING_MODE_INHIBIT                       5
#define TST_HEATING_MODE_ACTIVATE                      6


#define TST_HEATING_SM_STATE_OFF                       0
#define TST_HEATING_SM_STATE_WAIT                      1
#define TST_HEATING_SM_STATE_HEAT                      2


#define TST_HEATING_PRECISION                          2 /* 1/0,5 */

#define TST_INIT_VAL_HEATING_MODE                      TST_HEATING_MODE_OFF
#define TST_INIT_VAL_HEATING_STATE                     TST_HEATING_SM_STATE_OFF
#define TST_INIT_VAL_HEATING_THRESHOLD                 1 /* 0,5 degre */
#define TST_INIT_VAL_HEATING_TEMPERATURE_DEFAULT       20 * TST_HEATING_PRECISION
#define TST_INIT_VAL_HEATING_TEMPERATURE_COMFORT       21 * TST_HEATING_PRECISION
#define TST_INIT_VAL_HEATING_TEMPERATURE_ECO           TST_INIT_VAL_HEATING_TEMPERATURE_DEFAULT - (2 * TST_HEATING_PRECISION)
#define TST_INIT_VAL_HEATING_TEMPERATURE               0
#define TST_INIT_VAL_HEATING_CONSIGNE                  TST_INIT_VAL_HEATING_TEMPERATURE_DEFAULT


#define TST_HEATING_MAX_DEVICES                        2
#define TST_HEATING_TEMPERATURE_MAX                    255
/************************************************
 *
 *   UNIT TESTS
 *
 *************************************************/

int TEST_Heating_Init(void)
{
  int result=-1;
  int i;
  TEST_init();

  /* Init */
  Heating_Init();

  for(i=0; i< TST_HEATING_MAX_DEVICES; i++)
  {
    assert_cmp(HeatingState[i].mode,                TST_INIT_VAL_HEATING_MODE,                "wrong init value: mode");
    assert_cmp(HeatingState[i].state,               TST_INIT_VAL_HEATING_STATE,               "wrong init value: state");
    assert_cmp(HeatingState[i].consigne,            TST_INIT_VAL_HEATING_CONSIGNE,            "wrong init value: consigne");
    assert_cmp(HeatingState[i].threshold ,          TST_INIT_VAL_HEATING_THRESHOLD,           "wrong init value: threshold");
    assert_cmp(HeatingState[i].temperature,         TST_INIT_VAL_HEATING_TEMPERATURE,         "wrong init value: temperature");
    assert_cmp(HeatingState[i].temperature_default, TST_INIT_VAL_HEATING_TEMPERATURE_DEFAULT, "wrong init value: temperature_default");
    assert_cmp(HeatingState[i].temperature_confort, TST_INIT_VAL_HEATING_TEMPERATURE_COMFORT, "wrong init value: temperature_comfort");
  }
  
  assert(HEATING_MAX_DEVICES == TST_HEATING_MAX_DEVICES, "Nb of HEATING_MAX_DEVICES mismatched");

  return TEST_finish();
}

int TEST_Heating_mainfunction(void)
{
  int result=-1;
  unsigned char returnVal;
  int i;
  unsigned char testIndex=0;
  TEST_init();


  Heating_Init();
  returnVal = Heating_mainfunction();
  assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_OFF, "error: wrong init state. State OFF expected" );

  /* stay in OFF */
  HeatingState[testIndex].state = TST_HEATING_SM_STATE_OFF;
  returnVal = Heating_mainfunction();
  assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_OFF, "error: wrong state. State OFF expected" );

  /* force to WAIT */
  HeatingState[testIndex].state = TST_HEATING_SM_STATE_WAIT;
  
  /* stay in WAIT */
  for(i=TST_INIT_VAL_HEATING_CONSIGNE; i<TST_HEATING_TEMPERATURE_MAX; i++)
  {
    HeatingState[testIndex].temperature = i;
    returnVal = Heating_mainfunction();
    assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_WAIT, "error: wrong state. State WAIT expected" );
  }
  
  /* Transission from WAIT to HEAT */
  HeatingState[testIndex].temperature = TST_INIT_VAL_HEATING_CONSIGNE-(1*2);
  returnVal = Heating_mainfunction();
  assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_HEAT, "error: wrong state. State HEAT expected (1)" );
  
  /* decrease temperature */
  /* stay in HEAT */
  for(i=TST_INIT_VAL_HEATING_CONSIGNE-(1*2); i>0; i--)
  {
    HeatingState[testIndex].temperature = i;
    returnVal = Heating_mainfunction();
    assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_HEAT, "error: wrong state. State HEAT expected (2)" );
  }
  
  /* increase temperature */
  /* stay in HEAT */
  for(i=0; i<TST_INIT_VAL_HEATING_CONSIGNE; i++)
  {
    HeatingState[testIndex].temperature = i;
    returnVal = Heating_mainfunction();
    assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_HEAT, "error: wrong state. State HEAT expected (3)" );
  }

  /* transition from HEAT to WAIT */
  for(i=TST_INIT_VAL_HEATING_CONSIGNE+(1*2); i<TST_HEATING_TEMPERATURE_MAX; i++)
  {
    HeatingState[testIndex].temperature = i;
    returnVal = Heating_mainfunction();
    assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_WAIT, "error: wrong state. State WAIT expected (2)" );
  }

  /* unknown state - transission to OFF */
  HeatingState[testIndex].state = 255;
  returnVal = Heating_mainfunction();
  assert_cmp(HeatingState[testIndex].state, TST_HEATING_SM_STATE_OFF, "error: wrong state. State OFF expected (2)" );

  return TEST_finish();
}

/************************************************
 *
 *   INTEGRATION TESTS
 *
 *************************************************/



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
    else if(ret[i] == 1)
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
    else if(ret[i] > 1)
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
