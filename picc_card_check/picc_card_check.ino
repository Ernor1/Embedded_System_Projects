
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
char data;
int buzzerPin=8;
int red=6;
int green=7;
MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
void setup() { 
 Serial.begin(9600);
 SPI.begin();
 rfid.PCD_Init();
 Serial.println(F("READING THE CARD UNIQUE ID:"));
 for (byte i = 0; i < 6; i++) {
 key.keyByte[i] = 0xFF;
 }
pinMode(buzzerPin, OUTPUT);
pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
}
void loop(){
 if(!rfid.PICC_IsNewCardPresent()){
 return;
 }
 if(!rfid.PICC_ReadCardSerial()){
 return;
 }
 if (rfid.uid.uidByte[0] != nuidPICC[0] || 
 rfid.uid.uidByte[1] != nuidPICC[1] || 
 rfid.uid.uidByte[2] != nuidPICC[2] || 
 rfid.uid.uidByte[3] != nuidPICC[3] ) {
 for (byte i = 0; i < 4; i++) {
 nuidPICC[i] = rfid.uid.uidByte[i];
 }
 
 Serial.println(F("********************"));
 printHex(rfid.uid.uidByte, rfid.uid.size);
 Serial.println(F("\n********************"));
 }
 else{
 printHex(rfid.uid.uidByte, rfid.uid.size);
 Serial.println(F("\n********************"));
 }
   while(Serial.available()){
   data = Serial.read();
      if (data == '1'){
   digitalWrite (LED_BUILTIN, HIGH);
   digitalWrite (green, HIGH);
   tone(buzzerPin, 10000,500);
   delay(1000);
   noTone(buzzerPin);
   digitalWrite (green, LOW);


  }

  else if (data == '0')
{ 
  digitalWrite (LED_BUILTIN, LOW);
  digitalWrite (red, HIGH);
  tone(buzzerPin,5000,500);
  delay(1000);
  noTone(buzzerPin);
  digitalWrite (red, LOW);

  }

 }


 /*
 * Halt PICC
 * Stop encryption on PCD
 */
 rfid.PICC_HaltA();
 rfid.PCD_StopCrypto1();


}
void printHex(byte *buffer, byte bufferSize){
 for (byte i = 0; i < bufferSize; i++){
 Serial.print(buffer[i] < 0x10 ? " 0" : " ");
 Serial.print(buffer[i], HEX);
 }

} 
