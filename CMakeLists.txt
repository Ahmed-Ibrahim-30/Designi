cmake_minimum_required(VERSION 3.16)

project(Designi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_PREFIX_PATH "C:/Qt/6.6.1/msvc2019_64/lib/cmake")
find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)


qt_add_executable(${PROJECT_NAME}
    main.cpp
        Controller/HomeDesignController.cpp
        Controller/HomeDesignController.h
        Model/Room.cpp
        Model/Room.h
        Model/Design.cpp
        Model/Design.h
        Model/RoomBuilder.cpp
        Model/RoomBuilder.h
        Utils/UniqueIdGenerator.cpp
        Utils/UniqueIdGenerator.h
        View/UserInputView.cpp
        View/UserInputView.h
        View/DesignResultView.cpp
        View/DesignResultView.h
        Model/RoomDefaults.h
        Model/RoomTypes.h
        Utils/MathUtils.cpp
        Utils/MathUtils.h
        Utils/RoomTypeUtils.cpp
        Utils/RoomTypeUtils.h
        View/JsonInputView.cpp
        View/JsonInputView.h
        View/ConstInputView.cpp
        View/ConstInputView.h
        Utils/Logging.cpp
        Utils/Logging.h
        Utils/LogLevel.h
        View/ConsoleResultView.h
        View/ConsoleResultView.cpp
        View/QMLResultView.h
        View/QMLResultView.cpp
        Model/Point.h
        Model/Point.cpp
        Model/RectQML.h
        Model/TemplateRepository.cpp
        Model/TemplateRepository.h
        Model/DesignGenerator.cpp
        Model/DesignGenerator.h
        Model/DesignValidator.cpp
        Model/DesignValidator.h
        Model/RoomConnectionManager.cpp
        Model/RoomConnectionManager.h
        Model/RoomCoreAnalyzer.cpp
        Model/RoomCoreAnalyzer.h
        Model/CorridorConnectionManager.cpp
        Model/CorridorConnectionManager.h
        Model/AreaToDimensionsCalculator.cpp
        Model/AreaToDimensionsCalculator.h
        Model/CorridorDimensionsCalculator.h
        Model/HorizontalCorridorDimensionsCalculator.cpp
        Model/HorizontalCorridorDimensionsCalculator.h
        Model/DesignRepository.h
        Model/DesignRepository.cpp
        Model/DesignToDoublyLines.cpp
        Model/DesignToDoublyLines.h
        Model/Line.cpp
        Model/Line.h
        Model/DesignGeometryManager.cpp
        Model/DesignGeometryManager.h
        Model/Opening.h
        Model/Door.h
        Model/Window.h
        View/JsonExtraction.cpp
        View/JsonExtraction.h
        Model/DesignCompactnessSorter.cpp
        Model/DesignCompactnessSorter.h
        Model/DesignsSorting.h
        Model/DesignRefactor.h
        Model/DesignCompactnessRefactor.cpp
        Model/DesignCompactnessRefactor.h
        Model/TopAlignedRoomCorridorDimensionsCalculator.cpp
        Model/TopAlignedRoomCorridorDimensionsCalculator.h
        Model/Cluster.cpp
        Model/Cluster.h

        Model/DesignWallGenerator.h Model/DesignWallGenerator.cpp
        Model/Wall.h
        View/WallQml.h
        Model/Polygon.h
        Model/Polygon.cpp
        Model/Land/LandDivision.h
        Model/Land/LandDivisionBasedOnLandArea.cpp
        Model/Land/LandDivisionBasedOnLandArea.h
        Model/Land/LandDivisionBasedOnSidesConvergence.cpp
        Model/Land/LandDivisionBasedOnSidesConvergence.h
        Model/Land/LandNetwork.cpp
        Model/Land/LandNetwork.h
        Model/Land/LandNetworkByScaling.cpp
        Model/Land/LandNetworkByScaling.h
        Model/Land/LandNetworkBySpacing.cpp
        Model/Land/LandNetworkBySpacing.h
        Model/Land/Land.cpp
        Model/Land/Land.h
        Model/Land/LandDivision.cpp
        Model/Land/LandDivisionBasedOnInnerDesign.cpp
        Model/Land/LandDivisionBasedOnInnerDesign.h
        Model/DesignOutlines.cpp
        Model/DesignOutlines.h
        Model/PolygonLibrary/PolygonsSubtraction.cpp
        Model/PolygonLibrary/PolygonsSubtraction.h
        Model/PolygonLibrary/LineToPolygonConverter.cpp
        Model/PolygonLibrary/LineToPolygonConverter.h
        Model/PolygonLibrary/PolygonHelper.cpp
        Model/PolygonLibrary/PolygonHelper.h
        Model/PolygonLibrary/PolygonAdjacencyAnalyzer.cpp
        Model/PolygonLibrary/PolygonAdjacencyAnalyzer.h
        "Model/Land/Green Area/GreenAreaSelector.h"

        "Model/Land/Green Area/UniformGreenDistributor.cpp"
        "Model/Land/Green Area/UniformGreenDistributor.h"
        "Model/Land/Green Area/ClusteredGreenSelector.cpp"
        "Model/Land/Green Area/ClusteredGreenSelector.h"
)

qt_add_qml_module(${PROJECT_NAME}
    URI Designi
    VERSION 1.0
    QML_FILES main.qml  Design2D.qml   Design3D.qml   MyCube.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDesigni
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick)

#setup json library
target_include_directories(${PROJECT_NAME} PRIVATE "E:/Library/vcpkg/packages/nlohmann-json_x64-windows/include")

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
