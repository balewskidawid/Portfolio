/* File needed to convert simply format of ints into a string ( double )  */
#pragma once

#include <string>
#include <vector>

namespace vending {

std::string format_grosz(int value_grosz);          // " 500 -> 5.50 zł"
std::string format_coin_list(const std::vector<int>& coins_grosz);  // " 200 + 50 -> 2.00 zł + 0.50 zł"

}
