#include <U8glib.h>
#define USE_ARDUINO_INTERRUPTS true
//#include <PulseSensorPlayground.h>
//update with whatever pins you're using
const int pinSCK = 4;
const int pinMOSI = 5;
const int pinCS = 6;
const int pinDC = 7;

U8GLIB_SH1106_128X64 SH1106_Display( pinSCK, pinMOSI, pinCS, pinDC );

void setup(void)
  SH1106_Display.setFont(u8g_font_gdr25r);
  Serial.begin(9600);

  //
  if (pulseSensor.begin())
    Serial.println(" pulseSensor activated ");

}//setup

void loop(void)
{
  UpdateDisplay();

}//loop


void UpdateDisplay( void )
{
  static unsigned long
  timeUpdate = 0;
  unsigned long
  timeNow;

  timeNow = millis();

  //update heart rate at 250mS intervals
  if ( (timeNow - timeUpdate) < 250 )
    return;
  timeUpdate = timeNow;

  SH1106_Display.firstPage();

}//UpdateDisplay
