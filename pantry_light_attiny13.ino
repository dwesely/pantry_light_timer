// C++ code
//
/* LED Strip Light Timer
 *  
 * When activated, circuit lights LEDs for a preset duration.
 * After that duration, the lights fade out using PWM.
 * PIR sensor triggers a reset to the timer and LED brightness.
 * Light Dependent Resistor triggers a wakeup on sufficient brightness (e.g. - the
 * door opens to the pantry)
 * 
 *                ATTiny13a
 *                   __
 *            RST -o|\/|o- VCC (5V)
 *     (To LDR) 3 -o|  |o- 2
 *              4 -o|  |o- 1 (To PIR)
 *            GND -o|__|o- 0 (To MOSFET)
 * (created by AACircuit v1.28.6 beta 04/19/05 www.tech-chat.de)
 * 
 */

#define LED_DRIVER_PIN 0
#define PIR_INPUT_PIN 1
#define LDR_INPUT_PIN 3

uint8_t led_brightness = 0;
uint32_t period = 60000;                  // time before fade, in milliseconds
unsigned long last_lifesign = 0;
unsigned long current_time;

void wake_up() {
  last_lifesign = millis();
  while (led_brightness < 254) {
    led_brightness += 1;
    analogWrite(LED_DRIVER_PIN, led_brightness);
    delay(1); // Wait for x millisecond(s) 10: slow for room light, 1: quick for pantry light
  }
  digitalWrite(LED_DRIVER_PIN, HIGH);
  current_time = millis();
  while ((current_time - last_lifesign) < period) {
    current_time = millis();
    delay(1000);
    // reset timer if PIR is tripped
    if (digitalRead(PIR_INPUT_PIN) > LOW) {
      last_lifesign = millis();
    }
  }
}

void setup()
{
  pinMode(LED_DRIVER_PIN, OUTPUT);
  pinMode(PIR_INPUT_PIN, INPUT);
  pinMode(LDR_INPUT_PIN, INPUT);

  led_brightness = 0;
  last_lifesign = millis();
  wake_up();
}

void loop()
{
  // No PIR trigger for a while, time to fade out
  while (led_brightness > 0 && digitalRead(PIR_INPUT_PIN) < HIGH) {
    led_brightness += -1;
    analogWrite(LED_DRIVER_PIN, led_brightness);
    delay(100); // Wait for 100 millisecond(s)
  }

  // Ensure LED strip is completely off
  digitalWrite(LED_DRIVER_PIN, LOW);

  // Loop to check for wake-up triggers
  while (digitalRead(PIR_INPUT_PIN) < HIGH && digitalRead(LDR_INPUT_PIN) < HIGH) {
    delay(100); // Wait for 100 millisecond(s)
  }
  // PIR sensor was tripped, max brightness and wait
  wake_up();
}
