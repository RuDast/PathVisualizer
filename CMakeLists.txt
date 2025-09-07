cmake_minimum_required(VERSION 3.28)
project(PathVisualizer VERSION 0.2 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(PathVisualizer src/main.cpp src/core/game.cpp src/core/game.h src/config.h src/core/grid.cpp src/core/grid.h 
                src/graphics/render.h src/graphics/render.cpp src/utils/logger.h src/input/handler.h src/input/handler.cpp
                src/algorithms/dijkstra.h src/algorithms/dijkstra.cpp src/core/graph.h src/core/graph.cpp src/algorithms/astar.h src/algorithms/astar.cpp)
target_compile_features(PathVisualizer PRIVATE cxx_std_17)
target_link_libraries(PathVisualizer PRIVATE SFML::Graphics)

install(TARGETS PathVisualizer DESTINATION bin)

include(InstallRequiredSystemLibraries)
#include(BundleUtilities)

# После установки копируем все зависимости в bin
install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"\${CMAKE_INSTALL_PREFIX}/bin/PathVisualizer.exe\" \"\" \"\")
")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}") # указываем версию продукта
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_GENERATOR "NSIS") # указываем генераторы
set(CPACK_SOURCE_GENERATOR "NSIS")
include(CPack) # подключаем CPack
