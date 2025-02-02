//
// Created by ahmed Ibrahim on 25-Nov-24.
//

#ifndef DESIGNI_HOMEDESIGNCONTROLLER_H
#define DESIGNI_HOMEDESIGNCONTROLLER_H
/*
 * QML Includes
 */
#include <QQmlContext>
#include <QObject>
#include <QQmlApplicationEngine>
//////////////////////////////////////////
#include "Model/TemplateRepository.h"

#include "View/ConstInputView.h"
#include "View/JsonInputView.h"
#include "View/DesignResultView.h"
#include "View/ConsoleResultView.h"
#include "View/QMLResultView.h"
#include "Model/DesignGenerator.h"
#include "Model/DesignRepository.h"
#include "Model/DesignToDoublyLines.h"
#include "Model/Cluster.h"
#include "View/WallQml.h"


class HomeDesignController {
private:
    /**
     *  pointer to the qml engine
    */
    QQmlApplicationEngine *mEngine;

    /**
     * User Input View
     */
    UserInputView * userInputView;

    /**
     * pointer to out all designs
     */
    DesignResultView* designResultView;

    /**
     * Object from designGenerator
     */
    DesignGenerator designGenerator;

    /**
     * Input user Design
     */
    Design design;

    /**
     * all Output designs
     */
    vector<Design> designs;

    /**
     * 18 templates designs
     */
    DesignRepository templatesDesigns;

    /**
     * Store Model 2 Templates Designs Data
     * @return vector<Design> contains data for each template
     */
    vector<Design> storeTemplateDesigns();

    /**
     *
     * @return
     */
    DesignRepository extractRealTemplateDesign();

    void getUserInput();
public:
    explicit HomeDesignController(QQmlApplicationEngine *engine);

    /**
     * run Design Process
     */
    void designProcess();

    /**
     * take User Input
     */
    void initiateDesign();

    /**
     * showDesignResult
     */
    void showDesignResult();


};


#endif //DESIGNI_HOMEDESIGNCONTROLLER_H
