#ifndef WS_COMMON
#define WS_COMMON

#define BAUD_RATE 115200
#define JSON_BUFFER 1024

// Wifi Settings can be overwiriten by enviornment variables with the same name

#ifndef WIFI_SSID
#define WIFI_SSID "MY SSID"
#endif

#ifndef WIFI_PASS
#define WIFI_PASS "my password"
#endif

#define WIFI_CHECK_INTERVAL 100
#define WIFI_MAX_ATTEMPTS 50

// Webserver settings

#define HTTP_PORT 80

// LCD Settings 

#define LCD_RST 19
#define LCD_EN 23
#define LCD_D4 18
#define LCD_D5 17
#define LCD_D6 16
#define LCD_D7 15

// Sensor Setting

#define SENSOR_PIN 27
#define SENSOR_TYPE DHT22

#endif