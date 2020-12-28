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
             kWindowWidth - 2 * kSidePadding, kPianoHeight),
      player_(kStandardResonation) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void SyntherApp::setup() {
  // Set up instrument, keyboard, and keybinds
  SetupInstrument(kDefaultSoundJson);

  // Setup sustain pedal
  glm::dvec2 sustain_top_left((kWindowWidth - kPedalWidth) / 2,
                              kWindowHeight - (kBottomPadding + kPedalHeight));
  ci::Color primary(kPedalPrimaryColor.c_str());
  ci::Color secondary(kPedalSecondaryColor.c_str());
  sustain_pedal_ = Pedal(sustain_top_left, kPedalWidth, kPedalHeight, primary,
                         secondary, kSustainPedalLabel, kMainFontName);
}

void SyntherApp::draw() {
  ci::Color8u background_color(ci::Color(kBackgroundColor.c_str()));
  ci::gl::clear(background_color);

  // Draw instrument text
  glm::dvec2 instrument_text_center(kWindowWidth / 2, kTopPadding);
  ci::gl::drawStringCentered(
      instrument_, instrument_text_center, kInstrumentTextColor,
      ci::Font(kInstrumentFontName, kInstrumentTextHeight));

  sustain_pedal_.Draw();
  piano_.Draw();
}

void SyntherApp::mouseDown(ci::app::MouseEvent event) {
  if (sustain_pedal_.IsInBounds(event.getPos())) {
    ToggleSustainPedal();
  }
}

void SyntherApp::keyDown(ci::app::KeyEvent event) {
  if (keybinder_.IsKeybind(event.getCode())) {
    const music::Note& note = keybinder_.PressKey(event.getCode());
    piano_.PressKey(note);
    player_.PlayNote(note);
  }

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      HandleShiftView(-1 * kOctaveDistance);
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      HandleShiftView(kOctaveDistance);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      HandleShiftView(-1 * kWholetoneDistance);
      break;
    case ci::app::KeyEvent::KEY_UP:
      HandleShiftView(kWholetoneDistance);
      break;
    case ci::app::KeyEvent::KEY_n: {
      std::string instrument_asset_path = RequestInstrumentDirectory();
      SetupInstrument(instrument_asset_path);
      break;
    }
    case ci::app::KeyEvent::KEY_SPACE:
      ToggleSustainPedal();
      break;
  }
}

void SyntherApp::keyUp(ci::app::KeyEvent event) {
  if (keybinder_.IsKeybind(event.getCode())) {
    const music::Note& note = keybinder_.PressKey(event.getCode());
    piano_.ReleaseKey(note);
    player_.StopNote(note);
  }
}

std::string SyntherApp::RequestInstrumentDirectory() {
  ci::fs::path assets_directory = ci::app::getAssetPath(".");
  ci::fs::path sounds_directory = ci::app::getAssetPath("sounds");
  ci::fs::path instrument_full_path = getFolderPath(sounds_directory);
  std::string instrument_asset_path =
      ci::fs::relative(instrument_full_path, assets_directory).string() + "/";
  return instrument_asset_path;
}

void SyntherApp::HandleShiftView(int displacement) {
  piano_.ShiftView(displacement);
  UpdateKeybindsAndLabels();
}

void SyntherApp::SetupInstrument(const std::string& asset_directory) {
  std::string json_path = asset_directory + kJsonFilename;

  // Load json and build parser
  std::fstream json(ci::app::getAssetPath(json_path).string());
  if (!json.is_open()) {
    return;
  }
  audio::SoundJsonParser parser(json);

  // Update state
  instrument_ = parser.GetInstrumentName();
  player_.SetUpVoices(parser.GetNoteFiles(), asset_directory);

  // Update keyboard to match size of new instrument
  const std::vector<music::Note>& notes = parser.GetNotes();
  auto first_note = std::min_element(notes.begin(), notes.end());
  int note_count = notes.size();
  piano_.SetKeys(first_note->GetSemitoneIndex(), note_count,
                 kViewWhitekeyCount);
  UpdateKeybindsAndLabels();
}

void SyntherApp::ToggleSustainPedal() {
  if (player_.GetResonateDuration() == kStandardResonation) {
    sustain_pedal_.Press();
    player_.SetResonateDuration(kSustainedResonation);
  } else {
    sustain_pedal_.Release();
    player_.SetResonateDuration(kStandardResonation);
  }
}

void SyntherApp::UpdateKeybindsAndLabels() {
  keybinder_.SetKeyBinds(piano_.GetPianoKeysInView());
  piano_.SetKeyLabels(keybinder_.GetNoteChars());
}

}  // namespace visualizer

}  // namespace synther
