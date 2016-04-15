//Pin numbers for the LEDs
const int redLED = 8;
const int yelLED = 9;
const int grnLED = 10;
const int bluLED = 12;

//Pin numbers for the push buttons
const int redBut = 2;
const int yelBut = 3;
const int grnBut = 4;
const int bluBut = 5;

//Pin number for the buzzer
const int buzzer = 11;

//Variables for the game part of the project
int roundNum = 0;
int sequence[100];


void setup()
{
  //Sets the pins related to the leds to output data
  pinMode(redLED, OUTPUT);
  pinMode(yelLED, OUTPUT);
  pinMode(grnLED, OUTPUT);
  pinMode(bluLED, OUTPUT);

  //Sets the pins related to the buttons to input data
  pinMode(redBut, INPUT);
  pinMode(yelBut, INPUT);
  pinMode(grnBut, INPUT);
  pinMode(bluBut, INPUT);

  //Sets the pin for the buzzer to be an output
  pinMode(buzzer, OUTPUT);

  //Serial.begin(9600); //Enable if you need serial
}

void loop()
{
  //This part shows the opening pattern if the game isn't running
  //Pressing any button will start the game
  if (roundNum < 1)
  {
    while (checkButton() == -1)
    {
      openingPattern();
    }
  }

  //Generate a random starting point based on the total time the unit has be on
  randomSeed(millis());

  //If the player loses it restarts the game
  if (playGame() == true);
  resetPattern();
  roundNum = 0;
}

boolean playGame()
{
  //Runs the while look while the current round is less than the overall round
  while (roundNum < sizeof(sequence))
  {
    nextColor(); //Call the nextColor method
    playPattern(); //Call the playPattern method
    for (int q = 0; q < roundNum; q++)
    {
      int choice = waitForButton();
      if (choice != sequence[q]) //Checks if the button being pressed is the same color as the color in the sequence
      {
        return false;
      }
    }
    delay(500);
    roundNum++;
  }
  return true; //If the player doesn't screw up, then go to next round
}

int checkButton()
{
  //Checks if any of the buttons are being pressed
  //if one is then it returns the color value of it
  //if no button is being pressed then return -1
  if (digitalRead(redBut) == LOW)
  {
    return 1;
  }
  else if (digitalRead(yelBut) == LOW)
  {
    return 2;
  }
  else if (digitalRead(grnBut) == LOW)
  {
    return 3;
  }
  else if (digitalRead(bluBut) == LOW)
  {
    return 4;
  }
  else
  {
    return -1;
  }
}

int waitForButton()
{
  int button = checkButton();

  while (button == -1) //If no button is being pressed it loops indefinitly
  { 
    button = checkButton(); //Checks the buttons again
  }
  while(checkButton() != -1) //If a button is being pressed it lights it up and makes the sound
  {
  tone(buzzer,getSound(button),100);
  digitalWrite(getPinNumber(button), HIGH);
  }
  delay(200);
  digitalWrite(getPinNumber(button), LOW);
  return button; //Returns the button being pressed
}

int getPinNumber(int pin)
{
  //Takes in the number returned from the checkButton and turns
  //it into the corresponding LED pin number
  if (pin == 1)
  {
    return redLED;
  }
  else if (pin == 2)
  {
    return yelLED;
  }
  else if (pin == 3)
  {
    return grnLED;
  }
  else
  {
    return bluLED;
  }

}

int getSound(int pin)
{
  //Takes the pin number and returns the corresponding tone hz
  if (pin == 1)
  {
    //return NOTE_C4;
    return 252;
  }
  else if (pin == 2)
  {
    //return NOTE_E4;
    return 310;
  }
  else if (pin == 3)
  {
    //return NOTE_G4;
    return 209;
  }
  else
  {
    //return NOTE_C5;
    return 415;
  }
}

int nextColor()
{
  //Generates the next color in the sequence
  int color = random(4) + 1;
  //Serial.println("Color added");
  sequence[roundNum] = color;
}

void playPattern()
{
  //Loops for the amount of round numbers and lights up the LED corresponding to the 
  //color in the sequence and buzzs the correct tone
  for (int i = 0; i < roundNum; i++)
  {
    toner(getSound(sequence[i]));
    digitalWrite(getPinNumber(sequence[i]), HIGH);
    delay(400);
    digitalWrite(getPinNumber(sequence[i]), LOW);
    delay(300);
  }
  //Serial.println("End of pattern");
}

void toner(int hz)
{
  //Method to ease the tone fuction of arduino
  tone(buzzer, hz, 150);
}

void resetPattern()
{
  //Very bad reset pattern
  //Played when the player presses the incorrect color button
  tone(buzzer, 100, 1600);
  digitalWrite(redLED, HIGH);
  delay(200);
  digitalWrite(redLED, LOW);
  delay(200);
  digitalWrite(yelLED, HIGH);
  delay(200);
  digitalWrite(yelLED, LOW);
  delay(200);
  digitalWrite(grnLED, HIGH);
  delay(200);
  digitalWrite(grnLED, LOW);
  delay(200);
  digitalWrite(bluLED, HIGH);
  delay(200);
  digitalWrite(bluLED, LOW);
  delay(200);
}

void openingPattern()
{
  //The opening pattern
  //Just lights up the LEDs forward and backward
  int speedd = 150;
  digitalWrite(redLED, HIGH);
  delay(speedd);
  digitalWrite(redLED, LOW);
  delay(speedd);
  digitalWrite(yelLED, HIGH);
  delay(speedd);
  digitalWrite(yelLED, LOW);
  delay(speedd);
  digitalWrite(grnLED, HIGH);
  delay(speedd);
  digitalWrite(grnLED, LOW);
  delay(speedd);
  digitalWrite(bluLED, HIGH);
  delay(speedd);
  digitalWrite(bluLED, LOW);
  delay(speedd);

  digitalWrite(grnLED, HIGH);
  delay(speedd);
  digitalWrite(grnLED, LOW);
  delay(speedd);
  digitalWrite(yelLED, HIGH);
  delay(speedd);
  digitalWrite(yelLED, LOW);
  delay(speedd);
}

