#include <Adafruit_DotStar.h> // install the Adafruit DotStar library via Tools | Manage Libraries

#include <Keyboard.h> // the HID USB keyboard library
#include <Mouse.h> // the HID USB mouse library

// control the onboard RGB LED; technically, a strip with just one LED!
Adafruit_DotStar strip = Adafruit_DotStar(1, REG_DSU_DATA, EXTERNAL_INT_NMI, DOTSTAR_BGR);

// define a shimmy (a sequence of mouse movements)
struct shimmy{
  signed char *dx;         // (pointer to) array of char indicating x movements; -1, 0, or 1
  signed char *dy;         // (pointer to) array of char indicating y movements; -1, 0, or 1
  unsigned char num_steps;   // number of steps in sequence; 1-255
  unsigned char repeat;      // number of times to repeat this sequence; 1-255
  unsigned char scale;       // scale factor for sequence movements, e.g. DX = dx*scale
};

// a rectangle shimmy example
signed char dx_rectangle[] = {0, 0, 1, 0, 0, -1};
signed char dy_rectangle[] = {1, 1, 0, -1, -1, 0};
struct shimmy rectangle = {
  dx_rectangle, // dx
  dy_rectangle, // dy
  6,            // count
  1,            // repeat
  50            // scale
};

// define your configuration settings 
struct config{
  boolean do_mouse;     // move the mouse?
  boolean do_keyboard;  // generate keystrokes?
  float delay_s; // seconds between mouse/keyboard actions
};

// assign your configuration default values
struct config cfg = {
  true, //do_mouse
  false, //do_keyboard
  0.5   //delay_s
};

void mouse_draw(shimmy shimmy) {
  for(unsigned char i = 0; i < shimmy.repeat; i++)
  {
    for(unsigned char i = 0; i < shimmy.num_steps; i++)
    {
      Mouse.move(shimmy.dx[i] * shimmy.scale, shimmy.dy[i] * shimmy.scale);
      delay(cfg.delay_s * 1000);
    }
  }
}

void setup() {
  //initialize Serial communication
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the HID USB keyboard interface
  Keyboard.begin();
  // initilize the HID USB mouse interface
  Mouse.begin();
  // initialize the onboard RGB LED
  strip.begin();
  // set the color of the onboard RGB LED
  strip.setPixelColor(0, 0, 0, 64); //blue  
  // show the world!  
  strip.show();

  Serial.print('Setup Complete!');

}

void loop() {
  if (cfg.do_mouse == true) {
    mouse_draw(rectangle);
  }
}
