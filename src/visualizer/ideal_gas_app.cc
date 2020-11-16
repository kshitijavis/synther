#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"
#include "visualizer/ideal_gas_app.h"

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
  ci::audio::SourceFileRef source_file;
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_p:
       source_file = ci::audio::load(
          ci::app::loadAsset("Piano.pp.A6.aiff"));
       v1 = ci::audio::Voice::create(source_file);

       v1->start();
      break;
    case ci::app::KeyEvent::KEY_o:
      source_file = ci::audio::load(
          ci::app::loadAsset("Piano.pp.Ab6.aiff"));
      v2 = ci::audio::Voice::create(source_file);

      v2->start();
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
