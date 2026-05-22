#include "vending/Utils.hpp"

#include <sstream>
#include <iomanip>

namespace vending {

std::string format_grosz(int value_grosz) {
  const int zl = value_grosz / 100;
  const int gr = std::abs(value_grosz % 100);

  std::ostringstream oss;
  oss << zl << "." << std::setw(2) << std::setfill('0') << gr << " zł";
  return oss.str();
}

std::string format_coin_list(const std::vector<int>& coins_grosz) {
  if (coins_grosz.empty()) return "(brak)";

  std::ostringstream oss;
  for (std::size_t i = 0; i < coins_grosz.size(); ++i) {
    if (i) oss << " + ";
    oss << format_grosz(coins_grosz[i]);
  }
  return oss.str();
}

} 
