#include <SoftwareSerial.h>

#define ledpin 5
int status ;

//SoftwareSerial BluetoothSerial(2,3); //pin: 2 RX; 3 TX for bluetooth

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);// Komunikasi USC

//BluetoothSerial.begin(9600);// komunikasi Bluetooth HC-05

pinMode(ledpin,OUTPUT);

digitalWrite(ledpin,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0){
  Serial.write("Data baru diterima:\r\n");
  status=Serial.read();
  Serial.println(status);
  if(status==48){
  Serial.write("LED inaktif\r\n");
  }
  if(status==49){
  Serial.write("LED aktif\r\n");
  }
  Serial.println(status);
}

  if (status==49){
  digitalWrite(ledpin,1);
  }
if(status==48){
  digitalWrite(ledpin,0);
}
}
