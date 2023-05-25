include_directories(include)
qt6_wrap_cpp(loginWindow.moc include/loginWindow.h)
add_library(loginWindow ${loginWindow.moc} src/loginWindow.cpp)
qt6_wrap_cpp(userWindow.moc include/userWindow.h)
add_library(userWindow ${userWindow.moc} src/userWindow.cpp)


set(GUI_LIBRARIES loginWindow userWindow PARENT_SCOPE)