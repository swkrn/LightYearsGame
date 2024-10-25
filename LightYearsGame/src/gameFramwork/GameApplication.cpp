#include "gameFramwork/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "config.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
         AssetManager::Get().SetAssetRootDirectory(GetResouceRir());
         weak<World> newWorld = LoadWorld<World>();
         newWorld.lock()->SpawnActor<Actor>();
         testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
         testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
         testPlayerSpaceship.lock()->SetActorRotation(45.f);
         //testPlayerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
         counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        //counter += deltaTime;
        //if (counter > 2.f)
        //{
        //    if (!testPlayerSpaceship.expired())
        //    {
        //        testPlayerSpaceship.lock()->Destroy();
        //    }
        //}
    }
}