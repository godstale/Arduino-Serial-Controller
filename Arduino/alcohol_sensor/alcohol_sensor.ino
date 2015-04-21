#define COUNT_MAX 10
int index = 0;
float values[COUNT_MAX];

void setup() {
  Serial.begin(9600);
  
  initialize();
  delay(3000);
}

void loop() {
  float vol;
  int sensorValue = analogRead(A0);  // read data
  values[index] = sensorValue;
  
  // calc average and display value
  if(index >= COUNT_MAX - 1) {
    float average = calcAverage();
    float bac = pow(((-3.757)*pow(10, -7))*average, 2) + 0.0008613*average -0.3919;
    
    Serial.print("a");
    Serial.print(bac, 4);
    Serial.print("z");
    
    index=0;
  } else {
    index++;
  }
  
  delay(100);  // prepare next read
}

void initialize() {
  for(int i=0; i<COUNT_MAX; i++) {
    values[i] = 0;
  }
}

float calcAverage() {
  float avg = 0;
  for(int i=0; i<COUNT_MAX; i++) {
    avg += values[i];
  }
  avg = avg / COUNT_MAX;
  return avg;
}

