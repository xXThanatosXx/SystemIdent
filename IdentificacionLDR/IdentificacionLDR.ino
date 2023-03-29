float Y = 0.0;
float U = 0.0;

int PWM =0;

char Recepcion[30];
byte i = 0;
double YFilter = Y; //s(0) y(0)
double alpha = 0.1;//factor de atenuacion 0.05 ==> 0 y 1
void setup() {
  Serial.begin(9600);

}

void loop() {
  if(Serial.available())

  {
     memset(Recepcion,0,sizeof(Recepcion));
     while(Serial.available() > 0)
     {
      Recepcion[i] = Serial.read();
      i++;
      delay(3);
           
     }
     i = 0;
     U = atof(Recepcion);

       PWM = map(U,0,100,0,255);
       analogWrite(6,PWM);

       Y = map(analogRead(A0),40,1023,0,100);
       Y = constrain(Y,0,100);
       YFilter = alpha*Y+(1.0-alpha)*YFilter;
       Serial.println(YFilter);
    
  }
}
