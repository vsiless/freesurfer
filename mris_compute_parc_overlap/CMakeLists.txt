project(mris_compute_parc_overlap)
include_directories(${mris_compute_parc_overlap_SOURCE_DIR}
${INCLUDE_DIR_TOP} 
${VXL_INCLUDES} 
${MINC_INCLUDE_DIRS}) 

SET(mris_compute_parc_overlap_SRCS
mris_compute_parc_overlap.c
)


add_executable(mris_compute_parc_overlap ${mris_compute_parc_overlap_SRCS})
target_link_libraries(mris_compute_parc_overlap ${FS_LIBS})
install(TARGETS mris_compute_parc_overlap DESTINATION bin)	


