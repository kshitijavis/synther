import os
import re
import json

instrument = "Acoustic Piano"
organization = "University of Iowa Electronic Music Studios"
performer = "Evan Mazunik"

directory = "./sounds/piano/"
notePattern = r"\w[bs]?\d"
soundFiles = {}

# Map note names to sound files
for filename in os.listdir(directory):
    if not filename.endswith(".mp3"):
        continue
    match = re.search(notePattern, filename)
    notename = match.group()
    soundFiles[notename] = filename

# Create JSON
data = {
    "instrument": instrument,
    "organization": organization,
    "performer": performer,
    "soundFiles": soundFiles
}
savedFilename = directory + "details.json"
with open(savedFilename, 'w') as outfile:
    json.dump(data, outfile, indent=2)

