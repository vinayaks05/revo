#define voltage 35
#define t 25
//# define current 25
#define led 13
const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
const double R2 = 10000;            // 10k ohm series resistor
const double adc_resolution = 4096.00; // 12-bit adc
int tmp;
float v, i, r1 = 11100, r2 = 2200;
double Vout, Rth, temperature, adc_value, Vr,ln;
char d;

void setup() {
  pinMode(t, INPUT);
  pinMode(voltage, INPUT);
  //pinMode(current, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);  
}

float volt() {  
  v = analogRead(voltage);
  v = map(v, 0, 4096, 0, 3.3);
  v = v*(r1+r2)/(r2);
  return v;
}

float temp(){
  tmp = analogRead(t);
  Vout = (tmp)*(VCC) / adc_resolution;
  Vr = VCC - Vout;
  Rth = (Vout)/ (Vr/R2);
  ln = log(Rth/ R2);
  temperature = (1/ ((ln / 3977) + (1/ 298.15)));
  temperature = temperature - 273.15;
  return temperature;
}
void loop() {
  digitalWrite(led , HIGH);
  delay(500);
  digitalWrite(led , LOW);
  delay(500);
  
  while (Serial.available() > 0){
    d = Serial.read();
    switch (d){
      case 'a':
        Serial.println(volt());
        break;
      case 'b':
        Serial.println(temp());
        break;
      default:
        Serial.println("please check");
        break;  
    }
  }
  //i = analogRead(current);
  
  //Serial.println(i);

}
