# =============================================================================
# 1. SETUP AND IMPORTS
# =============================================================================
import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Flatten, Dense, Dropout, GlobalAveragePooling2D
from tensorflow.keras.applications import VGG16
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.callbacks import EarlyStopping, ReduceLROnPlateau

import cv2
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import classification_report, confusion_matrix
import seaborn as sns
import os

print("TensorFlow Version:", tf.__version__)

# =============================================================================
# 2. DATA PREPARATION
# =============================================================================
base_dir = '/kaggle/input/chest-xray-pneumonia/chest_xray/chest_xray'

train_dir = os.path.join(base_dir, 'train')
validation_dir = os.path.join(base_dir, 'val')
test_dir = os.path.join(base_dir, 'test')

if not os.path.exists(base_dir):
    raise FileNotFoundError(f"Dataset directory not found at {base_dir}. Please double-check the input path in your Kaggle notebook.")

IMG_WIDTH, IMG_HEIGHT = 224, 224
BATCH_SIZE = 32

train_datagen = ImageDataGenerator(rescale=1./255, rotation_range=20, width_shift_range=0.1, height_shift_range=0.1, shear_range=0.1, zoom_range=0.1, horizontal_flip=True, fill_mode='nearest')
validation_datagen = ImageDataGenerator(rescale=1./255)
test_datagen = ImageDataGenerator(rescale=1./255)

train_generator = train_datagen.flow_from_directory(train_dir, target_size=(IMG_WIDTH, IMG_HEIGHT), batch_size=BATCH_SIZE, class_mode='binary')
validation_generator = validation_datagen.flow_from_directory(validation_dir, target_size=(IMG_WIDTH, IMG_HEIGHT), batch_size=BATCH_SIZE, class_mode='binary', shuffle=False)
test_generator = test_datagen.flow_from_directory(test_dir, target_size=(IMG_WIDTH, IMG_HEIGHT), batch_size=BATCH_SIZE, class_mode='binary', shuffle=False)

print("Class Indices:", train_generator.class_indices)

# =============================================================================
# 3. MODEL BUILDING (TRANSFER LEARNING WITH VGG16)
# =============================================================================
base_model = VGG16(weights='imagenet', include_top=False, input_shape=(IMG_WIDTH, IMG_HEIGHT, 3))
for layer in base_model.layers:
    layer.trainable = False

x = base_model.output
x = GlobalAveragePooling2D()(x)
x = Dense(512, activation='relu')(x)
x = Dropout(0.5)(x)
predictions = Dense(1, activation='sigmoid')(x)

model = Model(inputs=base_model.input, outputs=predictions)
model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=0.0001), loss='binary_crossentropy', metrics=['accuracy'])
model.summary()

# =============================================================================
# 4. MODEL TRAINING
# =============================================================================
early_stopping = EarlyStopping(monitor='val_loss', patience=5, restore_best_weights=True)
reduce_lr = ReduceLROnPlateau(monitor='val_loss', factor=0.2, patience=3, min_lr=1e-6)

history = model.fit(train_generator, epochs=20, validation_data=validation_generator, callbacks=[early_stopping, reduce_lr])

output_model_path = '/kaggle/working/pneumonia_vgg16_model.h5'
model.save(output_model_path)
print(f"Model saved as {output_model_path}")

# =============================================================================
# 5. MODEL EVALUATION
# =============================================================================
test_loss, test_accuracy = model.evaluate(test_generator)
print(f"\nTest Loss: {test_loss:.4f}")
print(f"Test Accuracy: {test_accuracy*100:.2f}%")

predictions_prob = model.predict(test_generator)
predicted_classes = (predictions_prob > 0.5).astype(int).flatten()
true_classes = test_generator.classes
class_labels = list(test_generator.class_indices.keys())

print("\nClassification Report:")
print(classification_report(true_classes, predicted_classes, target_names=class_labels))

cm = confusion_matrix(true_classes, predicted_classes)
plt.figure(figsize=(8, 6))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=class_labels, yticklabels=class_labels)
plt.xlabel('Predicted Label')
plt.ylabel('True Label')
plt.title('Confusion Matrix')
plt.show()

# =============================================================================
# 6. PREDICTION AND VISUALIZATION FUNCTION
# =============================================================================
def predict_and_visualize(image_path, model):
    img = cv2.imread(image_path)
    if img is None:
        print(f"Error: Unable to load image at {image_path}")
        return

    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_resized = cv2.resize(img_rgb, (IMG_WIDTH, IMG_HEIGHT))
    img_array = np.expand_dims(img_resized, axis=0) / 255.0
    
    prediction = model.predict(img_array)[0][0]
    
    if prediction > 0.5:
        label = "PNEUMONIA"
        confidence = prediction
        color = (0, 0, 255)
    else:
        label = "NORMAL"
        confidence = 1 - prediction
        color = (0, 255, 0)
        
    text = f"{label} ({confidence*100:.2f}%)"
    output_img = img.copy()
    cv2.putText(output_img, text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.9, color, 2)

    output_filename = '/kaggle/working/detected_' + os.path.basename(image_path)
    cv2.imwrite(output_filename, output_img)
    print(f"Result saved as {output_filename}")
    
    plt.figure(figsize=(6, 6))
    plt.imshow(cv2.cvtColor(output_img, cv2.COLOR_BGR2RGB))
    plt.title("Prediction Result")
    plt.axis('off')
    plt.show()

# =============================================================================
# 7. PREDICTION ON YOUR CUSTOM UPLOADED IMAGE
# =============================================================================
custom_image_path = "/kaggle/input/source/task_3_source.png"

if os.path.exists(custom_image_path):
    print(f"Found image at: {custom_image_path}")
    print("\n--- Running prediction on your custom image ---")
    predict_and_visualize(custom_image_path, model)
else:
    print(f"Error: Image not found at {custom_image_path}. Please check the path from the Kaggle sidebar.")
