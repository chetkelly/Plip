#include <Plip.h>

// Use the pin number where your IR LED is connected, active low
// The second argument is optional and defaults to 2000. If your receiver isn't accepting the code at the default you may need to increase/decrease this slightly
Plip plip(3, 2100); // Example with custom timing parameter

void setup() {
  // No setup needed for Plip
}

void loop() {
  // Send a Plip code (replace 12345 with your actual code)
  // The second argument is the number of repeats for code sending, this is optional and defaults to 3
  plip.send(12345, 3); // Sends code 12345, 3 times
  delay(5000); // Wait 5 seconds before sending again
} 