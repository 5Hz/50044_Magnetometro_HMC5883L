// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  
  Serial.println("**********************************************");
  Serial.println("***************Electronica 5 Hz***************");
  Serial.println("******Programa de prueba para el HMC5883******");
  Serial.println("**********************************************");

  Serial.println("Starting the I2C interface.");
  Wire.begin(); // Start the I2C interface.

  Serial.println("Constructing new HMC5883L");
  compass = HMC5883L(); // Construct a new HMC5883 compass.
    
  Serial.println("Setting scale to +/- 1.3 Ga");
  error = compass.SetScale(1.3); // Set the scale of the compass.
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));
  
  Serial.println("Setting measurement mode to continous.");
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));
}

// Our main program loop.
void loop()
{
  menu();
  do{}while(Serial.available() == 0);
  switch (Serial.read())
  {
    case '1':
      //read the x tilt
      do{bargraphx();}while(Serial.read() != '*');
    break;
    case '2':
      //read the y tilt
      do{bargraphy();}while(Serial.read() != '*');
    break;
    case '3':
      //read the z tilt
      do{bargraphz();}while(Serial.read() != '*');
    break;
    default:
      Serial.println("intenta otra vez :)");
    break;
  }
}


void menu()
{
  Serial.println("Que eje quieres medir?");
  Serial.println("1.- x");
  Serial.println("2.- y");
  Serial.println("3.- z");
}
  
void bargraphx()
{
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.ReadRawAxis();
  int x = raw.XAxis;
    for (int barx = constrain(map(x, -800, 800, 0, 40), -800, 800); barx>0;barx--)
    {
      Serial.print("x");
    }
    Serial.println(x);
    delay(100);
}

void bargraphy()
{
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.ReadRawAxis();
  int y = raw.YAxis;
    for (int bary = constrain(map(y, -800, 800, 0, 40), -800, 800); bary>0; bary--)
    {
      Serial.print("y");
    }
    Serial.println(y);
    delay(100);
}

void bargraphz()
{
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.ReadRawAxis();
  int z = raw.ZAxis;
    for (int barz = constrain(map(z, -800, 800, 0, 40), -800, 800); barz>0;barz--)
    {
      Serial.print("z");
    }
    Serial.println(z);
    delay(100);
}
