/**
 * camera controller
 * Dylan Wright
 * dylan@dcwright.xyz
 *
 * version 2
 * rewritten to 
 *  correct flipped led logic
 *  add bulb feature
 *    press SW2 to start exposure 
 *    press SW2 again to stop
 */

const int pc4 = 37;
const int pc5 = 36;
const int pf4 = 31;
const int pf0 = 17;
const int pf1 = 30;
const int pf2 = 40;
const int pf3 = 39;

const int focus = pc4;
const int shutter = pc5;
const int button0 = pf4;
const int button1 = pf0;
const int led_red = pf1;
const int led_blue = pf2;
const int led_green = pf3;

const int msdelay = 2000;

// because my onboard leds are literally blinding
const int led_brightness = 32;

int last_b0 = 1;
int last_b1 = 1;

void setup()
{
  // put your setup code here, to run once:
  pinMode(shutter, OUTPUT);
  pinMode(focus, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(button0, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
 
  digitalWrite(shutter, HIGH);
  digitalWrite(focus, HIGH);
  analogWrite(led_red, LOW);
  analogWrite(led_blue, LOW);
}

/* Get the time to take between exposures
 * 0 press -> msdelay
 * 1 presses -> msdelay * 2
 * 2 presses -> medelay * 3
 */
int getMs()
{
  // Button status variables
  int button0stat;
  int button1stat;

  // Number of presses
  int count = 0;

  analogWrite(led_red, led_brightness / 3);

  // debounce
  while (true) {
    button0stat = digitalRead(button0);
    button1stat = digitalRead(button1);

    // change
    if (button0stat != last_b0 && last_b0) {
      count += 1;
      analogWrite(led_red, led_brightness / (3 - count % 3));
    }
    
    if (button1stat != last_b1 && last_b1) {
      break;
    }
    
    last_b0 = button0stat;
    
    delay(100);
  }

  return msdelay * (count % 3 + 1);
}

void capture(int pics, int ms)
{
  ms = getMs();

  analogWrite(led_red, led_brightness);
  delay(ms);
  analogWrite(led_red, LOW);

  const int focus_time = ms/2;
  const int exposure_time = ms/4;
  int i;
  int start_time;
  
  for(i = 0; i < pics; i++) {
    start_time = millis();
    
    //focus
    analogWrite(led_red, led_brightness);
    digitalWrite(focus, LOW);
    delay(focus_time);
  
    analogWrite(led_red, LOW);
  
    // blue led on indicates photo is being taken
    analogWrite(led_blue, led_brightness);
    digitalWrite(shutter, LOW);
  
    delay(exposure_time);
  
    digitalWrite(shutter, HIGH);
    digitalWrite(focus, HIGH);
    analogWrite(led_blue, LOW);
    
    analogWrite(led_green, led_brightness);
  
    delay(ms - (millis() - start_time));
    
    analogWrite(led_green, LOW);
  }
}

void bulb() {
  const int focus_time = msdelay/2;
  
  // focus
  analogWrite(led_red, led_brightness);
  digitalWrite(focus, LOW);
  
  delay(focus_time);
  
  analogWrite(led_red, LOW);
 
  //expose
  analogWrite(led_blue, led_brightness);
  digitalWrite(shutter, LOW);
  
  // b1 is button to watch
  // debounce
  int button1stat;
  while (true) {
    button1stat = digitalRead(button1);
    
    // change
    if (button1stat != last_b1 && last_b1) {
      break;
    }
    
    last_b1 = button1stat;
    
    delay(100);
  }
  
  analogWrite(led_blue, LOW);
  digitalWrite(shutter, HIGH);
  digitalWrite(focus, HIGH);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // debounce
  int button0stat = digitalRead(button0);
  int button1stat = digitalRead(button1);
  
  if ((button0stat != last_b0 || button1stat != last_b1) && (!last_b0 || !last_b1)) {
    if (button0stat != last_b0 && !last_b0) {
      capture(20000, msdelay);
    } else if (button1stat != last_b1 && !last_b1) {
      bulb();
    }
  }
  
  last_b0 = button0stat;
  last_b1 = button1stat;
  
  delay(100);
}
