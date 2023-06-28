#include "oled-wing-adafruit.h"
#define TMP36 A4
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

// setup() runs once, when the device is first turned on.
void setup()
{

  // Put initialization like pinMode and begin functions here.
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  pinMode(TMP36, INPUT);
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.display(); // cause the display to be updated
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  uint64_t reading = analogRead(TMP36);
  double voltage = (reading * 3.3) / 4095.0;
  double temperatureC = (voltage - 0.5) * 100;
  double temperatureF = (temperatureC * 9 / 5) + 32;
  // this doesnt work display.printf("Celcius: %.2lf", temperatureC);
  display.println("Celcius " + String(temperatureC, 2));
  display.println("Fahrenheit " + String(temperatureF, 2));
  display.display();
  delay(100);
}