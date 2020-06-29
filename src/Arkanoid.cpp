#include "./Arkanoid.h"
#include "./Constants.h"
#include <iostream>

Arkanoid::Arkanoid(Map * map, Platform * platform, Ball * ball) {
    this->ball = ball;
    this->platform = platform;
    this->map = map;
    
    this->ball->SetDirection({top, right});
    this->MoveBall();
};


void Arkanoid::RunGame() {
    this->isGameStarted = true;
};

bool Arkanoid::IsGameStarted() {
    return this->isGameStarted;
};

void Arkanoid::MoveBall() {
    
    this->CheckBallIfOnPlatform();
    this->CheckBallIfOnBottom();
    this->CheckBallIfOnMapElementCorner();
    this->CheckBallIfOnRoomCorner();


    float currentX = this->ball->GetX();
    float currentY = this->ball->GetY();
    switch (this->ball->GetDirection().heightDirection) {
        case noneHeightDirection: {
            break;
        };
        case top: {
            currentY = currentY - this->velocity;
            break;
        };
        case bottom: {
            currentY = currentY + this->velocity;
            break;
        };
    };

    switch (this->ball->GetDirection().widthDirection) {
        case noneWidthDirection: {
            break;
        };
        case left: {
            currentX = currentX - this->velocity;
            break;
        };
        case right: {
            currentX = currentX + this->velocity;
            break;
        };
    }

    this->ball->SetPosition(currentX, currentY);   
}

void Arkanoid::CheckBallIfOnMapElementCorner() {
    for(int i = 0; i < 90; i++) {
        if(this->map->blocks[i].hidden == false && this->map->blocks[i].isCrossingOverBy((Rectangle *) this->ball)) {
            this->map->blocks[i].hidden = true;
            BallDirection newDirection;
            newDirection.heightDirection = this->ball->GetDirection().heightDirection == top ? bottom : top;
            newDirection.widthDirection = this->ball->GetDirection().widthDirection == left ? right : left;
            this->ball->SetDirection(newDirection);
        }
    }
}

void Arkanoid::CheckBallIfOnRoomCorner() {
    if(
        this->ball->GetX() == WINDOW_WIDTH || this->ball->GetX() == 0
    ) {
        //Отзеркаливаем направление шарика (квадратика)
        BallDirection newDirection;
        newDirection.heightDirection = this->ball->GetDirection().heightDirection;
        newDirection.widthDirection = this->ball->GetDirection().widthDirection == left ? right : left;
        this->ball->SetDirection(newDirection);
    } else if(this->ball->GetY() == 0) {
        BallDirection newDirection;
        newDirection.heightDirection = this->ball->GetDirection().heightDirection == top ? bottom : top;
        newDirection.widthDirection = this->ball->GetDirection().widthDirection;
        this->ball->SetDirection(newDirection);
    } else if(this->ball->GetY() == WINDOW_HEIGHT) {
        //Теряем жизнь
        this->lives--;
        //Стартуем игру сначала
        this->ball->SetDirection({top, right});
        this->ball->SetPosition(this->platform->GetX(), this->platform->GetMaxY());
    }
}

void Arkanoid::CheckBallIfOnBottom() {
    
}

void Arkanoid::CheckBallIfOnPlatform() {
    if(this->platform->isCrossingOverBy((Rectangle *) this->ball)) {
        BallDirection newDirection;
        std::cout << "On platform" << std::endl;
        std::cout << std::to_string(this->platform->GetX()) << std::endl;
        std::cout << std::to_string(this->ball->GetX()) << std::endl;
        if (this->ball->GetX() > this->platform->GetX()) {
            
            newDirection.widthDirection = right;
        } else if (this->ball->GetX() < this->platform->GetX()) {
            newDirection.widthDirection = left;
        } else {
            newDirection.widthDirection = noneWidthDirection;
        }
        newDirection.heightDirection = top;
        this->ball->SetDirection(newDirection);
    }
}

void Arkanoid::CheckIfMapIsEmpty() {
    for(int i = 0; i < 90; i++) {
        if(this->map->blocks[i].hidden == false) {
            return;
        }
    }

    this->isGameStarted = false;
}



