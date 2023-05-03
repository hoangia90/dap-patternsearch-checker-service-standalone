/*
  (C) Copyright 2022 CEA LIST. All Rights Reserved.
  */

#ifndef _CSV_API_H_
#define _CSV_API_H_

/* includes */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "print_api.h"

/* prototypes */
int load_csv_line(const std::string& filename, std::vector<int64_t>& in, bool print_info = 0);
int load_csv_line(const std::string& filename, std::vector<double>& in, bool print_info = 0);

int load_windows_csv_line(const std::string& filename, std::vector<int64_t>& in, bool print_info = 0);
int load_windows_csv_line(const std::string& filename, std::vector<double>& in, bool print_info = 0);

void string_to_number_vector(std::string& s, std::vector<int64_t>& in, bool print_info = 0);
void string_to_number_vector(std::string& s, std::vector<double>& in, bool print_info = 0);

int load_csv_file(const std::string& filename, std::vector<std::vector<int64_t>>& in, bool print_info = 0);
int load_csv_file(const std::string& filename, std::vector<std::vector<double>>& in, bool print_info = 0);

int read_csv_file(const std::string& filename, std::vector<std::string>& in, bool print_info = 0);

int write_to_csv_file(const std::string& filename, std::vector<int64_t> &in);
int write_to_csv_file(const std::string& filename, std::vector<double> &in);

int convert_crlf_to_lf(char *in, char *out);
int convert_lf_to_crlf(char *in, char *out);

#endif
