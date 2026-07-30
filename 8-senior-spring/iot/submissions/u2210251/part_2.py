import cv2
import pytesseract
import re
import time  # Added for FPS control


pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

# Replace this URL with the phone's IP webcam URL
url = "http://172.18.0.47:8080/video" 

###### FPS control settings ######
PROCESS_FPS = 2  # Process only 2 frames per second
PROCESS_INTERVAL = 1.0 / PROCESS_FPS  # 0.5 seconds between processing

###### Begin capturing video from the specified address of the phone ######
cap = cv2.VideoCapture(url)

# Check if the camera opened successfully
if not cap.isOpened():
    print("Error: Could not open video stream from phone")
    print(f"Make sure the phone is on the same WiFi network and IP Webcam is running")
    print(f"Current URL: {url}")
    exit()

print("Video stream connected successfully!")
print("Show a number to the camera to detect temperature")
print("Press 's' to save a screenshot")
print("Press 'q' to quit")

screenshot_count = 0
last_process_time = 0
last_detected_temperature = None  # Store last detected value

while True:
    # Read frame from the video stream
    ret, frame = cap.read()
    
    if not ret:
        print("Error: Failed to grab frame")
        break
    
    frame = cv2.resize(frame, (640, 480))
    
    # Create a copy of the frame for display
    display_frame = frame.copy()
    
    current_time = time.time()
    
    # Only process OCR if enough time has passed
    if current_time - last_process_time >= PROCESS_INTERVAL:
        last_process_time = current_time
        
        ###### Digit detection code snippet ######
        # Convert frame to grayscale for better OCR accuracy
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        
        # Apply thresholding to improve digit detection
        _, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)
        
        # Use pytesseract to detect text/digits in the image
        text = pytesseract.image_to_string(thresh, config='--psm 6 digits')
        
        # Extract only numbers from the detected text
        detected_numbers = re.findall(r'\d+', text)
        
        # If we detected any numbers, update the last detected temperature
        if detected_numbers:
            last_detected_temperature = detected_numbers[0]
            print(f"Detected temperature: {last_detected_temperature}")
    
    # Display the last detected temperature (even if not processing this frame)
    if last_detected_temperature:
        text_to_display = f"Temperature in the room is {last_detected_temperature}"
        
        cv2.putText(display_frame, text_to_display, 
                    (10, 50),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    1.2,
                    (0, 0, 255),
                    3,
                    cv2.LINE_AA)
    
    # Display the frame in a window
    cv2.imshow('Temperature Detection', display_frame)
    
    # Wait for key press (1ms delay)
    key = cv2.waitKey(1) & 0xFF
    
    # Press 's' to save screenshot
    if key == ord('s'):
        screenshot_count += 1
        filename = f'screenshot_{screenshot_count}.png'
        cv2.imwrite(filename, display_frame)
        print(f"Screenshot saved as {filename}")
    
    # Press 'q' to quit
    elif key == ord('q'):
        break

# Release the video capture object and close windows
cap.release()
cv2.destroyAllWindows()

print(f"\nTotal screenshots captured: {screenshot_count}")
print("Remember: Screenshot should show the person and the number visible!")