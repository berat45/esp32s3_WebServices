/***********************************************/
/****************** ABOUT **********************/
/***********************************************/
/* Author    : Berat Erdemkilic
 * Changeset : 
 *             06_02_2023 , Flash API functionality is added , beraterdemkilic 
 *             13_02_2023 , Test code is being implemented   , beraterdemkilic
 */

/***********************************************/
/***************** INCLUDE *********************/
/***********************************************/
#include "ESP32_S3_Web.h"

/***********************************************/
/***************** DEFINES *********************/
/***********************************************/

/***********************************************/
/***************** VARIABLES *******************/
/***********************************************/

/***********************************************/
/*********** FUNCTION DECLARATIONS *************/
/***********************************************/

/* INPUT:  void 
 * RETURN: void
 * Initialization routine of the web services */
void setup() 
{
  /* Take a time for user */
  delay(10000);

#if 0
  callMe();
#endif



  esp32s3_Web_FSM();

}

void loop() 
{
  // put your main code here, to run repeatedly:
  while(1)
  {
    Serial.println("Done..!");
    delay(15000);
  }
}
