#pragma once

#include "IGIS3DPlatform.h"

#include "CELLImage.hpp"


namespace CELL
{
    class   ENGINE_API  CELLImageLoader
    {
    public:
        /// <summary>
        /// �����ļ�����ͼ����Ϣ
        /// </summary>
        static  CELLImage*  load(const char* fileName);
        static  bool        loadImage( const char* fileName,CELL::CELLImage& image );
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgb
        /// </summary>
        static  RgbBuffer*  loadRgb_256X256(const char* fileName);
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  RgbaBuffer* loadRgba_256X256(const char* fileName);
 
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgb
        /// </summary>
        static  bool        loadImageToRgb( const char* fileName,CELLImage& image );
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  bool        loadImageToRgba( const char* fileName,CELLImage& image );

        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  bool        loadImageToDXT1(const char* fileName, CELLImage& image);

        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  bool        loadImageBufferToDXT1(const void* data,int len, CELLImage& image);
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  bool        loadImageToDXT5(const char* fileName, CELLImage& image);

        /// <summary>
        /// RGBA a���ݲ�ת����DXT1
        /// </summary>
        static  bool        rgbaBufferToDXT1(const void* data, int w,int h, CELLImage& image);
       

    };
}