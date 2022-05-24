if (TARGET tinyusb_device)
    set(SOURCE_EXE main.cpp wifiSingleton.cpp)

    add_executable(main ${SOURCE_EXE})

#    add_executable(main
#		main.cpp
#            )

    # Include hpp files
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    # pull in common dependencies
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
