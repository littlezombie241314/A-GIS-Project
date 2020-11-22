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
        /// ���ò���
        /// </summary>
        virtual void        setParam(const char* name,const char* value)    =   0;
        /// <summary>
        /// ��������s
        /// </summary>
        virtual CELLTask*   load(CELLTask* task)    =   0;

        /// <summary>
        /// ж������
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
    /// ʸ��Ҫ����Ϣ
    /// </summary>
    class   IFeature
    {
    public:
        virtual ~IFeature(){}
        /// <summary>
        /// Ҫ������
        /// </summary>
        virtual char*   getName()   =   0;
        /// <summary>
        /// ��ȡ��ĸ���
        /// </summary>
        virtual size_t  getGroupCount() =   0;
        /// <summary>
        /// ��ȡ������
        /// </summary>
        virtual Group*  getGroup(size_t index)  =   0;
        /// <summary>
        /// ��ȡ��Χ����Ϣ
        /// </summary>
        virtual aabb2dr getAabb()   =   0;
        /// <summary>
        /// ��ȡ�����ݸ���
        /// </summary>
        virtual size_t  getPointCount() =   0;
        /// <summary>
        /// ��ȡ������
        /// </summary>
        virtual real2   getPoint(size_t nindx)  =   0;
    };

    typedef std::vector<IFeature*>  ArrayFeature;
    /// <summary>
    /// ʸ��Ҫ����Ϣ
    /// </summary>
    class   IFeaturePoint :public IFeature
    {
    };
    /// <summary>
    /// ʸ��Ҫ����Ϣ
    /// </summary>
    class   IFeatureLine :public IFeature
    {};
    /// <summary>
    /// ʸ��Ҫ����Ϣ
    /// </summary>
    class   IFeaturePolygon :public IFeature
    {};

    class   ILayer
    {
    public:
        /// <summary>
        /// ����shp�ļ�
        /// </summary>
        virtual bool        loadShp(const char*shp) =   0;
        /// <summary>
        /// ʸ��Ҫ�ظ���
        /// </summary>
        virtual size_t      getFeatureCount()    =   0;
        /// <summary>
        /// ��ȡ ʸ��Ҫ��
        /// </summary>
        virtual IFeature*   getFeature(size_t index)    =   0;
        /// <summary>
        /// ���ʸ��Ҫ��
        /// </summary>
        virtual void        addFeature(IFeature* feature)   =   0;
        /// <summary>
        /// �Ƴ�ʸ��Ҫ��
        /// </summary>
        virtual void        removeFeature(IFeature* feature)    =   0;
        /// <summary>
        /// �Ƴ�����ʸ��Ҫ��
        /// </summary>
        virtual void        removeAllFeature()  =   0;
        /// <summary>
        /// ɾ������ʸ��Ҫ��
        /// </summary>
        virtual void        destoryAllFeature() =   0;
        /// <summary>
        /// ��ѯʸ��Ҫ��
        /// </summary>
        virtual IFeature*   query(const char* name) =   0;
        /// <summary>
        /// ��ѯʸ��Ҫ��
        /// </summary>
        virtual size_t      query(const CELL::aabb2dr& aabb,ArrayFeature& features) =   0;
    };
    class   IGIS3DPlatform
    {
    public:
        /// <summary>
        /// ��ʼ��ƽ̨
        /// </summary>
        virtual bool    initialzie()    =   0;
        /// <summary>
        /// �¼����봦��ӿ�
        /// </summary>
        virtual bool    loadScene(const char* sceneFile)    =   0;
        /// <summary>
        /// �¼����봦��ӿ�
        /// </summary>
        virtual LRESULT inputEvent(HWND hwnd,UINT msgId,WPARAM wParam,LPARAM lParam)    =   0;
        /// <summary>
        /// ж��
        /// </summary>
        virtual void    unInitialize()  =   0;

        /// <summary>
        /// ����shape file,�����ض���
        /// </summary>
        virtual ILayer* loadLayer(const char* shp) = 0;

    };

    struct  CREATEPARAM
    {
        /// �����ھ��
        HWND    _hWnd;
    };
    ENGINE_API   IGIS3DPlatform* createPlatform(const CREATEPARAM& param);

}
