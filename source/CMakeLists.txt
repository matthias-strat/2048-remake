# Source files
set(RM2_SRC_LIST
	Assets.cpp
	GameBase.cpp
	Game.cpp
	Grid.cpp
	NinePatch.cpp
	Tile.cpp
	TileManager.cpp
	Main.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${RM2_SRC_LIST})

# Link SFML
rm2_link_sfml(${PROJECT_NAME})
if(NOT RM2_SFML_SHARED_LIBS)
	add_definitions(-DSFML_STATIC)
	rm2_link_sfml_dependencies(${PROJECT_NAME})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")