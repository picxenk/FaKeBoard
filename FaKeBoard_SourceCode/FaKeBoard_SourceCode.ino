// FA.KE. Board
// by SeungBum Kim <picxenk@gmail.com>

boolean debugOn = false;

int lightSensorPin = A0;
int toneOutPin = 0;

int lightValue;
int highestLightValue = 100;
int lowestLightValue = 100;

int note;
int noteDuration = 100;
int noteDelay = 20;


void setup() {
  if (debugOn) {
    Serial.begin(9600);
  }
}

/**********  MAIN CODE : READ ME FIRST **********/
void loop() {
  lightValue = read_light_value_from(lightSensorPin);
  
  note = make_note_from(lightValue);
  
  play_tone(note);
 
  check_value_for_debugging(debugOn); 
}


/**********  DETAILS BELOW **********/
int read_light_value_from(int pin) {
  return analogRead(pin);
}

int make_note_from(int value) {
  int halfValue = (lowestLightValue + highestLightValue) / 2;
  if (value > highestLightValue) {
    highestLightValue = value;
  }
  if (value < lowestLightValue) {
    lowestLightValue = value;
  }
  
  if (value > halfValue) {
    return map(value, halfValue, highestLightValue, 0, 3000);
  } else {
    return 0;
  }
}

void play_tone(int value) {
  tone(toneOutPin, value, noteDuration);
  delay(noteDelay);
  noTone(toneOutPin);
}

void check_value_for_debugging(boolean debugOn) {
  if (debugOn) {
    Serial.print("light = " );                       
    Serial.print(lightValue);      
    Serial.print("\t note = ");      
    Serial.println(note);  
  }
}
