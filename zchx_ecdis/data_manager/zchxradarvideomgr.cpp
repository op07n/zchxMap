#include "zchxradarvideomgr.h"
#include "zchxmapframe.h"

namespace qt {
zchxRadarVideoMgr::zchxRadarVideoMgr(zchxMapWidget *w, QObject *parent):
    zchxTemplateDataMgr<RadarVideoGlowElement, ZCHX::Data::ITF_RadarVideoGLow>(w, DATA_MGR_RADAR_VIDEO, ZCHX::LAYER_RADARVIDEO, parent)
{
    mRadarVideoData.afterglowType = 3;
    mRadarVideoData.type = ZCHX::Data::ITF_RadarVideoGLow::RadarVideo;
    mRadarVideoData.afterglowIndex = 0;
    mRadarVideoData.showvideo = false;
    QPixmap objPixmap(ZCHX::Data::RadarVideoPixmapWidth, ZCHX::Data::RadarVideoPixmapHeight);
    objPixmap.fill(Qt::transparent);//用透明色填充
    mRadarVideoData.videoPixmap = objPixmap;
    for(int i = 0;i<12;i++)
    {
        QPixmap nullPixmap;
        mRadarVideoData.afterglowPixmap[i] = nullPixmap;
    }
    setData(mRadarVideoData);
}

void zchxRadarVideoMgr::setIsDisplay(bool sts)
{
    mRadarVideoData.showvideo = sts;
    setData(mRadarVideoData);
}

void zchxRadarVideoMgr::setRadarVideoData(double dCentreLon, double dCentreLat, double dDistance, int uDisplayType,int uLoopNum)
{
    mRadarVideoData.lat = dCentreLat;
    mRadarVideoData.lon = dCentreLon;
    mRadarVideoData.distance = dDistance;
    mRadarVideoData.type = ZCHX::Data::ITF_RadarVideoGLow::RadarVideoGLowType(uDisplayType);
    mRadarVideoData.afterglowType = ((uLoopNum > 12) ? 12 : uLoopNum);
    setData(mRadarVideoData);
}

void zchxRadarVideoMgr::setRadarVideoPixmap(int uIndex, const QPixmap &objPixmap, const QPixmap &prePixmap)
{
    if(mRadarVideoData.type == ZCHX::Data::ITF_RadarVideoGLow::RadarVideo)
    {
        mRadarVideoData.videoPixmap = objPixmap;
    } else {
        if(uIndex >= 12) return;
        //最新的数据 固定放在5,4位置
        mRadarVideoData.afterglowPixmap[5] = objPixmap;
        mRadarVideoData.afterglowIndex = 5;
        for(int i=1; i<5; ++i)
        {
            QPixmap tempPix = mRadarVideoData.afterglowPixmap[i];
            mRadarVideoData.afterglowPixmap[i-1] = tempPix;
        }
        mRadarVideoData.afterglowPixmap[4] = prePixmap;
    }
    mRadarVideoData.showvideo = true;
    setData(mRadarVideoData);
}

void zchxRadarVideoMgr::setCurrentRadarVideoPixmap(const QPixmap &objPixmap)
{
    if(mRadarVideoData.type == ZCHX::Data::ITF_RadarVideoGLow::RadarVideo)
    {
        mRadarVideoData.videoPixmap = objPixmap;
    } else {
        mRadarVideoData.afterglowPixmap[5] = objPixmap;
        mRadarVideoData.afterglowIndex = 5;
    }
    mRadarVideoData.showvideo = true;
    setData(mRadarVideoData);
}

}

