int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
int LEDred = 5;
int LEDyellow = 4;
int LEDgreen = 3;
int fog = 8;
long duration, cm, inches;
 
void setup() {
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin, INPUT);
  pinMode(LEDred, OUTPUT); 
  pinMode(LEDyellow, OUTPUT); 
  pinMode(LEDgreen, OUTPUT); 
  pinMode(fog, OUTPUT);
  //digitalWrite(fog, HIGH);
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
  //inches = (duration/2) / 74; 

  if(cm <= 50)
  {
    digitalWrite(LEDgreen , LOW);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDred, HIGH);
    analogWrite(fog, 0);
  }
  else if(cm <= 150)
  {
    digitalWrite(LEDgreen , LOW);
    digitalWrite(LEDyellow, HIGH);
    digitalWrite(LEDred, LOW);
    analogWrite(fog, 128);
  }
  else
  {
    digitalWrite(LEDgreen , HIGH);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDred, LOW); 
    analogWrite(fog, 0);
  }

  Serial.print("Distance : ");  
  //Serial.print(inches);
  //Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(50);
}
