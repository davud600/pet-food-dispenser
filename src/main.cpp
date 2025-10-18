#include <Servo.h>

Servo motor1;
Servo motor2;

const int motor1Pin = 11;
const int motor2Pin = 10;
const int startingButtonPin = 13;
const int timeOptionsButtonPin = 12;
const int startedTimerPin = 8;
int ledPins[] = {7, 6, 5, 4, 3};

bool started = false;
bool buttonPressed = false;
bool button1Pressed = false;
int numOfTimesPressedButton = 0;

int timeOptions[4];
int timeOptionsLength = 4;
int timeOptionsIndex = 0;
int timeToOpenDoor = 0;
int timeDoorIsOpen = 1000;
unsigned long previousMillisForClosedDoor = 0;
unsigned long previousMillisForOpenDoor = 0;

void setup() {
  Serial.begin(9600);
  motor1.attach(motor1Pin);
  motor2.attach(motor2Pin);
  pinMode(startingButtonPin, INPUT);
  pinMode(timeOptionsButtonPin, INPUT);
  pinMode(startedTimerPin, OUTPUT);

  for (int i = 0; i < timeOptionsLength; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  timeOptions[0] = 1500;
  timeOptions[1] = 3000;
  timeOptions[2] = 4000;
  timeOptions[3] = 8000;

  motor1.write(0);
  motor2.write(0);
}

void loop() {
  digitalWrite(startedTimerPin, started);

  unsigned long currentMillis = millis();

  // Initial position of the motors
  if (currentMillis - previousMillisForOpenDoor >= timeDoorIsOpen) {
    previousMillisForOpenDoor = currentMillis;
    motor1.write(0);
    motor2.write(0);
  }

  // Check if start/stop button is pressed to start/stop the timer
  if (digitalRead(startingButtonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;
    numOfTimesPressedButton++;
  } else if (digitalRead(startingButtonPin) == LOW && buttonPressed) {
    buttonPressed = false;
  }

  if (numOfTimesPressedButton % 2 == 0 || numOfTimesPressedButton == 0) {
    started = false;
  } else {
    started = true;
  }

  // Check if the timeOptions button is being pressed to go through the time options
  if (digitalRead(timeOptionsButtonPin) == HIGH && !button1Pressed && !started) {
    button1Pressed = true;
    if (timeOptionsIndex < timeOptionsLength - 1) {
      timeOptionsIndex++;
    } else {
      timeOptionsIndex = 0;
    }
  } else if (digitalRead(timeOptionsButtonPin) == LOW && button1Pressed && !started) {
    button1Pressed = false;
  }

  // Change the time option and light up it's led
  int indexOfLedThatShouldBeLitUp;
  timeToOpenDoor = timeOptions[timeOptionsIndex];
  for (int i = 0; i < timeOptionsLength; i++) {
    if (i != timeOptionsIndex) {
      digitalWrite(ledPins[i], LOW);
    } else {
      indexOfLedThatShouldBeLitUp = i;
    }
  }
  digitalWrite(ledPins[indexOfLedThatShouldBeLitUp], HIGH);

  if (!started) {
    return;
  }

  // Delay for a certain amount of time to open the door
  if (currentMillis - previousMillisForClosedDoor >= timeToOpenDoor) {
    previousMillisForClosedDoor = currentMillis;
    Serial.println(timeToOpenDoor);
    for (int i = 0; i <= 90; i++) {
      motor1.write(i);
      motor2.write(i);
      // delay(10);
    }
  }
}
