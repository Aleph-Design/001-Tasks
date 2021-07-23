/*
* Compiles after changes made in the framework location of FreeRTOSConfig.h:
* ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/freertos/freertos/FreeRTOSConfig.h
*/
#include <Arduino.h>

static void taskOneHandler(void *pvParam);
/*
static void taskTwoHandler(void *pvParam);
*/

void setup() 
{
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  Serial.printf("\nSetup() MY_FREE_RTOS_CONFIG: %d\n", MY_FREE_RTOS_CONFIG);
  Serial.printf("configUSE_PREEMPTION: %d\n", configUSE_PREEMPTION);
  Serial.printf("configMAX_PRIORITIES: %d\n\n", configMAX_PRIORITIES);


  TaskHandle_t taskOneHandle = NULL;   // actually a pointer
  //TaskHandle_t taskTwoHandle = NULL;

  BaseType_t status;                   // 32-bits variable

  //const char* textOne = "1111111111111111111111111111111111111";
  //const char* textTwo = "2222222222222222222222222222222222222";


  status = xTaskCreatePinnedToCore(
              taskOneHandler, 
              "Task-1", 
              1024,
              NULL, //(void*)textOne,
              2,
              &taskOneHandle,
              1);

  configASSERT(status = pdPASS);  // if evaluate to 1, no activation

/*

  status = xTaskCreate(taskTwoHandler, 
              "Task-2", 
              1024,
              (void*)textTwo,
              2,
              &taskTwoHandle);

  configASSERT(status = pdPASS);  // if evaluate to 1, no activation
*/

} // end setup() -------------------------------------------------------------


void loop() {
  // put your main code here, to run repeatedly:
}


// The scope of this task file is limited to this C++ file; private function
//
static void taskOneHandler(void *pvParam)
{
  //const char* localTextOne = (char*) pvParam;
  const char* localTextOne = "1111111111111111111111111111111111111";

  for (;;)
  {
    Serial.printf("localTextOne: %s\n", localTextOne);  // (char*) pvParam); // 
  }

  vTaskDelete(NULL);
  
} // end taskOneHandler()


/*
static void taskTwoHandler(void *pvParam)
{
  const char* localTextTwo = (char*) pvParam;

  for (;;)
  {
    Serial.printf("localTextTwo: %s", localTextTwo);
  }

  vTaskDelete(NULL);
  
} // end taskTwoHandler()
*/