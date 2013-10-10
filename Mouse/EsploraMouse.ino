/*
  Esplora Calibrated Joystick Mouse
 
 WARNING: this sketch will take over your mouse movement. If you lose control
 of your mouse do the following:
 1) unplug the Esplora.
 2) open the EsploraBlink sketch
 3) hold the reset button down while plugging your Esplora back in
 4) while holding reset, click "Upload"
 5) when you see the message "Done compiling", release the reset button.
 
 This will stop your Esplora from controlling your mouse while you upload a sketch
 that doesn't take control of the mouse.
 
 Instructions:
 
 
 
 Made by Michael on 16 May 2013
 */

#include <Esplora.h>

int JoyX;                                        // These Variables are global
int JoyY;
int activate = 0;

void setup()
{
  Esplora.writeRGB(0, 0, 10);                   // Signal Esplora is waiting to calibrate
  int start = Esplora.readButton(SWITCH_3);      // Read First Button
  while(start == HIGH) {                         // Wait until button is pressed
    start = Esplora.readButton(SWITCH_3);
  }
  JoyX = Esplora.readJoystickX();                // Set drift variable X
  JoyY = Esplora.readJoystickY();                // Set drift variable Y
  Esplora.writeRGB(10, 0, 0);                   // Calibration is done, waiting to run
} 

void loop()
{
  int xValue = Esplora.readJoystickX();          // read the joystick's X position
  int yValue = Esplora.readJoystickY();          // read the joystick's Y position
  xValue = xValue - JoyX;                        // Remove drift on X position
  yValue = yValue - JoyY;                        // Remove drift on Y position
  int JoyButton = Esplora.readJoystickButton();
  int button1 = Esplora.readButton(SWITCH_1);    // Read Buttons
  int button2 = Esplora.readButton(SWITCH_2);    // Read Buttons
  int button3 = Esplora.readButton(SWITCH_3);    // Read Buttons
  int button4 = Esplora.readButton(SWITCH_4);    // Read Buttons
  int slide = Esplora.readSlider();              // Read Slider Values

  int mousespeed = map(slide, 0, 1023, 10, 0);                  // Max Mouse Speed is Calculated from slider
  int mouseX = map( xValue,-512, 512, mousespeed, -mousespeed);  // map the X value to a range of movement for the mouse X, Changes input range to include new values
  int mouseY = map( yValue,-512, 512, -mousespeed, mousespeed);  // map the Y value to a range of movement for the mouse Y, Changes input range to include new values

  if(button3 == LOW){                          // Check if the Enable/Disable button is pressed
    if(activate == 1) activate = 0;
    else activate = 1;
    delay(500);
  }


  if(activate == 1){                               // Check if mouse is enabled

    Esplora.writeRGB(0 , 10, 0 );                 // Set light to green
    Mouse.begin();                                 // take control of the mouse

    if(JoyButton == LOW || button2 == LOW) Mouse.press(MOUSE_LEFT);       // Test if Left click is activated
    else Mouse.release(MOUSE_LEFT);


    if(button1 == LOW) Mouse.press(MOUSE_MIDDLE);                             // Middle Button    
    else Mouse.release(MOUSE_MIDDLE);

    if(button4 == LOW)  Mouse.press(MOUSE_RIGHT);      // Right Button
    else Mouse.release(MOUSE_RIGHT);

    Mouse.move(mouseX, mouseY, 0);                 // move the mouse

  }

  else {
    Mouse.end();
    Esplora.writeRGB(255, 0, 0 );  
  }
  
  delay(10);                                  // a short delay before moving again

}




