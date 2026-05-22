/* File needed to purchase logic, bridge to cashbox and inventory */
#pragma once

#include "vending/CashBox.hpp"
#include "vending/Inventory.hpp"
#include "vending/Products.hpp"

#include <vector>

namespace vending {

struct VendResult {
  ProductInfo product;
  std::vector<int> change;
};

class VendingMachine {
public:
  VendingMachine(Inventory inventory, CashBox cashbox);

  void insert_coin(int coin_value); 
  int inserted_total() const;

  VendResult buy(ProductId id);     
  std::vector<int> cancel_and_refund();

  const Inventory& inventory() const { return m_inventory; }
  const CashBox& cashbox() const { return m_cashbox; }

private:
  Inventory m_inventory;
  CashBox m_cashbox;
  std::vector<int> m_inserted; // coins inserted in actual transaction
};

}
