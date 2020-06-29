#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Component.h";
#include "Entity.h";
#include <vector>

class EntityManager {
    private:
        std::vector<Entity *> entities;
    public: 
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities();
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount() const;
        void PrintEntityTree();

};

#endif