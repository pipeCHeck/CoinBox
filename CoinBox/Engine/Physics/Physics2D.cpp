#include "Physics2D.h"

#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include "GameObject.h"

#include <algorithm>
#include <cmath>
#include <functional>

std::vector<Collider2D*> Physics2D::s_colliders;
std::set<Physics2D::ColliderPair> Physics2D::s_collidingPairs;

namespace
{
    float Dot(const Vector2& first, const Vector2& second)
    {
        return first.x * second.x + first.y * second.y;
    }

    float LengthSquared(const Vector2& value)
    {
        return Dot(value, value);
    }

    float Length(const Vector2& value)
    {
        return std::sqrt(LengthSquared(value));
    }

    Vector2 NormalizeOrDefault(const Vector2& value, const Vector2& fallback)
    {
        const float length = Length(value);
        if (length <= 0.00001f)
        {
            return fallback;
        }

        return value / length;
    }

    Vector2 Negate(const Vector2& value)
    {
        return Vector2(-value.x, -value.y);
    }

    float Clamp(float value, float minValue, float maxValue)
    {
        return (std::max)(minValue, (std::min)(value, maxValue));
    }

    float ProjectionRadius(const BoxCollider2D& box, const Vector2& axis)
    {
        const Vector2 halfSize = box.GetHalfSize();
        return halfSize.x * std::fabs(Dot(axis, box.GetAxisX()))
            + halfSize.y * std::fabs(Dot(axis, box.GetAxisY()));
    }

    bool TestBoxAxis(
        const BoxCollider2D& first,
        const BoxCollider2D& second,
        const Vector2& axis,
        float& smallestOverlap,
        Vector2& smallestAxis)
    {
        const float firstCenter = Dot(first.GetWorldCenter(), axis);
        const float secondCenter = Dot(second.GetWorldCenter(), axis);
        const float distance = std::fabs(secondCenter - firstCenter);
        const float overlap = ProjectionRadius(first, axis) + ProjectionRadius(second, axis) - distance;

        if (overlap < 0.0f)
        {
            return false;
        }

        if (overlap < smallestOverlap)
        {
            smallestOverlap = overlap;
            smallestAxis = axis;
        }

        return true;
    }

    bool CheckBoxBox(const BoxCollider2D& first, const BoxCollider2D& second, Collision2D& collision)
    {
        float smallestOverlap = 3.402823466e+38F;
        Vector2 smallestAxis = Vector2(1.0f, 0.0f);

        if (!TestBoxAxis(first, second, first.GetAxisX(), smallestOverlap, smallestAxis)
            || !TestBoxAxis(first, second, first.GetAxisY(), smallestOverlap, smallestAxis)
            || !TestBoxAxis(first, second, second.GetAxisX(), smallestOverlap, smallestAxis)
            || !TestBoxAxis(first, second, second.GetAxisY(), smallestOverlap, smallestAxis))
        {
            return false;
        }

        const Vector2 centerDelta = second.GetWorldCenter() - first.GetWorldCenter();
        if (Dot(centerDelta, smallestAxis) < 0.0f)
        {
            smallestAxis = Negate(smallestAxis);
        }

        collision.normal = smallestAxis;
        collision.penetration = smallestOverlap;
        collision.point = first.GetWorldCenter() + centerDelta * 0.5f;
        return true;
    }

    bool CheckCircleCircle(const CircleCollider2D& first, const CircleCollider2D& second, Collision2D& collision)
    {
        const Vector2 centerDelta = second.GetWorldCenter() - first.GetWorldCenter();
        const float radiusSum = first.GetWorldRadius() + second.GetWorldRadius();
        const float distanceSquared = LengthSquared(centerDelta);

        if (distanceSquared > radiusSum * radiusSum)
        {
            return false;
        }

        const float distance = std::sqrt(distanceSquared);
        collision.normal = NormalizeOrDefault(centerDelta, Vector2(1.0f, 0.0f));
        collision.penetration = radiusSum - distance;
        collision.point = first.GetWorldCenter() + collision.normal * (first.GetWorldRadius() - collision.penetration * 0.5f);
        return true;
    }

    bool CheckCircleBox(const CircleCollider2D& circle, const BoxCollider2D& box, Collision2D& collision)
    {
        const Vector2 circleCenter = circle.GetWorldCenter();
        const Vector2 boxCenter = box.GetWorldCenter();
        const Vector2 boxToCircle = circleCenter - boxCenter;
        const Vector2 halfSize = box.GetHalfSize();
        const Vector2 axisX = box.GetAxisX();
        const Vector2 axisY = box.GetAxisY();

        const float localX = Dot(boxToCircle, axisX);
        const float localY = Dot(boxToCircle, axisY);
        const float closestX = Clamp(localX, -halfSize.x, halfSize.x);
        const float closestY = Clamp(localY, -halfSize.y, halfSize.y);
        const Vector2 closestPoint = boxCenter + axisX * closestX + axisY * closestY;
        Vector2 circleToBox = closestPoint - circleCenter;
        float distanceSquared = LengthSquared(circleToBox);
        const float radius = circle.GetWorldRadius();

        if (distanceSquared > radius * radius)
        {
            return false;
        }

        if (distanceSquared <= 0.00001f)
        {
            const float overlapX = halfSize.x - std::fabs(localX);
            const float overlapY = halfSize.y - std::fabs(localY);

            if (overlapX < overlapY)
            {
                circleToBox = (localX < 0.0f) ? axisX : Negate(axisX);
                distanceSquared = 0.0f;
                collision.penetration = radius + overlapX;
                collision.point = boxCenter + axisX * ((localX < 0.0f) ? -halfSize.x : halfSize.x) + axisY * localY;
            }
            else
            {
                circleToBox = (localY < 0.0f) ? axisY : Negate(axisY);
                distanceSquared = 0.0f;
                collision.penetration = radius + overlapY;
                collision.point = boxCenter + axisX * localX + axisY * ((localY < 0.0f) ? -halfSize.y : halfSize.y);
            }
        }
        else
        {
            const float distance = std::sqrt(distanceSquared);
            collision.penetration = radius - distance;
            collision.point = closestPoint;
        }

        collision.normal = NormalizeOrDefault(circleToBox, Vector2(1.0f, 0.0f));
        return true;
    }
}

bool Physics2D::ColliderPair::operator<(const ColliderPair& other) const
{
    std::less<Collider2D*> less;
    if (less(first, other.first))
    {
        return true;
    }

    if (less(other.first, first))
    {
        return false;
    }

    return less(second, other.second);
}

void Physics2D::RegisterCollider(Collider2D* collider)
{
    if (!collider)
    {
        return;
    }

    if (std::find(s_colliders.begin(), s_colliders.end(), collider) == s_colliders.end())
    {
        s_colliders.push_back(collider);
    }
}

void Physics2D::UnregisterCollider(Collider2D* collider)
{
    s_colliders.erase(std::remove(s_colliders.begin(), s_colliders.end(), collider), s_colliders.end());

    for (auto it = s_collidingPairs.begin(); it != s_collidingPairs.end();)
    {
        if (it->first == collider || it->second == collider)
        {
            it = s_collidingPairs.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Physics2D::Step(float deltaTime)
{
    (void)deltaTime;

    std::vector<Collider2D*> colliders = s_colliders;
    std::set<ColliderPair> currentPairs;

    for (size_t firstIndex = 0; firstIndex < colliders.size(); ++firstIndex)
    {
        for (size_t secondIndex = firstIndex + 1; secondIndex < colliders.size(); ++secondIndex)
        {
            Collider2D* first = colliders[firstIndex];
            Collider2D* second = colliders[secondIndex];
            if (!ShouldCollide(first, second))
            {
                continue;
            }

            Collision2D collision;
            if (!CheckCollision(first, second, collision))
            {
                continue;
            }

            const ColliderPair pair = MakePair(first, second);
            currentPairs.insert(pair);

            if (s_collidingPairs.find(pair) == s_collidingPairs.end())
            {
                DispatchEnter(collision);
            }
            else
            {
                DispatchStay(collision);
            }
        }
    }

    for (const ColliderPair& pair : s_collidingPairs)
    {
        if (currentPairs.find(pair) == currentPairs.end())
        {
            DispatchExit(pair.first, pair.second);
        }
    }

    s_collidingPairs = currentPairs;
}

void Physics2D::Clear()
{
    s_colliders.clear();
    s_collidingPairs.clear();
}

Physics2D::ColliderPair Physics2D::MakePair(Collider2D* first, Collider2D* second)
{
    std::less<Collider2D*> less;
    if (less(second, first))
    {
        return ColliderPair{ second, first };
    }

    return ColliderPair{ first, second };
}

bool Physics2D::ShouldCollide(Collider2D* first, Collider2D* second)
{
    return first
        && second
        && first != second
        && first->GetOwner() != second->GetOwner()
        && first->IsActiveAndEnabled()
        && second->IsActiveAndEnabled();
}

bool Physics2D::CheckCollision(Collider2D* first, Collider2D* second, Collision2D& collision)
{
    if (!first || !second)
    {
        return false;
    }

    bool collided = false;

    if (first->GetShape() == Collider2DShape::Box && second->GetShape() == Collider2DShape::Box)
    {
        collided = CheckBoxBox(*static_cast<BoxCollider2D*>(first), *static_cast<BoxCollider2D*>(second), collision);
    }
    else if (first->GetShape() == Collider2DShape::Circle && second->GetShape() == Collider2DShape::Circle)
    {
        collided = CheckCircleCircle(*static_cast<CircleCollider2D*>(first), *static_cast<CircleCollider2D*>(second), collision);
    }
    else if (first->GetShape() == Collider2DShape::Circle && second->GetShape() == Collider2DShape::Box)
    {
        collided = CheckCircleBox(*static_cast<CircleCollider2D*>(first), *static_cast<BoxCollider2D*>(second), collision);
    }
    else if (first->GetShape() == Collider2DShape::Box && second->GetShape() == Collider2DShape::Circle)
    {
        collided = CheckCircleBox(*static_cast<CircleCollider2D*>(second), *static_cast<BoxCollider2D*>(first), collision);
        if (collided)
        {
            collision.normal = Negate(collision.normal);
        }
    }

    if (!collided)
    {
        return false;
    }

    collision.self = first;
    collision.other = second;
    collision.isTrigger = first->IsTrigger() || second->IsTrigger();
    return true;
}

Collision2D Physics2D::ReverseCollision(const Collision2D& collision)
{
    Collision2D reversed = collision;
    reversed.self = collision.other;
    reversed.other = collision.self;
    reversed.normal = Negate(collision.normal);
    return reversed;
}

void Physics2D::DispatchEnter(const Collision2D& firstCollision)
{
    if (firstCollision.self && firstCollision.self->GetOwner())
    {
        firstCollision.self->GetOwner()->DispatchCollisionEnter2D(firstCollision);
    }

    const Collision2D secondCollision = ReverseCollision(firstCollision);
    if (secondCollision.self && secondCollision.self->GetOwner())
    {
        secondCollision.self->GetOwner()->DispatchCollisionEnter2D(secondCollision);
    }
}

void Physics2D::DispatchStay(const Collision2D& firstCollision)
{
    if (firstCollision.self && firstCollision.self->GetOwner())
    {
        firstCollision.self->GetOwner()->DispatchCollisionStay2D(firstCollision);
    }

    const Collision2D secondCollision = ReverseCollision(firstCollision);
    if (secondCollision.self && secondCollision.self->GetOwner())
    {
        secondCollision.self->GetOwner()->DispatchCollisionStay2D(secondCollision);
    }
}

void Physics2D::DispatchExit(Collider2D* first, Collider2D* second)
{
    if (!first || !second)
    {
        return;
    }

    Collision2D firstCollision;
    firstCollision.self = first;
    firstCollision.other = second;
    firstCollision.isTrigger = first->IsTrigger() || second->IsTrigger();

    Collision2D secondCollision = ReverseCollision(firstCollision);

    if (first->GetOwner())
    {
        first->GetOwner()->DispatchCollisionExit2D(firstCollision);
    }

    if (second->GetOwner())
    {
        second->GetOwner()->DispatchCollisionExit2D(secondCollision);
    }
}
