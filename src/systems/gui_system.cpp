#include "systems/gui_system.hpp"

#include <entt/entt.hpp>
#include <optional>

#include "components/body.hpp"
#include "components/name.hpp"
#include "components/pos.hpp"
#include "imgui.h"
#include "systems/camera_system.hpp"

auto settings_checkbox(const std::string &text) -> bool {
    static bool is_checked = false;

    if (ImGui::Checkbox(text.c_str(), &is_checked)) {
        return is_checked;
    }
    return is_checked;
}

auto settings_dropdown(const std::string &label, const std::vector<std::string> &items) -> size_t {
    static int selected_idx = 0;

    if (ImGui::BeginCombo(label.c_str(), items[selected_idx].c_str())) {
        for (int i = 0; i < items.size(); ++i) {
            const bool is_selected = (selected_idx == i);
            if (ImGui::Selectable(items[i].c_str(), is_selected)) {
                selected_idx = i;
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    return selected_idx;
}

void focus_body_settings(entt::registry &registry) {
    // XXX: limited to single camera
    auto cam_view = registry.view<Camera>();
    Camera &cam = registry.get<Camera>(cam_view.front());

    // XXX: this should be a component in the registry
    if (!settings_checkbox("Enable Single Body Focus")) {
        set_camera_follow_none(registry, cam);
        return;
    }

    std::vector<std::string> items = {};
    auto bodies_view = registry.view<Name, Body, Pos>();
    for (auto [entity, name, body, pos] : bodies_view.each()) {
        items.push_back(name.value);
    }
    // XXX: probably should make the currently selected body a component in the registry
    size_t selected_idx = settings_dropdown("Focused Body", items);

    std::string selected_name = items[selected_idx];
    for (auto [entity, name, body, pos] : bodies_view.each()) {
        // XXX: what happens if two bodies have the same name
        // prob like store a map of items index to entity id
        if (name.value == selected_name) {
            set_camera_follow_target(registry, cam, std::optional(entity));
        }
    }
}
