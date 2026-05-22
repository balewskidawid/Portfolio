/* File needed for better structure of the errors, catching errors by the type od error not a worlds */
#pragma once

#include <stdexcept>

namespace vending {

struct VendingError : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct InvalidCoin : VendingError {
  using VendingError::VendingError;
};

struct UnknownProduct : VendingError {
  using VendingError::VendingError;
};

struct OutOfStock : VendingError {
  using VendingError::VendingError;
};

struct InsufficientFunds : VendingError {
  using VendingError::VendingError;
};

struct CannotMakeChange : VendingError {
  using VendingError::VendingError;
};

}
