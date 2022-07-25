// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#include "GLFW/glfw.hpp"

namespace glfw {

#pragma region Monitor

static bool g_monitorsInitialized = false;
static std::vector<Monitor*> g_monitors;

void onMonitorEvent(GLFWmonitor* handle, int event) {
  switch (event) {
    case GLFW_CONNECTED: {
      g_monitors.push_back(new Monitor(handle));
    } break;
    case GLFW_DISCONNECTED: {
      auto it = std::find_if(
          g_monitors.begin(), g_monitors.end(),
          [handle](auto monitor) { return monitor->_monitor == handle; });

      delete *it;
      g_monitors.erase(it);
    } break;
    default: {
      throw std::exception();
    }
  }
}

const std::vector<Monitor*>& Monitor::GetMonitors() {
  if (!g_monitorsInitialized) {
    int monCount = 0;
    auto monitorHandles = glfwGetMonitors(&monCount);

    for (auto i = 0; i < monCount; ++i) {
      g_monitors.push_back(new Monitor(monitorHandles[i]));
    }

    glfwSetMonitorCallback(onMonitorEvent);

    g_monitorsInitialized = true;
  }

  return g_monitors;
}

Monitor::Monitor(GLFWmonitor* monitor) : _monitor(monitor) {}

#pragma endregion

#pragma region Window

static Window* UserPointerToWindow(void* userPointer) {
  return reinterpret_cast<Window*>(userPointer);
}

static Window* GlfwWindowToWindow(GLFWwindow* window) {
  return UserPointerToWindow(glfwGetWindowUserPointer(window));
}

static void onClose(GLFWwindow* _window) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeClose();
}

static void onRefresh(GLFWwindow* _window) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeRefresh();
}

static void onSizeChanged(GLFWwindow* _window, int width, int height) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeSizeChanged(width, height);
}

static void onPosChanged(GLFWwindow* _window, int xpos, int ypos) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeSizeChanged(xpos, ypos);
}

static void onScaleChanged(GLFWwindow* _window, float xscale, float yscale) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeScaleChanged(xscale, yscale);
}

static void onIconify(GLFWwindow* _window, int iconified) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeIconify(iconified == GLFW_TRUE);
}

static void onMaximize(GLFWwindow* _window, int maximized) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeMaximize(maximized == GLFW_TRUE);
}

static void onFocus(GLFWwindow* _window, int focused) {
  auto window = GlfwWindowToWindow(_window);
  window->_InvokeFocus(focused == GLFW_TRUE);
}

Window::Window(int width, int height, const char* title, const Monitor* monitor)
    : _window(glfwCreateWindow(width, height, title,
                               monitor ? monitor->_monitor : nullptr,
                               nullptr)) {
  glfwSetWindowUserPointer(_window, this);
  glfwSetWindowCloseCallback(_window, onClose);
  glfwSetWindowRefreshCallback(_window, onRefresh);
  glfwSetWindowSizeCallback(_window, onSizeChanged);
  glfwSetWindowPosCallback(_window, onPosChanged);
  glfwSetWindowContentScaleCallback(_window, onScaleChanged);
  glfwSetWindowIconifyCallback(_window, onIconify);
  glfwSetWindowMaximizeCallback(_window, onMaximize);
  glfwSetWindowFocusCallback(_window, onFocus);
}

#pragma endregion

} // namespace glfw