#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial smss(2,3);
 
 const int trigPin = 5;
const int echoPin = 4;

TinyGPS gps;

void gpscheck();

void lcddisplay(String temp = "");
void family_sms( char *p, char *m);

void setup() {
  // put your setup code here, to run once:
 pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
Serial.begin(9600);
 smss.begin(9600);
lcd.begin(16,2);
      lcd.clear();
      
      lcd.setCursor(0,0);
      lcd.print("SMART DUST BIN ");
      lcd.setCursor(0,1);
      lcd.print("USING GSM");
      delay(3000);
      lcd.clear();
      
      lcd.setCursor(0,0);
      lcd.print("Initialized  ");
      lcd.setCursor(0,1);
      lcd.print("Successfully");
      delay(3000);
   
 
}



void loop() {

     long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Display distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  
  // Check if bin level is below 75%
  if (distance <= 15) {

    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DUST BIN FULL ");
      lcd.setCursor(0,1);
      lcd.print("SENDING SMS");
      family_sms("9901129847","DUST BIN FULL "); gpscheck();
      delay(3000);
      while(1);
  }
  else
  {
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DUST BIN  ");
      lcd.setCursor(0,1);
      lcd.print("EMPTY");
   delay(2000); 
   }
   
   
    
}

  void family_sms( char *p, char *m)
{
  smss.print("AT\r");
  delay(1000);
  
  smss.print("AT+CMGF=1\r");
  delay(1000);
  
  smss.print("AT+CMGS=\"");
  smss.print(p);
  smss.print("\"\r");
  delay(1000);

  smss.print(m);
  smss.print((char)26);
  delay(1000);
  
}
void gpscheck()
{ 
  while(1)
  {
  
  while (Serial.available())
  { int c = Serial.read();
    if (gps.encode(c))
    {
float slat,slon;
      gps.f_get_position(&slat, &slon);
    //  sprintf(buf,"TEMP HIGH FOUND At latitude %s longitude %s",gps.f_get_position.slat,gps.f_get_position.slon);
    //  Serial.print("Latitude :");
     // Serial.println(slat, 6);
     // Serial.print("Longitude:");
     // Serial.println(slon, 6);
      String latitude = String(slat,6); 
  String longitude = String(slon,6); 
Serial.println(latitude+";"+longitude);
            delay(2000);  
while(1);
    }
  }
  }
  }
