#include "testmainwindow.h"
#include "ui_testmainwindow.h"
#include <QDateTime>
#include "../zchx_ecdis/zchxutils.hpp"
#include "../zchx_ecdis/element/fixelement.h"
#include "../zchx_ecdis/element/aiselement.hpp"

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QVBoxLayout);
    m_pEcdisWin = new qt::MainWindow;
    ui->centralwidget->layout()->addWidget(m_pEcdisWin);

    //添加防区图层
    std::shared_ptr<qt::MapLayer> warningZoneLayer(new qt::MapLayer(ZCHX::LAYER_DEFENCE, ZCHX::TR_LAYER_DEFENCE, true));
    m_pEcdisWin->itfAddLayer(warningZoneLayer);

    //添加船舶计划航线图层
    std::shared_ptr<qt::MapLayer> pShipPlanLineLayer(new qt::MapLayer(ZCHX::LAYER_SHIPPLAN_LINE,ZCHX::TR_LAYER_SHIPPLAN_LINE,true));
    m_pEcdisWin->itfAddLayer(pShipPlanLineLayer);

    //经纬网格
    std::shared_ptr<qt::MapLayer> pLonlatGirdLayer(new qt::MapLayer(ZCHX::LAYER_LONLAT_GIRD,ZCHX::TR_LAYER_LONLAT_GIRD,false));
    m_pEcdisWin->itfAddLayer(pLonlatGirdLayer);

    //ais
    std::shared_ptr<qt::MapLayer> pAisLayer(new qt::MapLayer(ZCHX::LAYER_AIS,ZCHX::TR_LAYER_AIS,true));
    m_pEcdisWin->itfAddLayer(pAisLayer);

    std::shared_ptr<qt::MapLayer> pAisCurrentLayer(new qt::MapLayer(ZCHX::LAYER_AIS_CURRENT,ZCHX::TR_LAYER_AIS_CURRENT,true));
    m_pEcdisWin->itfAddLayer(pAisCurrentLayer);

    std::shared_ptr<qt::MapLayer> pAisTrackLayer(new qt::MapLayer(ZCHX::LAYER_AIS_TRACK,ZCHX::TR_LAYER_AIS_TRACK,true));
    m_pEcdisWin->itfAddLayer(pAisTrackLayer);

    //雷达
    std::shared_ptr<qt::MapLayer> pRadarLayer(new qt::MapLayer(ZCHX::LAYER_RADAR,ZCHX::TR_LAYER_RADAR,true));
    m_pEcdisWin->itfAddLayer(pRadarLayer);

    std::shared_ptr<qt::MapLayer> pRadarCurrentLayer(new qt::MapLayer(ZCHX::LAYER_RADAR_CURRENT,ZCHX::TR_LAYER_RADAR_CURRENT,true));
    m_pEcdisWin->itfAddLayer(pRadarCurrentLayer);

    std::shared_ptr<qt::MapLayer> pRadarTrackLayer(new qt::MapLayer(ZCHX::LAYER_RADAR_TRACK,ZCHX::TR_LAYER_RADAR_TRACK,true));
    m_pEcdisWin->itfAddLayer(pRadarTrackLayer);

    std::shared_ptr<qt::MapLayer> pNavigationMark(new qt::MapLayer(ZCHX::LAYER_NAVIGATION_MARK,ZCHX::TR_LAYER_NAVIGATION_MARK,true));
    m_pEcdisWin->itfAddLayer(pNavigationMark);

    std::shared_ptr<qt::MapLayer> pTowerRod(new qt::MapLayer(ZCHX::LAYER_TOWER_ROD,ZCHX::TR_LAYER_TOWER_ROD,true));
    m_pEcdisWin->itfAddLayer(pTowerRod);

    //雷达回波
    std::shared_ptr<qt::MapLayer> pRadarVideo(new qt::MapLayer(ZCHX::LAYER_RADARVIDEO,ZCHX::TR_LAYER_RADARVIDEO,true));
    m_pEcdisWin->itfAddLayer(pRadarVideo);

    //历史雷达和AIS
    std::shared_ptr<qt::MapLayer> pHistoryAis(new qt::MapLayer(ZCHX::LAYER_HISTORY_AIS,ZCHX::TR_LAYER_HISTORY_AIS,true));
    m_pEcdisWin->itfAddLayer(pHistoryAis);

    std::shared_ptr<qt::MapLayer> pHistoryRadar(new qt::MapLayer(ZCHX::LAYER_HISTORY_RADAR,ZCHX::TR_LAYER_HISTORY_RADAR,true));
    m_pEcdisWin->itfAddLayer(pHistoryRadar);

    //添加航道图层
    std::shared_ptr<qt::MapLayer> channelLayer(new qt::MapLayer(ZCHX::LAYER_CHANNEL, ZCHX::TR_LAYER_CHANNEL, true));
    m_pEcdisWin->itfAddLayer(channelLayer);

    //添加锚泊图层
    std::shared_ptr<qt::MapLayer> mooringLayer(new qt::MapLayer(ZCHX::LAYER_MOORING, ZCHX::TR_LAYER_MOORING, true));
    m_pEcdisWin->itfAddLayer(mooringLayer);

    //添加自定义区域图层
    std::shared_ptr<qt::MapLayer> defineZoneLayer(new qt::MapLayer(ZCHX::LAYER_DEFINEZONE, ZCHX::TR_LAYER_DEFINEZONE, true));
    m_pEcdisWin->itfAddLayer(defineZoneLayer);

    //添加卡口图层
    std::shared_ptr<qt::MapLayer> cardMouthLayer(new qt::MapLayer(ZCHX::LAYER_CARDMOUTH, ZCHX::TR_LAYER_CARDMOUTH, true));
    m_pEcdisWin->itfAddLayer(cardMouthLayer);

    //添加船舶预警图层
    std::shared_ptr<qt::MapLayer> shipAlarmLayer(new qt::MapLayer(ZCHX::LAYER_ALARMASCEND, ZCHX::TR_LAYER_ALARMASCEND, true));
    m_pEcdisWin->itfAddLayer(shipAlarmLayer);

    //添加危险圈图层
    std::shared_ptr<qt::MapLayer> dangerLayer(new qt::MapLayer(ZCHX::LAYER_DANGEROUS_CIRLE, ZCHX::TR_LAYER_DANGEROUS_CIRLE, true));
    m_pEcdisWin->itfAddLayer(dangerLayer);

    //本地标注
    std::shared_ptr<qt::MapLayer> localMarkLayer(new qt::MapLayer(ZCHX::LAYER_LOCALMARK, ZCHX::TR_LAYER_LOCALMARK, true));
    m_pEcdisWin->itfAddLayer(localMarkLayer);
    //相机图层
    std::shared_ptr<qt::MapLayer> cameraMarkLayer(new qt::MapLayer(ZCHX::LAYER_CAMERA, ZCHX::TR_LAYER_CAMERA, true));
    m_pEcdisWin->itfAddLayer(cameraMarkLayer);
    //相机网格图层
    std::shared_ptr<qt::MapLayer> cameraGridLayer(new qt::MapLayer(ZCHX::LAYER_CAMERANETGRID, ZCHX::TR_LAYER_CAMERANETGRID, true));
    m_pEcdisWin->itfAddLayer(cameraGridLayer);

    mTestTimer = new QTimer;
    mTestTimer->setInterval(3000);
    connect(mTestTimer, SIGNAL(timeout()), this, SLOT(slotTimerout()));
//    mTestTimer->setSingleShot(true);
//    mTestTimer->start();
//    m_pEcdisWin->itfsetPluginUseModel(ZCHX::Data::ECDIS_PLUGIN_USE_EDIT_MODEL);
//    m_pEcdisWin->itfToolBarChannelAreaAdd();
    ZCHX::Data::ITF_AISBASESTATION cam;
    cam.latItude = 22.223459;
    cam.longIteude = 113.083457;
    cam.aisName = tr("test ais station");
    cam.aisId = "1";
    m_pEcdisWin->itfGetLayer(ZCHX::LAYER_AIS_STATION)->addElement(std::shared_ptr<qt::Element>(new qt::AISBaseStationElement(cam, m_pEcdisWin->getMapWidget()) ));
    m_pEcdisWin->itfSetZoomLableDisplay(false);

    //防区测试
    ZCHX::Data::ITF_CameraRegion zone;
    zone.id = "123";
    zone.harbourId = "1";
    zone.regionId = "2";
    zone.CameraBallName = "ball";
    zone.CameraGunName = "gun";
    zone.Berth = "berth";
    zone.Status = ZCHX::Data::CameraRegionStatus::DEFAULT;
    zone.lat = 22.6472;
    zone.lon = 114.074;
    zone.shipNumbers = "10";
    zone.photoNumbers = "0";
    zone.CameraPointList.append(ZCHX::Data::LatLon(22.6472, 114.074));
    zone.CameraPointList.append(ZCHX::Data::LatLon(22.6453, 114.083));
    zone.CameraPointList.append(ZCHX::Data::LatLon(22.6472, 114.084));
    zone.CameraPointList.append(ZCHX::Data::LatLon(22.6483, 114.083));
    std::shared_ptr<qt::MapLayer> layer = m_pEcdisWin->itfGetLayer(ZCHX::LAYER_CAMERA_REGION);
    layer->addElement(std::shared_ptr<qt::Element>(new qt::CameraRegionElement(zone, m_pEcdisWin->getMapWidget())));



    //检查椭圆图层是否存在，不存在就添加
    layer = m_pEcdisWin->itfGetLayer(ZCHX::LAYER_ELLIPSE);
    if(!layer)
    {
        m_pEcdisWin->itfAddLayer(ZCHX::LAYER_ELLIPSE, tr("航行位置点"), true);
        layer = m_pEcdisWin->itfGetLayer(ZCHX::LAYER_ELLIPSE);
        if(!layer) return;
    }

    ZCHX::Data::ITF_EleEllipse ele;
    ele.name = "";
    ele.pen = QPen(Qt::red);
    ele.rx = 20;
    ele.ry = 20;
    ele.showCircleCenter = false; // 禁止显示圆心
    ele.ll.lat = QString::number(22.6472,'f', 13).toDouble();
    ele.ll.lon = QString::number(114.084,'f', 13).toDouble();
    layer->addElement(std::shared_ptr<qt::Element>(new qt::EllipseElement(ele,  m_pEcdisWin->getMapWidget())));
    m_pEcdisWin->itfSetEnableShipTag(qt::SHIP_ITEM_LABEL | qt::SHIP_ITEM_NAME | qt::SHIP_ITEM_MULTILINE);
    connect(m_pEcdisWin, SIGNAL(itfSendPickPoints(QList<ZCHX::Data::LatLon>)),
            this, SLOT(slotRecvPickPnts(QList<ZCHX::Data::LatLon>)));
    m_pEcdisWin->itfToolBarPickPoints();


}

void TestMainWindow::slotRecvPickPnts(const QList<ZCHX::Data::LatLon> &list)
{
    qDebug()<<"total pnts size:"<<list.size();
    foreach (ZCHX::Data::LatLon ll, list) {
        qDebug()<<"ll:"<<ll.lat<<ll.lon;
    }
}

TestMainWindow::~TestMainWindow()
{
    if(m_pEcdisWin) delete m_pEcdisWin;
    delete ui;
}

void TestMainWindow::slotTimerout()
{
    //Lat=20.123456780000001
    //Lon=110.12345678
    qsrand(QDateTime::currentDateTime().toTime_t());
    QList<ZCHX::Data::tagITF_RadarPoint> radarList;
    QList<ZCHX::Data::ITF_AIS> aisList;
    for(int i=0; i<10; i++)
    {
        ZCHX::Data::ITF_AIS data;
        data.mmsi = i*100+1000;
        data.id = QString("AIS_%1").arg(data.mmsi);
        data.lat =  20.123456 + qrand() % 1000 * 0.0001;
        data.lon =  110.12345678 + qrand() % 1000 * 0.0001;
        data.type = ZCHX::Data::ITF_AIS::Target_AIS;
        data.shipName = tr("test_%1").arg(i+1);
        std::vector<std::pair<double, double> > path;
        path.push_back(std::pair<double, double>(data.lat, data.lon));
        data.setPath(path);
        aisList.append(data);
        ZCHX::Data::tagITF_RadarPoint item;
        //构建雷达的尾迹
//        qDebug()<<"track point size:"<<data.tracks().tracks_size();
        double lat =  22.223456 + qrand() % 1000 * 0.0001;
        double lon =  113.08345678 + qrand() % 1000 * 0.0001;
        item.path.push_back(std::pair<double,double>(lat, lon));
        item.wgs84PosLat = lat;
        item.wgs84PosLon = lon;
        item.trackNumber = i*100+1000;
        item.cog = 110;
        item.sog = 1.2;
        item.status = 1;
        item.warnStatusColor = Qt::red;
//        if(item.status>=1)
        radarList.append(item);
    }

    m_pEcdisWin->itfSetRadarPointData(radarList);
    m_pEcdisWin->itfSetAisData(aisList);



}
