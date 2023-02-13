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
esp32s3Web_Singleton* webServerSingleObject = webServerSingleObject->getInstance();         /* One object that rules them all! */

String ssidDummyString     = "";
String pwdDummyString      = "";
String ipAddrDummyString   = "";
String gatewayDummyString  = "";

/***********************************************/
/*********** FUNCTION DECLARATIONS *************/
/***********************************************/
void test_updateClientParameters()
{
  if(ESP32S3_RESULT_OK != esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_SSID,    ssidDummyString))
  {
    Serial.println("esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_SSID,    ssidDummyString)");
    return;
  }
  if(ESP32S3_RESULT_OK != esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_PWD,     pwdDummyString))
  {
    Serial.println("esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_PWD,     pwdDummyString)");
    return;
  }
  if(ESP32S3_RESULT_OK != esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_IPADDR,  ipAddrDummyString))
  {
    Serial.println("esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_IPADDR,  ipAddrDummyString)");
    return;
  }
  if(ESP32S3_RESULT_OK != esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_GATEWAY, gatewayDummyString))
  {
    Serial.println("esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_GATEWAY, gatewayDummyString)");
    return;
  }
}

/* INPUT:  void 
 * RETURN: void
 * Initialization routine of the web services */
void setup() 
{
  /* Take a time for user */
  delay(10000);
  
  /* Initialize the serial line */
  esp32s3_web_initializeSerialLine();

  /* Initialize EEPROM */
  if(ESP32S3_RESULT_OK != esp32s3_Web_InitializeEepromInstance(ESP32S3_WEBSERVICE_EEPROM_SIZE))
  {
    Serial.println("esp32s3_Web_InitializeEepromInstance(ESP32S3_WEBSERVICE_EEPROM_SIZE) failed!");
    return;
  }

  ssidDummyString     = "1testDummyStringSSID";
  pwdDummyString      = "2testDummyStringPWD";
  ipAddrDummyString   = "3testDummyStringIPADDR";
  gatewayDummyString  = "4testDummyStringGATEWAY";

  /* Set client parameters with test values */
  test_updateClientParameters();
  
  /* Write updated client parameters into Flash memory */
  esp32s3_Web_WriteClientParamsIntoFlash(webServerSingleObject);

  ssidDummyString     = "";
  pwdDummyString      = "";
  ipAddrDummyString   = "";
  gatewayDummyString  = "";

  /* Set client parameters with null values */
  test_updateClientParameters();

  /* Read client parameters from Flash memory */
  esp32s3_Web_ReadClientParamsFromFlashAndSet(webServerSingleObject);
 
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
