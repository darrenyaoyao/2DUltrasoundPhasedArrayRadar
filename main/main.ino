const int ARRAY_SIZE = 120;
int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;        // variable to store the value read
long int lasttime = 0;
int timeArray[ARRAY_SIZE];
int valArray[ARRAY_SIZE];
int phases[7] = {0, 3, 6, 9, -3, -6, -9};
int phase_num = 0;

void delay0()
{
  PORTD = B11111100;
  PORTB = B00001111;
  delayMicroseconds(12);
  PORTD = B00001100;
  PORTB = B00000000;
  delayMicroseconds(12);
}

void delay3()
{
  PORTD = B00011100;
  PORTB = B00001110;
  delayMicroseconds(3);
  PORTD = B00111100;
  PORTB = B00001100;
  delayMicroseconds(3);
  PORTD = B01111100;
  PORTB = B00001000;
  delayMicroseconds(3);
  PORTD = B11111100;
  PORTB = B00000000;
  delayMicroseconds(3);
  PORTD = B11101100;
  PORTB = B00000001;
  delayMicroseconds(3);
  PORTD = B11001100;
  PORTB = B00000011;
  delayMicroseconds(3);
  PORTD = B10001100;
  PORTB = B00000111;
  delayMicroseconds(3);
  PORTD = B00001100;
  PORTB = B00001111;
  delayMicroseconds(3);
}

void delay6()
{
  PORTD = B10011100;
  PORTB = B00001001;
  delayMicroseconds(6);
  PORTD = B00111100;
  PORTB = B00000011;
  delayMicroseconds(6);
  PORTD = B01101100;
  PORTB = B00000110;
  delayMicroseconds(6);
  PORTD = B11001100;
  PORTB = B00001100;
  delayMicroseconds(6);
}

void delay9()
{
  PORTD = B01011100;
  PORTB = B00001010;
  delayMicroseconds(3);
  PORTD = B11011100;
  PORTB = B00000010;
  delayMicroseconds(3);
  PORTD = B10011100;
  PORTB = B00000110;
  delayMicroseconds(3);
  PORTD = B10111100;
  PORTB = B00000100;
  delayMicroseconds(3);
  PORTD = B10101100;
  PORTB = B00000101;
  delayMicroseconds(3);
  PORTD = B00101100;
  PORTB = B00001101;
  delayMicroseconds(3);
  PORTD = B01101100;
  PORTB = B00001001;
  delayMicroseconds(3);
  PORTD = B01001100;
  PORTB = B00001011;
  delayMicroseconds(3);
}

void delaym3()
{
  PORTD = B11111100;
  PORTB = B00000000;
  delayMicroseconds(3);
  PORTD = B01111100;
  PORTB = B00001000;
  delayMicroseconds(3);
  PORTD = B00111100;
  PORTB = B00001100;
  delayMicroseconds(3);
  PORTD = B00011100;
  PORTB = B00001110;
  delayMicroseconds(3);
  PORTD = B00001100;
  PORTB = B00001111;
  delayMicroseconds(3);
  PORTD = B10001100;
  PORTB = B00000111;
  delayMicroseconds(3);
  PORTD = B11001100;
  PORTB = B00000011;
  delayMicroseconds(3);
  PORTD = B11101100;
  PORTB = B00000001;
  delayMicroseconds(3);
}

void delaym6()
{
  PORTD = B00111100;
  PORTB = B00000011;
  delayMicroseconds(6);
  PORTD = B10011100;
  PORTB = B00001001;
  delayMicroseconds(6);
  PORTD = B11001100;
  PORTB = B00001100;
  delayMicroseconds(6);
  PORTD = B01101100;
  PORTB = B00000110;
  delayMicroseconds(6);
}

void delaym9()
{
  PORTD = B10111100;
  PORTB = B00000100;
  delayMicroseconds(3);
  PORTD = B10011100;
  PORTB = B00000110;
  delayMicroseconds(3);
  PORTD = B11011100;
  PORTB = B00000010;
  delayMicroseconds(3);
  PORTD = B01011100;
  PORTB = B00001010;
  delayMicroseconds(3);
  PORTD = B01001100;
  PORTB = B00001011;
  delayMicroseconds(3);
  PORTD = B01101100;
  PORTB = B00001001;
  delayMicroseconds(3);
  PORTD = B00101100;
  PORTB = B00001101;
  delayMicroseconds(3);
  PORTD = B10101100;
  PORTB = B00000101;
  delayMicroseconds(3);
}

void phasearray(int delay_us)
{
  if (delay_us == 0)
  {
    for (int i = 0; i < 8; i++)
    {
      delay0();
    }
  }
  else if (delay_us == 3)
  {
    for (int i = 0; i < 8; i++)
    {
      delay3();
    }
  }
  else if (delay_us == 6)
  {
    for (int i = 0; i < 8; i++)
    {
      delay6();
    }
  }
  else if (delay_us == 9)
  {
    for (int i = 0; i < 8; i++)
    {
      delay9();
    }
  }
  else if (delay_us == -3)
  {
    for (int i = 0; i < 8; i++)
    {
      delaym3();
    }
  }
  else if (delay_us == -6)
  {
    for (int i = 0; i < 8; i++)
    {
      delaym6();
    }
  }
  else if (delay_us == -9)
  {
    for (int i = 0; i < 8; i++)
    {
      delaym9();
    }
  }
}

void setup()
{
  Serial.begin(115200); //  setup serial
  DDRD = B11111100;     // Digital pins 2 to 7 as output
  DDRB = B00001111;
  PORTD = B00001100;
  PORTB = B00000000;
}

void loop()
{
  int phase = phases[phase_num % 7];
  long int time = micros();
  if ((time - lasttime) > 10000)
  {
    lasttime = time;
    phasearray(phase);
    PORTD = B00000000;
    PORTB = B00000000;
  }

  delayMicroseconds(random(50));
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    val = analogRead(analogPin); // read the input pin
    time = micros();
    timeArray[i] = time - lasttime;
    valArray[i] = val;
  }

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    Serial.print(timeArray[i] + String(","));
  }
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    Serial.print(valArray[i] + String(","));
  }
  Serial.println(phase_num % 7);
  phase_num += 1;
}
