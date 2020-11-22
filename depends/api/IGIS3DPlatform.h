#pragma once
#ifdef  ENGINE_API_EXP
#define ENGINE_API  __declspec(dllexport)
#else
#define ENGINE_API  __declspec(dllimport)
#endif

#define     EXPORTFUNC  __declspec(dllexport) 
#define     IMPORTFUNC  __declspec(dllimport) 

#include    <windows.h>

#include    "CELLMath.hpp"
#include    <vector>

namespace   CELL
{
    class   CELLTask;
    class   IPluginTileSource;
    class   IGIS3DPlatform;

    class   IPlugin
    {
    public:
    };

    #define CREATE_TILESOURCE   "createTileSource"
    typedef IPluginTileSource*  (*CREATETILESOURCEFUNC)(IGIS3DPlatform*);

    class   IPluginTileSource :public IPlugin
    {
    public:
        /// <summary>
        /// 设置参数
        /// </summary>
        virtual void        setParam(const char* name,const char* value)    =   0;
        /// <summary>
        /// 加载数据s
        /// </summary>
        virtual CELLTask*   load(CELLTask* task)    =   0;

        /// <summary>
        /// 卸载数据
        /// </summary>
        virtual void        unload(CELLTask* task) = 0;

    };

    class   Group
    {
    public:
        uint    start;
        uint    count;
    };
    
    /// <summary>
    /// 矢量要素信息
    /// </summary>
    class   IFeature
    {
    public:
        virtual ~IFeature(){}
        /// <summary>
        /// 要素名称
        /// </summary>
        virtual char*   getName()   =   0;
        /// <summary>
        /// 获取组的个数
        /// </summary>
        virtual size_t  getGroupCount() =   0;
        /// <summary>
        /// 获取组数据
        /// </summary>
        virtual Group*  getGroup(size_t index)  =   0;
        /// <summary>
        /// 获取包围盒信息
        /// </summary>
        virtual aabb2dr getAabb()   =   0;
        /// <summary>
        /// 获取点数据个数
        /// </summary>
        virtual size_t  getPointCount() =   0;
        /// <summary>
        /// 获取点数据
        /// </summary>
        virtual real2   getPoint(size_t nindx)  =   0;
    };

    typedef std::vector<IFeature*>  ArrayFeature;
    /// <summary>
    /// 矢量要素信息
    /// </summary>
    class   IFeaturePoint :public IFeature
    {
    };
    /// <summary>
    /// 矢量要素信息
    /// </summary>
    class   IFeatureLine :public IFeature
    {};
    /// <summary>
    /// 矢量要素信息
    /// </summary>
    class   IFeaturePolygon :public IFeature
    {};

    class   ILayer
    {
    public:
        /// <summary>
        /// 加载shp文件
        /// </summary>
        virtual bool        loadShp(const char*shp) =   0;
        /// <summary>
        /// 矢量要素个数
        /// </summary>
        virtual size_t      getFeatureCount()    =   0;
        /// <summary>
        /// 获取 矢量要素
        /// </summary>
        virtual IFeature*   getFeature(size_t index)    =   0;
        /// <summary>
        /// 添加矢量要素
        /// </summary>
        virtual void        addFeature(IFeature* feature)   =   0;
        /// <summary>
        /// 移除矢量要素
        /// </summary>
        virtual void        removeFeature(IFeature* feature)    =   0;
        /// <summary>
        /// 移除所有矢量要素
        /// </summary>
        virtual void        removeAllFeature()  =   0;
        /// <summary>
        /// 删除所有矢量要素
        /// </summary>
        virtual void        destoryAllFeature() =   0;
        /// <summary>
        /// 查询矢量要素
        /// </summary>
        virtual IFeature*   query(const char* name) =   0;
        /// <summary>
        /// 查询矢量要素
        /// </summary>
        virtual size_t      query(const CELL::aabb2dr& aabb,ArrayFeature& features) =   0;
    };
    class   IGIS3DPlatform
    {
    public:
        /// <summary>
        /// 初始化平台
        /// </summary>
        virtual bool    initialzie()    =   0;
        /// <summary>
        /// 事件输入处理接口
        /// </summary>
        virtual bool    loadScene(const char* sceneFile)    =   0;
        /// <summary>
        /// 事件输入处理接口
        /// </summary>
        virtual LRESULT inputEvent(HWND hwnd,UINT msgId,WPARAM wParam,LPARAM lParam)    =   0;
        /// <summary>
        /// 卸载
        /// </summary>
        virtual void    unInitialize()  =   0;

        /// <summary>
        /// 加载shape file,并返回对象
        /// </summary>
        virtual ILayer* loadLayer(const char* shp) = 0;

    };

    struct  CREATEPARAM
    {
        /// 父窗口句柄
        HWND    _hWnd;
    };
    ENGINE_API   IGIS3DPlatform* createPlatform(const CREATEPARAM& param);

}
