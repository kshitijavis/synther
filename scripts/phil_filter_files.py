import os
import re

required = ["normal"]

extension = "mp3"
rootDir = "./"
subDirs = [x[0] for x in os.walk(rootDir)]

for directory in subDirs:
    # Remove duplicate note sounds based on priority
    priorityDur = ["_15_", "_1_", "_05_", "_025_"]
    priorityDyn = ["_forte_", "_mezzo-forte_", "_mezzo-piano_", "_fortissimo_", "piano_", "_pianissimo_"]
    bestFiles = dict()
    notePattern = r"\w[bs]?\d"

    for filename in os.listdir(directory):
        filepath = directory + "/" + filename
        if not filename.endswith(extension):
            continue

        # Remove files that don't contain required strings
        if not all(x in filename for x in required):
            os.remove(filepath)
            continue
        
        durs = [s for s in priorityDur if s in filename]
        dyns = [s for s in priorityDyn if s in filename]
        # Remove files that don't specify duration or dynamic
        if (len(durs) == 0 or len(dyns) == 0):
            os.remove(filepath)
            continue

        dur = durs[0]
        dyn = dyns[0]

        lenRank = priorityDur.index(dur)
        dynRank = priorityDyn.index(dyn)
        fileData = [filename, lenRank, dynRank]

        match = re.search(notePattern, filename) 
        noteName = match.group()

        # Find files with best rank in priority and remove all other files
        if not noteName in bestFiles:
            bestFiles[noteName] = fileData
        else:
            best = bestFiles[noteName]
            bestFilename = best[0]
            bestLenRank = best[1]
            bestDynRank = best[2]

            if lenRank < bestLenRank:
                bestFiles[noteName] = fileData
                # Remove old file, which is not the best file anymore
                os.remove(directory + "/" + bestFilename)
            elif lenRank == bestLenRank and dynRank <= bestDynRank:
                bestFiles[noteName] = fileData
                # Remove old file, which is not the best file anymore
                os.remove(directory + "/" + bestFilename)
            else:
                os.remove(filepath)