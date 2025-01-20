/*
  ZMPT101B - AC Voltage sensor
  Calculate Voltage

  modified on 7 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home
*/

// Declare variables to store sensor values and results
double sensorValue1 = 0;
double sensorValue2 = 0;
int crosscount = 0;
int climb_flag = 0;
int val[100];   // Array to store sensor values
int max_v = 0;
double VmaxD = 0;  // Max voltage
double VeffD = 0;  // Effective voltage
double Veff = 0;   // Resulting voltage

// Setup function: Initializes the program
void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
}

// Loop function: Main program logic runs repeatedly
void loop() {
  // Read and process sensor values
  for (int i = 0; i < 100; i++) {
    sensorValue1 = analogRead(A0);  // Read analog sensor value from A0
    if (analogRead(A0) > 511) {
      val[i] = sensorValue1;  // Store sensor value in the array if it's greater than 511
    } else {
      val[i] = 0;  // Otherwise, set the value to 0
    }
    delay(1);  // Short delay for stability
  }

  // Find the maximum sensor value in the array
  max_v = 0;
  for (int i = 0; i < 100; i++) {
    if (val[i] > max_v) {
      max_v = val[i];  // Update max_v if a higher value is found
    }
    val[i] = 0;  // Reset the array element to 0
  }

  // Calculate effective voltage based on the maximum sensor value
  if (max_v != 0) {
    VmaxD = max_v;  // Set VmaxD to the maximum sensor value
    VeffD = VmaxD / sqrt(2);  // Calculate effective voltage (RMS) from VmaxD
    Veff = (((VeffD - 420.76) / -90.24) * -210.2) + 210.2;  // Apply calibration and scaling to Veff
  } else {
    Veff = 0;  // If no maximum value, set Veff to 0
  }

  // Print the calculated voltage to the serial monitor
  Serial.print("Voltage: ");
  Serial.println(Veff);

  VmaxD = 0;  // Reset VmaxD for the next iteration

  delay(100);  // Delay for 100 milliseconds before the next loop
}