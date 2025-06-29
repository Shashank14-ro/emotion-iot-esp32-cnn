# Emotion-iot-esp32-cnn
CNN emotion detection with real-time LED indicator using ESP32

# Emotion Detection with CNN & ESP32 LED Indicator 💡😄

This project combines image-based facial emotion detection using a Convolutional Neural Network (CNN) and an ESP32 microcontroller. The system detects a user's emotion from a live webcam feed and transmits the result to an ESP32 over serial communication (UART), which then lights up an RGB LED based on the detected emotion.

Haarcascade.xml is used for face detection in this project. The detected faces are classified using a CNN algorithm, and the result is transmitted via an ESP32 microcontroller, which sends signals to a breadboard to control an LED indicator.

## 🧠 Features

- Real-time facial emotion detection using CNN
- Serial communication between Python and ESP32 (UART)
- RGB LED feedback for detected emotions
- Lightweight, efficient model for fast inference
- Easily extendable to IoT applications (e.g., smart devices)


## 📦 Tech Stack

- **Frontend**: OpenCV (for webcam video capture)
- **Backend**: Python (TensorFlow/Keras-based CNN)
- **Hardware**: ESP32, RGB LED
- **Communication**: UART (Serial) via USB
- **Model**: Trained on FER2013 dataset

```
## 🛠 Project Structure

emotion-iot-esp32-cnn/
├── esp32_code/ # Arduino code for ESP32
│ └── emotion_led.ino
├── python_code/ # CNN-based detection in Python
│ ├── detect_emotion.py
│ ├── model.h5 # Trained CNN model
│ └── utils.py
├── images/ # Demo screenshots or system photos
├── requirements.txt # Python dependencies
├── README.md
└── LICENSE
```
🔌 ESP32 Setup
```
Open esp32_code/emotion_led.ino in Arduino IDE

Select correct board: ESP32 Dev Module

Upload the code to your ESP32

Connect RGB LED to the specified GPIO pins

ESP32 listens over UART and changes LED color based on emotion received
```

Steps:
   1. Connect the ESP32 to your local network to enable signal transmission over Wi-Fi.
      
   2.Install the Arduino IDE and select the ESP32 DevKit board from the board manager.
   
   3.Upload the code to ESP32 via the Arduino IDE.
   
   4.Run the Python script to start detecting emotions and sending the results to ESP32 through UART.
   
   5.Verify signal transmission by observing the LED behavior on the breadboard.
   
   6.Each LED color corresponds to a specific emotion, so ensure all LEDs function correctly.
   
🎯 Emotion-to-LED Mapping
```
  Emotion	LED Color
    Happy	Green
    Sad	Blue
    Angry	Red
    Surprise	Yellow
    Neutral	White
```
These are the colors 

