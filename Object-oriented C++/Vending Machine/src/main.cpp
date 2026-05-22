#include "ui/App.hpp"

#include "vending/Inventory.hpp"
#include "vending/CashBox.hpp"
#include "vending/VendingMachine.hpp"

int main() {
  auto inventory = vending::make_default_inventory(5);
  auto cashbox = vending::make_default_cashbox();
  vending::VendingMachine machine{inventory, cashbox};

  ui::RunApp(std::move(machine));
  return 0;
}
