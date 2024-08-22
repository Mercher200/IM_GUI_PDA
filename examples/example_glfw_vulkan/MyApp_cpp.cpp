#include "MyApp_h.h"
#include "imgui.h"
#include "fstream"
#include "iostream"
#include "std_image.h"
#include "imgui_impl_vulkan.h"

namespace MyApp {

    void RenderUI( MyTextureData my_texture) {

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
     ImGui::Begin("MainDockSpace", nullptr, window_flags);

        static bool show_window1 = true;
        static bool show_inner_window1_1 = false;
        static bool show_inner_window1_2 = false;
        static bool show_inner_window1_3 = false;

        static bool show_window2 = false;
        static bool show_inner_window2_1 = false;
        static bool show_inner_window2_2 = false;
        static bool show_inner_window2_3 = false;

        static char text_buffer[1000] = { 0 };
        static char view_text[4056] = { 0 };
        static float characterCount[40] = { 0 };
        static int i = 0; 
        static int multiplication_index = 1;
        static float count = 1;

        float button_height = 80.0f;
        float button_spacing = ImGui::GetStyle().ItemSpacing.x;
        float y_offset = button_height;

        ImVec4 active_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
        ImVec4 default_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_Button, show_window1 ? active_color : default_color);
        if (ImGui::Button("button 1", ImVec2(237.5f, button_height))) {
             show_window1 = true;
             show_window2 = false;
            ImGui::SetKeyboardFocusHere();
        }
        ImGui::PopStyleColor();
            ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, show_window2 ? active_color : default_color);
        if (ImGui::Button("button 2", ImVec2(237.5f, button_height))) {
             show_window2 = true;
             show_window1 = false;
            ImGui::SetKeyboardFocusHere();
        }
        ImGui::PopStyleColor();
          ImVec2 window_size = ImVec2(viewport->WorkSize.x, viewport->WorkSize.y - y_offset - 15.0f);
          ImVec2 window_pos = ImVec2(viewport->WorkPos.x, viewport->WorkPos.y + y_offset + 15.0f);
        if (show_window1) {
            ImGuiWindowFlags window_1_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
              static bool show_inner_window1_1 = true;
              static bool show_inner_window1_2 = true;
              static bool show_inner_window1_3 = true;
                ImGui::SetNextWindowPos(window_pos);
                ImGui::SetNextWindowSize(window_size);
            ImGui::Begin("Window 1", nullptr, window_1_flags | ImGuiWindowFlags_NoBringToFrontOnFocus);
            {// Inner window 1.1-3
                // 1
                  ImVec2 inner_window1_pos = ImVec2(window_pos.x + 10.0f, window_pos.y + 10.0f);
                  ImVec2 inner_window1_size = ImVec2(window_size.x / 2.0f - 15.0f, window_size.y - 20.0f);
                    ImGui::SetNextWindowPos(inner_window1_pos);
                    ImGui::SetNextWindowSize(inner_window1_size);
               ImGui::Begin("Inner Window 1", &show_inner_window1_1, window_1_flags | ImGuiWindowFlags_AlwaysVerticalScrollbar);
                ImGui::TextWrapped("%s", view_text);
               ImGui::End();

                // 2
                  ImVec2 inner_window2_pos = ImVec2(window_pos.x + 252.5f, window_pos.y + 10.0f);
                  ImVec2 inner_window2_size = ImVec2(window_size.x - 260.5f, window_size.y - 537.5f);
                    ImGui::SetNextWindowPos(inner_window2_pos);
                    ImGui::SetNextWindowSize(inner_window2_size);
               ImGui::Begin("Inner Window 2", &show_inner_window1_2, window_1_flags);
                if (ImGui::InputTextMultiline("Inner window 2", text_buffer, IM_ARRAYSIZE(text_buffer), ImVec2(inner_window2_size.x - 15.0f, inner_window2_size.y - 17.0f), ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue)) {
                    strncat_s(view_text, text_buffer, IM_ARRAYSIZE(view_text) - strlen(view_text) - 1);
                    characterCount[i++] = strlen(view_text);
                    text_buffer[0] = '\0';
                }
               ImGui::End();

                // 3
                ImVec2 inner_window3_pos = ImVec2(window_pos.x + 252.5f, window_pos.y + 272.5f);
                ImVec2 inner_window3_size = ImVec2(window_size.x - 260.5f, window_size.y - 282.5f);
                  ImGui::SetNextWindowPos(inner_window3_pos);
                  ImGui::SetNextWindowSize(inner_window3_size);
                    ImGuiStyle& style = ImGui::GetStyle();
                    ImVec2 oldWindowPadding = style.WindowPadding;
                 style.WindowPadding = ImVec2(1, 1);
               ImGui::Begin("Inner Window 3", &show_inner_window1_3, window_1_flags | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar);
                ImGui::Image((ImTextureID)my_texture.DS, ImVec2(my_texture.Width, my_texture.Height));
               ImGui::End();
                 style.WindowPadding = oldWindowPadding;
            }

            { // Inner Botton 1.1-3
                // 1
                  ImVec2 button1_pos = ImVec2(window_size.x - 247.5f, window_size.y - 520.5f);
                  ImGui::SetCursorPos(button1_pos);
                if (ImGui::Button("send", ImVec2(window_size.x - 500.5f, window_size.y - 1197.5f))) {
                    strncat_s(view_text, text_buffer, IM_ARRAYSIZE(view_text) - strlen(view_text) - 1);
                    characterCount[i++] = strlen(view_text);
                    text_buffer[0] = '\0';
                }
                // 2
                  ImVec2 button2_pos = ImVec2(window_size.x - 247.5f, window_size.y - 490.5f);
                  ImGui::SetCursorPos(button2_pos);
                if (ImGui::Button("clear", ImVec2(window_size.x - 500.5f, window_size.y - 1167.5f))) {
                    view_text[0] = '\0';
                    text_buffer[0] = '\0';
                }
                // 3
                 ImVec2 button3_pos = ImVec2(window_size.x - 247.5f, window_size.y - 460.5f);
                 ImGui::SetCursorPos(button3_pos);
                 static char buffer_filename[128] = "C:\\test_ImGui_text.txt";
                 static bool input_window_open = false;
                  if (ImGui::Button("save", ImVec2(window_size.x - 500.5f, window_size.y - 1137.5f))) {           
                    input_window_open = true;     
                  }
                   ImVec2 filename_input_window = ImVec2(window_size.x - 95.0f, window_size.y - 300.0f);
                   ImGui::SetNextWindowPos(filename_input_window);
                   ImGui::SetNextWindowSize(ImVec2(window_size.x - 85.0f, window_size.y - 645.0f));
                    if(input_window_open){
                     ImGui::Begin("Input Window", &input_window_open, window_1_flags);
                        ImGui::InputTextMultiline(" ", buffer_filename, IM_ARRAYSIZE(buffer_filename), ImVec2(window_size.x - 100.0f, window_size.y - 685.0f), ImGuiInputTextFlags_AutoSelectAll);
                        if (ImGui::Button("Ok")) {
                            std::ofstream outfile(buffer_filename, std::ios::trunc);
                            if (outfile.is_open()) {
                                outfile.write(view_text, strlen(view_text));
                                outfile.close();
                                ImGui::Text("File saved successfully!");
                            }
                            else {
                                ImGui::Text("Failed to open file for writing.");
                            }
                            input_window_open = false;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Cancel")) {
                            input_window_open = false;
                        }
                     ImGui::End();
                    }
            }
            ImGui::End();
        }

        if (show_window2) {
                ImGuiWindowFlags window_2_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
             static bool show_inner_window2_1 = true;
             static bool show_inner_window2_2 = true;
             static bool show_inner_window2_3 = true;
            ImGui::SetNextWindowPos(window_pos);
            ImGui::SetNextWindowSize(window_size);
            ImGui::SetNextWindowBgAlpha(0.0f);
         ImGui::Begin("Window 2", nullptr, window_2_flags | ImGuiWindowFlags_NoBringToFrontOnFocus);
            float inner_window1_2_height = window_size.y / 3.0f - 10.0f;
            {// Inner window 2.1-3
                ImVec2 inner_window_size = ImVec2(window_size.x - 20.0f, inner_window1_2_height);
                ImVec2 inner_window3_size = ImVec2(window_size.x - 20.0f, window_size.y / 3.0f - 80.0f);
                // 1
                ImVec2 inner_window1_pos = ImVec2(window_pos.x + 10.0f, window_pos.y + 10.0f);
                ImGui::SetNextWindowPos(inner_window1_pos);
                ImGui::SetNextWindowSize(inner_window_size);
               ImGui::Begin("Inner Window 1", &show_inner_window2_1, window_2_flags);
                {// Geometric shapes
                    ImDrawList* draw_list = ImGui::GetWindowDrawList();
                    ImVec2 position = ImGui::GetCursorScreenPos();          
                    draw_list->AddRect(ImVec2(position.x + 110, position.y + 80), ImVec2(position.x + 200, position.y + 150), IM_COL32(255, 255, 255, 100), 0.0f, 0, 2.0f);
                    draw_list->AddCircle(ImVec2(position.x + 270, position.y + 80), 50.0f, IM_COL32(255, 255, 255, 100), 0, 2.0f);
                    draw_list->AddTriangle(ImVec2(position.x + 120, position.y + 70), ImVec2(position.x + 170, position.y + 10), ImVec2(position.x + 210, position.y + 60), IM_COL32(255, 255, 255, 100), 2.0f);
                }
               ImGui::End();
                // 2
                ImVec2 inner_window2_pos = ImVec2(window_pos.x + 10.0f, window_pos.y + 30.0f + inner_window1_2_height + 50.0f);
                ImGui::SetNextWindowPos(inner_window2_pos);
                ImGui::SetNextWindowSize(inner_window_size);
               ImGui::Begin("Inner Window 2", &show_inner_window2_2, window_2_flags);
                ImGui::PlotLines(" ", characterCount, IM_ARRAYSIZE(characterCount), 0, "(Number of letters)", 0.0f, 200.0f, ImVec2(465.0f, 209.0f));
               ImGui::End();
                // 3
                ImVec2 inner_window3_pos = ImVec2(window_pos.x + 10.0f, window_pos.y + 20.0f + 2 * (inner_window1_2_height + 34.0f));
                ImGui::SetNextWindowPos(inner_window3_pos);
                ImGui::SetNextWindowSize(inner_window3_size);
               ImGui::Begin("Inner Window 3", &show_inner_window2_3, window_2_flags);
                ImGui::Text("  HELP\n (Window#1)\nInner window #1 (left) - for text viewing only\nInternal window #2 (right+top) - only for text input\n(ENTER - sending text to Internal window #2)\n(CTRL+ENTER - moving to the next line)\nButton #1-3 = {=Enter, clear surfaces, save to file}\n (Window#2)\nInner window #1-3 = {picture, diagram, help text}\nButton 1-3 and menu - increase the content of the diagram 1-3 times");
               ImGui::End();
            }

            {// Inner button 2.1-4
               static int selected_button = 0;
               const char* button_labels[] = { "1 time", "2 time", "3 time" };
               const char* combo_items[] = { "1 time", "2 time", "3 time" };

               // 1-3
               ImVec2 inner_window_size = ImVec2(window_size.x - 460.0f, inner_window1_2_height + 35.0f);
               ImGui::SetCursorPos(inner_window_size);

               ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));
               for (int i = 0; i < 3; i+=1) {
                  ImGui::PushID(i);
                  
                 if (ImGui::RadioButton(button_labels[i], selected_button == i)) {
                      selected_button = i;
                      count = multiplication_index;
                      multiplication_index = i+1;
                          for (int i = 0; i < 40; i++) {
                              characterCount[i] = ((characterCount[i])/ count)*multiplication_index;
                          }
                 }
                 ImGui::PopID();
                 ImGui::SameLine();
               }
               ImGui::PopStyleVar();

               //4
               ImGui::PushItemWidth(150);
               if (ImGui::Combo(" ", &selected_button, combo_items, IM_ARRAYSIZE(combo_items))) {
                   count = multiplication_index;
                   multiplication_index = selected_button + 1;
                   for (int i = 0; i < 40; i++) {
                       characterCount[i] = ((characterCount[i]) / count) * multiplication_index;
                   }
               }
               ImGui::PopItemWidth();
            }
         ImGui::End();
        }
     ImGui::End();
    }
}
