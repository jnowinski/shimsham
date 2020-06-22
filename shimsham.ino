// define your configuration settings 
struct config{
  boolean do_blink;
  float delay_s;
};

// assign your configuration default values
struct config cfg = {
  true, //do_blink
  0.5   //delay_s
};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(cfg.do_blink == true) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(cfg.delay_s*1000);           // wait for a delay_s second(s)
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(cfg.delay_s*1000);           // wait for a delay_s second(s)    
  }
}
