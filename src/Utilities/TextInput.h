#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H
#include <string>
#include <SDL2/SDL.h>1

class TextInput
{
private:
    /* data */
    std::string text;
public:
    std::string MakeInput() {
            //Main loop flag
            SDL_bool done = SDL_FALSE;
    /* ... */

    SDL_StartTextInput();
    while (!done) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
                    strcat(text.c_str(), event.text.text);
                    break;
                case SDL_TEXTEDITING:
                    /*
                    Update the composition text.
                    Update the cursor position.
                    Update the selection length (if any).
                    */
                    composition = event.edit.text;
                    cursor = event.edit.start;
                    selection_len = event.edit.length;
                    break;
            }
        }
    }

    SDL_Quit();

    }
};
#endif