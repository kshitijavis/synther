//
// Created by Kshitij Sinha on 11/18/20.
//

#include "visualizer/piano.h"

namespace synther {

namespace visualizer {

Piano::Piano(int first_semitone, size_t key_count)
    : first_semitone_(first_semitone), key_count_(key_count) {
}
}  // namespace visualizer

}  // namespace synther