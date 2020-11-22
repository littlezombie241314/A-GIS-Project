#pragma once

#include "CELLTask.hpp"
#include "CELLMath.hpp"
#include "CELLImage.hpp"

namespace CELL
{
    class CELLQuadTree;
    class CELLTileTask :public CELLTask
    {
    public:
        CELLQuadTree*   _node;
        TileId          _tileId;
        CELLImage       _image;
    };

}
