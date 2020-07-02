#ifndef UI_LABEL_COMPONENT_H
#define UI_LABEL_COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../SceneManager.h"
#include "../Game.h"


class UILabelComponent: public Component {
    private:
        SDL_Rect position;
        std::string text;
        std::string fontName;
        SDL_Color color;
        SDL_Color hoverColor;
        SDL_Color currentColor; 
        SDL_Texture* texture;
    public:
        UILabelComponent(int x, int y, std::string text,  std::string fontName, const SDL_Color color, const SDL_Color hoverColor) {
            this->position.x = x;
            this->position.y = y;
            std::cout << "3" << std::endl;
            this->text = text;
            std::cout << "4" << std::endl;
            this->fontName = fontName;
            std::cout << "5" << std::endl;
            this->color = color;
            std::cout << "6" << std::endl;
            this->hoverColor = hoverColor;
            std::cout << "7" << std::endl;
            this->currentColor = color;
            std::cout << "8" << std::endl;
            
            
        } 

        void Initialize() override {
            SetLabelText(text, fontName);
        }

        void SetLabelText(std::string text, std::string fontName) {
            
            SDL_Surface* surface = TTF_RenderText_Blended(this->owner->GetManager()->GetScene()->GetAssetManager().GetFont(fontName), text.c_str(), currentColor);
            texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
        }


        void MakeHovered() {
            this->currentColor = hoverColor;
        }

        void MakeDefault() {
            this->currentColor = color;
        }

        void Update(float deltaTime) override{
            SetLabelText(text, fontName);
        }

        void Render() override {
            FontManager::Draw(texture, position);
        }
    
};
#endif