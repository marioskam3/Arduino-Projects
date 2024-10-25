#include <LiquidCrystal_I2C.h>
#include  <Wire.h>

#define trigPin 9
#define echoPin 10
#define buzzer 11

long duration;
int distance;
LiquidCrystal_I2C lcd(0x27,  16, 2);

unsigned long previousMillis = 0;
unsigned long buzzerMillis = 0;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Distance:");
}
void loop() {
  //clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //generates sound
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //reads the echo of the sound through echoPin and returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  //calculating the distance
  distance = duration * 0.034 / 2;

  //padding
  lcd.setCursor(10, 0);
  if (distance < 10) lcd.print("  ");      
  else if (distance < 100) lcd.print(" ");  

  Serial.print("Distance: ");
  Serial.println(distance);
  lcd.print(distance);

  unsigned long currentMillis = millis();
  if (distance < 101 && distance > 50){
    if (currentMillis - previousMillis >= 900){  //buzzer cycle: 200ms ON, 700ms OFF
      previousMillis = currentMillis;
      tone(buzzer, 500);
      buzzerMillis = currentMillis;
    }
  } else if (distance < 51 && distance > 25){
    if (currentMillis - previousMillis >= 500){  // Buzzer cycle: 200ms ON, 300ms OFF
      previousMillis = currentMillis;
      tone(buzzer, 500);
      buzzerMillis = currentMillis;
    }
  } else if (distance < 26) {
    if (currentMillis - previousMillis >= 150){  //uzzer cycle: 50ms ON, 100ms OFF
      previousMillis = currentMillis;
      tone(buzzer, 500);
      buzzerMillis = currentMillis;
    }
  }

  //turn off the buzzer
  if (distance < 101 && distance > 50 && (currentMillis - buzzerMillis >= 200)){
    noTone(buzzer);
  } else if (distance < 51 && distance > 25 && (currentMillis - buzzerMillis >= 200)){
    noTone(buzzer);
  } else if (distance < 26 && (currentMillis - buzzerMillis >= 50)){
    noTone(buzzer);
  }

}
