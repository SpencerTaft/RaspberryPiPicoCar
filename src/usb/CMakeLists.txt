cmake_minimum_required(VERSION 3.23.1)

if (TARGET tinyusb_device)

    project("RCCarCode")

    include_directories(${PROJECT_SOURCE_DIR} inc)

    add_executable(${PROJECT_NAME} main.cpp wifiSingleton.cpp TimeAlgo.cpp Light.cpp FrLight.cpp RLight.cpp LRMotor.cpp DriveMotor.cpp)

    target_link_libraries(${PROJECT_NAME} pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(${PROJECT_NAME} 1)
    pico_enable_stdio_uart(${PROJECT_NAME} 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(${PROJECT_NAME})

    # add url via pico_set_program_url
    example_auto_set_url(${PROJECT_NAME})
elseif(PICO_ON_DEVICE)
    message(WARNING "not building main because TinyUSB submodule is not initialized in the SDK")
endif()
