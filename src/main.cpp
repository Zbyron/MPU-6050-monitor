#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
 #include <Adafruit_I2CDevice.h> 
#include <Adafruit_SSD1306.h>
#include <MPU6050_tockn.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
MPU6050 mpu6050(Wire);

long timer = 0;
float temp = 0;
float accX = 0;
float accY = 0;
float accZ = 0;
float accAngleX =0;
float accAngleY = 0;

void initDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
   display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Initializing");
}

void initMpu6050() {
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void updateDisplay(){
  display.clearDisplay();

  // display R G B Values
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Motion Sensor:");

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("temp: " + String(temp));

  display.setCursor(0, 30);
  display.print("accAngleX: " + String(accAngleX));

  display.setCursor(0, 40);
  display.print("accAngleY: " + String(accAngleY));

  display.setCursor(0, 56);
  display.print("Move me around!");
 
  display.display(); 
}

void updateMPU6050() {
  mpu6050.update();
  if(millis() - timer > 500){
    temp = mpu6050.getTemp();
    accX = mpu6050.getAccX();
    accY = mpu6050.getAccY();
    accZ = mpu6050.getAccZ();
    accAngleX = mpu6050.getAccAngleX();
    accAngleY = mpu6050.getAccAngleY();
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(temp);
    Serial.print("accX : ");Serial.print(accX);
    Serial.print("\taccY : ");Serial.print(accY);
    Serial.print("\taccZ : ");Serial.println(accZ);
    
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
    
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
    
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    timer = millis();
  }
}

void setup() {
  Wire.begin();
  Serial.begin(57600);
  initDisplay();
  initMpu6050();
}

void loop() {
  updateMPU6050();
  updateDisplay();
}
