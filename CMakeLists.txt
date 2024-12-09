cmake_minimum_required(VERSION 3.29)
project(DatabaseManagementSystem)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


add_executable(DatabaseManagementSystem main.cpp
        TextInput/StateEnum.h
        TextInput/States.cpp
        TextInput/States.h
        TextInput/Font.cpp
        TextInput/Font.h
        TextInput/Cursor.cpp
        TextInput/Cursor.h
        TextInput/GUIComponent.cpp
        TextInput/GUIComponent.h
        TextInput/Label.cpp
        TextInput/Label.h
        TextInput/TextInput.cpp
        TextInput/TextInput.h
        TextInput/LabelPosition.h
        Model/Table.cpp
        Model/Table.h
        Model/InvalidColumnNameException.cpp
        Model/InvalidColumnNameException.h
        Model/Database.cpp
        Model/Database.h
        Parser/QueryParser.cpp
        Parser/QueryParser.h
        Parser/StateMachine.cpp
        Parser/StateMachine.h
        View/TextInputView.cpp
        View/TextInputView.h
        View/SpreadsheetView.cpp
        View/SpreadsheetView.h
        Controller/DatabaseController.cpp
        Controller/DatabaseController.h)

target_link_libraries(DatabaseManagementSystem sfml-system sfml-window sfml-graphics sfml-network sfml-audio)