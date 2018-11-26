#define WIFI_MODE "AT+CWMODE=3\r\n"
#define WIFI_CONNECT "AT+CWJAP=\"SSID\", \"PASSWORD\"\r\n"

#define TCP_CONNECT "AT+CIPSTART=\"TCP\",\"IP\",PORT\r\n"
#define TCP_DISCONNECT "AT+CIPCLOSE\r\n"

#define MQTT_CONNECT_SIZE "AT+CIPSEND=20\r\n"
#define MQTT_CONNECT "\x10\x12\x00\x04\aMQTT\x04\x02\x00\x14\x00\x06\aNios 2\r\n"

#define MESSAGE_SIZE "AT+CIPSEND=21\r\n"
#define MESSAGE_0 "\x30\x13\x00\x06\aPBL 02Mensagem 01"
#define MESSAGE_1 "\x30\x13\x00\x06\aPBL 02Mensagem 02"
#define MESSAGE_2 "\x30\x13\x00\x06\aPBL 02Mensagem 03"
#define MESSAGE_3 "\x30\x13\x00\x06\aPBL 02Mensagem 04"
#define MESSAGE_4 "\x30\x13\x00\x06\aPBL 02Mensagem 05"

#define MQTT_DISCONNECT_SIZE "AT+CIPSEND=2\r\n"
#define MQTT_DISCONNECT "\xe0\x00\r\n"