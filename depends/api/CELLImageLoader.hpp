#pragma once

#include "IGIS3DPlatform.h"

#include "CELLImage.hpp"


namespace CELL
{
    class   ENGINE_API  CELLImageLoader
    {
    public:
        /// <summary>
        /// 根据文件加载图形信息
        /// </summary>
        static  CELLImage*  load(const char* fileName);
        static  bool        loadImage( const char* fileName,CELL::CELLImage& image );
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgb
        /// </summary>
        static  RgbBuffer*  loadRgb_256X256(const char* fileName);
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  RgbaBuffer* loadRgba_256X256(const char* fileName);
 
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgb
        /// </summary>
        static  bool        loadImageToRgb( const char* fileName,CELLImage& image );
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  bool        loadImageToRgba( const char* fileName,CELLImage& image );

        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  bool        loadImageToDXT1(const char* fileName, CELLImage& image);

        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  bool        loadImageBufferToDXT1(const void* data,int len, CELLImage& image);
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  bool        loadImageToDXT5(const char* fileName, CELLImage& image);

        /// <summary>
        /// RGBA a数据并转化成DXT1
        /// </summary>
        static  bool        rgbaBufferToDXT1(const void* data, int w,int h, CELLImage& image);
       

    };
}