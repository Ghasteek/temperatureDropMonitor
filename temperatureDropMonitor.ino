#include <OneWire.h>
#include <DallasTemperature.h>

int maxFallOff = 0;

const int tempPin = 2;
const int buttonPin = 9;
const int resetPin = 10;
const int buzzPin = 8;
const int statePin = 7;

const int dip1 = 3;
const int dip2 = 4;
const int dip3 = 5;
const int dip4 = 6;

int buttonState = 0;
int resetState = 0;
int dip1state = 0;
int dip2state = 0;
int dip3state = 0;
int dip4state = 0;

float refTemp = 0;
float temp = 0;

// nastavení komunikace senzoru přes pin
OneWire oneWire(tempPin);     
// převedeme onewire do Dallasu                     
DallasTemperature sensors(&oneWire);           
 
void setup(void)
{
  pinMode(buzzPin, OUTPUT);
  pinMode(statePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(resetPin, INPUT);
  pinMode(dip1, INPUT);
  pinMode(dip2, INPUT);
  pinMode(dip3, INPUT);
  pinMode(dip4, INPUT);
  Serial.begin(9600);
  setMaxFallOff();
  // zapnutí senzoru                          
  sensors.begin();                             
}
 
void loop() {

  // get temperature from sensor
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  
  // should I set refTemp?
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    refTemp = temp;
  }
  
  // should I reset refTemp?
  resetState = digitalRead(resetPin);
  if (resetState == HIGH) {
    refTemp = 0;
    setMaxFallOff();
  }
  
  // write current temp to serial
  Serial.print("temp: ");
  Serial.println(temp);
  
  // if refTemp is set, turn on status LED, 
  // print refTemp and
  // difference to serial
  if (refTemp != 0 ){
    digitalWrite(statePin, HIGH);
    float diff = temp - refTemp;
    
    Serial.print("ref temp: ");
    Serial.println(refTemp);
    Serial.print("diff: ");
    Serial.println(diff);
      
    // if difference is greater than maxFallOff,
    // make buzzing to buzz output, where is tranzistor
    // for piezo buzzer
    if (diff < maxFallOff) {
      digitalWrite(buzzPin, HIGH);
      delay(1000);
      digitalWrite(buzzPin, LOW);
      delay(500);
      Serial.println("Buzz");
      
    } else {
      digitalWrite(buzzPin, LOW);
      
    }
  } else {
      // if refTemp is not set, turn off state LED
      digitalWrite(statePin, LOW);
    }
  
  delay(1000);
}

void setMaxFallOff() {
  // Get setting of maxFallOff from dipswitch and set it
  // to variable
  bool isSet = false;
  dip1state = digitalRead(dip1);
  if (dip1state == HIGH) {
    Serial.println("setting max fallOff to 2C");
    maxFallOff = -2;
    isSet = true;
  }
  
  dip2state = digitalRead(dip2);
  if (dip2state == HIGH) {
    Serial.println("setting max fallOff to 3C");
    maxFallOff = -3;
    isSet = true;
  }
  
  dip3state = digitalRead(dip3);
  if (dip3state == HIGH) {
    Serial.println("setting max fallOff to 4C");
    maxFallOff = -4;
    isSet = true;
  }
  
  dip4state = digitalRead(dip4);
  if (dip4state == HIGH) {
    Serial.println("setting max fallOff to 5C");
    maxFallOff = -5;
    isSet = true;
  }
  
  if (isSet == false) {
    Serial.println("setting max fallOff to 0C");
    maxFallOff = 0;
  }
}
