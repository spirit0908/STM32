#include <stdio.h>
#include "Heating.h"


typedef struct
{
  unsigned char functionName[40];
  int (*pf)(void);
} T_testFunction;


int TEST_Heating_Init(void);

T_testFunction test_list_config[]=
{
  /* Unit tests*/
  {"Heating_Init", TEST_Heating_Init},

  /* Integration tests*/
//  {"Integration test: TeleInfo_Integration", TEST_TeleInfo_Integration},
};

#define TEST_LIST_CONFIG_SIZE (sizeof(test_list_config)/sizeof(T_testFunction))


#define TST_RET_OK    0
#define TST_RET_N_OK  1

int testStringFill(int *strPtr, int *string)
{
  unsigned char strSize = sizeof(string);
  unsigned char i;

  for(i=0; i<strSize; i++)
  {
    strPtr[i] = string[i];
  }
}

unsigned int errorNum;
void assert(int check, char *str)
{
  if(check == 0)
  {
    printf("Error: %s\n", str);
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


#define TST_HEATING_MODE_NORMAL                        0
#define TST_HEATING_MODE_ECO                           1
#define TST_HEATING_MODE_CONFORT                       2
#define TST_HEATING_MODE_OFF                           3
#define TST_HEATING_MODE_FROST                         4
#define TST_HEATING_MODE_INHIBIT                       5
#define TST_HEATING_MODE_ACTIVATE                      6


#define TST_HEATING_SM_STATE_OFF                       0
#define TST_HEATING_SATE_SM_WAIT                       1
#define TST_HEATING_STATE_SM_HEAT                      2


#define TST_HEATING_PRECISION                          2 /* 1/0,5 */

#define TST_INIT_VAL_HEATING_MODE                      TST_HEATING_MODE_OFF
#define TST_INIT_VAL_HEATING_STATE                     TST_HEATING_SM_STATE_OFF
#define TST_INIT_VAL_HEATING_CONSIGNE                  255  
#define TST_INIT_VAL_HEATING_THRESHOLD                 1 /* 0,5 degre */
#define TST_INIT_VAL_HEATING_TEMPERATURE               20 * TST_HEATING_PRECISION
#define TST_INIT_VAL_HEATING_TEMPERATURE_DEFAULT       20 * TST_HEATING_PRECISION
#define TST_INIT_VAL_HEATING_TEMPERATURE_COMFORT       21 * TST_HEATING_PRECISION


/************************************************
 *
 *   UNIT TESTS
 *
 *************************************************/

int TEST_Heating_Init(void)
{
  int result=-1;
  TEST_init();

  /* Init */
  Heating_Init();

  for(i=0; i< TST_HEATING_MAX_DEVICES; i++)
  {
    assert(HeatingState[i].mode                = TST_INIT_VAL_HEATING_MODE,                 "wrong init value: mode");
    assert(HeatingState[i].state               = TST_INIT_VAL_HEATING_STATE,                "wrong init value: state");
    assert(HeatingState[i].consigne            = TST_INIT_VAL_HEATING_CONSIGNE,             "wrong init value: consigne");
    assert(HeatingState[i].threshold           = TST_INIT_VAL_HEATING_THRESHOLD,            "wrong init value: threshold");
    assert(HeatingState[i].temperature         = TST_INIT_VAL_HEATING_TEMPERATURE,          "wrong init value: temperature");
    assert(HeatingState[i].temperature_default = TST_INIT_VAL_HEATING_TEMPERATURE_DEFAULT,  "wrong init value: temperature_default");
    assert(HeatingState[i].temperature_confort = TST_INIT_VAL_HEATING_TEMPERATURE_COMFORT;, "wrong init value: temperature_comfort");
  }
  
  assert(HEATING_MAX_DEVICES == TST_HEATING_MAX_DEVICES, "Nb of HEATING_MAX_DEVICES mismatched");

  return TEST_finish();
}

//unsigned char HeatingOrderTmt( unsigned char DeviceId, unsigned char Order, unsigned char *param)
//unsigned char Heating_mainfunction(void)



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
  unsigned int ret[TEST_LIST_CONFIG_SIZE];
  unsigned int test_passed=0, test_failed=0;

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
      test_passed++;
      printf("[v] TEST %s: passed\n", test_list_config[i].functionName);
    }
    else
    {
      test_failed++;
      printf("[x] TEST %s: failed\n", test_list_config[i].functionName);
    }
  }
  printf("%d failed - %d passed - total: %d tests\n", test_failed, test_passed, test_passed+test_failed);
  printf("-------------------\n");
  return 0;
}
