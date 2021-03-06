IF(BUILD_DOCBOOK)
  FIND_PROGRAM(XMLTO xmlto)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/index.xml.cmake ${CMAKE_CURRENT_BINARY_DIR}/index.xml)
 GET_TARGET_PROPERTY(FASTDIST_EXE fastdist LOCATION)


 FILE(GLOB commands RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/commands ${CMAKE_CURRENT_SOURCE_DIR}/commands/[^.]*[^~])


FOREACH(i ${commands})
  ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xincluded_files/${i}
   COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/helper.sh ${CMAKE_BINARY_DIR}/src/c++ ${CMAKE_CURRENT_SOURCE_DIR}/commands/${i} > ${CMAKE_CURRENT_BINARY_DIR}/xincluded_files/${i}
   DEPENDS fastdist fnj fastprot fastprot_mpi
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example_files
  )
  LIST( APPEND depfiles ${CMAKE_CURRENT_BINARY_DIR}/xincluded_files/${i} )
ENDFOREACH(i)



MAKE_DIRECTORY( ${CMAKE_CURRENT_BINARY_DIR}/xincluded_files )
ADD_CUSTOM_TARGET(docbook-doc ALL ${XMLTO} --skip-validation -m ${CMAKE_CURRENT_SOURCE_DIR}/params.xsl xhtml-nochunks -o ${CMAKE_CURRENT_BINARY_DIR}  ${CMAKE_CURRENT_BINARY_DIR}/index.xml 
    DEPENDS ${depfiles} )
  INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/style DESTINATION share/doc/fastphylo PATTERN ".svn" EXCLUDE )
  INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example_files DESTINATION share/doc/fastphylo PATTERN ".svn" EXCLUDE )
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/index.html DESTINATION share/doc/fastphylo )
ENDIF(BUILD_DOCBOOK)
