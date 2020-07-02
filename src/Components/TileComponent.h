#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <SDL2/SDL.h>
#include "../../lib/glm/glm.hpp"
#include "../Component.h"
#include "../EntityManager.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../SceneManager.h"
class TileComponent: public Component {
    public: 
        SDL_Texture *texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        glm::vec2 position;

        TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId) {
            texture = this->owner->GetManager()->GetScene()->GetAssetManager().GetTexture(assetTextureId);
            sourceRectangle.x = sourceRectX;
            sourceRectangle.y = sourceRectY;
            sourceRectangle.w = tileSize;
            sourceRectangle.h = tileSize;

            destinationRectangle.x = x;
            destinationRectangle.y = y;
            destinationRectangle.w = tileSize * tileScale;
            destinationRectangle.h = tileSize * tileScale;

            position.x = x;
            position.y = y;
        }

        ~TileComponent() {
            SDL_DestroyTexture(texture);
        }

        void Update(float deltaTime) override {
            destinationRectangle.x = position.x - Game::camera.x;
            destinationRectangle.y = position.y - Game::camera.y;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
};
#endif