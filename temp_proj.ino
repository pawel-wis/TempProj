#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>



//SDA -> pin A4
//SCL -> pin A5
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SimpleDHT11 dht11;
int tick_tack = 0;
int time_interval = 180;

void setup() {
  //Serial port
  Serial.begin(9600);
  //LCD Setup
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.setCursor(9,0);
  lcd.print((char)223);
  lcd.setCursor(10,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("HUM :");
  lcd.setCursor(9,1);
  lcd.print("%");
}

void loop() {
  delay(10000);

  //Print data at lcd screen
  lcd.setCursor(6,0);
  byte temp = 0;
  byte hum = 0;
  int err = SimpleDHTErrSuccess;
  if ((err=dht11.read(2, &temp, &hum, NULL)) != SimpleDHTErrSuccess){
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    delay(500);
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    return;
  }
  lcd.print(temp);
  lcd.setCursor(6,1);
  lcd.print(hum);

  // Send data to serial port
  tick_tack++;
  if(tick_tack == time_interval){
    String msg = (String)temp + ":" + (String)hum;
    Serial.println(msg);
    tick_tack = 0;
  }
}
