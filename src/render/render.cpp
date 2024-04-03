#include <iostream>
#include <array>
#include <cstdint>

#include "imgui.h"
#include "implot.h"

#include "render.hpp"

void render_window1()
{
    ImGui::SetNextWindowPos(ImVec2{0,0});
    ImGui::SetNextWindowSize(ImVec2{115,120});
    const auto window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("window###1", nullptr, window_flags))
    {
        if(ImGui::Button("testButton###1", ImVec2{ 100, 50 }))
        {
            ImGui::Text("Clicked");
        }

        ImGui::Button("testButton###2", ImVec2{ 100, 50 });
    }
    ImGui::End();
}

void render_window2()
{
    ImGui::SetNextWindowPos(ImVec2{0,125});
    ImGui::SetNextWindowSize(ImVec2{300,100});
    const auto window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("window###2", nullptr, window_flags))
    {
        if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable))
        {
            for (size_t row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Row %d", row);
                ImGui::TableNextColumn();
                ImGui::Text("Some Content");
                ImGui::TableNextColumn();
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1,0,0,1});
                ImGui::Text("1235.5141");
                ImGui::PopStyleColor();
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void render_window3()
{
    static auto checked = false;
    static auto slider_val = 1;

    ImGui::SetNextWindowPos(ImVec2{310,0});
    ImGui::SetNextWindowSize(ImVec2{300,200});
    const auto window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("window###3", nullptr, window_flags))
    {
        ImGui::Text("Text1");
        ImGui::SameLine();
        ImGui::Text("Text2");

        ImGui::Separator();

        ImGui::Checkbox("Auto-resize", &checked);
        ImGui::SliderInt("Slider", &slider_val, 1, 12);
    }
    ImGui::End();
}

void render_window4()
{
    constexpr auto size1 = 1001U;
    constexpr auto size2 = 11U;
    auto xs1 = std::array<float, size1>{};
    auto xs2 = std::array<float, size2>{};
    auto ys1 = std::array<float, size1>{};
    auto ys2 = std::array<float, size2>{};

    for (int i = 0; i < 1001; ++i) {
        xs1[i] = i * 0.001f;
        ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
    }

    for (int i = 0; i < 11; ++i) {
        xs2[i] = i * 0.1f;
        ys2[i] = xs2[i] * xs2[i];
    }

    ImGui::SetNextWindowPos(ImVec2{300,300}, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2{500,400}, ImGuiCond_FirstUseEver);
    const auto window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("window###4", nullptr, window_flags))
    {
        ImPlot::CreateContext();
        ImGui::BulletText("Anti-aliasing can be enabled from the plot's context menu (see Help).");
        if (ImPlot::BeginPlot("Line Plot")) {
            ImPlot::SetupAxes("x","f(x)");
            ImPlot::PlotLine("sin(x)", xs1.data(), ys1.data(), size1);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
            ImPlot::PlotLine("x^2", xs2.data(), ys2.data(), size2);
            ImPlot::EndPlot();
        }
    }
    ImGui::End();
}

void render()
{
    render_window1();
    render_window2();
    render_window3();
    render_window4();
}
