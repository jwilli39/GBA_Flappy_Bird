// flappyBird.c
// Game loop for the Flappy Bird GBA recreation

#include <stdio.h>

#include "background_utils.h"
#include "koopa_logic.h"
#include "gba.h"
#include "flappyBird.h"
#include "sprite_image.h"
#include "flappy_utils.h"

// Forward declarations for Flappy Bird gameplay
static void setup_display();
static void run_countdown();
static void initialize_game(struct Koopa *koopa);
static void run_game_loop(struct Koopa *koopa);

// Internal helpers for game loop
static void handle_input(struct Koopa *koopa);
static int check_game_over(struct Koopa *koopa, int *xscroll, int *lives, int score);
static void update_score_and_speed(int *fps, int *score, int *xscroll);
static void render(int xscroll, int yscroll);

/**
 * @brief Starts and runs the Flappy Bird game.
 */
void play_flappy_bird()
{
    struct Koopa koopa;
    
    setup_display();         // Configure video mode and enable layers/sprites
    run_countdown();         // Display countdown before starting the game
    initialize_game(&koopa); // Load sprite graphics, clear memory, and initialize player
    run_game_loop(&koopa);   // Main loop: handles input, scrolling, collisions, and score
}

/**
 * @brief Configures the display mode and enables backgrounds and sprite layers.
 */
static void setup_display()
{
    // Set video mode to 0 and enable background 0, background 1, and sprite rendering
    *display_control = MODE0 | MODE1 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE | SPRITE_MAP_1D;
}

/**
 * @brief Displays a countdown screen before the game begins.
 */
static void run_countdown()
{
    int count = 16;  // Initial countdown value
    int num;

    while (1)
    {
        setup_background0();                  // Show static background
        num = countDown(count, 1, 6, 11);     // Update countdown timer
        if (num == 0)
            break;                            // Exit loop when countdown ends

        char str[32];
        sprintf(str, "NEW GAME IN %d", num);  // Format countdown text
        set_text(str, 8, 8);                  // Display text on screen

        count--;                              // Decrease countdown
        delay(10000);                         // Delay for visual pacing
    }
}

/**
 * @brief Executes the main gameplay loop for Flappy Bird.
 * @param koopa Pointer to the Koopa structure representing the player character.
 */
static void run_game_loop(struct Koopa *koopa)
{
    int xscroll = 0;   // Horizontal scrolling position
    int yscroll = 0;   // Vertical scroll (optional)
    int score = 0;     // Player's score
    int fps = 0;       // Frame counter for timing
    int lives = 5;     // Number of retries

    while (1)
    {
        setup_background();            // Draw the scrolling background
        koopa_update(koopa, xscroll);  // Update Koopa's movement and physics
        xscroll++;                     // Move screen to the right
        delay(300);                    // Control update speed

        handle_input(koopa);           // Jump or fall based on button press

        // If the player hits a pipe
        if (check_collision_top(koopa, xscroll) || check_collision_bottom(koopa, xscroll))
        {
            if (check_game_over(koopa, &xscroll, &lives, score))
                break;                 // Exit loop if lives reach zero
        }
        else
        {
            update_score_and_speed(&fps, &score, &xscroll);  // Adjust score and difficulty
        }

        render(xscroll, yscroll);      // Push scroll and sprite updates to screen
        delay(500);                    // Small delay before next loop
    }
}

/**
 * @brief Initializes sprite graphics and sets up the player character.
 * @param koopa Pointer to the Koopa structure that will represent the player.
 */
static void initialize_game(struct Koopa *koopa)
{
    setup_sprite_image();   // Load sprite image data and palette into memory
    sprite_clear();         // Clear all existing sprites from the screen
    koopa_init(koopa);      // Initialize the player's sprite and properties
}

/**
* @brief Handles input for the Koopa character, including jumping and idle behavior.
* @param koopa Pointer to the Koopa structure.
*/
static void handle_input(struct Koopa *koopa)
{
   // If A is pressed, jump and face up
   if (button_pressed(BUTTON_A)) {
       koopa_jump(koopa);
       koopa_right(koopa);
   }
   // Otherwise, stop movement and fall
   else {
       koopa_stop(koopa);
   }
}

/**
* @brief Handles collision response, displays game over screen, and tracks remaining lives.
* @param koopa Pointer to the Koopa structure.
* @param xscroll Pointer to the horizontal scroll value (will be decremented on collision).
* @param lives Pointer to the player's remaining lives.
* @param score The current score at the time of collision.
* @return 1 if lives reach zero and the game should end, 0 otherwise.
*/
static int check_game_over(struct Koopa *koopa, int *xscroll, int *lives, int score)
{
   (*xscroll)--;              // Undo scroll for visual consistency
   clear_background();        // Clear screen graphics
   setup_background0();       // Reset to non-scrolling background
   (*lives)--;                // Decrement life count

   // Display game over message
   char str[32];
   sprintf(str, "GAME OVER!");
   set_text(str, 10, 10);

   // Display the score
   char str2[32];
   sprintf(str2, "     TOTAL SCORE %d", score);
   set_text(str2, 6, 4);

   delay(50500);              // Pause before allowing retry

   return (*lives == 0);      // Return true if lives ran out
}

/**
* @brief Updates the player's score and increases scroll speed under certain conditions.
* @param fps Pointer to the current frame counter.
* @param score Pointer to the player's score.
* @param xscroll Pointer to the horizontal scroll value (may be increased for difficulty).
*/
static void update_score_and_speed(int *fps, int *score, int *xscroll)
{
   // Increase scroll speed after 31 points and sufficient time
   if (increment_speed(*fps) >= 25 && *score > 31)
       (*xscroll)++;

   // Update frame counter and score
   (*fps)++;
   if (*fps >= 70) {
       *fps = 0;
       (*score)++;
   }
}

/**
* @brief Renders the current frame by applying scroll values and updating all sprites.
* @param xscroll The current horizontal scroll value.
* @param yscroll The current vertical scroll value.
*/
static void render(int xscroll, int yscroll)
{
   wait_vblank();                       // Wait for vertical blank to avoid tearing
   *bg0_x_scroll = xscroll;            // Apply horizontal scroll to background
   *bg0_y_scroll = yscroll;            // Apply vertical scroll (optional)
   sprite_update_all();                // Upload sprite data to display
}
