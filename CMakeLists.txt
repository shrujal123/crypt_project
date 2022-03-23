cmake_minimum_required(VERSION 3.10)

#set project name
project(Crypt LANGUAGES C CXX)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/source)
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

add_executable(exe ${SOURCE_FILES})

message()
message()

message("*** MPI ***")
if(NOT MPI_DISABLE)
	find_package(MPI)
if(MPI_C_FOUND OR MPI_CXX_FOUND)
	message()
	
	#compile with MPI if found
	if(MPI_C_FOUND)
		set(CMAKE_C_FLAGS "${}")
