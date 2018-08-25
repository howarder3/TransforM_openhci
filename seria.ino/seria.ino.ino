#include <Wire.h>  // Arduino IDE 內建
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>
char dataString[50] = {0};
int a =0; 
int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
int LEDred = 5;
int LEDyellow = 4;
int LEDgreen = 3;
int fog = 8;
int beep = 9;
long duration, cm, inches;

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址

void ringTone(int pin) {
  for (int i=0; i<10; i++) { //repeat 10 times
    tone(pin, 1000);
    delay(50);
    tone(pin, 500);
    delay(50);
    }
  noTone(pin);
  delay(2000);
}

void setup() {
  Serial.begin(115200);  // 用於手動輸入文字
  lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光

  // 閃爍三次
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); // 開啟背光
    delay(250);
    lcd.noBacklight(); // 關閉背光
    delay(250);
  }
  lcd.backlight();

  // 輸出初始化文字
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("Hello! ^_^");
  delay(1000);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print("Welcome !!!");
  delay(3000);
  
  Serial.begin(9600);              //Starting serial communication
  pinMode(trigPin, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin, INPUT);
  pinMode(LEDred, OUTPUT); 
  pinMode(LEDyellow, OUTPUT); 
  pinMode(beep, OUTPUT);
  pinMode(LEDgreen, OUTPUT); 
  pinMode(fog, OUTPUT);
}
  
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);             // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  //inches = (duration/2) / 74; 

  lcd.clear();
  // 讀取新訊息
  while (Serial.available() > 0) {
    // 將訊息顯示在 LCD 上
    lcd.write(cm);
  }
  if(cm <= 10)
  {
    // 告知使用者可以開始手動輸入訊息
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("( ^_^ )");
    lcd.setCursor(0, 1);
    lcd.print("Enjoy Me !!!");
    //lcd.print(cm);
    //lcd.print(" cm");
    digitalWrite(LEDgreen , LOW);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDred, HIGH);
    analogWrite(fog, 255);
  }
  else if(cm <= 100)
  {
    // 告知使用者可以開始手動輸入訊息
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("( ^_^ )");
    lcd.setCursor(0, 1);
    lcd.print("Enjoy Me !!!");
    //lcd.print(cm);
    //lcd.print(" cm");
    digitalWrite(LEDgreen , LOW);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDred, HIGH);
    analogWrite(fog, 0);
  }
  else if(cm <= 200)
  {
    // 告知使用者可以開始手動輸入訊息
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("( >_< ) !!!");
    lcd.setCursor(0, 1);
    lcd.print("Come Here!!!");
    //lcd.print(cm);
    //lcd.print(" cm");
    digitalWrite(LEDgreen , LOW);
    digitalWrite(LEDyellow, HIGH);
    digitalWrite(LEDred, LOW);
    analogWrite(fog, 0);
    tone(beep, 1047*3, 200);
    delay(400);
    tone(beep, 880*3, 100); 
    delay(1000);
  }
  /*else if(cm <= 300)
  {
    // 告知使用者可以開始手動輸入訊息
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("( 0_0 )");
    lcd.setCursor(0, 1);
    lcd.print("I see someone!!!");
    //lcd.print(cm);
    //lcd.print(" cm");
    digitalWrite(LEDgreen , LOW);
    digitalWrite(LEDyellow, HIGH);
    digitalWrite(LEDred, LOW);
    tone(beep, 1047*3, 200);
    delay(400);
    tone(beep, 880*3, 100); 
    delay(1000);
    analogWrite(fog, 32);
    //ringTone(beep);
  }*/
  
  else
  {
    // 告知使用者可以開始手動輸入訊息
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("( -_- ) zzz");
    lcd.setCursor(0, 1);
    lcd.print("NO one here...");
    //lcd.print(cm);
    //lcd.print(" cm");
    digitalWrite(LEDgreen , HIGH);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDred, LOW); 
    analogWrite(fog, 0);
  }
  Serial.print(cm);
  Serial.println();
   
  delay(300);
}
