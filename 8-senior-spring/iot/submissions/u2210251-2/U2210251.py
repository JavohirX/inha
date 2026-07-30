import cv2
import numpy as np

# here phone's IP camera URL
# For Android: Install "IP Webcam" app from Play Store
# For iPhone: Install "EpocCam" or similar app
# The URL format is typically: http://PHONE_IP:PORT/video
url = "http://192.168.16.170:8080/video"  # here phone's IP

###### Begin capturing video from phone camera ######
# Initialize video capture from the specified URL
cap = cv2.VideoCapture(url)

# Check if video stream is opened successfully
if not cap.isOpened():
    print("Error: Could not open video stream from phone camera")
    print("Please check:")
    print("1. Phone and computer are on the same WiFi network")
    print("2. The IP address and port are correct")
    print("3. The IP Webcam app is running on the phone")
    exit()

###### Human detection and count initialization ######
# Initialize the HOG (Histogram of Oriented Gradients) descriptor
# This is a pre-trained model for detecting people in images
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

print("Starting human detection... Press 'q' to quit")

while True:
    # Read frame from video stream
    ret, frame = cap.read()
    
    if not ret:
        print("Error: Failed to receive frame from phone camera")
        break
    
    # Resize frame for faster processing (optional)
    frame = cv2.resize(frame, (640, 480))
    
    ###### Human detection and counting logic ######
    # Detect humans in the frame
    # detectMultiScale returns bounding boxes of detected humans
    # Parameters:
    # - winStride: step size for the sliding window (8,8 is good balance)
    # - padding: padding around detection window
    # - scale: image pyramid scale factor
    (humans, weights) = hog.detectMultiScale(
        frame,
        winStride=(8, 8),
        padding=(4, 4),
        scale=1.05
    )
    
    # Count the number of humans detected
    human_count = len(humans)
    
    # Draw bounding boxes around detected humans
    for (x, y, w, h) in humans:
        # Draw green rectangle around each detected person
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        # Add label showing "Human Detected"
        cv2.putText(
            frame,
            'Human Detected',
            (x, y - 10),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.5,
            (0, 255, 0),
            2
        )
    
    # Display the count on the frame
    count_text = f'Human Detected : {human_count}'
    cv2.putText(
        frame,
        count_text,
        (10, 30),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        (0, 0, 255),
        2
    )
    
    # Show the video frame with detections
    cv2.imshow('Human Detection - Phone Camera', frame)
    
    # Print count to console
    if human_count > 0:
        print(f'{count_text}')
    
    # Press 'q' to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()