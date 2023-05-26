const int step_pin = 10;
const int dir_pin = 11;

const int step_pin_base = 9; //was 7
const int dir_pin_base = 8; //was 6

const int sensor_pin = 7; // was 2

const int go_button_pin = 12;
const int increment_button_pin = 13;

const int led_2_pin = 2;
const int led_4_pin = 3;
const int led_6_pin = 4;
const int led_8_pin = 5;


const int stepsPerRotation = 200;
const float degreesPerStep = 1.8;
const float cmPerRotation = 3.9;

const int toSensorSide = 0;
const int toMotorSide = 1;

int cutCountSet = 1;

unsigned long lastReadTime = millis();

void setup()
{
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(step_pin_base, OUTPUT);
    pinMode(dir_pin_base, OUTPUT);
    pinMode(sensor_pin, INPUT);

    pinMode(go_button_pin, INPUT);
    pinMode(increment_button_pin, INPUT);

    pinMode(led_2_pin, OUTPUT);
    pinMode(led_4_pin, OUTPUT);
    pinMode(led_6_pin, OUTPUT);
    pinMode(led_8_pin, OUTPUT);
    // initialize the serial port:
    Serial.begin(9600);
    cutUntilLimit(toMotorSide); // find home
}

void cutCm(float distance, int direction) {
    digitalWrite(dir_pin_base, LOW);
    digitalWrite(step_pin_base, LOW);

    digitalWrite(dir_pin, direction);
    digitalWrite(step_pin, LOW);
    const float steps = (distance / cmPerRotation) * stepsPerRotation;
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(step_pin, LOW);
        delay(2);
    }
}

void cutUntilLimit(int direction) {
    digitalWrite(dir_pin_base, LOW);
    digitalWrite(step_pin_base, LOW);

    digitalWrite(dir_pin, direction);
    digitalWrite(step_pin, LOW);
    int stepCount = 0;
    int sensorBlack = digitalRead(sensor_pin);

    while(stepCount < 100 || sensorBlack) {
      digitalWrite(step_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(step_pin, LOW);
      delay(2);
      stepCount++;
      sensorBlack = digitalRead(sensor_pin);
    }
}

void rotateBase(int degrees) {
  digitalWrite(dir_pin, LOW);
  digitalWrite(step_pin, LOW);
  const float steps = degrees / degreesPerStep;
  for (int i = 0; i < steps; i++)
  {
      digitalWrite(step_pin_base, HIGH);
      delayMicroseconds(10);
      digitalWrite(step_pin_base, LOW);
      delay(25);
  }
}

void setLeds() {
  digitalWrite(led_2_pin, HIGH);
  digitalWrite(led_4_pin, cutCountSet >= 2);
  digitalWrite(led_6_pin, cutCountSet >= 3);
  digitalWrite(led_8_pin, cutCountSet >= 4);
}

void readIncrement() {
  unsigned long now = millis();
  if (now - lastReadTime > 400 && digitalRead(increment_button_pin)) {
    cutCountSet++;
    if (cutCountSet >= 5) cutCountSet = 1;
    lastReadTime = now;
  }
}

void loop()
{
  readIncrement();
  setLeds();
  if (digitalRead(go_button_pin)) {
    for (int i = 0; i < cutCountSet; i++) {
      cutUntilLimit(toSensorSide);
      cutUntilLimit(toMotorSide);
      if (i < cutCountSet - 1) {
        rotateBase(180 / cutCountSet);
        delay(500);
      }
    }
  }
}