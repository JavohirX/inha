import cv2
import numpy as np
import datetime

WIDTH, HEIGHT = 500, 500
BG_COLOR = (255, 255, 255)
INITIAL_COLOR = (0, 0, 0)
INITIAL_THICKNESS = 5

drawing = False
prev_pt = None
color = list(INITIAL_COLOR)
thickness = INITIAL_THICKNESS

canvas = np.full((HEIGHT, WIDTH, 3), BG_COLOR, dtype=np.uint8)

palette = [
    (0, 0, 0),
    (0, 0, 255),
    (0, 255, 0),
    (255, 0, 0),
    (0, 255, 255),
    (255, 0, 255),
    (255, 255, 0)
]
palette_index = 0

def mouse_callback(event, x, y, flags, param):
    global drawing, prev_pt, canvas, color, thickness
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        prev_pt = (x, y)
        cv2.circle(canvas, prev_pt, max(1, thickness // 2), tuple(color), -1)
    elif event == cv2.EVENT_MOUSEMOVE and drawing:
        current_pt = (x, y)
        cv2.line(canvas, prev_pt, current_pt, tuple(color), thickness, lineType=cv2.LINE_AA)
        prev_pt = current_pt
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        current_pt = (x, y)
        cv2.line(canvas, prev_pt, current_pt, tuple(color), thickness, lineType=cv2.LINE_AA)
        prev_pt = None
    elif event == cv2.EVENT_RBUTTONDOWN:
        canvas[:] = BG_COLOR

def show_instructions(img):
    lines = [
        "drawer1"
    ]
    x, y0 = 8, 20
    for i, line in enumerate(lines):
        y = y0 + i * 20
        cv2.putText(img, line, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (50, 50, 50), 1, cv2.LINE_AA)

def main():
    global color, thickness, palette_index, canvas
    win_name = "OpenCV Paint"
    cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)
    cv2.setMouseCallback(win_name, mouse_callback)

    while True:
        display = canvas.copy()
        show_instructions(display)
        cv2.rectangle(display, (WIDTH - 160, 8), (WIDTH - 8, 52), (230, 230, 230), -1)
        cv2.putText(display, f"Brush: {thickness}px", (WIDTH - 150, 28), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (20, 20, 20), 1)
        cv2.putText(display, f"Color: {tuple(color)}", (WIDTH - 150, 48), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (20, 20, 20), 1)

        cv2.imshow(win_name, display)
        key = cv2.waitKey(20) & 0xFF

        if key == 27:
            break
        elif key == ord('s'):
            fname = f"drawing_{datetime.datetime.now().strftime('%Y%m%d_%H%M%S')}.png"
            cv2.imwrite(fname, canvas)
        elif key == ord('c'):
            palette_index = (palette_index + 1) % len(palette)
            color = list(palette[palette_index])
        elif key in (ord('r'), ord('g'), ord('b'), ord('k'), ord('w')):
            if key == ord('r'):
                color = [0, 0, 255]
            elif key == ord('g'):
                color = [0, 255, 0]
            elif key == ord('b'):
                color = [255, 0, 0]
            elif key == ord('k'):
                color = [0, 0, 0]
            elif key == ord('w'):
                color = [255, 255, 255]
        elif key in (ord('+'), ord(']')):
            thickness = min(100, thickness + 1)
        elif key in (ord('-'), ord('[')):
            thickness = max(1, thickness - 1)

    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
