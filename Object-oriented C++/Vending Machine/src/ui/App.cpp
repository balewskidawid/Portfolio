#include "ui/App.hpp"

#include "vending/Utils.hpp"
#include "vending/Products.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

namespace ui {

using namespace ftxui;

static std::vector<vending::ProductInfo> ProductsSortedByName() {
  auto products = vending::default_products();
  std::ranges::sort(products, {}, &vending::ProductInfo::name);
  return products;
}

void RunApp(vending::VendingMachine machine) {
    auto screen = ScreenInteractive::Fullscreen();

  auto products = ProductsSortedByName();
  int selected = 0;

  std::string status = "Siema! Wybierz produkt i wrzuć monety.";
  std::vector<int> last_change;

  // coins buttons
  const std::vector<int> coin_values = {10, 20, 50, 100, 200, 500};
  std::vector<Component> coin_buttons;
  coin_buttons.reserve(coin_values.size());

for (int c : coin_values)
  {
      coin_buttons.push_back(Button(vending::format_grosz(c), [&, c] {
          try
          {
              machine.insert_coin(c);
              status = "Wrzucono: " + vending::format_grosz(c);
          }
          catch (const std::exception& e)
          {
              status = std::string("Błąd: ") + e.what();
          }
      }));
  }

  auto coin_row1  = Container::Horizontal({coin_buttons[0], coin_buttons[1], coin_buttons[2]});
  auto coin_row2  = Container::Horizontal({coin_buttons[3], coin_buttons[4], coin_buttons[5]});
  auto coin_panel = Container::Vertical({coin_row1, coin_row2});


  auto buy_button = Button("Kup", [&] {
    try {
      const auto id = products.at(static_cast<std::size_t>(selected)).id;
      auto result = machine.buy(id);
      last_change = std::move(result.change);
      status = "Wydano: " + result.product.name + " | Reszta: " + vending::format_coin_list(last_change);
    }
    // Auto Refund
    catch (const vending::CannotMakeChange& e)
    {
        auto refund = machine.cancel_and_refund();
        last_change.clear();
        status = std::string("Błąd: ") + e.what() + " | Zwrot: " + vending::format_coin_list(refund);
    } 
    catch (const std::exception& e) {
      status = std::string("Błąd: ") + e.what();
    }
  });

  auto cancel_button = Button("Anuluj", [&] {
    auto refund = machine.cancel_and_refund();
    status = "Zwrot: " + vending::format_coin_list(refund);
    last_change.clear();
  });

  auto exit_button = Button("Wyjdź", [&] { screen.Exit(); });

  auto actions = Container::Horizontal({buy_button, cancel_button, exit_button});

  // List of products
  std::vector<std::string> product_lines;
  product_lines.reserve(products.size());

  auto rebuild_product_lines = [&] {
    product_lines.clear();
    for (const auto& p : products) {
      int stock = 0;
      try {
        stock = machine.inventory().get(p.id).count;
      } catch (...) {
        stock = 0;
      }

      std::string line = p.name + " | " + vending::format_grosz(p.price_grosz) + " | szt: " + std::to_string(stock);
      product_lines.push_back(std::move(line));
    }
  };

  rebuild_product_lines();
  auto product_box = Radiobox(&product_lines, &selected);

  // main layout
  auto root = Container::Vertical({
      product_box,
      coin_panel,
      actions,
  });

  auto renderer = Renderer(root, [&] {
    rebuild_product_lines();

    const int inserted = machine.inserted_total();
    const auto inserted_str = vending::format_grosz(inserted);

auto left = vbox({
    text("Produkty") | bold,
    separator(),
    product_box->Render() | frame | flex,
}) | size(WIDTH, EQUAL, 60);

auto right = vbox({
    text("Monety") | bold,
    separator(),
    coin_panel->Render(),
    separator(),
    paragraph("Wrzucono: " + inserted_str) | bold,
    paragraph("Status: " + status),
    paragraph("Ostatnia reszta: " + vending::format_coin_list(last_change)),
    separator(),
    actions->Render(),
}) | flex;


    return vbox({
        text("Automat z napojami (FTXUI)") | bold | center,
        separator(),
        hbox({left, separator(), right}) | flex,
        separator(),
        text("Sterowanie: strzałki góra/dół, Enter, Tab") | dim,
    });
  });

  screen.Loop(renderer);
}

}