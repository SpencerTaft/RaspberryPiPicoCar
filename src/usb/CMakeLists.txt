if (TARGET tinyusb_device)

    include_directories(${PROJECT_SOURCE_DIR})

    add_executable(main main.cpp wifiSingleton.cpp TimeAlgo.cpp Light.cpp FrLight.cpp RLight.cpp)

    target_link_libraries(main pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(main 1)
    pico_enable_stdio_uart(main 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(main)

    # add url via pico_set_program_url
    example_auto_set_url(main)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building main because TinyUSB submodule is not initialized in the SDK")
endif()
