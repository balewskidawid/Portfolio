/* File needed to operate on inserted coins, cashbox, change  */
#pragma once

#include "vending/Exceptions.hpp"

#include <map>
#include <vector>
#include <functional>

namespace vending {

// to simplyfy value of coins in groszach: 1 zl - 100 gr
class CashBox {
public:
	CashBox() = default;

	void set_coin(int coin_value, int count);
    void add_coin(int coin_value, int count = 1);
    bool accepts(int coin_value) const;
	int total_amount() const;
    void deposit_coin(int coin_value); // inserted coins

	std::vector<int> make_change(int amount_grosz);
	const std::map<int, int, std::greater<int>>& coins() const { return m_coins; }

private:
	std::map<int, int, std::greater<int>> m_coins;  // decreasing order
};

CashBox make_default_cashbox();

}
