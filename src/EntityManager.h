#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Component.h"
#include "Entity.h"
#include "Constants.h"
#include <vector>

class EntityManager {
    private:
        std::vector<Entity *> entities;
    public: 
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

};

#endif