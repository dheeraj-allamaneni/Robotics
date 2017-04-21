




// Created a simple color detection system using easily available materials.
// A photoresistor
int photoResistor = 0;

int b = 2;
int r = 3;
int g = 4;
int y = 5;

//Calibration

double bAdj = 1.0;
double rAdj = 1.02;
double gAdj = 1.0;
double yAdj = 1.17;
double ambientAdj = 1.0;

void setup()
{
  // Determining the pinModes for the pins that will be used ahead.
  pinMode(g, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(photoResistor, OUTPUT);
  Serial.begin(9600);
}

void loop()
{  
  //All of this code is repeated till the end of runTime.
    allOff();
    delay(100);
    asses(100,100);
}

void allOff()
{
    digitalWrite(g, HIGH);
    digitalWrite(y, HIGH);
    digitalWrite(r, HIGH);
    digitalWrite(b, HIGH);
}

void allOn()
{
    digitalWrite(g, LOW);
    digitalWrite(y, LOW);
    digitalWrite(r, LOW);
    digitalWrite(b, LOW);
}

void pulse(int colour)
{
  // Using a RGB light and LDR to determine the color of the object.
   for(int i=0;i<3;i++)
   {
      digitalWrite(colour, LOW);
      delay(100);
      digitalWrite(colour, HIGH);
      delay(100);
   }
}
 

void asses(int colldownTime, int saturationTime)
{
    // the value from the photoresistor is recieved and processed to evaluate the reflection co-efficeint of the object to determine its color.
    delay(500);
    double ambient = analogRead(photoResistor);
    Serial.print("Ambient: ");
    Serial.println(ambient*ambientAdj);
    
    digitalWrite(g, LOW);
    delay(saturationTime);
    double green = analogRead(photoResistor);
    Serial.print("Green: ");
    Serial.println(green*gAdj);
    digitalWrite(g, HIGH);
    delay(colldownTime);
    
    digitalWrite(r, LOW);
    delay(saturationTime);
    double red = analogRead(photoResistor);
    Serial.print("Red: ");
    Serial.println(red*rAdj);
    digitalWrite(r, HIGH);
    delay(colldownTime);
    
    digitalWrite(b, LOW);
    delay(saturationTime);
    double blue = analogRead(photoResistor);
    Serial.print("Blue: ");
    Serial.println(blue*bAdj);
    digitalWrite(b, HIGH);
    delay(colldownTime);
    
    digitalWrite(y, LOW);
    delay(saturationTime);
    double yellow = analogRead(photoResistor);
    Serial.print("Yellow: ");
    Serial.println(yellow*yAdj);
    digitalWrite(y, HIGH);
    delay(colldownTime);
    
    double rawData[] = {(green*gAdj), (red*rAdj), (blue*bAdj), (yellow*yAdj)};
    double maximum = ambient*ambientAdj;
    int decision;
    
    for (int i=0; i<4; i++)  
    {
       if (maximum<rawData[i])
      {
          maximum = rawData[i];
          decision = i+1;
      }
    }
         
    Serial.println("");

    // Depending on the amount of value recieved the color is determined and printed on the serial monitor.
    if(decision == 0)
    {
       Serial.println("No object detected.");
       allOn();
       delay(1000);
       allOff();
    }
    else if(decision == 1)
    {
       Serial.println("GREEN");
       pulse(g);
    }
    else if(decision == 2)
    {
       Serial.println("RED");
       pulse(r);
    }
    else if(decision == 3)
    {
       Serial.println("BLUE");
       pulse(b);
    }
    else if(decision == 4)
    {
       Serial.println("YELLOW");
       pulse(y);
    }
    Serial.println("");

}


 

