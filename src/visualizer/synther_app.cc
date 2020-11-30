#include "visualizer/synther_app.h"

#include "cinder/audio/audio.h"
#include "cinder/gl/gl.h"

namespace synther {

namespace visualizer {

SyntherApp::SyntherApp()
    : piano_(glm::dvec2(kSidePadding, kTopPadding),
             kWindowWidth - 2 * kSidePadding, kPianoHeight,
             kFirstSemitoneIndex, kKeyCount, kViewWhitekeyCount) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void SyntherApp::setup() {
}

void SyntherApp::update() {
}

void SyntherApp::draw() {
  ci::Color8u background_color(ci::Color(kBackgroundColor.c_str()));
  ci::gl::clear(background_color);

  piano_.Draw();
}

void SyntherApp::mouseDown(ci::app::MouseEvent event) {
}

void SyntherApp::keyDown(ci::app::KeyEvent event) {
  if (piano_.IsKeybind(event.getCode())) {
    piano_.PressKey(event.getCode());
  }

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      piano_.ShiftView(-1 * kOctaveDistance);
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      piano_.ShiftView(kOctaveDistance);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      piano_.ShiftView(-1 * kWholetoneDistance);
      break;
    case ci::app::KeyEvent::KEY_UP:
      piano_.ShiftView(kWholetoneDistance);
      break;
  }
}

void SyntherApp::keyUp(ci::app::KeyEvent event) {
  if (piano_.IsKeybind(event.getCode())) {
    piano_.ReleaseKey(event.getCode());
  }
}

void SyntherApp::SetupInstrument(const std::string& json_path) {
  auto data = ci::app::loadAsset(json_path);
}

}  // namespace visualizer

}  // namespace synther
