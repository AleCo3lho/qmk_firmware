#define BONGO_ANIM_FRAME_DURATION 100 // how long each frame lasts in ms
#define BONGO_ANIM_SIZE 636 // number of bytes in array, minimize for adequate firmware size, max is 1024
#define IDLE_FRAMES 5
#define IDLE_TIMEOUT 750 // the amount of time it takes to return to idle
#define TAP_FRAMES 2
#define KEYS_SIZE 100 // the number of keys stored in the array that tracks keypresses; how many keys are on the board?

enum anim_states
{
    Idle,
    Prep,
    Tap,
    Off
};

extern uint8_t anim_state;
extern uint32_t idle_timeout_timer;
extern uint32_t anim_timer;
extern uint8_t current_idle_frame;
extern uint8_t current_tap_frame;

struct pair_int_int {
    uint8_t first;
    uint8_t second;
};

extern struct pair_int_int pressed_keys[KEYS_SIZE];
extern struct pair_int_int pressed_keys_prev[KEYS_SIZE];
extern uint8_t pressed_keys_index;

extern bool key_down;
extern char wpm[42];
void draw_bongo(bool minimal);
