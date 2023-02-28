#pragma once
#ifndef ESP32S3_HTML_DEFINITIONS_H
#define ESP32S3_HTML_DEFINITIONS_H

/***********************************************/
/****************** ABOUT **********************/
/***********************************************/
/* Author    : Berat Erdemkilic
 * Changeset : 
 *             26_02_2023 , HTML pages are definied , beraterdemkilic 

 * Note: Since WiFiClient.h works based on TCP_MSS
 * as 1460 bytes, we need to divide each message into 1460 byte max */

/***********************************************/
/***************** INCLUDE *********************/
/***********************************************/

/***********************************************/
/***************** DEFINES *********************/
/***********************************************/
#define ESP32_S3_HTML_DEFINITIONS_NEWLINE    '\n'
#define ESP32_S3_HTML_DEFINITIONS_TAG_SSID   "ssid"

/***********************************************/
/**************** VARIABLES ********************/
/***********************************************/
char responseMessageHeaderData[] = "HTTP/1.1 200 OK \nContent-type:text/html\nConnection: close\n";
char responseMessagePayloadData_segment1[] =      "<!DOCTYPE html>";
char responseMessagePayloadData_segment2[]  =     "<html>"
                                                  "<head>";
char responseMessagePayloadData_segment3[]  =     "<title>Title of the document</title>"
                                                  "<style>"
                                                  "div {"
                                                  "margin-bottom: 10px;"
                                                  "}";
char responseMessagePayloadData_segment4[]  =     "input[type=text] {"
                                                  "padding: 5px;"
                                                  "border: 2px solid #cccccc;"
                                                  "-webkit-border-radius: 5px;"
                                                  "border-radius: 5px;";
char responseMessagePayloadData_segment5[]  =     "}"
                                                  "input[type=text]:focus {"
                                                  "border-color: #33333;"
                                                  "}"
                                                  "input[type=submit] {"
                                                  "padding: 5px 15px;"
                                                  "background: #99e0b2;";
char responseMessagePayloadData_segment6[]  =     "border: 0 none;"
                                                  "cursor: pointer;"
                                                  "-webkit-border-radius: 5px;"
                                                  "border-radius: 5px;"
                                                  "}"
                                                  "</style>"
                                                  "</head>";
char responseMessagePayloadData_segment7[]  =     "<body>"
                                                  "<h2 style=\"color:red\">Submit your network information</h2>"
                                                  "<form action=\"http://192.168.4.1\" method=\"GET\" id=\"webForm\">"
                                                  "<div>"
                                                  "<label for=\"SSID\">Surname</label>"
                                                  "<input type=\"text\" name=\"ssid\" id=\"id_ssid\" placeholder=\"Please type SSID\" />"
                                                  "</div>";
char responseMessagePayloadData_segment8[]  =     "<div>"
                                                  "<label for=\"Password\">Password</label>"
                                                  "<input type=\"text\" name=\"pwd\" id=\"id_pwd\" placeholder=\"Please type Password\" />"
                                                  "</div>"
                                                  "<div>"
                                                  "<label for=\"IP Address\">IP Address</label>"
                                                  "<input type=\"text\" name=\"ipaddr\" id=\"id_ipaddr\" placeholder=\"Please type IP Address\" />"
                                                  "</div>"
                                                  "<div>";
char responseMessagePayloadData_segment9[]  =     "<label for=\"Gateway\">Gateway</label>"
                                                  "<input type=\"text\" name=\"gateway\" id=\"id_gateway\" placeholder=\"Please type Gateway Address\" />"
                                                  "</div>"
                                                  "<input type=\"button\" value=\"push\" onclick=\"webFormCallback();\" />"
                                                  "</form>"
                                                  "</body>"
                                                  "<script>"
                                                  // Be sure that each field has been filled in correctly
                                                  "function webFormCallback() "
                                                  "{";
char responseMessagePayloadData_segment10[] =     "if((document.getElementById('id_ssid').value != \"\") && (document.getElementById('id_pwd').value != \"\") &&"
                                                  "(document.getElementById('id_ipaddr').value != \"\") && (document.getElementById('id_gateway').value != \"\"))"
                                                  "{"
                                                  "document.getElementById('webForm').submit()"
                                                  "}"
                                                  "else"
                                                  "{"
                                                  "alert(\"Please fiil in each network entries\");"
                                                  "}"
                                                  "}"
                                                  "</script>"
                                                  "</html>";

char responseMessageFarewellData_segment1[] =   "<!DOCTYPE html>"
                                                "<html>"
                                                "<head>";
char responseMessageFarewellData_segment2[] =   "<title>Title of the document</title>"
                                                "<style>"
                                                "div {"
                                                "margin-bottom: 10px;"
                                                "}";
char responseMessageFarewellData_segment3[] =   "input[type=text] {"
                                                "padding: 5px;"
                                                "border: 2px solid #cccccc;"
                                                "-webkit-border-radius: 5px;"
                                                "border-radius: 5px;"
                                                "}"
                                                "input[type=text]:focus {"
                                                "border-color: #33333;"
                                                "}";
char responseMessageFarewellData_segment4[] =   "input[type=submit] {"
                                                "padding: 5px 15px;"
                                                "background: #99e0b2;"
                                                "border: 0 none;"
                                                "cursor: pointer;"
                                                "-webkit-border-radius: 5px;"
                                                "border-radius: 5px;"
                                                "}"
                                                "</style>"
                                                "</head>";
char responseMessageFarewellData_segment5[] =   "<body onload=\"autoClosure();\">"
                                                "<h2>Thank you for your submission. This page will be closed automatically in 5 seconds or close it manually.</h2>" /* Some browsers prevent automatic closure because of security reasons */
                                                "</body>"
                                                "<script type=\"text/javascript\">"
                                                "function autoClosure()"
                                                "{"
                                                "setTimeout(closeMe, 5000);";
char responseMessageFarewellData_segment6[] =   "}"
                                                "function closeMe()"
                                                 "{"
                                                 "window.close();"
                                                 "}"
                                                 "</script>"
                                                 "</html>";



#endif /* ESP32S3_HTML_DEFINITIONS_H */
