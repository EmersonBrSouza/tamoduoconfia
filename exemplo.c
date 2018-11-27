//os pacotes que usei como exemplo foram esses, baseado nesse link: https://www.ibm.com/developerworks/community/blogs/messaging/entry/write_your_own_mqtt_client_without_using_any_api_in_minutes1?lang=en
  
  char connectMessage [] = {0x10 //Connect
      , 0x0C + 0x04 //Remaining Length
      , 0x00 //0
      , 0x06 //6
      , 0x4d //M
      , 0x51 //Q
      , 0x49 //I
      , 0x73 //S
      , 0x64 //D
      , 0x70 //P
      , 0x03 //Protocol version = 3
      , 0x02 //Clean session only
      , 0x00 //Keepalive MSB
      , 0x3c //Keepaliave LSB = 60
      , 0x00 //String length MSB
      , 0x02 //String length LSB = 2
      , 0x4d //M
      , 0x70 //P .. Let's say client ID = MP
  };
    
  char publishMessage []= { 0x30 //Publish with QOS 0
      , 0x05 + 0x05 //Remaining length
      , 0x00 //MSB
      , 0x03 //3 bytes of topic
      , 0x61 //a
      , 0x2F ///
      , 0x62 //b (a/b) is the topic
      , 0x48, 0x45 , 0x4c , 0x4c, 0x4f //HELLO is the message  
  };
    
  char disconnectMessage []= { 0xE0 //Disconnect
      , 0x00
  };
  
  int main(){
          
          /*comandos para realizar a configuração wi-fi*/
          
          //abri a conexão TCP
          alt_putstr("AT+CIPSTART=\"TCP\",\"ip\", porta\r\n");
          
        //enviar tamanho da mensagem
        //para obter o tamanho pode usar sizeof(vetor). ex.: sizeof(connectMessage)
        alt_putstr("AT+CIPSEND=18"); //exemplo connect
        
        //enviar mensagem
        int i; //[0 - (tamanho da mensagem-1)]
        //exemplo connect
        for(i=0;i<18; i++){
                alt_putchar(connectMessage[i]);
        }
          alt_putstr("\r\n");
        
        //repete a mesma logica para as outras mensagens
        return 0;
  }