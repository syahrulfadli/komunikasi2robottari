#include <SoftwareSerial.h>
SoftwareSerial BT(2,3);
char musik=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
BT.begin(9600);
Serial.print("#8P1478#9P1426#10P1478#11P1487#12P1533#13P1811#14P1656#15P1522#16P1522#17P1510T500\r\n");
delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
berhenti:
if (BT.available()>0){
  musik=BT.read();
}

while(musik=='0'){
Serial.print("#8P1478#9P1426#10P1478#11P1487#12P1533#13P1811#14P1656#15P1522#16P1522#17P1510T500\r\n");
if (BT.available()>0){
  goto berhenti;
}
delay(500);
}

while(musik=='1'){
Serial.print("#1GC1\r\n");
if (BT.available()>0){ 
  goto berhenti;
}
delay(500);
}
}
