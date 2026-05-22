#include "vending/VendingMachine.hpp"

#include <numeric>
#include <ranges>

namespace vending {

VendingMachine::VendingMachine(Inventory inventory, CashBox cashbox)
    : m_inventory(std::move(inventory)), m_cashbox(std::move(cashbox)) {}

void VendingMachine::insert_coin(int coin_value) {
    if (!m_cashbox.accepts(coin_value))
    {
        throw InvalidCoin("Coin not accepted by machine");
  }
    m_inserted.push_back(coin_value);
}

int VendingMachine::inserted_total() const {
  return std::accumulate(m_inserted.begin(), m_inserted.end(), 0);
}

VendResult VendingMachine::buy(ProductId id) {
  const auto& item = m_inventory.get(id);
  if (item.count <= 0) {
    throw OutOfStock("Selected product is out of stock");
  }

  const int total = inserted_total();
  const int price = item.product.price_grosz;
  if (total < price) {
    throw InsufficientFunds("Not enough money inserted");
  }

  const int change_amount = total - price;

  CashBox trial = m_cashbox; // using copy in case machine is not able to give change
  for (int c : m_inserted) {
    trial.deposit_coin(c);
  }

  std::vector<int> change = trial.make_change(change_amount); 

  
  m_inventory.take_one(id);
  m_cashbox = std::move(trial);
  m_inserted.clear();

  return VendResult{item.product, change};
}

std::vector<int> VendingMachine::cancel_and_refund() {
  std::vector<int> refund = std::move(m_inserted);
  m_inserted.clear();
  return refund;
}

}
