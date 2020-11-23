#include "visualizer/synther_app.h"

#include "cinder/audio/audio.h"
#include "cinder/gl/gl.h"

namespace synther {

namespace visualizer {

SyntherApp::SyntherApp()
    : piano_(glm::dvec2(kSidePadding, kTopPadding),
             kWindowWidth - 2 * kSidePadding, kPianoHeight,
             kFirstSemitoneIndex, kKeyCount) {
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
  ci::audio::SourceFileRef source_file;
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_p:
      source_file = ci::audio::load(ci::app::loadAsset("Piano.pp.A6.aiff"));
      v1 = ci::audio::Voice::create(source_file);

      v1->start();
      break;
    case ci::app::KeyEvent::KEY_o:
      source_file = ci::audio::load(ci::app::loadAsset("Piano.pp.Ab6.aiff"));
      v2 = ci::audio::Voice::create(source_file);

      v2->start();
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      piano_.ShiftView(-10);
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      piano_.ShiftView(10);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      piano_.ShiftView(-1);
      break;
    case ci::app::KeyEvent::KEY_UP:
      piano_.ShiftView(1);
      break;
  }
}

}  // namespace visualizer

}  // namespace synther
