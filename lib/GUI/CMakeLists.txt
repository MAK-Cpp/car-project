include_directories(include)
qt6_wrap_cpp(loginWindow.moc include/loginWindow.h)
add_library(loginWindow ${loginWindow.moc} src/loginWindow.cpp)
qt6_wrap_cpp(registrationWindow.moc include/registrationWindow.h)
add_library(registrationWindow ${registrationWindow.moc} src/registrationWindow.cpp)
qt6_wrap_cpp(userWindow.moc include/userWindow.h)
add_library(userWindow ${userWindow.moc} src/userWindow.cpp)


set(GUI_LIBRARIES loginWindow userWindow registrationWindow PARENT_SCOPE)