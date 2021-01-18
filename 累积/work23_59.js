const fs = require('fs')
const filename = 'data/accumulate.txt'
let archiveAccumulate = require('./archive')

// 处理失败事件，并清除状态，迎接第二天
function work23_59() {
    let date = new Date().toLocaleDateString();

    const readfile = fs.readFileSync(filename, {
        encoding: 'utf8',
        flag: 'r',
    });

    if (readfile.length == 0) {
        // do nothing
        return
    }
    var data = JSON.parse(readfile);
    if (data.finished["阿洁"] == 0 || data.finished["恒炜"] == 0) {
        data.failed++;
        if (data.failed == 4) {
            archiveAccumulate('data/accumulate(failed).txt', data.accumulate);
        }
    } else {
        data.finished = {
            "阿洁": 0,
            "恒炜": 0
        };
        data.failed = 0;
        data.lastUpdated = date;
    }


}

module.exports = work23_59;