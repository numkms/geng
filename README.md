# GENG
Geng is an another 2d game engine. 
Geng is just my pet project and nothing more but you can help me with it by issue or pull-request
### Based on
* GLM for math
* SDL for output 
### Features (today and planned)
- [x] Scenes - Make scenes with entities and manage them via scene manager.
- [x] Layering - each sprite can be render with selected layer. You can create your own layers in Constatns.h file right now.
- [x] Entities - create entity for everything and add needed components
- [x] Components - use default components or create your own 
- [x] Components from the box: 
* ColliderComponent - to check collisions of your objects.
* KeyboardComponent - (will be rewrited soon) now you can move your object with keyboard keys with this component.
* ProjectileEmitterComponent - for projectile objects like bullets, platforms and etc
* SpriteComponent - for rendering sprites
* TileComponent - for rendering map tiles
* TransformComponent - for position and (w8 for it) transform your objects
* UILabelComponent - is just component for rendering text in your game
* ... comming soon

- [x] Camera support
- [x] PNG Sprite Animation Support 
- [x] Loading and rendering map from .map files 
- [x] Asset managment
- [ ] Lua scripting for configure objects 
- [ ] Map editor 
- [ ] Demo games 
* Arkanoid 
* Match3
* Some RPG (j4f)
- [ ] Object configurator 
- [ ] IDE Plugins
- [ ] Console toolkit for generating code Components

### How to compile and run:
$ make 
$ make run
