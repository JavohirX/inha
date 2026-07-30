import cv2
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

#variables to change: image_path, k
def segment_local_image_with_kmeans(image_path, k=4):
    try:
        original_image_bgr = cv2.imread(image_path)
        if original_image_bgr is None:
            print(f"Error: Could not read the image file at {image_path}")
            print("Please check if the path is correct and the file is a valid image.")
            return None, None
            
        original_image = cv2.cvtColor(original_image_bgr, cv2.COLOR_BGR2RGB)
    except Exception as e:
        print(f"An error occurred while loading the image: {e}")
        return None, None

    pixel_vals = original_image.reshape((-1, 3))
    pixel_vals = np.float32(pixel_vals)

    kmeans = KMeans(n_clusters=k, n_init=10, random_state=42)
    kmeans.fit(pixel_vals)

    centers = np.uint8(kmeans.cluster_centers_)
    labels = kmeans.labels_

    segmented_data = centers[labels.flatten()]
    segmented_image = segmented_data.reshape(original_image.shape)

    return original_image, segmented_image

if __name__ == "__main__":
    LOCAL_IMAGE_PATH = r"C:\Users\user\Desktop\hw\task_2_source.png"
    NUM_CLUSTERS = 5
    
    original, segmented = segment_local_image_with_kmeans(LOCAL_IMAGE_PATH, k=NUM_CLUSTERS)
    
    if original is not None and segmented is not None:
        plt.figure(figsize=(12, 6))

        plt.subplot(1, 2, 1)
        plt.imshow(original)
        plt.title('Original Image')
        plt.axis('off')

        plt.subplot(1, 2, 2)
        plt.imshow(segmented)
        plt.title(f'Segmented Image (k={NUM_CLUSTERS})')
        plt.axis('off')

        plt.tight_layout()
        plt.show()
