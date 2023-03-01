/*#pragma once*/
#ifndef ESP32S3_WEB_H
#define ESP32S3_WEB_H
/***********************************************/
/****************** ABOUT **********************/
/***********************************************/
/* Author    : Berat Erdemkilic
 * Changeset : 
 *             06_02_2023 , main file definitions and variables are defined , beraterdemkilic 
 */

/***********************************************/
/***************** INCLUDE *********************/
/***********************************************/
#include "EEPROM.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

/***********************************************/
/***************** DEFINES *********************/
/***********************************************/
#define ESP32S3_WEBSERVICE_UART_BAUDRATE            (int)115200     /* Serial line baud rate */
#define ESP32S3_WEBSERVICE_EEPROM_SIZE              (size_t)200     /* Number of bytes to use on the Flash memory */
#define ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_SSID   (int)0          /* Index of SSID on Flash memory in terms of bytes */
#define ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_PWD    (int)50         /* Index of PWD on Flash memory in terms of bytes */
#define ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_IPADDR (int)100        /* Index of IPADDR on Flash memory in terms of bytes */
#define ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_GW     (int)150        /* Index of GATEWAY on Flash memory in terms of bytes */

#define ESP32S3_WEBSERVICE_WIRELESS_SERVER_PORT     (int)80         /* Port number of the web server */
#define ESP32S3_WEBSERVICE_WIRELESS_AP_DELAY        (int)1000       /* Access point mode server listering delay time */

/***********************************************/
/****************** ENUMS **********************/
/***********************************************/
typedef enum
{
  ESP32S3_RESULT_OK = 0,
  ESP32S3_RESULT_ERROR,
  ESP32S3_TOTAL_NUM_OF_RESULTS
}ESP32S3_RESULT_ENUM;

typedef enum
{
  ESP32S3_PARAMETER_SSID = 0,
  ESP32S3_PARAMETER_PWD,
  ESP32S3_PARAMETER_IPADDR,
  ESP32S3_PARAMETER_GATEWAY,
  ESP32S3_TOTAL_NUM_OF_PARAMS
}ESP32S3_PARAMETER_ID_ENUM;

typedef enum
{
  ESP32S3_SET_SSID = 0,
  ESP32S3_SET_PWD,
  ESP32S3_SET_IPADDR,
  ESP32S3_SET_GATEWAY,
  ESP32S3_TOTAL_NUM_OF_SET
}ESP32S3_WEB_REQUEST_TYPE_ENUM;

/* Client parameters - max length of the strings can be ESP32S3_WEBSERVICE_EEPROM_SIZE */
typedef struct
{
  String ssid;
  String pwd;
  String ipAddr;
  String gateway;
}ESP32S3_CLIENT_PARAMS_STRUCT;

/***********************************************/
/***************** CLASSES *********************/
/***********************************************/
/* Singleton class definition */
class esp32s3Web_Singleton {
    private:
    static esp32s3Web_Singleton *instance;

    /* Client parameters */
    bool clientAllParamsUpdated;
    ESP32S3_CLIENT_PARAMS_STRUCT clientParams;
  
   /* Private constructor so that no objects can be created. */
   /* Initial states of class attributes:
    * - clientAllParamsUpdated: false, Parameters will be updated by user from the web interface 
    * - ssid    : null, Parameters will be updated by user from the web interface
    * - pwd     : null, Parameters will be updated by user from the web interface
    * - ipAddr  : null, Parameters will be updated by user from the web interface
    * - gateway : null, Parameters will be updated by user from the web interface
    */
    public:
    esp32s3Web_Singleton() 
    {
       clientAllParamsUpdated = false;
       this->clientParams.ssid    = String("");
       this->clientParams.pwd     = String("");
       this->clientParams.ipAddr  = String("");
       this->clientParams.gateway = String("");
    }

    /* Single instance request will be granted */
    static esp32s3Web_Singleton *getInstance() 
    {
       if (!instance)
       {
         instance = new esp32s3Web_Singleton;
         return instance;
       }
       else
       {
         return NULL;  
       }
    }

    /* Update the class attributes (client parameters) */
    ESP32S3_RESULT_ENUM setClientParameterAttributes(ESP32S3_PARAMETER_ID_ENUM paramId, String newParamStr)
    {
         switch (paramId)
         {
           /* Update parameter SSID */
           case ESP32S3_PARAMETER_SSID:
           {
             this->clientParams.ssid = newParamStr;
             break;
           }
          
           /* Update parameter password */
           case ESP32S3_PARAMETER_PWD:
           {
             this->clientParams.pwd = newParamStr;
             break;
           }
          
           /* Update parameter ip address of the client */
           case ESP32S3_PARAMETER_IPADDR:
           {
             this->clientParams.ipAddr = newParamStr;
             break;
           }

           /* Update parameter gateway */
           case ESP32S3_PARAMETER_GATEWAY:
           {
             this->clientParams.gateway = newParamStr;
             break;
           }

           default:
           {
             Serial.println("Unknown parameter ID detected, failed!");
             return ESP32S3_RESULT_ERROR;
             break;
           }
         }
         return ESP32S3_RESULT_OK;
    }

    /* Client parameters getter member function */
    String getClientParameterAttributes(ESP32S3_PARAMETER_ID_ENUM paramId)
    {
         switch (paramId)
         {
           /* Update parameter SSID */
           case ESP32S3_PARAMETER_SSID:
           {
             return (this->clientParams.ssid);
             break;
           }
          
           /* Update parameter password */
           case ESP32S3_PARAMETER_PWD:
           {
             return (this->clientParams.pwd);
             break;
           }
          
           /* Update parameter ip address of the client */
           case ESP32S3_PARAMETER_IPADDR:
           {
             return (this->clientParams.ipAddr);
             break;
           }

           /* Update parameter gateway */
           case ESP32S3_PARAMETER_GATEWAY:
           {
             return (this->clientParams.gateway);
             break;
           }

           default:
           {
             Serial.println("Unknown parameter ID detected, failed!");
             return String("");
             break;
           }
         }
         return String("");
    }

    /* Length of client parameters getter member function */
    int getClientParameterLength(ESP32S3_PARAMETER_ID_ENUM paramId)
    {
         switch (paramId)
         {
           /* Update parameter SSID */
           case ESP32S3_PARAMETER_SSID:
           {
             return (this->clientParams.ssid.length());
             break;
           }
          
           /* Update parameter password */
           case ESP32S3_PARAMETER_PWD:
           {
             return (this->clientParams.pwd.length());
             break;
           }
          
           /* Update parameter ip address of the client */
           case ESP32S3_PARAMETER_IPADDR:
           {
             return (this->clientParams.ipAddr.length());
             break;
           }

           /* Update parameter gateway */
           case ESP32S3_PARAMETER_GATEWAY:
           {
             return (this->clientParams.gateway.length());
             break;
           }

           default:
           {
             Serial.println("Unknown parameter ID detected, failed!");
             return -1;
             break;
           }
         }
         return -1;
    }
    
};

/***********************************************/
/***************** VARIABLES *******************/
/***********************************************/
extern esp32s3Web_Singleton* webServerSingleObject;

/***********************************************/
/************ FUNCTION PROTOTYPES **************/
/***********************************************/
void esp32s3_web_initializeSerialLine(void);
ESP32S3_RESULT_ENUM esp32s3_Web_UpdateClientParameters(esp32s3Web_Singleton* pWebObject, ESP32S3_PARAMETER_ID_ENUM paramId, String newParamStr);
/* Flash memory function prototypes */
ESP32S3_RESULT_ENUM esp32s3_Web_InitializeEepromInstance(size_t sizeOfEeprom);
ESP32S3_RESULT_ENUM esp32s3_Web_WriteClientParamsIntoFlash(esp32s3Web_Singleton* pWebObject);
ESP32S3_RESULT_ENUM esp32s3_Web_ReadClientParamsFromFlashAndSet(esp32s3Web_Singleton* pWebObject);
/* Wireless networking function prototypes */
ESP32S3_RESULT_ENUM esp32s3_Web_AccessPointService();
ESP32S3_RESULT_ENUM esp32s3_Web_ParseNetworkParameters(String uriMsg);

#endif /* ESP32S3_WEB_H */
