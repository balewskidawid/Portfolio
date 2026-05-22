/* File needed to operate on stock of the inventory */
#pragma once

#include "vending/Exceptions.hpp"
#include "vending/Products.hpp"

#include <unordered_map>

namespace vending {

struct StockItem {
    ProductInfo product; // Class declared in Products.hpp
    int count = 0;
};

struct ProductIdHash { // Some type of convertion key -> number needed cuz of use enum
    std::size_t operator()(ProductId id) const noexcept {
    return static_cast<std::size_t>(id);
  }
};

class Inventory {
public:
    Inventory() = default;

    void set_stock(const ProductInfo& p, int count);
    const StockItem& get(ProductId id) const;  
    bool available(ProductId id) const;        
    void take_one(ProductId id);              

    const std::unordered_map<ProductId, StockItem, ProductIdHash>& items() const { return m_items; }

private:
    std::unordered_map<ProductId, StockItem, ProductIdHash> m_items;
};

Inventory make_default_inventory(int each_count);

}