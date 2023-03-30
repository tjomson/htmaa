const int potentioPin = PIN_A0;
const int ledPin = 5;

void setup()
{
    pinMode(potentioPin, INPUT);
    pinMode(ledPin, OUTPUT);

    analogWrite(ledPin, 0);
}

void loop()
{
    int potentioVal = analogRead(potentioPin);
    analogWrite(ledPin, potentioVal / 4);
}
