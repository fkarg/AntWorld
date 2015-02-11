/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Canvas.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Canvas()
    {
        m_Loaded = true;
        m_Callback.widgetType = Type_Canvas;

        setSize(100, 100);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::Canvas(const Canvas& copy) :
    ClickableWidget(copy)
    {
        setSize(static_cast<float>(copy.m_renderTexture.getSize().x),
                static_cast<float>(copy.m_renderTexture.getSize().y));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas::~Canvas()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas& Canvas::operator= (const Canvas& right)
    {
        // Make sure it is not the same widget
        if (this != &right)
        {
            this->ClickableWidget::operator=(right);

            setSize(static_cast<float>(right.m_renderTexture.getSize().x),
                    static_cast<float>(right.m_renderTexture.getSize().y));
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Canvas* Canvas::clone()
    {
        return new Canvas(*this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::setPosition(float x, float y)
    {
        Transformable::setPosition(x, y);

        m_sprite.setPosition(x, y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::setSize(float width, float height)
    {
        m_renderTexture.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        m_sprite.setTexture(m_renderTexture.getTexture(), true);

        m_renderTexture.clear();
        m_renderTexture.display();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f Canvas::getSize() const
    {
        return sf::Vector2f(m_renderTexture.getSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::clear(const sf::Color& color)
    {
        m_renderTexture.clear(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_renderTexture.draw(drawable, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(const sf::Vertex* vertices, unsigned int vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
    {
        m_renderTexture.draw(vertices, vertexCount, type, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::display()
    {
        m_renderTexture.display();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
