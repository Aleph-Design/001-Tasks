#include <Arduino.h>

#include <freeRTOS/freeRTOSConfig.h>

#define SMALL_TEST 1

//#define configAssert(x) if( (x) == 0) { taskDISABLE_INTERRUPS(); for(;;); }

static void taskOneHandler(void *pvParam);
static void taskTwoHandler(void *pvParam);

void setup() 
{
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  Serial.printf("\nSetup() %d\n", MY_FREE_RTOS_CONFIG);

  TaskHandle_t taskOneHandle = NULL;   // actually a pointer
  TaskHandle_t taskTwoHandle = NULL;

  BaseType_t status;            // 32-bits variable

  const char* textOne = "1111111111111111111111111111111111111";
  const char* textTwo = "2222222222222222222222222222222222222";

  status = xTaskCreate(taskOneHandler, 
              "Task-1", 
              1024,
              (void*)textOne,
              12,
              &taskOneHandle);

  configASSERT(status = pdPASS);  // if evaluate to 1, no activation

  status = xTaskCreate(taskTwoHandler, 
              "Task-2", 
              1024,
              (void*)textTwo,
              2,
              &taskTwoHandle);

  configASSERT(status = pdPASS);  // if evaluate to 1, no activation


} // end setup() -------------------------------------------------------------


void loop() {
  // put your main code here, to run repeatedly:
}


// The scope of this task file is limited to this C++ file; private function
//
static void taskOneHandler(void *pvParam)
{
  const char* localTextOne = (char*) pvParam;

  for (;;)
  {
    Serial.printf("localTextOne: %s", localTextOne);
  }

  vTaskDelete(NULL);
  
} // end taskOneHandler()



static void taskTwoHandler(void *pvParam)
{
  const char* localTextTwo = (char*) pvParam;

  for (;;)
  {
    Serial.printf("localTextTwo: %s", localTextTwo);
  }

  vTaskDelete(NULL);
  
} // end taskTwoHandler()
