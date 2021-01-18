function archiveAccumulate(archiveFilename, accumulate) {
    const readfile = fs.readFileSync(archiveFilename, {
        encoding: 'utf8',
        flag: 'r',
    });

    
    let archivedData = [];
    let periodCounter = 1;
    if (readfile.length != 0) { 
        archivedData = JSON.parse(readfile);
        periodCounter = archivedData[archivedData.length-1].periodCounter + 1;
    }
    archivedData.push({
        periodCounter: periodCounter,
        accumulate: accumulate
    });

    fs.writeFileSync(archiveFilename, JSON.stringify(archivedData), {
        encoding: 'utf8',
        mode: 0o666,
        flags: 'w',
    });

    fs.writeFileSync('data/accumulate.txt', '', {
        encoding: 'utf8',
        mode: 0o666,
        flags: 'w',
    });
}

module.exports = archiveAccumulate;