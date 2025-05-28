#include "ScoreAchievementComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <iomanip>
#include "BaseComponent.h"
#include "TextComponent.h"
#include "ScoreChangedEvent.h"
#include <steam_api.h>
#include "Event.h"
#include "GameObject.h"

namespace dae {
	void ScoreAchievementComponent::FixedUpdate()
	{
	}

    void ScoreAchievementComponent::Update(const float&)
    {

    }

    void ScoreAchievementComponent::Render() const
    {

    }

    void ScoreAchievementComponent::Update(const Event& event)
    {
        if (event.GetType() == EventType::ScoreChanged)
        {
            const ScoreChangedEvent& scoreEvent = static_cast<const ScoreChangedEvent&>(event);

            if (scoreEvent.GetScore() >= 500)
            {
                std::cout << "Player score is equel to or over 500!" << std::endl;

                bool achieved = false;
                SteamUserStats()->GetAchievement("ACH_WIN_100_GAMES", &achieved);
                if (!achieved)
                {
                    SteamUserStats()->SetAchievement("ACH_WIN_100_GAMES");
                    if (SteamUserStats()->StoreStats()) {
                        std::cout << "Achievement " << "ACH_WIN_100_GAMES" << " unlocked!" << std::endl;
                    }
                    else {
                        std::cerr << "Failed to store stats for achievement " << "ACH_WIN_100_GAMES" << "." << std::endl;
                    }
                }
            }
        }
    }


    ScoreAchievementComponent::ScoreAchievementComponent(GameObject* pOwner) :
        BaseComponent(pOwner)
    {
    }

    ScoreAchievementComponent::~ScoreAchievementComponent()
    {
    }
}
