const int step_pin = 10;
const int dir_pin = 11;

void setup()
{
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    // initialize the serial port:
    Serial.begin(9600);
}

void loop()
{
    // step one revolution  in one direction:
    Serial.println("clockwise");
    digitalWrite(dir_pin, LOW);
    digitalWrite(step_pin, LOW);

    for (int i = 0; i < 100; i++)
    {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(step_pin, LOW);
        delay(1);
    }
    delay(1000);
    digitalWrite(dir_pin, HIGH);

    for (int i = 0; i < 100; i++)
    {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(step_pin, LOW);
        delay(1);
    }

    delay(500);

    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    delay(500);
}
