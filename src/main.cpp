/*
* Compiles after changes made in the framework location of FreeRTOSConfig.h:
* ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/freertos/freertos/FreeRTOSConfig.h
*/
#include <Arduino.h>

static void taskOneHandler(void *pvParam);
static void taskTwoHandler(void *pvParam);


void setup() 
{
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  Serial.printf("\nSetup() MY_FREE_RTOS_CONFIG: %d\n", MY_FREE_RTOS_CONFIG);
  Serial.printf("configUSE_PREEMPTION: %d\n", configUSE_PREEMPTION);
  Serial.printf("configMAX_PRIORITIES: %d\n\n", configMAX_PRIORITIES);


  TaskHandle_t taskOneHandle = NULL;   // actually just a pointer
  TaskHandle_t taskTwoHandle = NULL;

  BaseType_t status;                   // 32-bits variable

  const char* textOne = "1111111111111111111111111111111111111";
  const char* textTwo = "2222222222222222222222222222222222222";

  /*
  * Using core 0 runs into:
  * E (11183) task_wdt: Task watchdog got triggered. 
  * The following tasks did not reset the watchdog in time:
  * E (11183) task_wdt:  - IDLE0 (CPU 0)
  * E (11183) task_wdt: Tasks currently running:
  * E (11183) task_wdt: CPU 0: Task-1
  * E (11183) task_wdt: CPU 1: IDLE1
  * E (11183) task_wdt: Aborting.
  * abort() was called at PC 0x400e111f on core 0
  */
  status = xTaskCreatePinnedToCore(
              taskOneHandler, 
              "Task-1", 
              1536,
              (void*)textOne,
              2,
              &taskOneHandle,
              1);

  configASSERT(status = pdPASS);  // if evaluate to 1, no activation


  status = xTaskCreatePinnedToCore(taskTwoHandler, 
              "Task-2", 
              1536,
              (void*)textTwo,
              2,
              &taskTwoHandle,
              1);

  configASSERT(status = pdPASS);  // if evaluate to 1, no activation

  //vTaskDelete(NULL);    // Delete loop()

} // end setup() -------------------------------------------------------------


void loop() {
  // put your main code here, to run repeatedly:
}


// The scope of this task file is limited to this C++ file; private function
//
static void taskOneHandler(void *pvParam)
{
  for (;;)
  {
    Serial.printf("%s\n", (char*) pvParam);

    // Necessary to give task-2 a chance
    //
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
  
} // end taskOneHandler()



static void taskTwoHandler(void *pvParam)
{
  for (;;)
  {
    Serial.printf("%s\n", (char*) pvParam);
  }

  vTaskDelete(NULL);
  
} // end taskTwoHandler()
