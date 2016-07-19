
/*  Dylan Wright - dylan.wright@uky.edu
 *    Nikon D100 Controller
 *    Interface to 10 pin port:
 *      http://www.petermillerphoto.com/nikongps/diagrams/nikon_10pins.gif
 *      e1  - shutter
 *      e2  - focus
 *      gnd - gnd
 *    Push button 1 captures an image
 *    indicated by red led.
 */
 
#include <Sseg.h>

const int sseg_e = 27;
const int sseg_d = 28;
const int sseg_c = 29;
const int sseg_b = 5;
const int sseg_a = 6;
const int sseg_f = 23;
const int sseg_g = 24;
const int sseg_dp = 25;
const int sseg_0 = 26;
Sseg sseg(sseg_a, sseg_b, sseg_c, sseg_d, sseg_e, sseg_f, sseg_g, sseg_dp, sseg_0);

const int e1 = 27;
const int focus = 37;

const int e2 = 28;
const int shutter = 36;

const int f4 = 31;
const int button = f4;

const int f0 = 17;
const int button2 = f0;

const int f1 = 30;
const int led = f1;

const int ir_in = 35;

void setup()
{
  // put your setup code here, to run once:
  pinMode(shutter, OUTPUT);
  pinMode(focus, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(button2, INPUT_PULLUP);
  
  digitalWrite(shutter, HIGH);
  digitalWrite(focus, HIGH);
  digitalWrite(led, LOW);
  
  pinMode(ir_in, INPUT);
  attachInterrupt(ir_in, capture_ir, FALLING);
}

void capture_ir() 
{
  digitalWrite(led, HIGH);
  capture(1, 2000);
  delay(2);  
  digitalWrite(led, LOW);
}

/*  Take pics pictures with 
 *    a time interval of ms
 *    milliseconds
 */
void capture(int pics, int ms)
{
  const int focus_time = ms/2;
  const int exposure_time = ms/4;
  
  int i;
  int start_time;
  for (i = 0; i < pics; i++) {
    start_time = millis();
    sseg.setChar((pics-i)%10+48);
    
    // focus
    digitalWrite(led, LOW);
    digitalWrite(focus, LOW);
    delay(focus_time);
    
    digitalWrite(led, HIGH);
    // expose
    digitalWrite(shutter, LOW);
    delay(exposure_time);
    digitalWrite(shutter, HIGH);
    digitalWrite(focus, HIGH);
    
    // wait
    delay(ms - (millis() - start_time));
  }
}

int last_b2 = 1;
int last_b1 = 1;
int msdelay = 2000;
void loop()
{
  // put your main code here, to run repeatedly:
  // debounce button
  int button1stat = digitalRead(button);
  int button2stat = digitalRead(button2);
  if((button1stat!=last_b1 || button2stat != last_b2) && (!last_b1 || !last_b2)) {
    digitalWrite(led, HIGH);
    if (button1stat!=last_b1 && !last_b1) {
      capture(20000, msdelay);
    } else {
      capture(1, 1000);
    }
    digitalWrite(led, LOW);
  }
  last_b1 = button1stat;
  last_b2 = button2stat;
  delay(100);
}
