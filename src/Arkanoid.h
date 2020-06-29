#ifndef ARKANOID
#define ARKANOID
#include "./Map.h"
#include "./Ball.cpp"
#include "./Platform.h"

class Arkanoid {
    public:
        int lives = 3;
        int velocity = 1;
        Arkanoid(Map * map, Platform * platform, Ball * ball);
        void RunGame();
        void RestartGame();
        bool IsGameStarted();
        void MoveBall();
    protected:
        bool isGameStarted = false;
        Ball * ball;
        Platform * platform;
        Map * map;
        void MirrorBall();
        void CheckBallIfOnMapElementCorner();
        void CheckBallIfOnRoomCorner();
        void CheckBallIfOnBottom();
        void CheckBallIfOnPlatform();
        void CheckIfMapIsEmpty();
};

#endif