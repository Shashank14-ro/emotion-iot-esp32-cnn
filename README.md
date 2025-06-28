# Emotion-iot-esp32-cnn
CNN emotion detection with real-time LED indicator using ESP32

# Emotion Detection with CNN & ESP32 LED Indicator 💡😄

This project combines image-based facial emotion detection using a Convolutional Neural Network (CNN) and an ESP32 microcontroller. The system detects a user's emotion from a live webcam feed and transmits the result to an ESP32 over serial communication (UART), which then lights up an RGB LED based on the detected emotion.


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
 1. Before we need to connect the esp-32 to our local network for transmiting of signal using network
 2. We need Aurdino IDE Software to dump the code in ESP-32.We need to select the esp-32 dev-c kit and run in it
 3. After we need to check the signal is transmitting through esp-32 to bread board by running the python code
 4. Each led color represents each emotion, so check all led are working or not
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



Thes
