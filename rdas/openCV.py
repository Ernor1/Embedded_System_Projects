import cv2

# Load pre-trained models
traffic_sign_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'stop_sign2.xml')
object_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalcatface.xml')

# Load the image
image = cv2.imread('images.png')

# Convert the image to grayscale
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Perform traffic sign detection
traffic_signs = traffic_sign_cascade.detectMultiScale(gray_image, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

# Perform object detection
objects = object_cascade.detectMultiScale(gray_image, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

# Draw rectangles around the detected traffic signs
for (x, y, w, h) in traffic_signs:
    cv2.rectangle(image, (x, y), (x+w, y+h), (0, 0, 255), 2)

# Draw rectangles around the detected objects
for (x, y, w, h) in objects:
    cv2.rectangle(image, (x, y), (x+w, y+h), (255, 0, 0), 2)

# Display the image with detections
cv2.imshow('Traffic Sign and Object Detection', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
