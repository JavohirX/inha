#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>         // key definitions are in input.h
#include <linux/keyboard.h>
#include <linux/interrupt.h>
#include <linux/slab.h>


static struct notifier_block keyboard_notifier;
static unsigned long key_pressed[KEY_CNT / 32] = {0}; // Track key states (pressed/released)

// Key name lookup table for some common keys
const char *key_names[] = {
    [KEY_ESC] = "Esc", [KEY_1] = "1", [KEY_2] = "2", [KEY_3] = "3", [KEY_4] = "4",
    [KEY_5] = "5", [KEY_6] = "6", [KEY_7] = "7", [KEY_8] = "8", [KEY_9] = "9", 
    [KEY_0] = "0", [KEY_MINUS] = "-", [KEY_EQUAL] = "=", [KEY_BACKSPACE] = "Backspace", 
    [KEY_TAB] = "Tab", [KEY_Q] = "Q", [KEY_W] = "W", [KEY_E] = "E", [KEY_R] = "R", 
    [KEY_T] = "T", [KEY_Y] = "Y", [KEY_U] = "U", [KEY_I] = "I", [KEY_O] = "O", 
    [KEY_P] = "P", [KEY_LEFTBRACE] = "[", [KEY_RIGHTBRACE] = "]", [KEY_ENTER] = "Enter",
    [KEY_A] = "A", [KEY_S] = "S", [KEY_D] = "D", [KEY_F] = "F", [KEY_G] = "G", 
    [KEY_H] = "H", [KEY_J] = "J", [KEY_K] = "K", [KEY_L] = "L", [KEY_SEMICOLON] = ";", 
    [KEY_APOSTROPHE] = "'", [KEY_BACKSLASH] = "\\", [KEY_Z] = "Z", [KEY_X] = "X", 
    [KEY_C] = "C", [KEY_V] = "V", [KEY_B] = "B", [KEY_N] = "N", [KEY_M] = "M", 
    [KEY_COMMA] = ",", [KEY_DOT] = ".", [KEY_SLASH] = "/", [KEY_SPACE] = "Space",
    [KEY_F1] = "F1", [KEY_F2] = "F2", [KEY_F3] = "F3", [KEY_F4] = "F4",
    [KEY_F5] = "F5", [KEY_F6] = "F6", [KEY_F7] = "F7", [KEY_F8] = "F8",
    [KEY_F9] = "F9", [KEY_F10] = "F10", [KEY_F11] = "F11", [KEY_F12] = "F12",
    [KEY_LEFTSHIFT] = "Left Shift", [KEY_RIGHTSHIFT] = "Right Shift", 
    [KEY_LEFTCTRL] = "Left Ctrl", [KEY_RIGHTCTRL] = "Right Ctrl",
    [KEY_LEFTALT] = "Left Alt", [KEY_RIGHTALT] = "Right Alt",
    [KEY_UP] = "Up Arrow", [KEY_DOWN] = "Down Arrow", [KEY_LEFT] = "Left Arrow", 
    [KEY_RIGHT] = "Right Arrow",
    [KEY_INSERT] = "Insert", [KEY_DELETE] = "Delete", [KEY_HOME] = "Home",
    [KEY_END] = "End", [KEY_PAGEUP] = "Page Up", [KEY_PAGEDOWN] = "Page Down", 
    [KEY_NUMLOCK] = "NumLock", [KEY_CAPSLOCK] = "CapsLock", [KEY_SCROLLLOCK] = "ScrollLock"
};

// Key press/release handler
static int keyboard_event_handler(struct notifier_block *nb, unsigned long action, void *data) {
    struct keyboard_notifier_param *param = data;

    // Key press (0x01) or release (0x00)
    if (action == KBD_KEYCODE) {
        unsigned int keycode = param->value;

        // If the key is pressed
        if (param->down) {
            printk(KERN_INFO "Key Pressed: Scan Code = 0x%02X, Key = %s\n", keycode,
                   (keycode < ARRAY_SIZE(key_names) && key_names[keycode]) ? key_names[keycode] : "Unknown");
        } else {
            printk(KERN_INFO "Key Released: Scan Code = 0x%02X, Key = %s\n", keycode,
                   (keycode < ARRAY_SIZE(key_names) && key_names[keycode]) ? key_names[keycode] : "Unknown");
        }
    }

    return NOTIFY_OK;
}

// Module initialization function
static int __init keyboard_module_init(void) {
    // Initialize the notifier block
    keyboard_notifier.notifier_call = keyboard_event_handler;
    
    // Register the keyboard notifier
    if (register_keyboard_notifier(&keyboard_notifier)) {
        printk(KERN_ERR "Failed to register keyboard notifier\n");
        return -1;
    }

    printk(KERN_INFO "Keyboard module loaded successfully.\n");
    return 0;
}

// Module exit function
static void __exit keyboard_module_exit(void) {
    // Unregister the keyboard notifier
    unregister_keyboard_notifier(&keyboard_notifier);
    printk(KERN_INFO "Keyboard module unloaded successfully.\n");
}

module_init(keyboard_module_init);
module_exit(keyboard_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Davlatbek Kobiljonov");
MODULE_DESCRIPTION("A simple keyboard key press/release handler.");

