#include <SoftwareSerial.h>

SoftwareSerial BT1(2, 3);
SoftwareSerial BT2(10, 11);

#define ledIndikator 6 //indikator koneksi bluetooth
#define ledMusik 7 //indikator musik
#define BT1_State 8
#define BT2_State 12
#define BT_RSTin 5
#define BT_RSTout 4

char status = '0';
int audioValue = 0;
int counterStop = 0;
int counterStart = 0;
int ledState = 0;
unsigned long previousMillis = 0;
long interval = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledIndikator, OUTPUT);
  pinMode(ledMusik, OUTPUT);
  pinMode(BT1_State, INPUT);
  pinMode(BT2_State, INPUT);
  pinMode(BT_RSTin, INPUT_PULLUP);
  pinMode(BT_RSTout, OUTPUT);

  BT1.begin(9600);
  BT2.begin(9600);

  digitalWrite(BT_RSTout, HIGH);
}

void loop() {
  // Blok indikator Bluetooth
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledIndikator, ledState);
  }

  //Blok tombol reset koneksi Bluetooth
  if (digitalRead(BT_RSTin) == LOW) {
    digitalWrite(BT_RSTout, LOW);
  }
  else {
    digitalWrite(BT_RSTout, HIGH);
  }

  // Blok baca data audio dengan sampling -- secara berulang untuk mendapat nilai yg lebih konsisten
  for (int i = 0; i <= 50; i++) {
    audioValue = analogRead(A0);
  }

  int audioValueMapped = map(audioValue, 0, 1023, 0, 1000);// mapping nilai analog menjadi 0-1000(nggk terlalu berpengaruh mungkin ntar dihapus)
  
  if ((digitalRead(BT1_State == HIGH)) && (digitalRead(BT2_State == HIGH))) { //indikator kedua bluetooth tersambung
    interval = 2000;
  }
  else if ((digitalRead(BT1_State == LOW)) && (digitalRead(BT2_State == HIGH))) { //indikator bluetooth2 tersambung
    interval = 1000;
  }
  else if ((digitalRead(BT1_State == HIGH)) && (digitalRead(BT2_State == LOW))) { //indikator bluetooth1 tersambung
    interval = 500;
  }
  else if ((digitalRead(BT1_State == LOW)) && (digitalRead(BT2_State == LOW))) { //indikator kedua bluetooth tidak tersambung
    interval = 100;
  }

  // Blok pengiriman serial bluetooth
  if (counterStop == 16) {
    BT1.write("0");//stop tari, mengirim nilai "0" jika tidak ada musik
    BT2.write("0");
    counterStop = 0;
    counterStart = 0;
  }
  if (counterStart == 1) {
    BT1.write("1");//mulai tari, mengirim nilai "1" jika ada musik
    BT2.write("1");

  }
  if (audioValueMapped > 0) {
    digitalWrite(ledMusik, HIGH); //indikator musik on
    counterStart++;
    counterStop = 0;
  }
  else {
    digitalWrite(ledMusik, LOW); //indikator musik off
    counterStop++;
  }
}
