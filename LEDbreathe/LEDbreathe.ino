int brightness = 0;
int fadeAmount = 5;
int n=18;
int arr_light[] = {0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255};

void setup() {
  for(int i=7;i<=13;i++)
  {
    pinMode(i, OUTPUT);
  }
}

int port_start = 7; 
void loop()
{
  for(int i=0;i<126000;i++)
  {
    analogWrite(port_start+(i)%7, arr_light[(i)%n]);
    analogWrite(port_start+(i+1)%7, arr_light[(i+2)%n]);
    analogWrite(port_start+(i+2)%7, arr_light[(i+4)%n]);
    analogWrite(port_start+(i+3)%7, arr_light[(i+6)%n]);
    analogWrite(port_start+(i+4)%7, arr_light[(i+8)%n]);
    analogWrite(port_start+(i+5)%7, arr_light[(i+10)%n]);
    analogWrite(port_start+(i+6)%7, arr_light[(i+12)%n]);
    delay(100);
  }
}
