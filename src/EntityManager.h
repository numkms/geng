#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Component.h"
#include "Entity.h"
#include "Constants.h"
#include <vector>

class Scene;
class EntityManager {
    private:
        std::vector<Entity *> entities;
    public: 
        Scene* scene;
        EntityManager(Scene* scene);
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities();
        Entity& AddEntity(std::string entityName, LayerType layer);
        std::vector<Entity*> GetEntities() const;
        std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
        unsigned int GetEntityCount() const;
        void PrintEntityTree();
        CollisionType CheckEntityCollisions() const;
        void DestroyInactiveEntities();
        Scene* GetScene();
};

#endif