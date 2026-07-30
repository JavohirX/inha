#include <linux/module.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#define DRIVER_AUTHOR "Akmal Sodikov"
#define DRIVER_DESC   "A Kernel Module to Display Keyboard Scan Codes and Key Names"

static struct input_handle *kb_handle;

static const char *keymap[] = {
    "RESERVED", "ESC", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "BACKSPACE", "TAB",
    "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "[", "]", "ENTER", "LEFTCTRL", "A", "S",
    "D", "F", "G", "H", "J", "K", "L", ";",
    "'", "`", "LEFTSHIFT", "\\", "Z", "X", "C", "V",
    "B", "N", "M", ",", ".", "/", "RIGHTSHIFT", "*",
    "LEFTALT", "SPACE", "CAPSLOCK", "F1", "F2", "F3", "F4", "F5",
    "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "KP7",
    "KP8", "KP9", "KP_MINUS", "KP4", "KP5", "KP6", "KP_PLUS", "KP1",
    "KP2", "KP3", "KP0", "KP_DOT", "UNKNOWN", "ZENKAKUHANKAKU", "F11",
    "F12", "RO", "KATAKANA", "HIRAGANA", "HENKAN", "KATAKANAHIRAGANA", "MUHENKAN", "KP_JP_COMMA",
    "KP_ENTER", "RIGHTCTRL", "KP_SLASH", "SYSRQ", "RIGHTALT", "LINEFEED", "HOME", "UP",
    "PAGEUP", "LEFT", "RIGHT", "END", "DOWN", "PAGEDOWN", "INSERT", "DELETE",
    "MACRO", "MUTE", "VOLUMEDOWN", "VOLUMEUP", "POWER", "KPEQUAL", "KPPLUSMINUS", "PAUSE",
    "SCALE", "KPCOMMA", "HANGEUL", "HANJA", "YEN", "LEFTMETA", "RIGHTMETA", "COMPOSE"
};


static void kb_event(struct input_handle *handle, unsigned int type,
                     unsigned int code, int value)
{
    if (type == EV_KEY) {
        const char *key_status = (value) ? "Pressed" : "Released";
        const char *key_name = (code < ARRAY_SIZE(keymap)) ? keymap[code] : "UNKNOWN";

        printk(KERN_INFO "Key %s: %s (Scan Code: %d)\n", key_name, key_status, code);
    }
}

static int kb_connect(struct input_handler *handler, struct input_dev *dev,
                      const struct input_device_id *id)
{
    int error;

    kb_handle = kzalloc(sizeof(struct input_handle), GFP_KERNEL);
    if (!kb_handle)
        return -ENOMEM;

    kb_handle->dev = dev;
    kb_handle->handler = handler;
    kb_handle->name = "kb_handle";

    error = input_register_handle(kb_handle);
    if (error) {
        kfree(kb_handle);
        return error;
    }

    error = input_open_device(kb_handle);
    if (error) {
        input_unregister_handle(kb_handle);
        kfree(kb_handle);
        return error;
    }

    printk(KERN_INFO "Keyboard input device connected.\n");
    return 0;
}

static void kb_disconnect(struct input_handle *handle)
{
    input_close_device(handle);
    input_unregister_handle(handle);
    kfree(handle);
    printk(KERN_INFO "Keyboard input device disconnected.\n");
}

static const struct input_device_id kb_ids[] = {
    { .driver_info = 1 },
    { },
};

MODULE_DEVICE_TABLE(input, kb_ids);


static struct input_handler kb_input_handler = {
    .event     = kb_event,
    .connect   = kb_connect,
    .disconnect= kb_disconnect,
    .name      = "kb_input_handler",
    .id_table  = kb_ids,
};

static int __init kb_init(void)
{
    int ret;

    ret = input_register_handler(&kb_input_handler);
    if (ret)
        printk(KERN_ERR "Failed to register input handler\n");
    else
        printk(KERN_INFO "Keyboard Scan Code Module Loaded\n");

    return ret;
}

static void __exit kb_exit(void)
{
    input_unregister_handler(&kb_input_handler);
    printk(KERN_INFO "Keyboard Scan Code Module Unloaded\n");
}

module_init(kb_init);
module_exit(kb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);