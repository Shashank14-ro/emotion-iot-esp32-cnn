# emotion-iot-esp32-cnn
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
