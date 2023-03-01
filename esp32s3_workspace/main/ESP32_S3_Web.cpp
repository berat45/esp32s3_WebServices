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
#include "htmlDefinitions.h"

/***********************************************/
/***************** VARIABLES *******************/
/***********************************************/
esp32s3Web_Singleton* webServerSingleObject = webServerSingleObject->getInstance();         /* One object that rules them all! */

static WiFiServer wifiServerObject(ESP32S3_WEBSERVICE_WIRELESS_SERVER_PORT);
const char* esp32s3_webService_WirelessServerName     = "ESP32S3-WIFI-AP";
const char* esp32s3_webService_WirelessServerPassword = "123456789";

/***********************************************/
/************* FUNCTION PROTOTYPES *************/
/***********************************************/

/***********************************************/
/************ FUNCTION DECLARATIONS ************/
/***********************************************/
/* To make it initializable in the first call to getInstance, make it null */
esp32s3Web_Singleton *esp32s3Web_Singleton::instance = 0;

/***********************************************/
/* Initialize serial line to print out programmer logs */
/***********************************************/
void esp32s3_web_initializeSerialLine(void)
{
  /* Activate the serial line */
  Serial.begin(ESP32S3_WEBSERVICE_UART_BAUDRATE);
  Serial.println("Serial line launch successful!");
}

/***********************************************/
/* Input:
 *  - sizeOfEEprom : Size of EEROM that user needs to allocate
 * Return: 
 *  - Error status. If allocation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 * Initialize EEPROM to reserve sizeOfEEprom_number_of_bytes from Flash memory */
 /***********************************************/
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

/***********************************************/
/* Input:
 *  - paramId     : ID of the parameter that is about to get updated
 *  - newParamStr : Value of the parameter that will be updated to
 * Return: 
 *  - Error status. In case of paramId mismatch exception, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Basically, a wrapper for the class member function to get accessed from different modules */
 /***********************************************/
ESP32S3_RESULT_ENUM esp32s3_Web_UpdateClientParameters(esp32s3Web_Singleton* pWebObject, ESP32S3_PARAMETER_ID_ENUM paramId, String newParamStr)
{
  return pWebObject->setClientParameterAttributes(paramId, newParamStr);
}

/***********************************************/
/* Input:
 *  - pWebObject : Object of the web server that has a buffer that carries the client parameters to be written into flash memory
 * Return: 
 *  - Error status. If wiriting into flash memory operation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Write client parameters into specific String location that are defined as macros. These parameters can not be any
 *  random values or structures. They must be the contents of unique web server object. */
 /***********************************************/
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
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): SSID string has been written into flash memory successfully!");
  
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_PWD, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_PWD)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): PWD string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): PWD string has been written into flash memory successfully!");
  
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_IPADDR, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_IPADDR)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): IPADDR string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): IPADDR string has been written into flash memory successfully!");
  
  if(0 == EEPROM.writeString(ESP32S3_WEBSERVICE_EEPROM_INDEX_ADDR_GW, pWebObject->getClientParameterAttributes(ESP32S3_PARAMETER_GATEWAY)))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): GATEWAY string couldn't be written into flash memory!");
    return ESP32S3_RESULT_ERROR;
  }
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): GATEWAY string has been written into flash memory successfully!");

  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): All parameters are written into flash memory successfully!");
  return ESP32S3_RESULT_OK;
}

/***********************************************/
/* Input:
 *  - pWebObject : Object of the web server that has a buffer that will carry the client parameters stored in the flash memory
 * Return: 
 *  - Error status. If overall read and set operation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Read all attributes of ESP32S3_CLIENT_PARAMS_STRUCT from flash memory. If all values can be
 *  retrieved, set those parameters for webServerSingleObject, must be an input. */
/***********************************************/
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

  Serial.println("esp32s3_Web_ReadClientParamsFromFlashAndSet(): stringSsid: "    + stringSsid);
  Serial.println("esp32s3_Web_ReadClientParamsFromFlashAndSet(): stringPwd: "     + stringPwd);
  Serial.println("esp32s3_Web_ReadClientParamsFromFlashAndSet(): stringIpaddr: "  + stringIpaddr);
  Serial.println("esp32s3_Web_ReadClientParamsFromFlashAndSet(): stringGateway: " + stringGateway);

  /* Write read parameters into the client parameters attributes */
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_SSID, stringSsid))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): SSID string cannot be updated!");
    return ESP32S3_RESULT_ERROR;
  }
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): SSID string updated successfully!");
  
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_PWD, stringPwd))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): PWD string cannot be updated!");
    return ESP32S3_RESULT_ERROR;
  }
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): PWD string updated successfully!");
  
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_IPADDR, stringIpaddr))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): IPADDR string cannot be updated!");
    return ESP32S3_RESULT_ERROR;
  }
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): IPADDR string updated successfully!");
  
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(pWebObject, ESP32S3_PARAMETER_GATEWAY, stringGateway))
  {
    Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): GATEWAY string cannot be updated!");
    return ESP32S3_RESULT_ERROR;
  }  
  
  Serial.println("esp32s3_Web_WriteClientParamsIntoFlash(): GATEWAY string updated successfully!");
  return ESP32S3_RESULT_OK;
}

/***********************************************/
/* Input:
 *  - *uriMsg : Address of the URI string
 * Return: 
 *  - If parse operation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Expected URI pattern is: ssid=X&pwd=Y&ipaddr=Z&gateway=K*/
ESP32S3_RESULT_ENUM esp32s3_Web_ParseNetworkParameters(String uriMsg)
{
  unsigned int iSsid;
  unsigned int iPwd;
  unsigned int iIpaddr;
  unsigned int iGateway;
  unsigned int iEnd;
  String tempoString;
  
  /* Find the index values of the network parameters */
  iSsid    = uriMsg.indexOf(ESP32_S3_HTML_DEFINITIONS_TAG_SSID);
  iPwd     = uriMsg.indexOf(ESP32_S3_HTML_DEFINITIONS_TAG_PWD);
  iIpaddr  = uriMsg.indexOf(ESP32_S3_HTML_DEFINITIONS_TAG_IPADDR);
  iGateway = uriMsg.indexOf(ESP32_S3_HTML_DEFINITIONS_TAG_GATEWAY);
  iEnd     = uriMsg.indexOf(ESP32_S3_HTML_DEFINITIONS_TAG_END);
  
  /* First we need to check whether the incoming message contains correct entries */
  if((uriMsg.length() == 0) || (iSsid < 0) || (iPwd < 0) || (iIpaddr < 0) || (iGateway < 0))
  {
    return ESP32S3_RESULT_ERROR;
  }

  /* Step 1 - Parse for SSID, get rValue and update class SSID attribute */
  tempoString = uriMsg.substring(iSsid+5, iPwd-1);
  Serial.println("esp32s3_Web_ParseNetworkParameters(): SSID tempostring: " + tempoString);
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_SSID, tempoString))
  {
    Serial.println("esp32s3_Web_ParseNetworkParameters(): SSID parameter write error!");
    return ESP32S3_RESULT_ERROR;
  }

  /* Flush temporary string */
  tempoString = "";

  /* Step 2 - Parse for PWD, get rValue and update class PWD attribute */
  tempoString = uriMsg.substring(iPwd+4, iIpaddr-1);
  Serial.println("esp32s3_Web_ParseNetworkParameters(): PWD tempostring: " + tempoString);
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_PWD, tempoString))
  {
    Serial.println("esp32s3_Web_ParseNetworkParameters(): PWD parameter write error!");
    return ESP32S3_RESULT_ERROR;
  }

  /* Flush temporary string */
  tempoString = "";

  /* Step 3 - Parse for IPADDR, get rValue and update class IPADDR attribute */
  tempoString = uriMsg.substring(iIpaddr+7, iGateway-1);
  Serial.println("esp32s3_Web_ParseNetworkParameters(): IPADDR tempostring: " + tempoString);
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_IPADDR, tempoString))
  {
    Serial.println("esp32s3_Web_ParseNetworkParameters(): IPADDR parameter write error!");
    return ESP32S3_RESULT_ERROR;
  }

  /* Flush temporary string */
  tempoString = "";

  /* Step 4 - Parse for GATEWAY, get rValue and update class GATEWAY attribute */
  tempoString = uriMsg.substring(iGateway+8, iEnd);
  Serial.println("esp32s3_Web_ParseNetworkParameters(): GATEWAY tempostring: " + tempoString);
  if(ESP32S3_RESULT_ERROR == esp32s3_Web_UpdateClientParameters(webServerSingleObject, ESP32S3_PARAMETER_GATEWAY, tempoString))
  {
    Serial.println("esp32s3_Web_ParseNetworkParameters(): GATEWAY parameter write error!");
    return ESP32S3_RESULT_ERROR;
  }

  return ESP32S3_RESULT_OK;
}

/***********************************************/
/* Input:
 *  - void
 * Return: 
 *  - Error status. If AP operation fails, return ESP32S3_RESULT_ERROR, ESP32S3_RESULT_OK otherwise
 *
 *  Only get called when local network parameters (client parameters) are null. AP serves a welcome page 
 *  and an input page to the user so that user can type and submit LAN parameters.
 *  
 *  Note: This service is only for one client at a time and works in blocking manner */
/***********************************************/
ESP32S3_RESULT_ENUM esp32s3_Web_AccessPointService()
{
  ESP32S3_RESULT_ENUM apModeActive = ESP32S3_RESULT_OK;
  WiFiClient wifiRemoteClient;
  String uriMessage = "";             /* Holds incoming URI message */
  String currentLine = "";            /* Holds incoming header info (except URI message) */
  char clientMsgInBytes;
  
  Serial.println("Setting AP (Access Point)");
  /* Set AP name and null password */
  WiFi.softAP(esp32s3_webService_WirelessServerName, esp32s3_webService_WirelessServerPassword);

  IPAddress IP = WiFi.softAPIP();
   /* TODO : Remove after test starts */
  Serial.print("AP IP address: ");
  Serial.println(IP); 
  /* TODO : Remove after test ends  */

  /* Listen for incoming connections, non-blocking operation 
   * 
   * Release note: Unless delay is not applied, operation fails.
   * For more, library shall be investigated and updated if possible! */
   wifiServerObject.begin();
  while(apModeActive == ESP32S3_RESULT_OK)
  {
    while(true)
    {
      wifiRemoteClient = wifiServerObject.available(); 
      if (wifiRemoteClient)
      {
        break;
      }
      delay(ESP32S3_WEBSERVICE_WIRELESS_AP_DELAY);
    }
  Serial.println("Connection established..!");

    /* Provide AP services for the remote client */
    while(wifiRemoteClient.connected())
    {
      Serial.println("Debug point 1!");
      /* If there is a new message to read, read it in bytes */
      if(wifiRemoteClient.available())
      {
        Serial.println("Debug point 2!");
        clientMsgInBytes = wifiRemoteClient.read();
        uriMessage += clientMsgInBytes;
      
        /* We need to determine whether URI is completed by checking the value of the last client message.
        * If it is a new line command, two newline characters in a row means that's the end of the client 
        * HTTP request and request for the response */
        if(clientMsgInBytes == ESP32_S3_HTML_DEFINITIONS_NEWLINE)
        {
          Serial.println("Debug point 3!");
          if(currentLine.length() == 0)
          {

            Serial.println("Debug point 4!");
            wifiRemoteClient.println(responseMessageHeaderData);
            /* If incoming URI message contains ssid keyword, it means that this is the second
            * phase of the interface so
            * 1. Parse incoming message and get ssid, password, ip_address and gateway data 
            * 2. Return bye bye web page */
            if(uriMessage.indexOf(ESP32_S3_HTML_DEFINITIONS_TAG_SSID) >= 0)
            {

              /* Parse and set class attributes */
              esp32s3_Web_ParseNetworkParameters(uriMessage);
              /* Time to break the loop */
              apModeActive = ESP32S3_RESULT_ERROR;
              
              Serial.println("Debug point 5!");
              wifiRemoteClient.println(responseMessageFarewellData_segment1);
              wifiRemoteClient.println(responseMessageFarewellData_segment2);
              wifiRemoteClient.println(responseMessageFarewellData_segment3);
              wifiRemoteClient.println(responseMessageFarewellData_segment4);
              wifiRemoteClient.println(responseMessageFarewellData_segment5);
              wifiRemoteClient.println(responseMessageFarewellData_segment6);
            }
            /* If incoming URI message doesn't contain any ssid keyword, it means that it is the first time
            * web page request comes so
            * 1. Send the actual web page so that user can bring in network entries */
            else
            {
              Serial.println("Debug point 6!");
              wifiRemoteClient.println(responseMessagePayloadData_segment1);
              wifiRemoteClient.println(responseMessagePayloadData_segment2);
              wifiRemoteClient.println(responseMessagePayloadData_segment3);
              wifiRemoteClient.println(responseMessagePayloadData_segment4);
              wifiRemoteClient.println(responseMessagePayloadData_segment5);
              wifiRemoteClient.println(responseMessagePayloadData_segment6);
              wifiRemoteClient.println(responseMessagePayloadData_segment7);
              wifiRemoteClient.println(responseMessagePayloadData_segment8);
              wifiRemoteClient.println(responseMessagePayloadData_segment9);
              wifiRemoteClient.println(responseMessagePayloadData_segment10);
            }
          
            // The HTTP response ends with another blank line
            wifiRemoteClient.println();
            // Break out of the while loop
            break;
          }
        }
      }
      else
      {
        /* Pass */
      }
    }
    Serial.println("Debug point 7!");
    // Clear the header variable
    clientMsgInBytes = ' ';
    // Close the connection
    wifiRemoteClient.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    delay(10000);
  }
  
  return ESP32S3_RESULT_OK;
}
