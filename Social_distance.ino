// 接線 GND==>GND  VCC==>5V  SDA==>A4  SCL==>A5
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
long duration, cm, inches;
LiquidCrystal_I2C lcd(0x27, 20, 4);



const int buzzer = 8;

const int toneTable[7][5]={

    { 66, 131, 262, 523, 1046},  // C Do

    { 74, 147, 294, 587, 1175},  // D Re

    { 83, 165, 330, 659, 1318},  // E Mi

    { 88, 175, 349, 698, 1397},  // F Fa

    { 98, 196, 392, 784, 1568},  // G So

    {110, 220, 440, 880, 1760},  // A La

    {124, 247, 494, 988, 1976}   // B Si

};

char toneName[]="CDEFGAB";

//char beeTone[]="CCGGAAGFFEEDDCGGFFEEDGGFFEEDCCGGAAGFFEEDDC";
char beeTone[]="CCGGAAG";

int beeBeat[]={

    1,1,1,1,1,1,2, 1,1,1,1,1,1,2,

    1,1,1,1,1,1,2, 1,1,1,1,1,1,2,

    1,1,1,1,1,1,2, 1,1,1,1,1,1,2

};

 

int getTone(char symbol) {

    int toneNo = 0;

    for ( int ii=0; ii<7; ii++ ) {

        if ( toneName[ii]==symbol ) {

            toneNo = ii;

            break;

        }

    }

    return toneNo;

}






void setup()
{
  // initialize the LCD
  lcd.begin();

  //lcd.setCursor(0, 0);
  //lcd.print("12345678901234567890");
  //lcd.setCursor(0, 1);
  //lcd.print("This is Line 2!");
  //lcd.setCursor(0, 2);
  //lcd.print("This is Line 3!!");
  //lcd.setCursor(0, 3);
  //lcd.print("This is Line 4!");

  
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出 
  pinMode(echoPin, INPUT);



  pinMode(buzzer,OUTPUT);
  noTone(buzzer);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);             // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  inches = (duration/2) / 74; 
  
  lcd.setCursor(0, 0);
  lcd.print("Distance : ");
  lcd.setCursor(0, 1);
  lcd.print(inches);
  lcd.print("  inch");
  lcd.setCursor(0, 2);
  lcd.print(cm);
  lcd.print("    cm");
  //Serial.print("Distance : ");  
  //Serial.print(inches);
  //Serial.print("in,   ");
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();
  if(cm < 150){    


    int ii, length, toneNo;
    int duration;
    
    length = sizeof(beeTone)-1;

    for ( ii=0; ii<length; ii++ ) {
      toneNo = getTone(beeTone[ii]);
        duration = beeBeat[ii]*333;

        tone(buzzer,toneTable[toneNo][3]);

        delay(duration);

        noTone(buzzer);

    }
  }
    delay(250);
}