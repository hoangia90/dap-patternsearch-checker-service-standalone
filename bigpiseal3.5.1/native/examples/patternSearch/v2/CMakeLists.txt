# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

cmake_minimum_required(VERSION 3.10)

set(TEST_NAME patternSearch)

#set(GENKEY_BIN ${TEST_NAME}_genkey)
#set(ENCR_BIN ${TEST_NAME}_encrypt)
#set(DECR_BIN ${TEST_NAME}_decrypt)
#set(EVAL_BIN ${TEST_NAME}_evaluate)
#set(SCR_TEST test.sh)

set(GENKEY_BIN_2 ${TEST_NAME}_genkey_v2)
set(ENCR_BIN_2 ${TEST_NAME}_encrypt_v2)
set(DECR_BIN_2 ${TEST_NAME}_decrypt_v2)
set(DECR_RESULT_BIN_2 ${TEST_NAME}_decrypt_result_v2)
set(EVAL_BIN_2 ${TEST_NAME}_evaluate_v2)

set(SCR_ENC encrypt.sh)
set(SCR_DEC decrypt.sh)
set(SCR_DEC_RESULT decrypt_result.sh)
set(SCR_EVAL eval.sh)
set(SCR_GEN genkey.sh)
set(SCR_TEST_V2 test_v2.sh)


set(GENKEY_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_genkey.cpp
  )

set(ENCR_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_encrypt.cpp
  )

set(DECR_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/util.cpp
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_decrypt.cpp
  )

set(EVAL_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/util.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_evaluate.cpp
  )


set(GENKEY_SRCS_2
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_genkey_v2.cpp
  )

set(ENCR_SRCS_2
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_encrypt_v2.cpp
  )

set(DECR_SRCS_2
  ${CMAKE_CURRENT_LIST_DIR}/util.cpp
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_decrypt_v2.cpp
  )

set(DECR_RESULT_SRCS_2
  ${CMAKE_CURRENT_LIST_DIR}/util.cpp
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_decrypt_result_v2.cpp
  )

set(EVAL_SRCS_2
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/util.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_evaluate_v2.cpp
  )


set(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.h
  ${CMAKE_CURRENT_LIST_DIR}/util.h
  )

#add_executable(${GENKEY_BIN} ${GENKEY_SRCS} ${HEADER_FILES})
#add_executable(${ENCR_BIN} ${ENCR_SRCS} ${HEADER_FILES})
#add_executable(${DECR_BIN} ${DECR_SRCS} ${HEADER_FILES})
#add_executable(${EVAL_BIN} ${EVAL_SRCS} ${HEADER_FILES})
#target_include_directories(${TEST_NAME} PRIVATE ${HEADER_DIR})

add_executable(${GENKEY_BIN_2} ${GENKEY_SRCS_2} ${HEADER_FILES})
add_executable(${ENCR_BIN_2} ${ENCR_SRCS_2} ${HEADER_FILES})
add_executable(${DECR_BIN_2} ${DECR_SRCS_2} ${HEADER_FILES})
add_executable(${DECR_RESULT_BIN_2} ${DECR_RESULT_SRCS_2} ${HEADER_FILES})
add_executable(${EVAL_BIN_2} ${EVAL_SRCS_2} ${HEADER_FILES})
#target_include_directories(${TEST_NAME} PRIVATE ${HEADER_DIR})

# Import Microsoft SEAL
find_package(SEAL 3.5 REQUIRED)

# Link Microsoft SEAL
#target_link_libraries(${GENKEY_BIN} SEAL::seal)
#target_link_libraries(${ENCR_BIN} SEAL::seal)
#target_link_libraries(${DECR_BIN} SEAL::seal)
#target_link_libraries(${EVAL_BIN} SEAL::seal)

target_link_libraries(${GENKEY_BIN_2} SEAL::seal)
target_link_libraries(${ENCR_BIN_2} SEAL::seal)
target_link_libraries(${DECR_BIN_2} SEAL::seal)
target_link_libraries(${DECR_RESULT_BIN_2} SEAL::seal)
target_link_libraries(${EVAL_BIN_2} SEAL::seal)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#set_target_properties(${GENKEY_BIN}
#  PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
#  )
#set_target_properties(${ENCR_BIN}
#  PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
#  )
#set_target_properties(${DECR_BIN}
#  PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
#  )
#set_target_properties(${EVAL_BIN}
#  PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
#  )

set_target_properties(${GENKEY_BIN_2}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2"
  )
set_target_properties(${ENCR_BIN_2}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2"
  )
set_target_properties(${DECR_BIN_2}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2"
  )
set_target_properties(${DECR_RESULT_BIN_2}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2"
  )
set_target_properties(${EVAL_BIN_2}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2"
  )


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_TEST}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_ENC}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_DEC}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_DEC_RESULT}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_EVAL}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_GEN}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_TEST_V2}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}/v2)