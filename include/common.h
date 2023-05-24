#ifndef WS_COMMON
#define WS_COMMON

#define BAUD_RATE 115200

// Wifi Settings can be overwiriten by enviornment variables with the same name

#ifndef WIFI_SSID
#define WIFI_SSID "MY SSID"
#endif

#ifndef WIFI_PASS
#define WIFI_PASS "my password"
#endif

// Webserver settings

#define HTTP_PORT 80

#endif