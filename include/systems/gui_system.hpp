#pragma once

#include "entt/entity/fwd.hpp"
#include <vector>
auto settings_checkbox(const std::string &text) -> bool;
auto settings_dropdown(const std::string &label, const std::vector<std::string> &items) -> size_t;
void body_info_widget(entt::registry &registry);
void focus_body_settings(entt::registry &registry);
