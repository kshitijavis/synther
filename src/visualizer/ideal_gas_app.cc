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
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_p:
      ci::audio::SourceFileRef source_file = ci::audio::load(
          ci::app::loadAsset("epiano_mrk2_c1.wav"));
      output_voice = ci::audio::Voice::create(source_file);

      output_voice->setPan(10000);
      output_voice->start();
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
