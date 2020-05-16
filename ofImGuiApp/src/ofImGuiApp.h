// Copyright (c) 2019 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef OFIMGUIAPP_H
#define OFIMGUIAPP_H

#include "ofMain.h"

#include <cctype>
#include <type_traits>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

template<typename T>
class ofImGuiApp : public T
   {
   static_assert(std::is_base_of_v<ofBaseApp, T>, "Invalid template argument for ofImGuiApp<T>: T has to inherit from ofBaseApp.");

   public:
                             // Perfect forwarding constructor
      template<typename... Args>
      ofImGuiApp(Args&&... args) :
         T(std::forward<Args>(args)...)
         {
         ofAddListener(ofEvents().keyPressed, this, &ofImGuiApp::onKeyEvent);
         ofAddListener(ofEvents().keyReleased, this, &ofImGuiApp::onKeyEvent);
         }

      ~ofImGuiApp();

      void setup();
      void update();
      void draw();

      void mouseMoved(int x, int y);
      void mouseDragged(int x, int y, int button);
      void mousePressed(int x, int y, int button);
      void mouseReleased(int x, int y, int button);
      void mouseScrolled(int x, int y, float scrollX, float scrollY);
      void windowResized(int w, int h);

   private:
      void onKeyEvent(ofKeyEventArgs& event);
      void onMousePressed(int x, int y, int button, bool pressed);
   };

                             // Template implementation
template<typename T>
ofImGuiApp<T>::~ofImGuiApp()
   {
   ofRemoveListener(ofEvents().keyPressed, this, &ofImGuiApp::onKeyEvent);
   ofRemoveListener(ofEvents().keyReleased, this, &ofImGuiApp::onKeyEvent);

   ImGui_ImplOpenGL3_Shutdown();
   ImGui::DestroyContext();
   }

template<typename T>
void ofImGuiApp<T>::setup()
   {
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO();
   // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; // Not yet supported
   // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos; // Not yet supported
   io.BackendPlatformName = "imgui_impl_openframeworks";
   io.BackendRendererName = "imgui_impl_opengl3";

                             // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
   io.KeyMap[ImGuiKey_Tab] = OF_KEY_TAB;
   io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
   io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
   io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
   io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
   io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
   io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
   io.KeyMap[ImGuiKey_Home] = VK_HOME;
   io.KeyMap[ImGuiKey_End] = VK_END;
   io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
   io.KeyMap[ImGuiKey_Delete] = OF_KEY_DEL;
   io.KeyMap[ImGuiKey_Backspace] = OF_KEY_BACKSPACE;
   io.KeyMap[ImGuiKey_Space] = ' ';
   io.KeyMap[ImGuiKey_Enter] = OF_KEY_RETURN;
   io.KeyMap[ImGuiKey_Escape] = OF_KEY_ESC;
   //io.KeyMap[ImGuiKey_KeyPadEnter] = ???; // Not yet supported
   io.KeyMap[ImGuiKey_A] = 'a';
   io.KeyMap[ImGuiKey_C] = 'c';
   io.KeyMap[ImGuiKey_V] = 'v';
   io.KeyMap[ImGuiKey_X] = 'x';
   io.KeyMap[ImGuiKey_Y] = 'y';
   io.KeyMap[ImGuiKey_Z] = 'z';

   // io.ClipboardUserData = ???; // Not yet supported
   // io.GetClipboardTextFn = ???; // Not yet supported
   // io.SetClipboardTextFn = ???; // Not yet supported
   
   // io.ImeWindowHandle = ???; // Not yet supported

   const char* glsl_version = "#version 130";
   ImGui_ImplOpenGL3_Init(glsl_version);

   T::setup();
   }

template<typename T>
void ofImGuiApp<T>::update()
   {
   T::update();
   }

template<typename T>
void ofImGuiApp<T>::draw()
   {
   ImGui_ImplOpenGL3_NewFrame();

   ImGuiIO& io = ImGui::GetIO();
   // io.DeltaTime = ???; // Not yet supported
   io.DisplaySize = ImVec2(static_cast<float>(ofGetWidth()), static_cast<float>(ofGetHeight()));
   // io.DisplayFramebufferScale = ???; // Not yet supported
   
   ImGui::NewFrame();

   T::draw();

   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   ImGui::EndFrame();
   }

template<typename T>
void ofImGuiApp<T>::mouseMoved(int x, int y)
   {
   ImGuiIO& io = ImGui::GetIO();
   io.MousePos = ImVec2(static_cast<float>(x), static_cast<float>(y));

   T::mouseMoved(x, y);
   }

template<typename T>
void ofImGuiApp<T>::mouseDragged(int x, int y, int button)
   {
   ImGuiIO& io = ImGui::GetIO();
   io.MousePos = ImVec2(static_cast<float>(x), static_cast<float>(y));

   T::mouseDragged(x, y, button);
   }

template<typename T>
void ofImGuiApp<T>::mousePressed(int x, int y, int button)
   {
   onMousePressed(x, y, button, true /*pressed*/);

   T::mousePressed(x, y, button);
   }

template<typename T>
void ofImGuiApp<T>::mouseReleased(int x, int y, int button)
   {
   onMousePressed(x, y, button, false /*pressed*/);

   T::mouseReleased(x, y, button);
   }

template<typename T>
void ofImGuiApp<T>::mouseScrolled(int x, int y, float scrollX, float scrollY)
   {
   ImGuiIO& io = ImGui::GetIO();
   io.MousePos = ImVec2(static_cast<float>(x), static_cast<float>(y));

   io.MouseWheel = scrollY;
   io.MouseWheelH = scrollX;

   T::mouseScrolled(x, y, scrollX, scrollY);
   }

template<typename T>
void ofImGuiApp<T>::windowResized(int w, int h)
   {
   ImGuiIO& io = ImGui::GetIO();
   io.DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));

   T::windowResized(w, h);
   }

template<typename T>
void ofImGuiApp<T>::onKeyEvent(ofKeyEventArgs& event)
   {
   const bool pressed = (event.type == ofKeyEventArgs::Type::Pressed);
   int key = event.key;

                             // Unicode control codes (CTRL+A to CTRL+Z)
   if (event.hasModifier(OF_KEY_CONTROL) &&
       !event.isRepeat &&
       event.codepoint >= 1 && event.codepoint <= 26)
      {
      key = 'a' + (event.codepoint - 1);
      }

   ImGuiIO& io = ImGui::GetIO();

   if (pressed && key <= 255 && isprint(key))
      io.AddInputCharacter((ImWchar) key);

   if (key < IM_ARRAYSIZE(io.KeysDown))
      io.KeysDown[key] = pressed;

   switch (key)
      {
         case OF_KEY_SHIFT:
         case OF_KEY_LEFT_SHIFT:
         case OF_KEY_RIGHT_SHIFT:
            {
            io.KeyShift = pressed;
            break;
            }
         case OF_KEY_CONTROL:
         case OF_KEY_LEFT_CONTROL:
         case OF_KEY_RIGHT_CONTROL:
            {
            io.KeyCtrl = pressed;
            break;
            }
         case OF_KEY_ALT:
         case OF_KEY_LEFT_ALT:
         case OF_KEY_RIGHT_ALT:
            {
            io.KeyAlt = pressed;
            break;
            }
         case OF_KEY_SUPER:
         case OF_KEY_LEFT_SUPER:
         case OF_KEY_RIGHT_SUPER:
            {
            io.KeySuper = pressed;
            break;
            }
         case OF_KEY_LEFT:
            {
            io.KeysDown[VK_LEFT] = pressed;
            break;
            }
         case OF_KEY_RIGHT:
            {
            io.KeysDown[VK_RIGHT] = pressed;
            break;
            }
         case OF_KEY_UP:
            {
            io.KeysDown[VK_UP] = pressed;
            break;
            }
         case OF_KEY_DOWN:
            {
            io.KeysDown[VK_DOWN] = pressed;
            break;
            }
         case OF_KEY_PAGE_UP:
            {
            io.KeysDown[VK_PRIOR] = pressed;
            break;
            }
         case OF_KEY_PAGE_DOWN:
            {
            io.KeysDown[VK_NEXT] = pressed;
            break;
            }
         case OF_KEY_HOME:
            {
            io.KeysDown[VK_HOME] = pressed;
            break;
            }
         case OF_KEY_END:
            {
            io.KeysDown[VK_END] = pressed;
            break;
            }
         case OF_KEY_INSERT:
            {
            io.KeysDown[VK_INSERT] = pressed;
            break;
            }
         default:
            break;
      }
   }

template<typename T>
void ofImGuiApp<T>::onMousePressed(int x, int y, int button, bool pressed)
   {
   ImGuiIO& io = ImGui::GetIO();
   io.MousePos = ImVec2(static_cast<float>(x), static_cast<float>(y));

   constexpr int IMGUI_MOUSE_LEFT = 0;
   constexpr int IMGUI_MOUSE_RIGHT = 1;
   constexpr int IMGUI_MOUSE_MIDDLE = 2;

   switch (button)
      {
      case OF_MOUSE_BUTTON_LEFT:
         {
         io.MouseDown[IMGUI_MOUSE_LEFT] = pressed;
         break;
         }
      case OF_MOUSE_BUTTON_MIDDLE:
         {
         io.MouseDown[IMGUI_MOUSE_MIDDLE] = pressed;
         break;
         }
      case OF_MOUSE_BUTTON_RIGHT:
         {
         io.MouseDown[IMGUI_MOUSE_RIGHT] = pressed;
         break;
         }
      default:                
         break; // Not yet supported
      }
   }

#endif