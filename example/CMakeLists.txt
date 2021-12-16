set(EXAMPLES
    main
)

foreach(EXAMPLE ${EXAMPLES})
    set(TGT "${EXAMPLE}")
    list(APPEND EXAMPLE_TGTS ${TGT})
    add_executable(${TGT} ${EXAMPLE}.cpp)
    target_link_libraries(${TGT} exdir-cpp)
endforeach()
add_custom_target(exdir-cpp-examples DEPENDS ${EXAMPLE_TGTS})
