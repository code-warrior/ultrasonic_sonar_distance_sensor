/**
   HC-SR04 Demo
   Demonstration of the HC-SR04 Ultrasonic Sensor
   Date: August 3, 2016

   Description:
    Connect the ultrasonic sensor to the Arduino as per the
    hardware connections below. Run the sketch and open a serial
    monitor. The distance read from the sensor will be displayed
    in centimeters and inches.

   Hardware Connections:
    Arduino | HC-SR04
    -------------------
      5V    |   VCC
      7     |   Trig
      8     |   Echo
      GND   |   GND

   License:
    Public Domain
*/

// Pins
#define BAUD_RATE                 9600
#define TRIGGER_PIN               7
#define ECHO_PIN                  8
#define MAXIMUM_MICROSECOND_PULSE 23200 // Anything over 400 cm (23200 us pulse) is "out of range"

void setup() {
  // The trigger pin, connected to the left distance sensor if you’re facing the
  // front of the sensor, will send the 40kHz ultrasonic wave.
  pinMode(TRIGGER_PIN, OUTPUT);
  // The echo pin, connected to the right sensor, senses for the echo of the
  // 40kHz wave sent by the trigger sensor.
  pinMode(ECHO_PIN, INPUT);

  // Initialize the trigger pin to be low, or off.
  digitalWrite(TRIGGER_PIN, LOW);

  Serial.begin(BAUD_RATE);
}

void loop() {
  static unsigned long t1;
  static unsigned long t2;
  static unsigned long pulse_width;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Wait until a value is read on the echo pin (that is, a pulse occurs)
  while (0 == digitalRead(ECHO_PIN))
    ;

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while (1 == digitalRead(ECHO_PIN))
    ;
  t2 = micros();
  pulse_width = t2 - t1;


  if ( pulse_width > MAXIMUM_MICROSECOND_PULSE ) {
    Serial.println("Out of range");
  } else {
  }

  delay(60); // Wait at least 60 milliseconds before next measurement
}
