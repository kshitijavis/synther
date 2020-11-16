#include <cinder/Rand.h>
#include <visualizer/ideal_gas_app.h>

#include <fstream>
#include <vector>

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void IdealGasApp::setup() {
  }

void IdealGasApp::update() {
}

void IdealGasApp::draw() {
  ci::Color8u background_color(ci::Color("darkgreen"));
  ci::gl::clear(background_color);
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {}
}

}  // namespace visualizer

}  // namespace idealgas
