import os
import re
import json

organization = "Philharmonia Orchestra"
performer = ""

rootDir = "./"
notePattern = r"\w[bs]?\d"
extension = "mp3"

subDirs = [x[0] for x in os.walk(rootDir)]

for directory in subDirs:
    if directory == "./":
        continue

    soundFiles = {}
    instrument = directory.split("/", 1)[1].title()
    # Map note names to sound files
    for filename in os.listdir(directory):
        if not filename.endswith(extension):
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
    savedFilename = "details.json"
    with open(directory + "/" + savedFilename, 'w') as outfile:
        json.dump(data, outfile, indent=2)
