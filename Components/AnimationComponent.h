#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "../includes.h"

class AnimationComponent
{
private:
    class Animation
    {
    public:
        //Variables
        sf::Sprite& sprite;
        sf::Texture& textureSheet;

        float animationTimer;
        float timer;
        bool done;
        //float timer_modifier;
        int width;
        int height;

        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;
        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
              float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
            : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height),
             timer(0.f), done(false)
        {
            this->timer = 0.f;
            this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, this->width, this->height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect(frames_x * width, frames_y * height, this->width, this->height);

            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
        }

        //Accesors
        const bool& isDone() const 
        {
            return this->done;
        }

        //Functions
        const bool& play(const float& dt)
        {
            //update timer
            this->done = false;
            this->timer += 100.f * dt;
            if(this->timer >= this->animationTimer)
            {
                std::cout << "idle: " << timer <<"\n";
                //reset timer
                this->timer = 0.f;
                //animate
                if(this->currentRect != this->endRect)
                {
                    this->currentRect.left += width;
                }else
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentRect);
            }
            return this->done;
        }

        const bool& play(const float& dt, float mod_porcent)
        {
            //update timer
            this->done = false;
            std::cout << mod_porcent << "\n";
            if(mod_porcent < 0.5f)
                mod_porcent = 0.5f;

            this->timer +=  mod_porcent * 100.f * dt;
            if(this->timer >= this->animationTimer)
            {
                
                //reset timer
                this->timer = 0.f;
                //animate
                if(this->currentRect != this->endRect)
                {
                    this->currentRect.left += width;
                }else
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentRect);
            }
            return this->done;
        }

        //void pause();
        void reset()
        {
            this->timer = this->animationTimer;
            this->currentRect = this->startRect;
        }

    };
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string, Animation*> animations;
    Animation * lastAnimation;
    Animation * priorityAnimation;
public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();
    //Accesors
    const bool& isDone(const std::string key);

    //Functions

    void addAnimation(const std::string key,
        float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    const bool& play(const std::string key, const float& dt, const bool priority);
    const bool& play(const std::string key, const float& dt, const float & modifier, const float& modifier_max, const bool priority);
};

#endif //ANIMATIONCOMPONENT_H