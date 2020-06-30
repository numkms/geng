#ifndef UI_LABEL_COMPONENT_H
#define UI_LABEL_COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"


class UILabelComponent: public Component {
    private:
        SDL_Rect position;
        std::string text;
        std::string fontName;
        SDL_Color color;
        SDL_Texture* texture;
    public:
        UILabelComponent(int x, int y, std::string text,  std::string fontName, const SDL_Color color) {
            this->position.x = x;
            this->position.y = y;
            this->text = text;
            this->fontName = fontName;
            this->color = color;
            SetLabelText(text, fontName);
        } 

        void SetLabelText(std::string text, std::string fontName) {
            SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontName), text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
        }

        void Render() override {
            FontManager::Draw(texture, position);
        }
    
};
#endif