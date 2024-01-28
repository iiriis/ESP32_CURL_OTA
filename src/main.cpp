#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Update.h>

// Network credentials
const char* ssid = ":)";
const char* password = "B003";

// Create an instance of the server on port 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200); // Start the serial communication

  // Connect to the provided Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP()); // Print the local IP address

  // Define a route for the root URL which provides instructions for OTA update
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "You are nearby, goto /update with CURL :) ");
  });

  // Define a route for receiving OTA updates
  server.on("/update", HTTP_POST, 
    [](AsyncWebServerRequest *request) {
        // This callback is for the response part of the HTTP POST request
        // It is called after the entire request is processed
    },
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
        // This callback is for handling the incoming data (the new firmware)
        // It gets called for each chunk of the file being uploaded

        // Start the update process if this is the first chunk received
        if (!index) {
            Serial.println("Update Start: " + filename);
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { // Begin with unknown size for now
                Update.printError(Serial); // Print any errors
            }
        }
        
        // If no error, write the received data to the flash memory
        if (!Update.hasError()) {
            if (Update.write(data, len) != len) {
                Update.printError(Serial); // Print any errors
            }
        }

        // If this is the last chunk of data, finalize the update
        if (final) {
          bool success = Update.end(true);
          Serial.println(success ? "Update Complete" : "Update Failed");
          request->send(200, "text/plain", success ? "Update Success :)" : "Update Failed :(");
          if (success) {
              ESP.restart();
          }
          else {
              Update.printError(Serial); // Print any errors
              request->send(200, "text/plain", "Update Failed :("); // Send failed response
          }
        }
    }
  );

  server.begin(); // Start the AsyncWebServer
}

void loop() {
  // Periodically print a message (every second) to show the loop is running
  Serial.println("1234");
  delay(1000);
  // No other code here since the HTTP server runs in the background
}
