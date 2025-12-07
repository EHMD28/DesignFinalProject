namespace ButtonPins {
    // The value of the enum variant corresponds to the pin.
    enum : uint8_t {
        RED = 2,
        BLUE = 3,
        YELLOW = 4,
        GREEN = 5,
    };
};

namespace LedPins {
    // The value of the enum variant corresponds to the pin.
    enum : uint8_t {
        RED = 6,
        BLUE = 7,
        YELLOW = 8,
        GREEN = 9
    };
};

void setup() {
    /* Button pins should be configured as INPUT_PULLUP. A HIGH value indicates 
    the button isn't being pushed, and a LOW value indicates that it is being
    pushed. */
    pinMode(ButtonPins::RED, INPUT_PULLUP);
    pinMode(ButtonPins::BLUE, INPUT_PULLUP);
    pinMode(ButtonPins::YELLOW, INPUT_PULLUP);
    pinMode(ButtonPins::GREEN, INPUT_PULLUP);
    /* LED pins should be configured as OUTPUT. The circuit should be designed
    so that each LED only draws up to 20 mA of current. */
    pinMode(LedPins::RED, OUTPUT);
    pinMode(LedPins::BLUE, OUTPUT);    
    pinMode(LedPins::YELLOW, OUTPUT);
    pinMode(LedPins::GREEN, OUTPUT);
}

void loop() {
}
