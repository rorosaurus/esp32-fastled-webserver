/*
   ESP32 FastLED WebServer: https://github.com/jasoncoon/esp32-fastled-webserver
   Copyright (C) 2017 Jason Coon

   Built upon the amazing FastLED work of Daniel Garcia and Mark Kriegsman:
   https://github.com/FastLED/FastLED

   ESP32 support provided by the hard work of Sam Guyer:
   https://github.com/samguyer/FastLED

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void setupWeb() {
  if (apMode) dnsServer.start(53, "*", WiFi.softAPIP());
//  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP

  server.on("/all", HTTP_GET, [](AsyncWebServerRequest *request){
      digitalWrite(led, 0);
      String json = getFieldsJson(fields, fieldCount);
      request->send(200, "text/json", json);
      digitalWrite(led, 1);
  });

  server.on("/fieldValue", HTTP_GET, [](AsyncWebServerRequest *request){
      digitalWrite(led, 0);
      String name = request->getParam("name")->value();
      String value = getFieldValue(name, fields, fieldCount);
      request->send(200, "text/json", value);
      digitalWrite(led, 1);
  });

  server.on("/fieldValue", HTTP_POST, [](AsyncWebServerRequest *request) {
    digitalWrite(led, 0);
    String name = request->getParam("name")->value();
    String value = request->getParam("value")->value();
    Serial.println(name + " " + value);
    String newValue = setFieldValue(name, value, fields, fieldCount, request);
    Serial.println(newValue);
    request->send(200, "text/json", newValue);
    digitalWrite(led, 1);
  });

  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", [](AsyncWebServerRequest *request){
    request->redirect("/index.htm");
  });
  
  server.onNotFound([](AsyncWebServerRequest *request){
    request->redirect("/index.htm");
  });

  server.serveStatic("/", FFat, "/").setCacheControl("max-age=<large prime number>");;

  server.begin();
  Serial.println ( "HTTP server started" );
  webServerStarted = true;
}

void handleWeb() {
  static bool webServerStarted = false;

  // check for connection
  if ( WiFi.status() == WL_CONNECTED || apMode == true) {
    if (!webServerStarted) {
      // turn off the board's LED when connected to wifi
      digitalWrite(led, 1);
      Serial.println();
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      if(apMode) Serial.println(WiFi.softAPIP());
      else Serial.println(WiFi.localIP());
      setupWeb();
    }
  } else {
    // blink the board's LED while connecting to wifi
    static uint8_t ledState = 0;
    EVERY_N_MILLIS(125) {
      ledState = ledState == 0 ? 1 : 0;
      digitalWrite(led, ledState);
      Serial.print (".");
    }
  }
  if (apMode) dnsServer.processNextRequest();
}
