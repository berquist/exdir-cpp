/*
 * exdir-cpp
 *
 * Copyright (C) 2020, Hunter Belanger (hunter.belanger@gmail.com)
 * All rights reserved.
 *
 * Released under the terms and conditions of the BSD 3-Clause license.
 * For more information, refer to the GitHub repo for this library at:
 * https://github.com/HunterBelanger/exdir-cpp
 *
 * */
#ifndef EXDIR_NPY_H
#define EXDIR_NPY_H

#include <cstdint>
#include <cstring>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace exdir {

// Enum of possible data types which are currently handeled by this Exdir
// implementation.
enum class DType {
  CHAR,
  UCHAR,
  INT16,
  INT32,
  INT64,
  UINT16,
  UINT32,
  UINT64,
  FLOAT32,
  DOUBLE64,
  COMPLEX64,
  COMPLEX128
};

// The path is only given for diagnostic purposes: only the file handle is
// used and it is expected to be open before the function call.
size_t read_npy_header(
  boost::filesystem::path fpath,
  std::ifstream &file,
  std::vector<size_t> &shape,
  DType &dtype,
  bool &c_contiguous,
  bool &data_is_little_endian);

// Function which opens file fname, and loads in the binary data into 1D
// array of chars, which must latter be type cast be the user. The char* to
// the data is returned as a reference, along with the number of elements,
// continuits, and element size in bytes. Returned is a vector for the shape.
void load_npy(boost::filesystem::path fpath, char*& data_ptr,
              std::vector<size_t>& shape, DType& dtype, bool& c_contiguous);

// Function which writes binary data to a Numpy .npy file.
void write_npy(boost::filesystem::path fpath, const char* data_ptr,
               std::vector<size_t> shape, DType dtype, bool c_contiguous);

// Returns the proper DType for a given Numpy dtype.descr string.
DType descr_to_DType(const std::string &dtype);

// Returns Numpy descr string for given DType
std::string DType_to_descr(DType dtype);

// Returns the number of bytes used to represent the provided DType.
size_t size_of_DType(DType dtype);

// Function to check whether or not host system is little-endian
bool system_is_little_endian();

// Function to switch byte order of data for an array which contains
// n_elements, each with element_size bytes. The size of data should
// therefore be n_elements*element_size; if not, this is undefined behavior.
void swap_bytes(char* data, uint64_t n_elements, size_t element_size);

// Swaps the first and second byte pointed to by char* bytes.
void swap_two_bytes(char* bytes);

// Swaps the first four bytes pointed to by char* bytes.
void swap_four_bytes(char* bytes);

// Swaps the first eight bytes pointed to by char* bytes.
void swap_eight_bytes(char* bytes);

// Swaps the first sixteen bytes pointed to by char* bytes.
void swap_sixteen_bytes(char* bytes);

} // namespace exdir
#endif  // EXDIR_NPY_H
