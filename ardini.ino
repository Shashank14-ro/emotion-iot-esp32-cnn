#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "OPPO";       // Change to your WiFi SSID
const char* password = "00000000"; // Change to your WiFi Password

// Web server on port 80
WebServer server(80);

// Emotion state
String receivedEmotion = "Neutral";
String lastEmotion = "";

// RGB LED GPIOs
const int redLED = 2;    // Red component
const int greenLED = 4;  // Green component
const int blueLED = 5;   // Blue component

// Function to set RGB LED color
// Values for r, g, b should be between 0 (off) and 255 (full brightness)
void setRGB(int r, int g, int b) {
  analogWrite(redLED, r);
  analogWrite(greenLED, g);
  analogWrite(blueLED, b);
}

// Function to control LED based on emotion
void controlLED() {
  // Only update if the emotion has changed to avoid unnecessary operations
  if (receivedEmotion == lastEmotion) {
    return;
  }

  lastEmotion = receivedEmotion; // Update the last emotion state

  // Turn off all LEDs first (set to black) to ensure a clean transition
  setRGB(0, 0, 0);

  // Convert the received emotion to lowercase for case-insensitive comparison
  String emotionLower = receivedEmotion;
  emotionLower.toLowerCase();

  Serial.print("Controlling LED for emotion: ");
  Serial.println(emotionLower);

  // Apply LED colors based on the defined emotion constraints
  if (emotionLower == "happy") {
    setRGB(0, 255, 0); // Green (full green, no red or blue)
    Serial.println("Green LED ON for Happy");
  } else if (emotionLower == "sad") {
    setRGB(0, 0, 255); // Blue (full blue, no red or green)
    Serial.println("Blue LED ON for Sad");
  } else if (emotionLower == "angry" || emotionLower == "fear") {
    setRGB(255, 0, 0); // Red (full red, no green or blue)
    Serial.println("Red LED ON for Angry/Fear");
  } else if (emotionLower == "surprise") {
    setRGB(255, 255, 0); // Yellow (full red + full green, no blue)
    Serial.println("Yellow LED ON for Surprise");
  } else if (emotionLower == "neutral" || emotionLower == "disgust") {
    setRGB(255, 255, 255); // White (full red + full green + full blue)
    Serial.println("White LED ON for Neutral/Disgust");
  } else {
    // If an unrecognized emotion is received, turn all LEDs off
    setRGB(0, 0, 0);
    Serial.println("LEDs OFF - Unknown emotion received");
  }

  // Print the approximate PWM values for debugging.
  // Note: analogRead on an OUTPUT pin does not accurately reflect the set PWM duty cycle.
  // For true status, you'd track the r, g, b values in global variables.
  Serial.print("LED states (PWM) - Red: ");
  Serial.print(analogRead(redLED));
  Serial.print(", Green: ");
  Serial.print(analogRead(greenLED));
  Serial.print(", Blue: ");
  Serial.println(analogRead(blueLED));
}

// Handler for the root URL ("/")
void handleRoot() {
  String message = "ESP32 Emotion Display with LED Control\n";
  message += "Usage:\n";
  message += "  /emotion?emotion=<emotion_name> (e.g., happy, angry, sad, fear, neutral, surprise, disgust)\n";
  message += "  /status to see current emotion and LED states\n";
  message += "  /reset to turn off all LEDs and reset emotion to Neutral\n";
  server.send(200, "text/plain", message);
}

// Handler for the "/emotion" endpoint
void handleEmotion() {
  if (server.hasArg("emotion")) {
    receivedEmotion = server.arg("emotion");
    Serial.print("Received emotion: ");
    Serial.println(receivedEmotion);
    server.send(200, "text/plain", "Emotion received: " + receivedEmotion);
    controlLED(); // Call controlLED to update the LED based on the new emotion
  } else {
    // If the "emotion" argument is missing
    server.send(400, "text/plain", "Error: 'emotion' argument missing. Usage: /emotion?emotion=<emotion_name>");
  }
}

// Handler for the "/status" endpoint
// Returns current emotion and approximate LED states in JSON format
void handleStatus() {
  String status = "{ \"emotion\": \"" + receivedEmotion + "\", ";
  // Again, analogRead on an OUTPUT pin might not be perfectly accurate for set PWM values.
  status += "\"red_pwm\": " + String(analogRead(redLED)) + ", ";
  status += "\"green_pwm\": " + String(analogRead(greenLED)) + ", ";
  status += "\"blue_pwm\": " + String(analogRead(blueLED)) + " }";
  server.send(200, "application/json", status);
}

// Handler for the "/reset" endpoint
// Turns off all LEDs and resets the internal emotion state
void handleReset() {
  receivedEmotion = "Neutral"; // Reset the current emotion
  lastEmotion = "";            // Clear last emotion to force an LED update next time
  setRGB(0, 0, 0);             // Turn off all LEDs
  Serial.println("LEDs reset to OFF and emotion state reset.");
  server.send(200, "text/plain", "LEDs turned off and emotion reset.");
}

// Arduino setup function - runs once on startup
void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("ESP32 Emotion Receiver with RGB LED Control");

  // Set LED pins as outputs. This is crucial for analogWrite to work.
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // Short LED test sequence at startup
  setRGB(255, 255, 255); // Turn all LEDs ON (White)
  Serial.println("All LEDs ON (White) for testing...");
  delay(2000); // Keep them on for 2 seconds
  setRGB(0, 0, 0); // Turn all LEDs OFF
  Serial.println("LEDs OFF - Ready to receive emotions");

  // Connect to WiFi network
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Wait for 1 second before retrying
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP()); // Print the assigned IP address

  // Define server routes (endpoints) and their respective handler functions
  server.on("/", handleRoot);
  server.on("/emotion", HTTP_GET, handleEmotion); // HTTP GET request for /emotion
  server.on("/status", HTTP_GET, handleStatus);   // HTTP GET request for /status
  server.on("/reset", HTTP_GET, handleReset);     // HTTP GET request for /reset

  server.begin(); // Start the HTTP server
  Serial.println("HTTP Server started on port 80");
}

// Arduino loop function - runs repeatedly after setup
void loop() {
  server.handleClient(); // Continuously listen for incoming client requests
}
