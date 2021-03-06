#include <visualizer/synther_app.h>

using synther::visualizer::SyntherApp;

void prepareSettings(SyntherApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(SyntherApp, ci::app::RendererGl, prepareSettings);
