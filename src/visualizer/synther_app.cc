#include "visualizer/synther_app.h"

#include <string>

#include "cinder/gl/gl.h"
#include "core/music_note.h"
#include "core/sound_json_parser.h"

namespace synther {

namespace visualizer {

SyntherApp::SyntherApp()
    : piano_(glm::dvec2(kSidePadding, kTopPadding + kInstrumentTextHeight +
                                          kInstrumentTextPadding),
             kWindowWidth - 2 * kSidePadding, kPianoHeight, kFirstSemitoneIndex,
             kKeyCount, kViewWhitekeyCount) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void SyntherApp::setup() {
  SetupInstrument(kDefaultSoundPath);
}

void SyntherApp::update() {
}

void SyntherApp::draw() {
  ci::Color8u background_color(ci::Color(kBackgroundColor.c_str()));
  ci::gl::clear(background_color);

  // Draw instrument text
  glm::dvec2 instrument_text_center(kWindowWidth / 2, kTopPadding);
  ci::gl::drawStringCentered(instrument_, instrument_text_center, kInstrumentTextColor.c_str(),
                             ci::Font(kFontName, kInstrumentTextHeight));

  piano_.Draw();
}

void SyntherApp::mouseDown(ci::app::MouseEvent event) {
}

void SyntherApp::keyDown(ci::app::KeyEvent event) {
  if (piano_.IsKeybind(event.getCode())) {
    piano_.PressKey(event.getCode());
    const music::Note& note = piano_.GetNote(event.getCode());
    player_.PlayNote(note);
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
    const music::Note& note = piano_.GetNote(event.getCode());
    player_.StopNote(note);
  }
}

void SyntherApp::SetupInstrument(const std::string& asset_directory) {
  std::string json_path = asset_directory + kJsonFilename;

  // Load json and build parser
  std::fstream json(ci::app::getAssetPath(json_path).string());
  if (!json.is_open()) {
    return;
  }
  audio::SoundJsonParser parser(json);

  instrument_ = parser.GetInstrumentName();
  std::map<music::Note, std::string> note_files = parser.GetNoteFiles();

  player_.SetUpVoices(parser.GetNoteFiles(), asset_directory);
}

}  // namespace visualizer

}  // namespace synther
