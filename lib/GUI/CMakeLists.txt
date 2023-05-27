include_directories(include)
set(GUI_LIBRARIES LoginWindow RegistrationWindow CarCardWindow UserWindow)


foreach (LIBRARY ${GUI_LIBRARIES})
    qt6_wrap_cpp(${LIBRARY}.moc include/${LIBRARY}.h)
    add_library(${LIBRARY} ${${LIBRARY}.moc} src/${LIBRARY}.cpp)
    if ("${LIBRARY}" STREQUAL "UserWindow")
        target_link_libraries(${LIBRARY} PRIVATE CarCardWindow)
    endif ()
endforeach ()


set(GUI_LIBRARIES ${GUI_LIBRARIES} PARENT_SCOPE)