float Y = 0.0;//Y(0)
int PWM =0;

// Filtro media movil exponencial 
//Y(0) t = 0
//S(t)=alpha*Y(t)+(1-alpha)*S(t-1)
unsigned long lastTime = 0, sampleTime = 50;
double YFilter = Y; //s(0) y(0)
double alpha = 0.1;//factor de atenuacion 0.05 ==> 0 y 1

void setup() {
   Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-lastTime >= sampleTime)
  {
       PWM = 255;
       analogWrite(6,PWM);
       Y = map(analogRead(A0),40,1023,0,100);
       Y = constrain(Y,0,100);
       YFilter = alpha*Y+(1.0-alpha)*YFilter;
       lastTime = millis();
       Serial.print(Y);
       Serial.print(',');
       Serial.println(YFilter);
  }

}
