#pragma once
/***********************************************/
/****************** ABOUT **********************/
/***********************************************/
/* Author    : Berat Erdemkilic
 * Changeset : 
 *             08_02_2023 , EEPROM functionalities are added (read / write) , beraterdemkilic 
 */

/***********************************************/
/***************** INCLUDE *********************/
/***********************************************/
#include "ESP32_S3_Web.h"

/***********************************************/
/***************** VARIABLES *******************/
/***********************************************/
const esp32s3Web_Singleton* webServerSingleObject = webServerSingleObject->getInstance();         /* One object that rules them all! */

/***********************************************/
/************ FUNCTION DECLARATIONS **************/
/***********************************************/
/* To make it initializable in the first call to getInstance, make it null */
esp32s3Web_Singleton *esp32s3Web_Singleton::instance = 0;

/* Initialize serial line to print out programmer logs */
void esp32s3_web_initializeSerialLine(void)
{
  /* Activate the serial line */
  Serial.begin(ESP32S3_WEBSERVICE_UART_BAUDRATE);
  Serial.println("Serial line launch successful!");
}

/* Input:
 *  - sizeOfEEprom : Size of EEROM that user needs to allocate
 * Return: 
 *  - Error status. If allocation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 * Initialize EEPROM to reserve sizeOfEEprom_number_of_bytes from Flash memory */
ESP32S3_RESULT_ENUM esp32s3_Web_InitializeEepromInstance(size_t sizeOfEeprom)
{
  Serial.println("Initializing EEPROM/Flash unit!");
  if(false == EEPROM.begin(sizeOfEeprom))
  {
    Serial.println("EEPROM/Flash initialization failed!");
    return ESP32S3_RESULT_ERROR;
  }
  return ESP32S3_RESULT_OK;
}

/* Input:
 *  - paramId     : ID of the parameter that is about to get updated
 *  - newParamStr : Value of the parameter that will be updated to
 * Return: 
 *  - Error status. In case of paramId mismatch exception, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Basically, a wrapper for the class member function to get accessed from different modules */
ESP32S3_RESULT_ENUM esp32s3_Web_UpdateClientParameters(esp32s3Web_Singleton* pWebObject, ESP32S3_PARAMETER_ID_ENUM paramId, String newParamStr)
{
  return pWebObject->setClientParameterAttributes(paramId, newParamStr);
}
 
/* Input:
 *  - pWebObject : Object of the web server that has a buffer that carries the client parameters to be written into flash memory
 * Return: 
 *  - Error status. If wiriting into flash memory operation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Write client parameters into specific String location that are defined as macros. These parameters can not be any
 *  random values or structures. They must be the contents of unique web server object. */
ESP32S3_RESULT_ENUM esp32s3_Web_WriteClientParamsIntoFlash(esp32s3Web_Singleton* pWebObject)
{
  /* Error check - Input cannot be null */
  if(NULL == pWebObject)
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): Null web object!");
    return ESP32S3_RESULT_ERROR;
  }
         
  /* Error check - Input parameters cannot be empty */
  if((pWebObject->getClientParameterLength(ESP32S3_PARAMETER_SSID) == 0)   || (pWebObject->getClientParameterLength(ESP32S3_PARAMETER_PWD) == 0) ||
     (pWebObject->getClientParameterLength(ESP32S3_PARAMETER_IPADDR) == 0) || (pWebObject->getClientParameterLength(ESP32S3_PARAMETER_GATEWAY) == 0))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): Empty string content detected!");
    return ESP32S3_RESULT_ERROR;
  }

  /* It is time to write Strings into the flash memory one by one */
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_SSID, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_SSID)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): SSID string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_PWD, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_PWD)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): PWD string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_IPADDR, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_IPADDR)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): IPADDR string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_GW, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_GATEWAY)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): GATEWAY string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }

  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): All parameters are written into flash memory successfully!");
  return ESP32S3_RESULT_OK;
}

/* Input:
 *  - pWebObject : Object of the web server that has a buffer that will carry the client parameters stored in the flash memory
 * Return: 
 *  - Error status. If overall read and set operation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Read all attributes of ESP32S3_CLIENT_PARAMS_STRUCT from flash memory. If all values can be
 *  retrieved, set those parameters for webServerSingleObject, must be an input. */
ESP32S3_RESULT_ENUM esp32s3_Web_ReadClientParamsFromFlashAndSet(esp32s3Web_Singleton* pWebObject)
{
  /* It is time to reaed client parameters from flash memory one by one */
  String stringSsid    = EEPROM.readString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_SSID);    /* To check null-check, dummystring */
  String stringPwd     = EEPROM.readString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_PWD);     /* To check null-check, dummystring */
  String stringIpaddr  = EEPROM.readString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_IPADDR);  /* To check null-check, dummystring */
  String stringGateway = EEPROM.readString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_GW);      /* To check null-check, dummystring */
  
  /* Error check - Input cannot be null */
  if(NULL == pWebObject)
  {
    Serial.println("esp32s3_Web_ReadClientParamsFromFlashAndSet(): Null web object!");
    return ESP32S3_RESULT_ERROR;
  }
  
  /* Error check - String null check */
  if((String() == stringSsid) || (String() == stringPwd) || (String() == stringIpaddr) || (String() == stringGateway))
  {
    Serial.println("esp32s3_Web_ReadClientParamsFromFlashAndSet(): EEPROM client parameters are null!");
    return ESP32S3_RESULT_ERROR;
  }

  /* Write read parameters into the client parameters attributes */
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_SSID, stringSsid))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): SSID string couldn't be read from flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_PWD, stringPwd))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): PWD string couldn't be read from flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_IPADDR, stringIpaddr))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): IPADDR string couldn't be read from flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_GATEWAY, stringGateway))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): GATEWAY string couldn't be read from flash memory!");
    return ESP32S3_RESULT_ERROR;
  }  
}