#include <stdint.h>

// From USB HID documentation
#define KEY_W 0x1A
#define KEY_S 0x16
#define KEY_A 0x4
#define KEY_D 0x7
#define KEY_ESC 0x29
#define KEY_ENTER 0x28
#define MOD_RSHIFT (1 << 5)
#define MOD_NONE 0

#define PIN_UP 2
#define PIN_DOWN 4
#define PIN_LEFT 6
#define PIN_RIGHT 8
#define PIN_ESC 10
#define PIN_ENTER 12
#define PIN_GROUP 13

#define USBHID_BUF_SIZE 8

#define FIRMWARE_DEBOUNCE
// Delay is in ms, adjust as needed
#define FIRMWARE_DEBOUNCE_DELAY 5

typedef struct {
    uint8_t pin;
    uint8_t modkey;
    uint8_t keycode;
    uint8_t state;
} panel_t;

void get_states(panel_t *panels, uint8_t num_panels);
void write_keys(const panel_t *panels, uint8_t num_panels);

panel_t panels[] = {
  { PIN_UP, MOD_NONE, KEY_W, HIGH},
  { PIN_DOWN, MOD_NONE, KEY_S, HIGH},
  { PIN_LEFT, MOD_NONE, KEY_A, HIGH},
  { PIN_RIGHT, MOD_NONE, KEY_D, HIGH},
  { PIN_ESC, MOD_NONE, KEY_ESC, HIGH},
  { PIN_ENTER, MOD_NONE, KEY_ENTER, HIGH},
  { PIN_GROUP, MOD_RSHIFT, KEY_ENTER, HIGH}
};

#define NUM_PANELS (sizeof(panels)/sizeof(panels[0]));

void get_states(panel_t *panels, uint8_t num_panels)
{
    uint8_t i;
	
    for (i=0; i<num_panels; ++i) {
    	panels[i].state = digitalRead(panels[i].pin);
    }
}

void write_keys(const panel_t *panels, uint8_t num_panels)
{
    uint8_t buf[USBHID_BUF_SIZE] = {0}; // Keyboard buffer
    uint8_t slot = 2; // Slots 2-7 are for keys
    uint8_t i;
	
    // Go through each panel and check their state
    for (i=0; i< num_panels; ++i) {
	if (panels[i].state == LOW) { // The panel is pressed
            if (panels[i].modkey != MOD_NONE) {
		buf[0] |= panels[i].modkey;
	    }
	    buf[slot] = panels[i].keycode; // Add it to the buffer
	    ++slot;
		
	    if (slot >= (sizeof(buf)/sizeof(buf[0])) { // Overflow check
		break;
	    }
	}
    }
	
    Serial.write(buf, sizeof(buf));
}

void setup(void) 
{
    uint8_t i;
	
    for (i=0; i<NUM_PANELS; ++i) {
	pinMode(panels[i].pin, INPUT_PULLUP);
    }
	
    Serial.begin(9600);  
}

void loop(void)
{
    get_states(panels, NUM_PANELS);
    write_keys(panels, NUM_PANELS);
    
    #if defined(FIRMWARE_DEBOUNCE)
    delay(FIRMWARE_DEBOUNCE_DELAY); 
    #endif
}
