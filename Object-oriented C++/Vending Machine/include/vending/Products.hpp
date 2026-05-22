/* File needed to create default stock of inventory */
#pragma once

#include <string>
#include <vector>

namespace vending {

enum class ProductId
{
    CocaCola,
    Pepsi,
    Sprite,
    Nestea,
    RedBull,
    Fanta,
    WodaNGaz,
    WodaGaz,
    Oshee,
    SokPomidorowy,
    CappyJab,
    CappyPom,
    CappyPorzecz,
    KawaMrozona,
    Aloes,
};

struct ProductInfo {
    ProductId id{};
    std::string name;
    int price_grosz = 0;
};

inline std::vector<ProductInfo> default_products() {
  return {
      {ProductId::CocaCola, "Coca Cola", 550},
      {ProductId::Pepsi, "Pepsi", 520},
      {ProductId::Sprite, "Sprite", 500},
      {ProductId::Nestea, "Nestea", 450},
      {ProductId::RedBull, "Red Bull", 700},
      {ProductId::Fanta, "Fanta", 480},
      {ProductId::WodaNGaz, "Woda niegazowana", 250},
      {ProductId::WodaGaz, "Woda gazowana", 250},
      {ProductId::Oshee, "Oshee", 480},
      {ProductId::SokPomidorowy, "Sok pomidorowy", 450},
      {ProductId::CappyJab, "Cappy jablkowe", 520},
      {ProductId::CappyPom, "Cappy pomaranczowe", 520},
      {ProductId::CappyPorzecz, "Cappy porzeczkowe", 520},
      {ProductId::Aloes, "Aloes", 720},
  };
}

}