#ifndef WALLQML_H
#define WALLQML_H
//
// Created by ahmed Ibrahim on 23-Dec-24.
//

#include <QObject>
#include <QVector>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "QString"
#include "Model/Wall.h"

class WallQML : public QObject {
    Q_OBJECT
    Q_PROPERTY(double x1 READ x1 WRITE setX1 NOTIFY x1Changed)
    Q_PROPERTY(double y1 READ y1 WRITE setY1 NOTIFY y1Changed)
    Q_PROPERTY(double z1 READ z1 WRITE setZ1 NOTIFY z1Changed)
    Q_PROPERTY(double x2 READ x2 WRITE setX2 NOTIFY x2Changed)
    Q_PROPERTY(double y2 READ y2 WRITE setY2 NOTIFY y2Changed)
    Q_PROPERTY(double z2 READ z2 WRITE setZ2 NOTIFY z2Changed)
    Q_PROPERTY(QString wallColor READ wallColor WRITE setColor NOTIFY colorChanged)

public:
    explicit WallQML(QObject *parent = nullptr) : QObject(parent), x1_(0), y1_(0), z1_(0), x2_(0), y2_(0), z2_(0) {
        color_ = "#563232";
    }

    double x1() const { return x1_; }
    void setX1(double value) { if (x1_ != value) { x1_ = value; emit x1Changed(); } }

    double y1() const { return y1_; }
    void setY1(double value) { if (y1_ != value) { y1_ = value; emit y1Changed(); } }

    double z1() const { return z1_; }
    void setZ1(double value) { if (z1_ != value) { z1_ = value; emit z1Changed(); } }

    double x2() const { return x2_; }
    void setX2(double value) { if (x2_ != value) { x2_ = value; emit x2Changed(); } }

    double y2() const { return y2_; }
    void setY2(double value) { if (y2_ != value) { y2_ = value; emit y2Changed(); } }

    double z2() const { return z2_; }
    void setZ2(double value) { if (z2_ != value) { z2_ = value; emit z2Changed(); } }

    QString wallColor() const { return color_; }
    void setColor(QString c) { if (color_ != c) { color_ = c; emit colorChanged(); } }

signals:
    void x1Changed();
    void y1Changed();
    void z1Changed();
    void x2Changed();
    void y2Changed();
    void z2Changed();
    void colorChanged();

private:
    double x1_, y1_, z1_, x2_, y2_, z2_ ;  QString color_;
};

class QMLWallView : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<QObject*> wallRects READ wallRects NOTIFY wallRectsChanged)

public:
    explicit QMLWallView(QQmlApplicationEngine *engine, QObject* parent = nullptr) : QObject(parent) {
        engine->rootContext()->setContextProperty("qmlWallDrawing", this);
        connect(this, &QMLWallView::wallRectsChanged, this, &QMLWallView::wallRects);
    }

    void setWalls(const std::vector<Wall>& _walls) {
        walls = _walls;
        wallsSize = walls.size();
        cout<< " setWalls = "<<"\n";
        // cout<< " wallsSize2 = "<<wallsSize<<"\n";
        emit wallRectsChanged();
    }

    QVector<QObject*> wallRects() {
        cout<< " wallRects = "<<"\n";
        QVector<QObject*> rects;
        for (const Wall& wall : walls) {
            WallQML *rect = new WallQML();
            rect->setX1(wall.x1);
            rect->setY1(wall.y1);
            rect->setZ1(wall.z1);
            rect->setX2(wall.x2);
            rect->setY2(wall.y2);
            rect->setZ2(wall.z2);
            rect->setColor(QString::fromStdString(wall.color));
            rects.append(rect);
        }
        newWalls = rects;
        return rects;
    }

    Q_INVOKABLE int wallCount(){
        cout<< " wallsSize = "<<wallsSize<<"\n";
        return wallsSize;
    }

    Q_INVOKABLE QVector<QObject*> curWalls(){
        return newWalls;
    }

signals:
    void wallRectsChanged();

private:
    std::vector<Wall> walls;
    QVector<QObject*> newWalls;
    int wallsSize = 0;
};

#endif // WALLQML_H
