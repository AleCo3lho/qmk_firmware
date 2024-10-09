// Constants
#define FRAME_SIZE 512
#define LOGO_GLITCH_COUNT 5
#define LOGO_GLITCH_DIRTY_COUNT 2
#define TEXT_GLITCH_COUNT 7
#define TEXT_GLITCH_DIRTY_COUNT 3

// Variables
extern bool     glitch;
extern bool     dirty;
extern uint8_t  frame_count;
extern bool     show_text;
extern uint16_t arasaka_timer;

void arasaka_draw(void);
