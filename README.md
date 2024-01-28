# ESP32 Over-The-Air (OTA) Update Server

This project enables an ESP32 to act as an OTA update server. Using this server, you can wirelessly upload firmware updates to any ESP32 device on the network.

## Features

- Fully Asyncronous, no handle() to run in loop.
- Hosts an OTA endpoint in esp32 that listens for firmware binary uploads.
- Allows updates to be triggered using HTTP POST requests.

## Requirements

- ESPAsyncWebServer library
- AsyncTCP library for ESP32
- ESP32 board
- Arduino IDE or PlatformIO for compiling and uploading the firmware

## Setup and Configuration

1. Install the required libraries in your Arduino IDE or PlatformIO environment.
2. Open the provided sketch in the IDE.
3. Insert your WiFi credentials into the `ssid` and `password` variables in the sketch.
4. Upload the sketch to your ESP32.

## Usage

Once the ESP32 is running the uploaded sketch, it will act as an OTA update server on the local network. To update an ESP32 device:

1. Make sure that your ESP32 device is connected to power and the same network as your computer.
2. Open a terminal or command prompt on your computer.
3. Use `curl` to send a firmware image to the ESP32 using the following command:

   ```bash
   curl -F "image=@/path/to/firmware.bin" http://<ESP32-local-IP>/update
   ```

   Replace `/path/to/firmware.bin` with the actual path to your compiled firmware and `<ESP32-local-IP>` with the local IP address of your ESP32 device.

You should see the update progress in the Serial Monitor of the ESP32. Once the update is complete, the ESP32 will restart with the new firmware.


## Note on Security

This example does not implement security features such as HTTPS or authentication. It is recommended to secure the OTA update process in production environments to protect against unauthorized access.

## Contributing

Feel free to fork this project and contribute. Here's how you can contribute:

- Fork the project and create a new branch.
- Make your changes and commit them.
- Create a pull request with a comprehensive description of changes.

## License

This project is provided under the MIT License. See [LICENSE](LICENSE) for the full details.
