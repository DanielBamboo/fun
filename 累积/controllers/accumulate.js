const fs = require('fs')
const readline = require('readline')
const filename = 'data/accumulate.txt'
const archiveFilename = 'data/accumulate(succeed).txt'
let archiveAccumulate = require('../archive')

var data = {};



module.exports = {
    'GET /accumulate': async (ctx, next) => {
        const readfile = fs.readFileSync(filename, {
            encoding: 'utf8',
            flag: 'r',
        });

        if (readfile.length == 0) {
            // initialize
            data = {}
            data['number'] = 1;
            data['finished'] = {
                "阿洁": 0,
                "恒炜": 0
            }
            data['failed'] = 0;
            data['accumulate'] = [];
            data['lastUpdated'] = null;
        } else {
            data = JSON.parse(readfile)
        }

        let done = false;
        if (data.finished[ctx.session.name] == 1) {
            done = true;
        }

        ctx.render('accumulate.html', {
            name: ctx.session.name,
            accumulate: data.accumulate,
            todayDone: done 
        });
        /*
        fs.access(filename, fs.constants.F_OK, (err) => {
            if (err) {
                fs.writeFile(filename, '', function (err) {

                });
            }
        });
        const fileSystem = fs.createReadStream(filename);
        const rl = readline.createInterface({
            input: fileSystem,
            crlfDelay: Infinity
        });
        // 注意：我们使用 crlfDelay 选项将 input.txt 中的所有 CR LF 实例（'\r\n'）识别为单个换行符。

        let accumulate = [];
        for await (const line of rl) {
            console.log(`this is a line: ${JSON.parse(line).date}`);
            accumulate.push(JSON.parse(line));
        }
        
        console.log('read done')

        ctx.render('accumulate.html', {
            name: ctx.session.name,
            accumulate: accumulate
        });
        */
    },

    'POST /accumulate': async (ctx, next) => {
        const readfile = fs.readFileSync(filename, {
            encoding: 'utf8',
            flag: 'r',
        });

        if (readfile.length == 0) {
            // initialize
            data = {}
            data['number'] = 1;
            data['finished'] = {
                "阿洁": 0,
                "恒炜": 0
            }
            data['failed'] = 0;
            data['accumulate'] = [];
            data['lastUpdated'] = null;
        } else {
            data = JSON.parse(readfile)
        }

        data.lastUpdated = new Date().toLocaleDateString()
        data.finished[ctx.session.name] = 1;
        data.accumulate.push({
            number: data.number,
            who: ctx.session.name,
            date: data.lastUpdated
        })

        if (data.finished["阿洁"] == 1 && data.finished["恒炜"] == 1) {
            data.number++;
            if (data.number == 31) {
                // call archived procedure
                archiveAccumulate('data/accumulate(succeed).txt', data.accumulate);
            }
        }

        

        try {
            fs.writeFileSync(filename, JSON.stringify(data), {
                encoding: 'utf8',
                mode: 0o666,
                flags: 'w',
            });
        } catch (error) {
            console.log('something wrong with writeStream')
            console.log('here is the error: ')
            console.log(error)
            ctx.response.status = 400;
            ctx.response.body = '服务端发生错误';
        }

        ctx.response.status = 200;
        /*
        console.log('post accumulate')
        console.log(ctx.request.body);
        ctx.response.body = 'pikacu';
        const fileStream = fs.createWriteStream(
            filename, {
                flags: 'a',
                encoding: null,
                mode: '0666'
            }
        );

        const data = {
            date: new Date().toLocaleDateString(),
            who: ctx.session.name
        }
        
        try {
            fileStream.write(JSON.stringify(data) + '\n', (error) => {
                if(error) {
                    throw error;
                }
                console.log(`write done: ${JSON.stringify(data)}`);
            })
        } catch (error) {
            console.log('something wrong with writeStream')
            console.log('here is the error: ')
            console.log(error)
            ctx.response.status = 400;
            ctx.response.body = '服务端发生错误';
        }
        
        ctx.response.status = 200;
        */
    }
}