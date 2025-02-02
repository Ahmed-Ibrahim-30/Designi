//
// Created by ahmed Ibrahim on 30-Nov-24.
//

#ifndef DESIGNI_QMLRESULTVIEW_H
#define DESIGNI_QMLRESULTVIEW_H
#include <QObject>
#include <QVector>
#include <QRectF>
#include <QQmlContext>
#include <QObject>
#include <QQmlApplicationEngine>
#include "DesignResultView.h"
#include "QString"
#include "Model/RectQML.h"

class QMLResultView : public QObject , public DesignResultView
{

    Q_OBJECT
    Q_PROPERTY(QVector<QObject*> roomRects READ roomRects NOTIFY roomRectsChanged)

public:

    explicit QMLResultView( QQmlApplicationEngine *engine , QObject* parent = nullptr) : QObject(parent)
    {
        engine->rootContext()->setContextProperty("qmlDrawing", this);
        solutionIndex = 0;
        connect(this, &QMLResultView::roomRectsChanged, this, &QMLResultView::roomRects);
    }

    void displayDesigns(const vector<Design> &_designs) override {
        designs = _designs;
        //LOG(LogLevel::Info , "Design Changed IN QML");
        solutionIndex = 0;
        if(designs.empty())
        {
            //LOG(LogLevel::Warning , "designs is Empty !!");
            return;
        }

        currentDesign = designs[solutionIndex];
        rePositionBasedOnScreen(currentDesign);
    }

    Q_INVOKABLE void getNextSolution()
    {
        solutionIndex ++;
        if(solutionIndex >= designs.size())
        {
            solutionIndex = 0;
        }
        //LOG(LogLevel::Info , "Current Index = " + to_string(solutionIndex));
        currentDesign = designs[solutionIndex];
        rePositionBasedOnScreen(currentDesign);
        emit roomRectsChanged();
    }

    Q_INVOKABLE void getPrevSolution()
    {
        solutionIndex --;
        if(solutionIndex < 0)
        {
            solutionIndex = designs.size() - 1;
        }

        //LOG(LogLevel::Info , "Current Index = " + to_string(solutionIndex));
        currentDesign = designs[solutionIndex];
        rePositionBasedOnScreen(currentDesign);
        emit roomRectsChanged();
    }

    void rePositionBasedOnScreen( Design &design)
    {
        for(int unit = 100 ; unit >= 3 ; unit -=3)
        {
            Design copyDesign = design;
            copyDesign.scaleDesign((double)unit );
            Room mainDesign = copyDesign.getMainDesign();
            double width = mainDesign.getWidth();
            double height = mainDesign.getHeight();
            if(width + 4*unit> screenWidth || height + 4*unit> screenHeight)continue;

            design.scaleDesign((double)unit);
            double centerScreenX = screenWidth/2;
            double centerScreenY = screenHeight/2;
            design.moveDesign({centerScreenX - width/2 , centerScreenY - height/2 });
            break;
        }
        currentDesign = design ;
    }

    QVector<QObject*> roomRects()
    {
        QVector<QObject*> rects;
        for (const Room& room : currentDesign.getRooms()) {
            double x1 = room.getX1();
            double y1 = room.getY1();
            double x2 = room.getX2();
            double y2 = room.getY2();
            RectQML *rect = new RectQML();
            rect->setX(x1);
            rect->setY(y1);
            rect->setWidth(x2 - x1);
            rect->setHeight(y2 - y1);
            rect->setRoomId(QString::fromStdString(room.getRoomId()));

            rects.append(rect);
        }
        return rects;
    }

signals:
    void roomRectsChanged();

private:
    vector<Design> designs;

    Design currentDesign;

    const double screenWidth = 1539;
    const double screenHeight = 820;
    /**
     * Solution Index
     */
    int solutionIndex;
};


#endif //DESIGNI_QMLRESULTVIEW_H
