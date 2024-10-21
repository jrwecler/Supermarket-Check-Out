cmake_minimum_required(VERSION 3.10)
project(SupermarketCheckout)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Item.cpp
    src/PurchasedItem.cpp
    src/Deal.cpp
    src/Checkout.cpp
)

# Add executable
add_executable(SupermarketCheckout ${SOURCES})

# Include nlohmann JSON library
# Option 1: FetchContent (CMake 3.11+ required)
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(SupermarketCheckout PRIVATE nlohmann_json::nlohmann_json)

# Add tests subdirectory
enable_testing()
add_subdirectory(tests)

# Include CPack for packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_CONTACT "jwecler@gmail.com") # Replace with your contact info
set(CPACK_GENERATOR "ZIP;TGZ;DragNDrop;NSIS") # Specify the generators you need

# Define installation rules
install(TARGETS SupermarketCheckout DESTINATION bin)
install(DIRECTORY data/ DESTINATION data) # Install data at the root level alongside bin


# Configure CPack
include(CPack)