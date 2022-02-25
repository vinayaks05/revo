// code by vinayak for measuring 
// voltage and current for some generic sensor
#define voltage A1 // pins for input
#define i A0 // pins for input of current
float volt, min_volt = 0, max_volt = 0, current, min_current = 0, max_current = 0;
char usr;
void setup() {
  pinMode(voltage, INPUT);
  pinMode(current, INPUT);
  Serial.begin(9600); // for com interfacing

}

void loop() {
  // let the sensor output be the actual reading 
  // of the current and voltage
  volt = analogRead(voltage);
  current = analogRead(current);
  if(volt > max_volt){
    max_volt = volt; 
  }
  if (volt < min_volt){
    min_volt = volt;
  }
  if (current > max_current){
    max_current = current;
  }
  if (current < min_current){
    min_current = current;
  }
  while (Serial.available()>0){
    usr = Serial.read();
    switch(usr){
      case '1':
        Serial.println(volt);
        break;
      case '2':
        Serial.println(current);
        break;
      case '3':
        Serial.println(max_volt);
        break;
      case '4':
        Serial.println(min_volt);
        break;
      case '5':
        Serial.println(max_current);
        break;
      case '6':
        Serial.println(min_current);
        break;
      default:
        Serial.println("invald input");
        break;    
    }
  }
  delay(15);
}
