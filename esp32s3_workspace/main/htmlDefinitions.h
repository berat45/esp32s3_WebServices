#pragma once
#ifndef ESP32S3_HTML_DEFINITIONS_H
#define ESP32S3_HTML_DEFINITIONS_H

/***********************************************/
/****************** ABOUT **********************/
/***********************************************/
/* Author    : Berat Erdemkilic
 * Changeset : 
 *             26_02_2023 , HTML pages are definied , beraterdemkilic 
 */

/***********************************************/
/***************** INCLUDE *********************/
/***********************************************/

/***********************************************/
/***************** DEFINES *********************/
/***********************************************/
#define ESP32_S3_HTML_DEFINITIONS_NEWLINE    (char)'\n'
#define ESP32_S3_HTML_DEFINITIONS_TAG_SSID   (char)"ssid"

/***********************************************/
/**************** VARIABLES ********************/
/***********************************************/
char responseMessageHeaderData[] = "HTTP/1.1 200 OK \nContent-type:text/html\nConnection: close\n ";
char responseMessagePayloadData[] = "<!DOCTYPE html>"
"<html>"
  "<head>"
    "<title>Title of the document</title>"
    "<style>"
      "div {"
        "margin-bottom: 10px;"
      "}"
      "input[type=text] {"
        "padding: 5px;"
        "border: 2px solid #cccccc;"
        "-webkit-border-radius: 5px;"
        "border-radius: 5px;"
      "}"
      "input[type=text]:focus {"
        "border-color: #33333;"
      "}"
      "input[type=submit] {"
        "padding: 5px 15px;"
        "background: #99e0b2;"
        "border: 0 none;"
        "cursor: pointer;"
        "-webkit-border-radius: 5px;"
        "border-radius: 5px;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<h2 style=\"color:red\">Submit your network information</h2>"
    "<form action=\"http://192.168.4.1\" method=\"GET\" id=\"webForm\">"
      "<div>"
        "<label for=\"SSID\">Surname</label>"
        "<input type=\"text\" name=\"ssid\" id=\"id_ssid\" placeholder=\"Please type SSID\" />"
      "</div>"
      "<div>"
        "<label for=\"Password\">Password</label>"
        "<input type=\"text\" name=\"pwd\" id=\"id_pwd\" placeholder=\"Please type Password\" />"
      "</div>"
      "<div>"
        "<label for=\"IP Address\">IP Address</label>"
        "<input type=\"text\" name=\"ipaddr\" id=\"id_ipaddr\" placeholder=\"Please type IP Address\" />"
      "</div>"
      "<div>"
        "<label for=\"Gateway\">Gateway</label>"
        "<input type=\"text\" name=\"gateway\" id=\"id_gateway\" placeholder=\"Please type Gateway Address\" />"
      "</div>"
      "<input type=\"button\" value=\"push\" onclick=\"webFormCallback();\" />"
    "</form>"
  "</body>"
  "<script>"
  // Be sure that each field has been filled in correctly
  "function webFormCallback() "
  "{"
    "if((document.getElementById('id_ssid').value != "") && (document.getElementById('id_pwd').value != "") &&"
       "(document.getElementById('id_ipaddr').value != "") && (document.getElementById('id_gateway').value != ""))"
    "{"
      "document.getElementById('webForm').submit()"
    "}"
    "else"
    "{"
      "alert(\"Please fiil in each network entries\");"
    "}"
  "}"
  "</script>"
"</html>"

char responseMessageFarewellData[] = "<!DOCTYPE html>"
"<html>"
  "<head>"
    "<title>Title of the document</title>"
    "<style>"
      "div {"
        "margin-bottom: 10px;"
      "}"
      "input[type=text] {"
        "padding: 5px;"
        "border: 2px solid #cccccc;"
        "-webkit-border-radius: 5px;"
        "border-radius: 5px;"
      "}"
      "input[type=text]:focus {"
        "border-color: #33333;"
      "}"
      "input[type=submit] {"
        "padding: 5px 15px;"
        "background: #99e0b2;"
        "border: 0 none;"
        "cursor: pointer;"
        "-webkit-border-radius: 5px;"
        "border-radius: 5px;"
      "}"
    "</style>"
  "</head>"
  "<body onload=\"autoClosure();\">"
    "<h2>Thank you for your submission. This page will be closed automatically in 5 seconds.</h2>"
  "</body>"
  "<script type=\"text/javascript\">"
  "function autoClosure()"
  "{"
    "setTimeout(closeMe, 5000);"
  "}"
  "function closeMe()"
  "{"
    "window.close();"
  "}"
  "</script>"
"</html>"











#endif /* ESP32S3_HTML_DEFINITIONS_H */
