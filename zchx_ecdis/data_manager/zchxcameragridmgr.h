#ifndef ZCHXCAMERAGRIDMGR_H
#define ZCHXCAMERAGRIDMGR_H

#include "zchxtemplatedatamgr.h"

namespace qt {
class zchxCameraGridDataMgr : public zchxTemplateDataMgr<CameraGridElement, ZCHX::Data::ITF_NetGrid>
{
    Q_OBJECT
public:
    explicit zchxCameraGridDataMgr(zchxMapWidget* w, QObject *parent = 0);
    bool    updateActiveItem(const QPoint& pt);
    void    setCameraNetGridList(const QList<ZCHX::Data::ITF_CameraNetGrid> & list);
    void    show(QPainter *painter);

    //鼠标操作时临时的网格图形
    ZCHX::Data::ITF_CameraNetGrid makeCameraGrid(const LatLon &sll, const LatLon &ell);
    void    setCameraGridParam(const QString& id, const QSizeF& size);
    void    setDrawLonLat(const LatLon& start, const LatLon& end);
signals:




public slots:


private:
    QSizeF                                           mSize;
    QString                                          mCameraID;
    LatLon                                           mStartPnt;
    LatLon                                           mEndPnt;
};
}

#endif // ZCHXCAMERAGRIDMGR_H
