fs = require('fs');

function addControllers(router, dir) {
    // 读取controllers 文件夹下的这些文件并保存到files这个变量里
    var files = fs.readdirSync(__dirname + '/controllers');
    var js_files = files.filter((f) => {
        return f.endsWith('.js');
    })

    // 导入这些个file ( require(filepath) )
    for(var f of js_files) {
        console.log(`process controller: ${f}...`);

        // 获取到mapping ( index.js 或者 signin.js 的返回值，是键值对 )
        let mapping = require(__dirname + '/' + dir + '/' + f);

        //建立映射
        addMapping(router, mapping);
    }
}

function addMapping(router, mapping) {
    for(var url in mapping) {
        if(url.startsWith("GET")) {
            var path = url.substring(4);

            // mapping[url] 是一个 async 函数
            router.get(path, mapping[url]);
            console.log(`register URL mapping: GET ${path}`);
        } else if(url.startsWith('POST')) {
            var path = url.substring(5);
            router.post(path, mapping[url]);
            console.log(`register URL mappings: POST ${path}`);
        } else {
            console.log(`invalid URL: ${url}`);
        }
    }
}

module.exports = function(dir) {
    let
        controllers_dir = dir || 'controllers',
        router = require('koa-router')();
    addControllers(router, controllers_dir);
    return router.routes();
}