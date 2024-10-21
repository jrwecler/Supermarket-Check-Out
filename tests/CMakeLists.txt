# tests/CMakeLists.txt

# Download Catch2 v2.13.10 using FetchContent
include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.10
)

FetchContent_MakeAvailable(catch2)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# List of test source files
set(TEST_SOURCES
    ItemTests.cpp
    PurchasedItemTests.cpp
    DealType1Tests.cpp
    DealType2Tests.cpp
    CheckoutTests.cpp
)

# Create test executable
add_executable(RunTests ${TEST_SOURCES} ../src/Item.cpp ../src/PurchasedItem.cpp ../src/Deal.cpp ../src/Checkout.cpp)

# Link libraries
target_link_libraries(RunTests PRIVATE Catch2::Catch2 nlohmann_json::nlohmann_json)

# Enable testing
enable_testing()

# Register the test executable with CTest
add_test(NAME AllTests COMMAND RunTests)
