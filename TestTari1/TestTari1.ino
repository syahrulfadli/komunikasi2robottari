#include <SoftwareSerial.h>
SoftwareSerial BT(2,3);
char musik=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
BT.begin(9600);
Serial.print("#1P1522#2P567#3P789#4P1478#5P1500#6P1500#7P1500#8P1500#9P1544#10P1478#11P1500#12P1382#13P1525#14P1411#15P1522#16P1514#17P1329#18P1500#19P1500#20P1478#21P1500#22P900#23P2322#24P1500T450\r\n");
delay(450);
}

void loop() {
  // put your main code here, to run repeatedly:
berhenti:
if (BT.available()>0){
  musik=BT.read();
}

while(musik=='0'){
Serial.print("#1P1522#2P567#3P789#4P1478#5P1500#6P1500#7P1500#8P1500#9P1544#10P1478#11P1500#12P1382#13P1525#14P1411#15P1522#16P1514#17P1329#18P1500#19P1500#20P1478#21P1500#22P900#23P2322#24P1500T450\r\n");
if (BT.available()>0){
  goto berhenti;
}
delay(450);
}

while(musik=='1'){
Serial.print("#1GC1\r\n");
if (BT.available()>0){ 
  goto berhenti;
}
delay(450);
}
}
