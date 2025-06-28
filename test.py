import cv2
import numpy as np
import tensorflow as tf
import requests
import time

# Load the trained model
model = tf.keras.models.load_model('my_model.keras')

# Load Haar cascade for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Emotion labels (should match your training data)
emotion_labels = ['Angry', 'Disgust', 'Fear', 'Happy', 'Neutral', 'Sad', 'Surprise']

# ESP32 IP address (replace with your ESP32's IP)
esp32_ip = "YOUR_ESP32_IP_ADDRESS"  # Replace with the IP from serial monitor
emotion_endpoint = f"http://{esp32_ip}/emotion"

# Open laptop camera (0 for default camera)
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        print("Error: Could not read frame.")
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        face_roi = gray[y:y + h, x:x + w]
        try:
            resized_face = cv2.resize(face_roi, (48, 48))
            normalized_face = resized_face / 255.0
            reshaped_face = np.expand_dims(normalized_face, axis=[0, -1])
            prediction = model.predict(reshaped_face)[0]
            emotion_index = np.argmax(prediction)
            predicted_emotion = emotion_labels[emotion_index]
            cv2.putText(frame, predicted_emotion, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

            # Send emotion to ESP32
            try:
                params = {"emotion": predicted_emotion}
                response = requests.get(emotion_endpoint, params=params, timeout=1)
                if response.status_code == 200:
                    print(f"Sent emotion: {predicted_emotion} to ESP32")
                else:
                    print(f"Error sending emotion to ESP32: {response.status_code} - {response.text}")
            except requests.exceptions.ConnectionError as e:
                print(f"Could not connect to ESP32: {e}")
            except requests.exceptions.Timeout:
                print("Connection to ESP32 timed out.")

        except Exception as e:
            print(f"Error processing face: {e}")

    cv2.imshow('Facial Emotion Recognition', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
