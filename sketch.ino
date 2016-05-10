// Alan Ness 2/2016

const int temperaturePin = 0;
const int BLUE_PIN = 9;
const int GREEN_PIN = 10;
const int RED_PIN = 11;

// Color range
const int MIN = 0;
const int MAX = 768;

//const int COLD_LIGHT = 468;
const int COLD_LIGHT = 0;
const int HOT_LIGHT = 768;

//const int LOW_TEMP = 60;
const int LOW_TEMP = 65;
const int HIGH_TEMP = 90;

// Initiate stuff
void setup()
{
	Serial.begin(9600);
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);
}

float prevDegreesF = 60;
void loop()
{
	// Collect data
	float voltage, degreesC, degreesF;
	voltage = getVoltage(temperaturePin);
	degreesC = (voltage - 0.5) * 100.0;
	degreesF = degreesC * (9.0/5.0) + 32.0;

	// Debug
	Serial.print("voltage: ");
	Serial.print(voltage);
	Serial.print("	prev deg F: ");
	Serial.print(prevDegreesF);
	Serial.print("	deg F: ");
	Serial.println(degreesF);

	// Update the LED using the new temperature
	adjustBrightness(degreesF, prevDegreesF);

	// Prepare for next loop
	prevDegreesF = degreesF;
	delay(1000);
}

float getVoltage(int pin)
{
	// Magical voltage / temperature conversion
	return (analogRead(pin) * 0.004882814);
}

// Adjust the brightness based on the new temperature
void adjustBrightness(int degreesF, int prevDegreesF){
	
	// If there wasn't a change in temp, just pulse a single degree
	if(degreesF == prevDegreesF){
		prevDegreesF = degreesF - 1;
	}

	// Calculate the shift in color values
	int incrementBy =(HOT_LIGHT - COLD_LIGHT) / (HIGH_TEMP - LOW_TEMP);
	int movement = degreesF - LOW_TEMP;
	int movementPrev = prevDegreesF - LOW_TEMP;
	int newLow = COLD_LIGHT + movement * incrementBy;
	int newHigh = COLD_LIGHT + movementPrev * incrementBy;
	
	// Don't excede the min/max color values
	if(newLow < MIN){
		newLow = MIN;
	}
	if(newHigh > MAX){
		newHigh = MAX;
	}

	// Do technical stuff in here
	pulseColorRange(newLow, newHigh);
}

////////////////
// Below is a modified version of the Circuit #3 example project in the Vilros's Ultimate Starter Kit Guide for the Arduino Uno
////////////////
void pulseColorRange(int low, int high)
{
	int x;	
	// Pulse from low to high
	for (x = low; x < high; x++)
	{
		colorToLED(x);
		delay(10);
	}

	// Then pulse from high to low
	for (x = high; x > low; x--)
	{
		colorToLED(x);
		delay(10);
	}
}
void colorToLED(int color)
{
	int redIntensity;
	int greenIntensity;
	int blueIntensity;
	
	// GREEN-ish, the coldest color	
	if (color <= 255)
	{
		redIntensity = 255 - color;
		greenIntensity = color;
		blueIntensity = 0;
	}

	// BLUE-ish, the medium color
	else if (color <= 511)
	{
		redIntensity = 0;
		greenIntensity = 255 - (color - 256); 
		blueIntensity = (color - 256);
	}

	// RED-ish, the hottest color
	else 
	{
		redIntensity = (color - 512);
		greenIntensity = 0;
		blueIntensity = 255 - (color - 512);
	}

	// Output the calculated pin values to the LED
	analogWrite(RED_PIN, redIntensity);
	analogWrite(BLUE_PIN, blueIntensity);
	analogWrite(GREEN_PIN, greenIntensity);
}
