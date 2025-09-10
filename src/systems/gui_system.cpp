#include "systems/gui_system.hpp"

#include <entt/entt.hpp>
#include <optional>

#include "components/body.hpp"
#include "components/name.hpp"
#include "components/pos.hpp"
#include "imgui.h"
#include "systems/camera_system.hpp"

void camera_follow_dropdown(entt::registry &registry) {
    auto bodies_view = registry.view<Name, Body, Pos>();
    std::vector<std::string> items = {"None"};
    static int selected_idx = 0;
    for (auto [entity, name, body, pos] : bodies_view.each()) {
        items.push_back(name.value);
    }

    if (ImGui::BeginCombo("Camera Follow", items[selected_idx].c_str())) {
        for (int i = 0; i < items.size(); ++i) {
            const bool is_selected = (selected_idx == i);
            if (ImGui::Selectable(items[i].c_str(), is_selected)) {
                selected_idx = i;
            }
        }
        ImGui::EndCombo();
    }
    

    auto cam_view = registry.view<Camera>();
    Camera &cam = registry.get<Camera>(cam_view.front());

    // `None` is selected
    if (selected_idx == 0) {
        set_camera_follow_target(registry, cam, std::nullopt);
        return;
    }

    std::string selected_name = items[selected_idx];
    for (auto [entity, name, body, pos] : bodies_view.each()) {
        if (name.value == selected_name) {
            set_camera_follow_target(registry, cam, std::optional(entity));
        }
    }
}
