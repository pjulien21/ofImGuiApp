# ofImGuiApp
Provides an easy way to integrate [Dear ImGui](https://github.com/ocornut/imgui) to your openFrameworks projects.

## How it works
Basically, the platform integration is done by `ofImGuiApp` class.

It uses the OpenGL3/ES/ES2 renderer binding provided in the example folder of Dear ImGui.

## Setup
Add to your project a folder named `imgui` which contains all Dear ImGui self-contained files:
- imgui/imconfig.h
- imgui/imgui.cpp
- imgui/imgui.h
- imgui/imgui_demo.cpp
- imgui/imgui_draw.cpp
- imgui/imgui_internal.h
- imgui/imgui_widgets.cpp
- imgui/imstb_rectpack.h
- imgui/imstb_textedit.h
- imgui/imstb_truetype.h

Add to this folder the OpenGL3/ES/ES2 renderer binding:
- imgui/imgui_impl_opengl3.cpp
- imgui/imgui_impl_opengl3.h

Add to your project the `ofImGuiApp` file:
- ofImGuiApp.h

## Using Dear ImGui in your project
All you have to do is to `#include "ofImGuiApp.h"` and use `ofRunApp(new ofImGuiApp<ofApp>());`:
```C++
#include "ofMain.h"
#include "ofApp.h"
#include "ofImGuiApp.h"

int main() {
   ofSetupOpenGL(1024, 768, OF_WINDOW);
   ofRunApp(new ofImGuiApp<ofApp>());
}
```

Your openFrameworks `ofApp` class can `#include "imgui/imgui.h"` and use ImGui (ex. `ImGui::ShowDemoWindow();`):
```C++
#include "ofApp.h"
#include "imgui/imgui.h"

void ofApp::setup() {
   ofSetWindowTitle("ofImGuiApp demo");
}

void ofApp::draw() {
   ofClear(ofColor::midnightBlue);
   ImGui::ShowDemoWindow();
}
```
