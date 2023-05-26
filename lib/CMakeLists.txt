add_subdirectory(database)

include_directories(database/include)
link_libraries(database_action)

add_subdirectory(GUI)

set(GUI_LIBRARIES ${GUI_LIBRARIES} PARENT_SCOPE)
set(DATABASE_LIBRARIES ${DATABASE_LIBRARIES} PARENT_SCOPE)