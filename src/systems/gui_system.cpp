#include "systems/gui_system.hpp"

#include <cstddef>
#include <entt/entt.hpp>
#include <optional>

#include "components/body.hpp"
#include "components/force.hpp"
#include "components/name.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"
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
        for (size_t i = 0; i < items.size(); ++i) {
            const bool is_selected = (selected_idx == i);
            if (ImGui::Selectable(items[i].c_str(), is_selected)) {
                selected_idx = static_cast<int>(i);
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    return selected_idx;
}

void body_info_widget(entt::registry &registry) {
    auto bodies_view = registry.view<Name, Body, Pos, Vel, Force>();
    if (ImGui::BeginTable("Body Information", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Position");
        ImGui::TableSetupColumn("Velocity");
        ImGui::TableSetupColumn("Force");
        ImGui::TableHeadersRow();
        for (auto [entity, name, body, pos, vel, force] : bodies_view.each()) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", name.value.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("(%f, %f)", pos.x, pos.y);
            ImGui::TableNextColumn();
            ImGui::Text("(%f, %f)", vel.dx, vel.dy);
            ImGui::TableNextColumn();
            ImGui::Text("(%f, %f)", force.x, force.y);
        }
        ImGui::EndTable();
    }
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
