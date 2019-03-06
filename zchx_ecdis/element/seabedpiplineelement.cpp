#include "seabedpiplineelement.h"
#include "map_layer/zchxmaplayermgr.h"
#include "zchxmapframe.h"

namespace qt {
SeabedPipeLineElement::SeabedPipeLineElement(const ZCHX::Data::ITF_SeabedPipeLine &ele, zchxMapFrameWork* f)
    :MoveElement(f, ZCHX::Data::ELEMENT_SEABEDPIPLINE)
{
    setData(ele);
    setIsUpdate(true);
}

void SeabedPipeLineElement::setData(const ZCHX::Data::ITF_SeabedPipeLine &ele)
{
    m_path = ele.path;
    if(!ele.path.empty())
    {
        elelat = ele.path.front().first;
        elelon = ele.path.front().second;
    }
    m_data = ele;
    m_name = ele.name.toStdString();
    setIsUpdate(true);
}

std::vector<std::pair<double, double> > SeabedPipeLineElement::path() const
{
    return m_data.path;
}

void SeabedPipeLineElement::setPath(const std::vector<std::pair<double, double> > &path)
{
    m_data.path = path;
}

std::vector<std::pair<double, double> >& SeabedPipeLineElement::getPath()
{
    return m_data.path;
}

int SeabedPipeLineElement::id() const
{
    return uuid;
}

void SeabedPipeLineElement::setId(int id)
{
    uuid = id;
}

std::string SeabedPipeLineElement::name() const
{
    return m_name;
}

void SeabedPipeLineElement::setName(const std::string &name)
{
    m_name = name;
}

ZCHX::Data::ITF_SeabedPipeLine SeabedPipeLineElement::data() const
{
    return m_data;
}

//bool SeabedPipeLineElement::contains(int range, double x, double y) const
//{
//    if(!framework()) return false;
//    std::vector<std::pair<double,double>> tmp_path = path();
//    for(int i=0; i<tmp_path.size()-1;++i)
//    {
//        std::pair<double, double> p1 = tmp_path[i];
//        std::pair<double, double> p2 = tmp_path[i+1];
//        ZCHX::Data::Point2D start = framework()->LatLon2Pixel(p1.first, p1.second);
//        ZCHX::Data::Point2D end = framework()->LatLon2Pixel(p2.first, p2.second);

//        //检查3点是否共线
//        int p1x = start.x, p1y = start.y;
//        int p2x = end.x, p2y = end.y;
//        int check = (p1x - x) *(p2y - y) - (p2x - x) * (p1y - y);
//        //qDebug()<<"start:"<<p1x<<" "<<p1y<<" end:"<<p2x<<" "<<p2y<<" cur:"<<x<<" "<<y<<" area:"<<check;
//        if(abs(check) < range)
//        {
//            return true;
//        }
//    }

//    return false;
//}

void SeabedPipeLineElement::drawElement(QPainter *painter)
{
    if(!painter ||!MapLayerMgr::instance()->isLayerVisible(ZCHX::LAYER_SEABEDPIPELINE)) return;
    PainterPair chk(painter);
    std::vector<std::pair<double,double>> tmp_path = path();
    QPainterPath polygon;
    QString name = QString::fromStdString(this->name());

    painter->setPen(QPen(Qt::red,1,Qt::SolidLine));
    painter->setBrush(Qt::white);

    for(int i=0; i<tmp_path.size();++i)
    {
        std::pair<double, double> ll = tmp_path[i];
        QPointF pos = m_framework->LatLon2Pixel(ll.first, ll.second).toPointF();
        if(0 == i)
        {
            polygon.moveTo(pos);
        }
        else
        {
            polygon.lineTo(pos);
        }

        if(getIsActive())
        {
            painter->drawEllipse(pos,5,5);
        }
    }
    MapStyle colorType = m_framework->GetMapStyle();
    if(colorType == MapStyleEcdisNight || colorType == MapStyleEcdisDayDUSK)
    {
        painter->setPen(QPen(Qt::gray,2,Qt::DashLine));
    }
    else
    {
        painter->setPen(QPen(QColor(Qt::black), 4, Qt::DashLine));
    }

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(polygon);
    painter->drawText(polygon.boundingRect().center(),name);
}
}

