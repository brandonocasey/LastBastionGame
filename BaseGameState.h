#pragma once
#include "Utils.h"

//template<class ChildClass>
class BaseGameState
{
/*
private:
    ChildClass* This()
    {
        return static_cast<ChildClass*>(this);
    }
    */
public:

    virtual void Init(SDL_Renderer* current_renderer, SDL_Window* current_window) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void HandleEvents() = 0;
    virtual void PauseState() = 0;
    virtual void ResumeState() = 0;

    std::string GetName()
    {
        return m_sName;
    }

    std::string m_sName;
    GameLog *m_cLogger;
protected:
    BaseGameState() {};
};