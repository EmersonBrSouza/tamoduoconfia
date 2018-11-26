#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_uart_regs.h"
#include "io.h"
#include <string.h>
#define NUMTRY 5

char connectMessage[] = { 0x10 // Connect
			, 0x0C + 0x04 // Remaining Length
			, 0x00 // 0
			, 0x06 // 6
			, 0x4d // M
			, 0x51 // Q
			, 0x49 // I
			, 0x73 // S
			, 0x64 // D
			, 0x70 // P
			, 0x03 // Protocol version = 3
			, 0x02 // Clean session only
			, 0x00 // Keepalive MSB
			, 0x3c // Keepaliave LSB = 60
			, 0x00 // String length MSB
			, 0x02 // String length LSB = 2
			, 0x4d // M
			, 0x70 // P .. Let's say client ID = MP
	};
char publishMessage []= { 0x30 // Publish with QOS 0
			, 0x05 + 0x05 // Remaining length
			, 0x00 // MSB
			, 0x03 // 3 bytes of topic
			, 0x61 // a
			, 0x2F ///
			, 0x62 // b (a/b) is the topic
			, 0x48, 0x45, 0x4c, 0x4c, 0x4f // HELLO is the message
	};


void delay(int a) { //bounce
	volatile int i = 0;
	while (i < a * 10000) {
		i++;
	}
}

void write(char * v) {
	int i = 0;
	while (v[i] != '\0') {
		IOWR_ALTERA_AVALON_UART_TXDATA(RS232_BASE, v[i]);
		delay(1);
		i++;
	}

}

void writeEsp(char * v) {
	int i = 0;
	while (v[i] != '\0') {
		IOWR_ALTERA_AVALON_UART_TXDATA(ESP_BASE, v[i]);
		usleep(1000);
		i++;
	}

}

void sendCommand(char * cmd) {
	alt_putstr(cmd);
	char a;
	int control = 1;

	while(control){
		if(IORD_ALTERA_AVALON_UART_STATUS(ESP_BASE)&(1<<6)){
			control = 0;
			do {
				a = IORD_ALTERA_AVALON_UART_RXDATA(ESP_BASE);
				IOWR_ALTERA_AVALON_UART_TXDATA(RS232_BASE, a);
			} while (a != 'K');

		}
	}

}
void espTest() {
	sendCommand("AT\r\n");
}
void espMode() {
	sendCommand("AT+CWMODE=1\r\n");
}

void espConnect(char * ssid, char * pass) {
	char net[80] = "AT+CWJAP=\"";
	strcat(net, ssid);
	strcat(net, "\",\"");
	strcat(net, pass);
	strcat(net, "\"\r\n");
	sendCommand(net);
}

void espOpenTCPConnect(char * ip, char * port){
	char net [] = "AT+CIPSTART=\"TCP\",\"";
	strcat(net, ip);
	strcat(net, "\",");
	strcat(net, port);
	strcat(net, "\r\n");
	sendCommand(net);
}

void espTCPSend(char * message){

	//enviando tamanho da mensagem
	int i = strlen(message);
	char t[2];
	if(i<10){
		t [0]= i+48;
	}else{
		t[0] = i/10+48;
		t[1] = i%10+48;
	}
	char net [] = "AT+CIPSEND=";
	strcat(net, t);
	strcat(net, "\r\n");
	sendCommand(net);

	/*char net1 = "AT+CIPSEND=\"";
	strcat(net, message);
	strcat(net, "\"\r\n");*/
}

int main() {
	/*espTest();
	espMode();
	espConnect("ssid", "senha");*/
	//espOpenTCPConnect("192.168.16.102", "1883");
	sendCommand("AT+CIPSTART=\"TCP\",\"192.168.16.102\",1883\r\n");

	sendCommand("AT+CIPSEND=20\r\n");
	int i;
	for(i=0;i<18;i++){
		alt_putchar(connectMessage[i]);
	}
	sendCommand("\r\n");
	//espTCPSend(connectMessage);
	//espOpenTCPConnect("192.168.16.102","1883");
	//espTCPSend(publishMessage);
}
