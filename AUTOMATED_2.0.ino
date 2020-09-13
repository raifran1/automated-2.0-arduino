/*  
                                                                            PROJETO AUTOMATED HOUSE 2.0 BY RAIFRAN LUCAS  
                                                                            DESCRIÇÃO - AUTOMAÇÃO RESIDENCIAL UTILIZANDO A 
                                                                            INTERNET DAS COISAS

                                                                            - ARDUINO MEGA
                                                                            - BLUETOOTH
                                                                            - LCD
                                                                            - SENSORES
                                                                            - CONTROLE DE LAMPADAS
                                                                            - GOOGLE VOICE
*/

//  COMUNICAÇÕES EXTERNAS
#include "SoftwareSerial.h"
SoftwareSerial bluetooth(17, 16); //TX, RX (Bluetooth)


                                                                                                                        
// LCD IMPORT
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);



// RFID IMPORT
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 9
#define RST_PIN 8
char st[20];
MFRC522 mfrc522(SS_PIN, RST_PIN);



// INICIALIZADORES DO LCD SCROLL
int incomingByte;
int screenWidth = 16;
int screenHeight = 2;
int stringStart, stringStop = 0;
int scrollCursor = screenWidth;
int tamanho = 0;
int estado = 0;


//  VARIÁVEIS DIVERSAS UTILIZADAS
const int jardim = 2;
const int jarvis = 3;
const int mod_noite = 4;
const int chave_geral = 5;
const int sala = 6;
const int quarto = 7;

String line1 = "CASA AUTOMATIZADA, ULTIMO COMANDO:";
String line2 = "SALA LIGADA";
String line3 = "CASA AUTOMATIZADA, ULTIMO COMANDO:";
String line4 = "SALA DESLIGADA";
String line5 = "QUARTO LIGADO";
String line6 = "QUARTO DESLIGADO";
String line7 = "CASA AUTOMATIZADA, ULTIMO COMANDO:";
String line8 = "CASA AUTOMATIZADA, ULTIMO COMANDO:";
String line9 = "JARVIS: ESPERANDO COMANDO DE VOZ...";


//////
String line10 = "JARDIM LIGADO";
String line11 = "CASA AUTOMATIZADA, ULTIMO COMANDO:";
String line12 = "JARDIM DESLIGADO";
String line13 = "CASA AUTOMATIZADA, ULTIMO COMANDO:";
//////



byte byteRead;

//  CONFIGURAÇÕES INICIAIS
void setup()
{
  //  INICIA A LCD
  lcd.begin(screenWidth, screenHeight);

  //  INICIA O BLUETOOTH SERIAL
  bluetooth.begin(9600);
  
  // INICIA A SERIAL
  Serial.begin(9600);
  //Serial2.begin(9600);
  
  // INICIA A SPI BUS 
  SPI.begin();
  // INICIA MFRC522    
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao/TAG do leitor");
  Serial.println();
  
  //  INICIA A MENSAGEM INICIAL NA LCD  
  mensageminicial(); 

  //  INICIA AS PINOUT DOS ATUADORES
  pinMode(jardim, OUTPUT);
  pinMode(jarvis, OUTPUT);
  pinMode(mod_noite, OUTPUT);
  pinMode(chave_geral, OUTPUT);
  pinMode(sala, OUTPUT);
  pinMode(quarto, OUTPUT);


}

void loop()
{
/*  
     INICIALIZADORES DOS COMANDOS DA MAQUETE 
*/

if (estado == 1) {
/*
Serial.println(A2);
 //  LEDS DO JARDIM COM SENSOR LDR
    int estado = analogRead(A2);
    if (estado > 700){
      digitalWrite(jardim,LOW);
    }else{
      digitalWrite(jardim,HIGH);
    }
*/
   
//  INICIO DOS COMANDOS BLE
if (Serial.available()){//verifica se tem dados diponível para leitura
      
//  CASA ATIVADA - LENDO COMANDOS
      byteRead = Serial.read();


/////////////////////////////
// extra jardim nao funciona 
    if (byteRead == 'j') {
      digitalWrite(jardim,HIGH);
      Serial.println("Jardim Ligado");
    }
if (byteRead == 'q') {
      digitalWrite(jardim,LOW);
      Serial.println("Jardim Desligado");
    }
/////////////////////////////



if (byteRead == 'w') {
        digitalWrite(jarvis, LOW);
        Serial.println("ESPERANDO COMANDO DE VOZ");
    }

// LUZ DA SALA CONTROLES
    if (byteRead == 'a') {
        digitalWrite(sala, LOW);
        Serial.println("LUZ DA SALA LIGADA");
    }
    if (byteRead == 'e') {
        digitalWrite(sala, HIGH);
        Serial.println("LUZ DA SALA DESLIGADA");
    }
// LUZ DA SALA CONTROLES




// LUZ DA QUARTO CONTROLES
    if (byteRead == 'i') {
        digitalWrite(quarto, LOW);
        Serial.println("LUZ DO QUARTO LIGADA");
    }
    if (byteRead == 'o') {
        digitalWrite(quarto, HIGH);
        Serial.println("LUZ DO QUARTO DESLIGADA");
    }
// LUZ DA QUARTO CONTROLES



// LUZES NOTURNAS CONTROLES ----------------------------------- VERIFICAR
    if (byteRead == 'p') {
        digitalWrite(mod_noite, LOW);
        digitalWrite(sala,HIGH);
        digitalWrite(quarto,HIGH);
        Serial.println("MODO NOTURNO ATIVO");
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("MODO NOTURNO");
        lcd.setCursor(4, 1);
        lcd.print("ATIVADA");
    }
    if (byteRead == 'n') {
        digitalWrite(mod_noite, HIGH);
        Serial.println("MODO NOTURNO DESATIVO");
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("MODO NOTURNO");
        lcd.setCursor(3, 1);
        lcd.print("DESATIVADA");
    }
// LUZES NOTURNAS CONTROLES ----------------------------------- VERIFICAR


// CHAVE GERAL - COMANDO DE SAIDA/ENTRADA NA CASA
    if (byteRead == 'k') {
        digitalWrite(jardim, HIGH);
        digitalWrite(jarvis,HIGH);
        digitalWrite(mod_noite,HIGH);
        digitalWrite(chave_geral,HIGH);
        digitalWrite(quarto,HIGH);
        digitalWrite(sala,HIGH);
        Serial.println("CHAVE GERAL DESATIVADA");
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("CHAVE GERAL");
        lcd.setCursor(3, 1);
        lcd.print("DESATIVADA");
    } 
    if (byteRead == 'y') {
        digitalWrite(chave_geral,LOW);
        Serial.println("CHAVE GERAL ATIVADA");
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("CHAVE GERAL");
        lcd.setCursor(4, 1);
        lcd.print("ATIVADA");
    }
// CHAVE GERAL - COMANDO DE SAIDA/ENTRADA NA CASA

   
/*

        VERIFICAR SE COMANDOS BLE SE FECHA AKI
  
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
}    

    
    if (byteRead == 'w') {
      lcd.setCursor(scrollCursor, 0);
      lcd.print(line9.substring(stringStart, stringStop));
      lcd.setCursor(2, 1);
      lcd.print("OLA RAIFRAN");
      delay(500);
      scroll_sup();
      tamanho = line1.length();
      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
    if (byteRead == 'a') {
      lcd.setCursor(scrollCursor, 0);
      lcd.print(line1.substring(stringStart, stringStop));
      lcd.setCursor(2, 1);
      lcd.print(line2);
      delay(500);
      scroll_sup();
      tamanho = line1.length();
      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
    if ( byteRead == 'e') {
      lcd.setCursor(scrollCursor, 0);
      lcd.print(line3.substring(stringStart, stringStop));
      lcd.setCursor(1, 1);
      lcd.print(line4);
      delay(500);
      scroll_sup();
      tamanho = line3.length();

      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
    if (byteRead == 'i') {

      lcd.setCursor(scrollCursor, 0);
      lcd.print(line8.substring(stringStart, stringStop));
      lcd.setCursor(2, 1);
      lcd.print(line5);
      delay(500);
      scroll_sup();
      tamanho = line8.length();
      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
    if (byteRead == 'o') {

      lcd.setCursor(scrollCursor, 0);
      lcd.print(line7.substring(stringStart, stringStop));
      lcd.setCursor(0, 1);
      lcd.print(line6);
      delay(500);
      scroll_sup();
      tamanho = line7.length();
      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
////////////////////////////////////////////////////////////////
if (byteRead == 'j') {

      lcd.setCursor(scrollCursor, 0);
      lcd.print(line11.substring(stringStart, stringStop));
      lcd.setCursor(0, 1);
      lcd.print(line10);
      delay(500);
      scroll_sup();
      tamanho = line11.length();
      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
if (byteRead == 'q') {

      lcd.setCursor(scrollCursor, 0);
      lcd.print(line13.substring(stringStart, stringStop));
      lcd.setCursor(0, 1);
      lcd.print(line12);
      delay(500);
      scroll_sup();
      tamanho = line13.length();
      if (stringStart == tamanho)
      {
        stringStart = 0;
        stringStop = 0;
      }
    }
    ///////////////////////////////////////////////////////

}











/*  
 
     Busca novos cartões RFID
     LÊ O CODIGO TAG/CARTÃO RESPECTIVO
  

*/

   
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um cartão a ser lido
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Mostra ID na serial
  Serial.print("ID da tag:");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();











// CONDICIONAIS DE LEITURA DE TAG -----------------------------------------------------------------------------


// CASO A TAG/CARTÃO LIDO FOR DE CODIGO "F0 DB 5E 56"
  if (conteudo.substring(1) == "F0 DB 5E 56") //ID CARTÃO
  {
    // ATIVA TODOS OS COMANDOS DA CASA 
    estado = 1; 
    
    //  ATIVA O RELÉ GERAL
    digitalWrite(chave_geral, LOW);
      digitalWrite(jardim,HIGH);

    //  MOSTRA UMA MENSAGEM NA TELA DO LCD
    Serial.println("Ola RAIFRAN LUCAS !");
    Serial.println("BEM VINDO!");
    Serial.println("CASA ATIVADA");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Ola RAIFRAN !");
    lcd.setCursor(0, 1);
    lcd.print("Acesso Liberado!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Bem Vindo!");
    lcd.setCursor(2, 1);
    lcd.print("Casa Ativada");
    delay(3000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Esperando");
    lcd.setCursor(3, 1);
    lcd.print("Comandos...");
  }


  // CASO A TAG/CARTÃO LIDO FOR DE CODIGO "E9 61 25 D9"
  if (conteudo.substring(1) == "E9 61 25 D9") //UID 2 - TAG
  {
    // DESATIVA TODOS OS COMANDOS DA CASA
    estado = 0; 

    //  DESATIVA O RELÉ GERAL E TODOS OS RELÉS ATIVADOS
    digitalWrite(chave_geral, HIGH);
    digitalWrite(quarto, HIGH);
    digitalWrite(sala, HIGH);
      digitalWrite(jardim,LOW);
      digitalWrite(jardim,LOW);

    //  MOSTRA UMA MENSAGEM NA TELA DO LCD
    Serial.println("Ate mais... !");
    Serial.println("Casa Segura!");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Ola RAIFRAN!");
    lcd.setCursor(0, 1);
    lcd.print("Acesso Liberado !");
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Ate mais!");
    lcd.setCursor(0, 1);
    lcd.print("Casa Desativada");
    delay(3000);
    mensageminicial();
  }
// CONDICIONAIS DE LEITURA DE TAG -----------------------------------------------------------------------------
  
}




//  FUNÇÃO INICIALIZADORA DA LCD
void mensageminicial()
{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AUTOMATED  HOUSE");
      lcd.setCursor(0, 1);
      lcd.print("*    V. 2.0    *");
      //lcd.print("MODEL BY RAIFRAN");
      delay(1500);
      lcd.clear();
      lcd.print(" APROXIME O SEU");
      lcd.setCursor(0, 1);
      lcd.print("  CARTAO .....");
      digitalWrite(chave_geral, HIGH);
    digitalWrite(quarto, HIGH);
    digitalWrite(sala, HIGH);

}




//  FUNÇÃO INICIALIZADORA DO SCROLLUP DA LCD
void scroll_sup()
{
  lcd.clear();
  if (stringStart == 0 && scrollCursor > 0)
  {
    scrollCursor--;
    stringStop++;
  } else if (stringStart == stringStop) {
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  } else if (stringStop == line1.length() && scrollCursor == 0) {
    stringStart++;
  } else {
    stringStart++;
    stringStop++;
  }
}
