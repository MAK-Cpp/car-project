include_directories(include)
set(GUI_LIBRARIES LoginWindow RegistrationWindow CarCardWindow UserAccount UserWindow RootWindow)


foreach (LIBRARY ${GUI_LIBRARIES})
    qt6_wrap_cpp(${LIBRARY}.moc include/${LIBRARY}.h)
    add_library(${LIBRARY} ${${LIBRARY}.moc} src/${LIBRARY}.cpp)
endforeach ()

target_link_libraries(UserWindow PRIVATE CarCardWindow UserAccount RootWindow)

set(GUI_LIBRARIES ${GUI_LIBRARIES} PARENT_SCOPE)