# ESP32 FastLED Web Server
**Work in progress ESP32 port of https://github.com/jasoncoon/esp8266-fastled-webserver**

Update 09/08/2020: rorosaurus updated to use ESPAsyncWebServer as async server library. Also fixed AP mode to work standalone, with no internet connection needed. Large js files are gzipped, and the FatFS filesystem is used (instead of SPIFFS) to minimize chance of starving the watchdog timer while serving so many large files. I'm using [this tool to upload FatFS from Arduino IDE](https://github.com/lorol/arduino-esp32fs-plugin).

Control addressable LEDs with an ESP32 via a web browser over Wi-Fi.

## Features
### Currently Working:
* [x] DemoReel100 patterns
* [x] Static web app file serving from SPIFFS
* [x] Ability to adjust these settings via the HTTP REST API:
   * [x] power on/off
   * [x] brightness
   * [x] pattern
   * [x] autoplay on/off
   * [x] autoplay duration
   * [x] speed
   * [x] palette
   * [x] auto palette cycling
   * [x] palette duration
   * [x] solid color
   * [x] twinkle speed/density
   * [x] fire cooling/sparking
* [x] Setting storage in EEPROM

### Currently Lacking:
* [ ] WebSockets for automatically refreshing/syncing web clients

## Requirements

### Hardware

#### ESP32 Development Board

[![Adafruit HUZZAH32 – ESP32 Feather Board](https://cdn-learn.adafruit.com/assets/assets/000/041/619/thumb100/feather_3405_iso_ORIG.jpg?1494445509)](https://www.adafruit.com/product/3405)

[Adafruit HUZZAH32 – ESP32 Feather Board](https://www.adafruit.com/product/3405)

**or**

[WEMOS LOLIN D32](https://wiki.wemos.cc/products:d32:d32)

**or**

[An ESP32 development board of your choice](https://www.google.com/search?q=esp32+development+board)

#### Addressable LED strip

[![Adafruit NeoPixel Ring](https://www.adafruit.com/images/145x109/1586-00.jpg)](https://www.adafruit.com/product/1586)

[Adafruit NeoPixel Ring](https://www.adafruit.com/product/1586)

#### Other hardware:

* [3.3V to 5V Logic Level Shifter](http://www.digikey.com/product-detail/en/texas-instruments/SN74HCT245N/296-1612-5-ND/277258) (required if LEDs "glitch")
* [Octo Level Shifter FeatherWing](https://www.evilgeniuslabs.org/level-shifter-featherwing) (tidy level shifter PCB)

Recommended by [Adafruit NeoPixel "Best Practices"](https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices) to help protect LEDs from current onrush:
* [1000µF Capacitor](http://www.digikey.com/product-detail/en/panasonic-electronic-components/ECA-1EM102/P5156-ND/245015)
* [300 to 500 Ohm resistor](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/CF14JT470R/CF14JT470RCT-ND/1830342)

### Software

* [Arduino](https://www.arduino.cc/en/main/software)
* [ESP32 Arduino Libraries & Tools](https://github.com/espressif/arduino-esp32)
* [Arduino ESP32 filesystem uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin)

#### Libraries

* [FastLED](https://github.com/FastLED/FastLED)
* [ESP32 Arduino Libraries & Tools](https://github.com/espressif/arduino-esp32)
* [ESP8266/ESP32 WebServer](https://github.com/bbx10/WebServer_tng)
