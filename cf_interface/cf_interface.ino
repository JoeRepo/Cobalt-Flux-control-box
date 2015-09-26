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

#define FIRMWARE_DEBOUNCE 1

struct panel {
    uint8_t pin;
    uint8_t modkey;
    uint8_t keycode;
    uint8_t state;
    char name[6]; // Not used, but good for clarification
} panels[] = {
  { PIN_UP, MOD_NONE, KEY_W, HIGH, "up" },
  { PIN_DOWN, MOD_NONE, KEY_S, HIGH, "down" },
  { PIN_LEFT, MOD_NONE, KEY_A, HIGH, "left" },
  { PIN_RIGHT, MOD_NONE, KEY_D, HIGH, "right" },
  { PIN_ESC, MOD_NONE, KEY_ESC, HIGH, "exit" },
  { PIN_ENTER, MOD_NONE, KEY_ENTER, HIGH, "start" },
  { PIN_GROUP, MOD_RSHIFT, KEY_ENTER, HIGH, "group" }
};

uint8_t NUM_PANELS = sizeof(panels)/sizeof(panel);

void get_states(void)
{
    uint8_t i;
    for (i=0; i<NUM_PANELS; ++i) {
    	panels[i].state = digitalRead(panels[i].pin);
    }
}

void write_keys(void)
{
    uint8_t buf[8] = {0}; // Keyboard buffer
    uint8_t slot = 2; // Slots 2-7 are for keys
    uint8_t max_slot = 8;
    uint8_t i;
	
    // Go through each panel and check their state
    for (i=0; i< NUM_PANELS; ++i) {
	if (panels[i].state == LOW) { // The panel is pressed
            if (panels[i].modkey != MOD_NONE) {
		buf[0] |= panels[i].modkey;
	    }
	    buf[slot] = panels[i].keycode; // Add it to the buffer
	    ++slot;
	    if (slot >= max_slot) { // Overflow check
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
    get_states();
    write_keys();
    
    #ifdef FIRMWARE_DEBOUNCE
    delay(5); // could possibly need to be changed
    #endif
}
