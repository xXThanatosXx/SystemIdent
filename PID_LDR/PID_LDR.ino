float Y = 0.0;
float U = 0.0;
float SetPoint = 0.0;
int PWM = 0;

float error =0.0;
float error_anterior=0.0;
float Kp = 13.7;//0.09, 20.0
float Ki = 155.0;//11 , 250
float Kd = 0.0127;//
const int Ts = 50; // tiempo de muestreo ms
static unsigned long tiempoInicial = 0;
unsigned long tiempoActual = 0, tiempoPasado =0;

// Filtro media movil exponencial 
//Y(0) t = 0
//S(t)=alpha*Y(t)+(1-alpha)*S(t-1)
double YFilter = Y; //s(0) y(0)
double alpha = 0.01;//factor de atenuacion 0.05 ==> 0 y 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  
  tiempoActual = millis();
  //unsigned long dt = tiempoActual-pasado;
  if(tiempoActual-tiempoPasado >= Ts)
  {
    ProcessControl();

    tiempoPasado = tiempoActual;
  }
}

void ProcessControl()
{

    Y = map(analogRead(A0),15,850,0,100);
    YFilter = alpha*Y+(1.0-alpha)*YFilter;
    YFilter = constrain(YFilter,0,100);
   
    SetPoint = map(analogRead(A1),0,1023,0,100);

    error = SetPoint-YFilter;
    //Ecuación de control PID
    U = U+Kp*(error-error_anterior)+(Ki*0.05*0.5)*(error+error_anterior)+(Kp*Kd/0.05);
    error_anterior = error;

    //Acción de control
    U = constrain(floor(U),0,100);
    PWM = map(U,0,100,0,255);
    analogWrite(6,PWM);
    
//    Serial.print("SetPoint: ");
//    Serial.print(SetPoint);
//    Serial.print(" ");
//    Serial.print("Y: ");
//    Serial.print(Y);
//    Serial.print(" ");
//    Serial.print("U : ");
//    Serial.print(U);
//    Serial.print(" ");
//    Serial.print("ERROR : ");
//    Serial.println(error);

    //Data set point salida
    Serial.print("SetPoint: ");
    Serial.print(SetPoint);
    Serial.print(" ");
    Serial.print("Y: ");
    Serial.print(YFilter);
    Serial.print(" ");
    Serial.print("ERROR : ");
    Serial.println(error);
}
