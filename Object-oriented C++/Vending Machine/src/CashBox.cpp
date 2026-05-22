#include "vending/CashBox.hpp"

#include <algorithm>
#include <stdexcept>

namespace vending {

void CashBox::set_coin(int coin_value, int count) {
    if (coin_value <= 0 || count < 0) {
        throw std::invalid_argument("Niewłaściwa moneta lub suma");
    }
    m_coins[coin_value] = count;
}

void CashBox::add_coin(int coin_value, int count) {
    if (coin_value <= 0 || count <= 0) {
        throw std::invalid_argument("Da sie tylko jedną monete na raz wrzucić!");
    }
    m_coins[coin_value] += count;
}

bool CashBox::accepts(int coin_value) const
{
    return m_coins.contains(coin_value);
}

int CashBox::total_amount() const {
    int sum = 0;
    for (const auto& [denom, cnt] : m_coins) {
        sum += denom * cnt;
    }
    return sum;
}

void CashBox::deposit_coin(int coin_value)
{
    if (!accepts(coin_value))
    {
        throw InvalidCoin("Niewłaściwa moneta");
    }
    m_coins[coin_value] += 1;
}

std::vector<int> CashBox::make_change(int change) {
    if (change < 0)
    {
        throw std::invalid_argument("Coś nie tak z ta reszta (zły arg fun)");
    }
    if (change == 0)
    {
        return {};
    }

    std::vector<int> out;
    int remaining = change;

  for (auto& [coin_value, cnt] : m_coins) {
    if (remaining <= 0) break;
    if (coin_value <= 0 || cnt <= 0) continue;

    const int need = remaining / coin_value;
    const int take = std::min(need, cnt);

    for (int i = 0; i < take; ++i) {
      out.push_back(coin_value);
    }

    remaining -= take * coin_value;
    cnt -= take;
  }

  if (remaining != 0) {
    for (int denom : out) {
        m_coins[denom] += 1;
    }
    throw CannotMakeChange("Niestety nie mam jak ci wydac :( muszę zwrocic ci pieniądze");
    }

  return out;
}

CashBox make_default_cashbox() {
  CashBox cb;
  cb.set_coin(500, 5);  // 5 zl , amount of coins 
  cb.set_coin(200, 10); // 2 zl
  cb.set_coin(100, 10); // 1 zl
  cb.set_coin(50,  20); // 50 gr
  cb.set_coin(20,  30); // 20 gr
  cb.set_coin(10,  30); // 10 gr
  return cb;
}

} 
