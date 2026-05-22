#include "vending/Inventory.hpp"

#include <utility>

namespace vending {

void Inventory::set_stock(const ProductInfo& p, int count)
{
    StockItem item;
    item.product = p;
    item.count   = count;
    m_items[p.id] = item; 
}

const StockItem& Inventory::get(ProductId id) const {
    auto it = m_items.find(id);
    if (it == m_items.end()) {
        throw UnknownProduct("Nieznany produkt");
    }
    return it->second;
}

bool Inventory::available(ProductId id) const {
    const auto& item = get(id);
    return item.count > 0;
}

void Inventory::take_one(ProductId id) {
    auto it = m_items.find(id);
    if (it == m_items.end()) {
        throw UnknownProduct("Nieznany produkt");
    }
    if (it->second.count <= 0) {
        throw OutOfStock("Brak na stanie");
    }
     --it->second.count;
}

Inventory make_default_inventory(int each_count) {
    Inventory inv;
    for (const auto& p : default_products()) { // Default vector declared in Products.hpp
        inv.set_stock(p, each_count);
    }
    return inv;
}

}  
