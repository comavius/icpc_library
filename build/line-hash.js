const { execFileSync } = require('node:child_process');
const { createHash } = require('node:crypto');

// Based on NachiaVivias/yawn-at-the-top's cumulative two-digit MD5 hashes.
// Keep GCC's line markers so comments and blank lines cannot shift the hashes.
function lineHashes(text) {
    const preprocessed = execFileSync('g++', ['-dD', '-E', '-fpreprocessed', '-x', 'c++', '-'], {
        input: text,
        encoding: 'utf8',
    });
    const hashes = Array(text.split('\n').length).fill('');
    const hash = createHash('md5');
    let sourceLine = 1;
    for (const line of preprocessed.trimEnd().split('\n')) {
        const marker = line.match(/^# (\d+) "/);
        if (marker) {
            sourceLine = Number(marker[1]);
            continue;
        }
        // Match build/hash.sh's tr -d '[:space:]' in the C locale.
        const code = line.replace(/[ \t\n\v\f\r]/g, '');
        if (code) {
            hash.update(code);
            hashes[sourceLine - 1] = hash.copy().digest('hex').slice(0, 2);
        }
        sourceLine++;
    }
    return hashes;
}

module.exports = { lineHashes };
