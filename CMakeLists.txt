# -- Project Setup ------------------------------------------------------------

project(cuckoosnestbtc)

set(cuckoosnestbtc_sources
  rapidjson/document.h
  rapidjson/writer.h
  rapidjson/stringbuffer.h
  rapidjson/allocators.h
  rapidjson/filereadstream.h
  cuckoo/cuckoofilter.h
  cuckoo/singletable.h
  cuckoo/simd-block.h
  cuckoo/packedtable.h
  cuckoo/permencoding.h
  cuckoo/printutil.cc
  cuckoo/printutil.h
  cuckoo/siphash.h
  cuckoo/sha256.c
  cuckoo/sha256.h
  helpers/primitives.h
  cpp-datetimelite/datetimelite.h
  cuckoosnestbtc.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(cuckoosnestbtc ${cuckoosnestbtc_sources})
