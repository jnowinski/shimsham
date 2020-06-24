#include <Adafruit_DotStar.h> // install the Adafruit DotStar library via Tools | Manage Libraries

#include <Keyboard.h> // the HID USB keyboard library
#include <Mouse.h> // the HID USB mouse library

// control the onboard RGB LED; technically, a strip with just one LED!
Adafruit_DotStar strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);

// define a shimmy (a sequence of mouse movements)
struct shimmy{
  char *dx;         // (pointer to) array of char indicating x movements; -1, 0, or 1
  char *dy;         // (pointer to) array of char indicating y movements; -1, 0, or 1
  byte num_steps;   // number of steps in sequence; 1-255
  byte repeat;      // number of times to repeat this sequence; 1-255
  byte scale;       // scale factor for sequence movements, e.g. DX = dx*scale
};

// a rectangle shimmy example
char dx_rectangle[] = {0, 0, 1, 0, 0, -1};
char dy_rectangle[] = {1, 1, 0, -1, -1, 0};
struct shimmy rectangle = {
  dx_rectangle, // dx
  dy_rectangle, // dy
  6,            // count
  1,            // repeat
  10            // scale
};

// define your configuration settings 
struct config{
  boolean do_mouse;     // move the mouse?
  boolean do_keyboard;  // generate keystrokes?
  float delay_s;        // seconds between mouse/keyboard actions
};

// assign your configuration default values
struct config cfg = {
  false, //do_mouse
  false, //do_keyboard
  0.5   //delay_s
};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the HID USB keyboard interface
  Keyboard.begin();

  // initilize the HID USB mouse interface
  Mouse.begin();

  // initialize the onboard RGB LED
  strip.begin();
  // set the color of the onboard RGB LED
  //strip.setPixelColor(0, 0, 64, 0); //green
  //strip.setPixelColor(0, 64, 0, 0); //red
  strip.setPixelColor(0, 0, 0, 64); //blue  
  // show the world!  
  strip.show();
}

void loop() {
  if(cfg.do_mouse == true || cfg.do_keyboard == true) {
    if(cfg.do_mouse == true) {
      Mouse.move(10, 10, 0);       
    }
    if(cfg.do_keyboard == true) {
      Keyboard.write(65);      
    }    
    delay(cfg.delay_s*1000);           // wait for a delay_s second(s)    
  }
}
