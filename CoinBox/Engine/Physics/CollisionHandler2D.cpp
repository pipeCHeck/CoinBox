#include "CollisionHandler2D.h"

void CollisionHandler2D::OnCollisionEnter2D(const Collision2D& collision)
{
    if (m_onEnter)
    {
        m_onEnter(collision);
    }
}

void CollisionHandler2D::OnCollisionStay2D(const Collision2D& collision)
{
    if (m_onStay)
    {
        m_onStay(collision);
    }
}

void CollisionHandler2D::OnCollisionExit2D(const Collision2D& collision)
{
    if (m_onExit)
    {
        m_onExit(collision);
    }
}
