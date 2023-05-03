# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

cmake_minimum_required(VERSION 3.10)

set(TEST_NAME generic)
set(GENKEY_BIN ${TEST_NAME}_genkey)
set(ENCR_BIN ${TEST_NAME}_encrypt)
set(DECR_BIN ${TEST_NAME}_decrypt)
set(EVAL_BIN ${TEST_NAME}_evaluate)
set(EVAL_BIN_MUL ${TEST_NAME}_evaluate_multiply)
set(EVAL_BIN_SUB ${TEST_NAME}_evaluate_sub)
set(SCR_ENC encrypt_gen.sh)
set(SCR_DEC decrypt_gen.sh)
set(SCR_GEN genkey_gen.sh)




set(GENKEY_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_genkey.cpp
  )

set(ENCR_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_encrypt.cpp
  )

set(DECR_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_decrypt.cpp
  )

set(EVAL_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/add.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_evaluate.cpp
  )

set(EVAL_SRCS_SUB
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/sub.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_evaluate_sub.cpp
  )

set(EVAL_SRCS_MUL
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.cpp
  ${CMAKE_CURRENT_LIST_DIR}/multiply.cpp
  ${CMAKE_CURRENT_LIST_DIR}/${TEST_NAME}_evaluate_multiply.cpp
  )

set(HEADER_DIR ${CMAKE_SOURCE_DIR}/${TEST_NAME})
set(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/seal_api.h
  ${CMAKE_CURRENT_LIST_DIR}/add.h
  )

add_executable(${GENKEY_BIN} ${GENKEY_SRCS} ${HEADER_FILES})
add_executable(${ENCR_BIN} ${ENCR_SRCS} ${HEADER_FILES})
add_executable(${DECR_BIN} ${DECR_SRCS} ${HEADER_FILES})
add_executable(${EVAL_BIN} ${EVAL_SRCS} ${HEADER_FILES})
add_executable(${EVAL_BIN_SUB} ${EVAL_SRCS_SUB} ${HEADER_FILES})
add_executable(${EVAL_BIN_MUL} ${EVAL_SRCS_MUL} ${HEADER_FILES})

#target_include_directories(${TEST_NAME} PRIVATE ${HEADER_DIR})

# Import Microsoft SEAL
find_package(SEAL 3.5 REQUIRED)

# Link Microsoft SEAL
target_link_libraries(${GENKEY_BIN} SEAL::seal)
target_link_libraries(${ENCR_BIN} SEAL::seal)
target_link_libraries(${DECR_BIN} SEAL::seal)
target_link_libraries(${EVAL_BIN} SEAL::seal)
target_link_libraries(${EVAL_BIN_SUB} SEAL::seal)
target_link_libraries(${EVAL_BIN_MUL} SEAL::seal)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(${GENKEY_BIN}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
  )
set_target_properties(${ENCR_BIN}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
  )
set_target_properties(${DECR_BIN}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
  )
set_target_properties(${EVAL_BIN}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
  )

set_target_properties(${EVAL_BIN_SUB}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
  )


set_target_properties(${EVAL_BIN_MUL}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}"
  )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_ENC}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_DEC}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${SCR_GEN}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME})

