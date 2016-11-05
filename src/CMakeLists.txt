add_subdirectory(platform/windows)

add_library(cg SHARED cg.c)

if (WIN32)
    add_custom_command(TARGET cg PRE_BUILD
                       COMMAND del "cg_*.pdb"
                       WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

    string(RANDOM cg_PDB_NAME_DEBUG)
    string(CONCAT cg_PDB_NAME_DEBUG "cg_" ${cg_PDB_NAME_DEBUG})
    set_target_properties(cg PROPERTIES PDB_NAME_DEBUG ${cg_PDB_NAME_DEBUG})
endif (WIN32)
