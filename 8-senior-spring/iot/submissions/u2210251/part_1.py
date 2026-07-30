import cv2
import time

url = "http://172.18.0.47:8080/video" #phones ip

###### Begin capturing video from the specified address of the phone ######
# This creates a VideoCapture object that connects to the IP webcam stream
cap = cv2.VideoCapture(url)

# Check if the camera opened successfully
if not cap.isOpened():
    print("Error: Could not open video stream from phone")
    print(f"Make sure the phone is on the same WiFi network and IP Webcam is running")
    print(f"Current URL: {url}")
    exit()

print("Video stream connected successfully!")
print("Press 's' to save a screenshot")
print("Press 'q' to quit")

screenshot_count = 0

while True:
    # Read frame from the video stream
    ret, frame = cap.read()
    
    if not ret:
        print("Error: Failed to grab frame")
        break
    
     # Resize the frame to a smaller resolution (640x480)
    frame = cv2.resize(frame, (640, 480))
    cv2.flip(frame, 1)
    # Display the frame in a window
    cv2.imshow('Phone Camera Feed', frame)
    
    # Wait for key press (1ms delay)
    key = cv2.waitKey(1) & 0xFF
    
    # Press 's' to save screenshot
    if key == ord('s'):
        screenshot_count += 1
        filename = f'screenshot_{screenshot_count}.png'
        cv2.imwrite(filename, frame)
        print(f"Screenshot saved as {filename}")
        
        # Optional: stop after 2 screenshots
        if screenshot_count >= 2:
            print("Two screenshots captured. can press 'q' to quit or continue capturing.")
    
    # Press 'q' to quit
    elif key == ord('q'):
        break

# Release the video capture object and close windows
cap.release()
cv2.destroyAllWindows()

print(f"\nTotal screenshots captured: {screenshot_count}")
print("Remember to take screenshots showing:")
print("1. Myself and desktop with VSCode visible")
print("2. Infinite loop (camera pointing at screen)")