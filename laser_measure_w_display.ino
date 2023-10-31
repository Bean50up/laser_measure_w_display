
  #include "rgb_lcd.h"
  rgb_lcd lcd;

  char state = 0;
  char rnr_pin = 3;
  char button_pin = 4;
void setup() {

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Distance");
  pinMode(button_pin,INPUT);
  }

void loop() {

  pinMode(rnr_pin,OUTPUT);
  digitalWrite(rnr_pin, LOW);
  digitalWrite(rnr_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(rnr_pin, LOW);

  pinMode(rnr_pin,INPUT);
  uint64_t value = pulseIn(rnr_pin,HIGH); 

  float cm = ((float)value/1000)*186.48*0.1;

  if(digitalRead(button_pin) == HIGH)
  {
    lcd.setCursor(9,1);
    if(state == 0)
    {
      lcd.print("(cm)  ");
      state = 1;
    }
    else
    {
      lcd.print("(inch)");
      state = 0;
    }
      delay(250);
  }

  lcd.setCursor(0,2);

  if(state == 1)
  { 
    lcd.print(cm);
    Serial.print(cm);
    Serial.println("cm");
  }
  if(state == 0)
  {
    lcd.print(cm/2.54);
    Serial.print(cm/2.54);
    Serial.println("inch");
  }
  
  if(value == 13)
  {
    lcd.setCursor(0,2);
    lcd.print("Error: Too Close");
    delay(250);
    lcd.setCursor(0,2);
    lcd.print("                ");
    lcd.setCursor(9,1);
      if(state == 1)
        lcd.print("(cm)");
      if(state == 0)
        lcd.print("(inch)");
  }
  
  if(cm > 221)
  {
    lcd.setCursor(0,2);
    lcd.print("Error: Too Far  ");
    delay(250);
    lcd.setCursor(0,2);
    lcd.print("                ");
    lcd.setCursor(9,1);
      if(state == 1)
        lcd.print("(cm)");
      if(state == 0)
        lcd.print("(inch)");
  }

}
