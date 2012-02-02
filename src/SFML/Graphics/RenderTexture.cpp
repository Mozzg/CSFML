////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
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
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/RenderTextureStruct.h>
#include <SFML/Graphics/SpriteStruct.h>
#include <SFML/Graphics/TextStruct.h>
#include <SFML/Graphics/CircleShapeStruct.h>
#include <SFML/Graphics/ConvexShapeStruct.h>
#include <SFML/Graphics/RectangleShapeStruct.h>
#include <SFML/Graphics/VertexArrayStruct.h>
#include <SFML/Graphics/ConvertRenderStates.hpp>
#include <SFML/Internal.h>


////////////////////////////////////////////////////////////
sfRenderTexture* sfRenderTexture_Create(unsigned int width, unsigned int height, sfBool depthBuffer)
{
    sfRenderTexture* renderTexture = new sfRenderTexture;
    renderTexture->This.Create(width, height, depthBuffer == sfTrue);
    renderTexture->Target = new sfTexture(const_cast<sf::Texture*>(&renderTexture->This.GetTexture()));
    renderTexture->DefaultView.This = renderTexture->This.GetDefaultView();
    renderTexture->CurrentView.This = renderTexture->This.GetView();

    return renderTexture;
}


////////////////////////////////////////////////////////////
void sfRenderTexture_Destroy(sfRenderTexture* renderTexture)
{
    delete renderTexture->Target;
    delete renderTexture;
}


////////////////////////////////////////////////////////////
unsigned int sfRenderTexture_GetWidth(const sfRenderTexture* renderTexture)
{
    CSFML_CALL_RETURN(renderTexture, GetWidth(), 0);
}


////////////////////////////////////////////////////////////
unsigned int sfRenderTexture_GetHeight(const sfRenderTexture* renderTexture)
{
    CSFML_CALL_RETURN(renderTexture, GetHeight(), 0);
}


////////////////////////////////////////////////////////////
sfBool sfRenderTexture_SetActive(sfRenderTexture* renderTexture, sfBool active)
{
    CSFML_CALL_RETURN(renderTexture, SetActive(active == sfTrue), sfFalse)
}


////////////////////////////////////////////////////////////
void sfRenderTexture_Display(sfRenderTexture* renderTexture)
{
    CSFML_CALL(renderTexture, Display())
}


////////////////////////////////////////////////////////////
void sfRenderTexture_Clear(sfRenderTexture* renderTexture, sfColor color)
{
    sf::Color SFMLColor(color.r, color.g, color.b, color.a);

    CSFML_CALL(renderTexture, Clear(SFMLColor));
}


////////////////////////////////////////////////////////////
void sfRenderTexture_SetView(sfRenderTexture* renderTexture, const sfView* view)
{
    CSFML_CHECK(view);
    CSFML_CALL(renderTexture, SetView(view->This));
    renderTexture->CurrentView.This = view->This;
}


////////////////////////////////////////////////////////////
const sfView* sfRenderTexture_GetView(const sfRenderTexture* renderTexture)
{
    CSFML_CHECK_RETURN(renderTexture, NULL);

    return &renderTexture->CurrentView;
}


////////////////////////////////////////////////////////////
const sfView* sfRenderTexture_GetDefaultView(const sfRenderTexture* renderTexture)
{
    CSFML_CHECK_RETURN(renderTexture, NULL);

    return &renderTexture->DefaultView;
}


////////////////////////////////////////////////////////////
sfIntRect sfRenderTexture_GetViewport(const sfRenderTexture* renderTexture, const sfView* view)
{
    sfIntRect rect = {0, 0, 0, 0};
    CSFML_CHECK_RETURN(view, rect);
    CSFML_CHECK_RETURN(renderTexture, rect);

    sf::IntRect SFMLrect = renderTexture->This.GetViewport(view->This);
    rect.Left   = SFMLrect.Left;
    rect.Top    = SFMLrect.Top;
    rect.Width  = SFMLrect.Width;
    rect.Height = SFMLrect.Height;

    return rect;
}


////////////////////////////////////////////////////////////
void sfRenderTexture_ConvertCoords(const sfRenderTexture* renderTexture, unsigned int textureX, unsigned int textureY, float* viewX, float* viewY, const sfView* targetView)
{
    CSFML_CHECK(renderTexture);

    sf::Vector2f point;
    if (targetView)
        point = renderTexture->This.ConvertCoords(textureX, textureY, targetView->This);
    else
        point = renderTexture->This.ConvertCoords(textureX, textureY);

    if (viewX) *viewX = point.x;
    if (viewY) *viewY = point.y;
}


////////////////////////////////////////////////////////////
void sfRenderTexture_DrawSprite(sfRenderTexture* renderTexture, const sfSprite* object, const sfRenderStates* states)
{
    CSFML_CHECK(object);
    CSFML_CALL(renderTexture, Draw(object->This, ConvertRenderStates(states)));
}
void sfRenderTexture_DrawText(sfRenderTexture* renderTexture, const sfText* object, const sfRenderStates* states)
{
    CSFML_CHECK(object);
    CSFML_CALL(renderTexture, Draw(object->This, ConvertRenderStates(states)));
}
void sfRenderTexture_DrawCircleShape(sfRenderTexture* renderTexture, const sfCircleShape* object, const sfRenderStates* states)
{
    CSFML_CHECK(object);
    CSFML_CALL(renderTexture, Draw(object->This, ConvertRenderStates(states)));
}
void sfRenderTexture_DrawConvexShape(sfRenderTexture* renderTexture, const sfConvexShape* object, const sfRenderStates* states)
{
    CSFML_CHECK(object);
    CSFML_CALL(renderTexture, Draw(object->This, ConvertRenderStates(states)));
}
void sfRenderTexture_DrawRectangleShape(sfRenderTexture* renderTexture, const sfRectangleShape* object, const sfRenderStates* states)
{
    CSFML_CHECK(object);
    CSFML_CALL(renderTexture, Draw(object->This, ConvertRenderStates(states)));
}
void sfRenderTexture_DrawVertexArray(sfRenderTexture* renderTexture, const sfVertexArray* object, const sfRenderStates* states)
{
    CSFML_CHECK(object);
    CSFML_CALL(renderTexture, Draw(object->This, ConvertRenderStates(states)));
}


////////////////////////////////////////////////////////////
CSFML_GRAPHICS_API void sfRenderTexture_DrawPrimitives(sfRenderTexture* renderTexture,
                                              const sfVertex* vertices, unsigned int vertexCount,
                                              sfPrimitiveType type, const sfRenderStates* states)
{
    CSFML_CALL(renderTexture, Draw(reinterpret_cast<const sf::Vertex*>(vertices), vertexCount,
               static_cast<sf::PrimitiveType>(type), ConvertRenderStates(states)));
}


////////////////////////////////////////////////////////////
CSFML_GRAPHICS_API void sfRenderTexture_PushGLStates(sfRenderTexture* renderTexture)
{
    CSFML_CALL(renderTexture, PushGLStates());
}


////////////////////////////////////////////////////////////
CSFML_GRAPHICS_API void sfRenderTexture_PopGLStates(sfRenderTexture* renderTexture)
{
    CSFML_CALL(renderTexture, PopGLStates());
}


////////////////////////////////////////////////////////////
CSFML_GRAPHICS_API void sfRenderTexture_ResetGLStates(sfRenderTexture* renderTexture)
{
    CSFML_CALL(renderTexture, ResetGLStates());
}


////////////////////////////////////////////////////////////
const sfTexture* sfRenderTexture_GetTexture(const sfRenderTexture* renderTexture)
{
    CSFML_CHECK_RETURN(renderTexture, NULL);

    return renderTexture->Target;
}
