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
        std::string newText = "";
    public:
        UILabelComponent(int x, int y, std::string text,  std::string fontName, const SDL_Color color, const SDL_Color hoverColor);

        void Initialize() override {
            SetLabelText(text, fontName);
        }

        void SetText(const std::string& text) {
            newText = text;
        }

        void SetLabelText(std::string text, std::string fontName) {
            SDL_Surface* surface = TTF_RenderText_Blended(
                this->owner->GetManager()->GetScene()->GetAssetManager().GetFont(fontName),
                 text.c_str(),
                  currentColor
            );
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
            SDL_DestroyTexture(texture);
            if(this->owner->HasComponent<TransformComponent>()) {
                position = {
                    (int) this->owner->GetComponent<TransformComponent>()->position.x,
                    (int) this->owner->GetComponent<TransformComponent>()->position.y,
                    position.w,
                    position.h
                };
            }
            SetLabelText(newText == "" ?  text : newText, fontName);
        }

        void Render() override {
            FontManager::Draw(texture, position);
        }
    
};
UILabelComponent::UILabelComponent(int x, int y, std::string text,  std::string fontName, const SDL_Color color, const SDL_Color hoverColor)
: position({x,y}), text(text), fontName(fontName), color(color), hoverColor(hoverColor), currentColor(color)  {}
#endif