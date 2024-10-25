#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        : mOwningWorld{ owningWorld },
       mHasBeganPlay{ false },
        mSprite{},
        mTexture{}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if (!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
        LOG("Actor begin play");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor ticking");
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        AssetManager& assetManager = AssetManager::Get();
        mTexture = assetManager.LoadTexture(texturePath);
        if (!mTexture)
            return;

        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureWidth} });
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if (IsPendingDestroy())
            return;

        window.draw(mSprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLocation)
    {
        mSprite.setPosition(newLocation);
    }

    void Actor::SetActorRotation(float newAngle)
    {
        mSprite.setRotation(newAngle);
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
    {
        SetActorLocation(GetActorLocation() + offsetAmt);
    }

    void Actor::AddActorRotationOffset(float offsetAmt)
    {
        SetActorRotation(GetActorRotation() + offsetAmt);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation());
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation() + 90.f);
    }

    sf::Vector2u Actor::GetWindowsSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
    }
}