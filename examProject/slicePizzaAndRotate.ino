const int step_pin = 10;
const int dir_pin = 11;

const int step_pin_base = 7;
const int dir_pin_base = 6;

const int stepsPerRotation = 200;
const float degreesPerStep = 1.8;
const float cmPerRotation = 3.9;

void setup()
{
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(step_pin_base, OUTPUT);
    pinMode(dir_pin_base, OUTPUT);
    // initialize the serial port:
    Serial.begin(9600);
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

void loop()
{
    cutCm(25, 0);
    delay(100);
    cutCm(25, 1);
    rotateBase(90);
    delay(1000);
}