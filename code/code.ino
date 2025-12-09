namespace Colors {
    enum ColorType : uint8_t {
        NONE,
        RED,
        BLUE,
        YELLOW,
        GREEN
    };

    constexpr Colors::ColorType colors[] = {
        Colors::NONE,
        Colors::RED,
        Colors::BLUE,
        Colors::YELLOW,
        Colors::GREEN
    };
    constexpr uint8_t num_colors = sizeof(colors) / sizeof(colors[0]);
};

namespace Buttons {
    /* The value of the enum variant corresponds to the pin. PinType 0 (RX) and
    pin 1 (TX) should not be connected to anything, because it interferes with
    uploading code. */
    enum PinType : uint8_t {
        RED = 2,
        BLUE = 3,
        YELLOW = 4,
        GREEN = 5,
    };

    constexpr Buttons::PinType buttons[] = {
        Buttons::RED,
        Buttons::BLUE,
        Buttons::YELLOW,
        Buttons::GREEN
    };
    constexpr int num_buttons = sizeof(buttons) / sizeof(buttons[0]);
};

namespace Leds {
    // The value of the enum variant corresponds to the pin.
    enum PinType : uint8_t {
        RED = 6,
        BLUE = 7,
        YELLOW = 8,
        GREEN = 9
    };

    Leds::PinType pin_of(Colors::ColorType color) {
        switch (color) {
            case Colors::RED: return Leds::RED;
            case Colors::BLUE: return Leds::BLUE;
            case Colors::YELLOW: return Leds::YELLOW;
            case Colors::GREEN: return Leds::GREEN;
            /* This line of code should never run, but it's necessary for the
        function to return a value for every input.  */
            default: return (Leds::PinType) 0;
        }
    }
};

Leds::PinType button_to_led(Buttons::PinType pin) {
    switch (pin) {
        case Buttons::RED: return Leds::RED;  
        case Buttons::BLUE: return Leds::BLUE;  
        case Buttons::YELLOW: return Leds::YELLOW;  
        case Buttons::GREEN: return Leds::GREEN;
        /* This line of code should never run, but it's necessary for the
        function to return a value for every input.  */
        default: return (Leds::PinType) 0;  
    }
}

namespace Display {
    enum PinType : uint8_t {
        // Least significant bit
        BIT_ONE = 10,
        BIT_TWO = 11,
        BIT_THREE = 12,
        // Most significant bit
        BIT_FOUR = 13
    };

    constexpr Display::PinType pins[] = {
        Display::BIT_ONE,
        Display::BIT_TWO,
        Display::BIT_THREE,
        Display::BIT_FOUR
    };
    constexpr int num_pins = sizeof(pins) / sizeof(pins[0]);

    void display_score(uint8_t score) {
        for (int i = 0; i < num_pins; i++) {
            int bit = bitRead(score, i);
            if (bit == 1) {
                digitalWrite(pins[i], HIGH);
            } else {
                digitalWrite(pins[i], LOW);
            }
        }
    }
}

struct GameState {
    /* The longest a sequence can be is 256 colors, because that is the highest
    value which can be stored in an unsigned 8 bit integer like round. */
    Colors::ColorType sequence[UINT8_MAX];
    /* Represents the current length of the sequence, starting from 1. 0
    represents that no colors have been initalized. */
    uint8_t round;
    /* Represents if the player has made a mistake yet. Currently, the game
    doesn't have a win state. */ 
    bool has_lost;
};

/* This is the global struct used for representing the current game state. */
struct GameState game_state;

/* Initializes the values of the global game_state struct. This function MUST be
called in setup(), or else game_state will be using garbage values from memory.
*/
void initalize_game_state() {
    game_state.round = 0;
    /* TODO: Once the rest of the project is finished, check if this
    initialization is necessary. */
    for (int i = 0; i < UINT8_MAX; i++) {
        game_state.sequence[i] = Colors::NONE;
    }
}

void generate_next_color() {
    /* Generates a random color from RED until the last color (in this case
    green). */
    uint8_t index = random(Colors::RED, Colors::num_colors - 1);
    Colors::ColorType color = Colors::colors[index];
    game_state.sequence[game_state.round] = color;
    game_state.round++;
}

void display_sequence() {
    for (int i = 0; i < game_state.round; i++) {
        Leds::PinType pin = Leds::pin_of(game_state.sequence[i]);
        digitalWrite(pin, HIGH);
        // TODO: Remove magic numbers.
        delay(750);
        digitalWrite(pin, LOW);
        delay(250);
    }
}

void start_round() {
    generate_next_color();
    display_sequence();
}

void setup() {
    /* Seeding the random number generation is necessary to have different
    results each time. Calling analog read on an unconnected pin gives a
    relatively random seed. */
    randomSeed(analogRead(A0));
    initalize_game_state();
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

void loop() {
}
