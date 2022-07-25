// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#ifdef __cplusplus

#include <vector>

#ifndef GLFW_HPP
#define GLFW_HPP

#ifdef GLFW_INTERNALS
#define GLFW_INTERNAL public:
#define GLFW_INTERNALPROTECTED public:
#else
#define GLFW_INTERNAL private:
#define GLFW_INTERNALPROTECTED protected:
#endif

namespace glfw {

struct Workarea {
  int posx, posy, width, height;
};

class Monitor {
  GLFW_INTERNAL
  GLFWmonitor* const _monitor;
  Monitor(GLFWmonitor*);

public:
  inline operator GLFWmonitor*() { return _monitor; }

  inline const char* GetName() const { return glfwGetMonitorName(_monitor); }

  inline Workarea GetWorkarea() const {
    Workarea wa;
    glfwGetMonitorWorkarea(_monitor, &wa.posx, &wa.posy, &wa.width, &wa.height);
    return wa;
  }

  static const std::vector<Monitor*>& GetMonitors();
};

class Window {
  GLFW_INTERNAL
  GLFWwindow* const _window;

public:
  Window(int width, int height, const char* title = nullptr,
         const Monitor* monitor = nullptr);
  Window(Window&&) = delete;
  Window(const Window&) = delete;

  virtual ~Window() { glfwDestroyWindow(_window); }

  inline operator GLFWwindow*() { return _window; }

  inline void Show() { glfwShowWindow(_window); }
  inline void Hide() { glfwHideWindow(_window); }

  inline void SetShouldClose(bool value) {
    glfwSetWindowShouldClose(_window, value);
  }

  inline void SetSize(int width, int height) {
    glfwSetWindowSize(_window, width, height);
  }

  inline void SetSizeLimits(int minWidth, int minHeight, int maxWidth,
                            int maxHeight) {
    glfwSetWindowSizeLimits(_window, minWidth, minHeight, maxWidth, maxHeight);
  }

protected:
  inline virtual void OnClose() {}
  inline virtual void OnRefresh() {}
  inline virtual void OnSizeChanged(int width, int height) {}
  inline virtual void OnPosChanged(int xpos, int ypos) {}
  inline virtual void OnScaleChanged(float xscale, float yscale) {}
  inline virtual void OnIconify(bool iconified) {}
  inline virtual void OnMaximize(bool maximized) {}
  inline virtual void OnFocus(bool focused) {}

  GLFW_INTERNAL

  inline void _InvokeClose() { OnClose(); }
  inline void _InvokeRefresh() { OnRefresh(); }

  inline void _InvokeSizeChanged(int width, int height) {
    OnSizeChanged(width, height);
  };

  inline void _InvokePosChanged(int xpos, int ypos) {
    OnPosChanged(xpos, ypos);
  }

  inline void _InvokeScaleChanged(float xscale, float yscale) {
    OnScaleChanged(xscale, yscale);
  }

  inline void _InvokeIconify(bool iconified) { OnIconify(iconified); }
  inline void _InvokeMaximize(bool maximized) { OnMaximize(maximized); }
  inline void _InvokeFocus(bool focused) { OnFocus(focused); }
};

} // namespace glfw

#endif // GLFW_HPP

#endif