# GENG
Geng is an another 2d game engine. 
Geng is just my pet project and nothing more but you can help me with it by issue or pull-request

### Features (today and planned)
[ * ] Layering - each sprite can be render with selected layer. You can create your own layers in Constatns.h file right now.
[ * ] Manager -> Entity -> Components structure, so you can write your own components for entities and use it in any entity what you want.
[ * ] Components from the boz: 
      - ColliderComponent - to check collisions of your objects.
      - KeyboardComponent - (will be rewrited soon) now you can move your object with keyboard keys with this component.
      - ProjectileEmitterComponent - for projectile objects like bullets, platforms and etc
      - SpriteComponent - for rendering sprites
      - TileComponent - for rendering map tiles
      - TransformComponent - for position and (w8 for it) transform your objects
      - UILabelComponent - is just component for rendering text in your game
      - ... comming soon
[ * ] Camera support
[ * ] PNG Sprite Animation Support 
[ * ] Loading and rendering map from .map files 
[ * ] Asset managment
[   ] Lua scripting for configure objects 
[   ] Map editor 
[   ] Demo games 
      - Arkanoid 
      - Match3
      - Some RPG (j4f)
[   ] Object configurator 
[   ] IDE Plugins
[   ] Console toolkit for generating code Components