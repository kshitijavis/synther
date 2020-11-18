#include <visualizer/synther-app.h>

using idealgas::visualizer::SynterApp;

void prepareSettings(SynterApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(SynterApp, ci::app::RendererGl, prepareSettings);
