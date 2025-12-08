namespace Buttons {
    /* The value of the enum variant corresponds to the pin. Pin 0 (RX) and pin
    1 (TX) should not be connected to anything, because it interferes with
    uploading code. */
    enum Pin : uint8_t {
        RED = 2,
        BLUE = 3,
        YELLOW = 4,
        GREEN = 5,
    };
};

namespace Leds {
    // The value of the enum variant corresponds to the pin.
    enum Pin : uint8_t {
        RED = 6,
        BLUE = 7,
        YELLOW = 8,
        GREEN = 9
    };
};

Leds::Pin button_to_led(Buttons::Pin pin) {
    switch (pin) {
        case Buttons::RED: return Leds::RED;  
        case Buttons::BLUE: return Leds::BLUE;  
        case Buttons::YELLOW: return Leds::YELLOW;  
        case Buttons::GREEN: return Leds::GREEN;
        /* This line of code should never run, but it's necessary for the
        function to return a value for every input.  */
        default: return (Leds::Pin) 0;  
    }
}

void setup() {
    /* Button pins should be configured as INPUT_PULLUP. A HIGH value indicates 
    the button isn't being pushed, and a LOW value indicates that it is being
    pushed. */
    pinMode(Buttons::RED, INPUT_PULLUP);
    pinMode(Buttons::BLUE, INPUT_PULLUP);
    pinMode(Buttons::YELLOW, INPUT_PULLUP);
    pinMode(Buttons::GREEN, INPUT_PULLUP);
    /* LED pins should be configured as OUTPUT. The circuit should be designed
    so that each LED only draws up to 20 mA of current. */
    pinMode(Leds::RED, OUTPUT);
    pinMode(Leds::BLUE, OUTPUT);    
    pinMode(Leds::YELLOW, OUTPUT);
    pinMode(Leds::GREEN, OUTPUT);
}

constexpr Buttons::Pin buttons[] = {
    Buttons::RED,
    Buttons::BLUE,
    Buttons::YELLOW,
    Buttons::GREEN
};
constexpr int num_buttons = sizeof(buttons) / sizeof(buttons[0]);

void loop() {
    for (int i = 0; i < num_buttons; i++) {
        Leds::Pin ledPin = button_to_led(buttons[i]);
        if (digitalRead(buttons[i]) == LOW) {
            digitalWrite(ledPin, HIGH);
        } else {
            digitalWrite(ledPin, LOW);
        }
    }
}
