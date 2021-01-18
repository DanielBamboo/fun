const Koa = require('koa');
const bodyParser = require('koa-bodyparser');
const app = new Koa();
const session = require('koa-session');


app.keys = ['some secret hurr'];

const CONFIG = {
    key: 'koa:sess',
    /** (string) cookie key (default is koa:sess) */
    /** (number || 'session') maxAge in ms (default is 1 days) */
    /** 'session' will result in a cookie that expires when session/browser is closed */
    /** Warning: If a session cookie is stolen, this cookie will never expire */
    maxAge: 86400000,
    overwrite: true,
    /** (boolean) can overwrite or not (default true) */
    httpOnly: true,
    /** (boolean) httpOnly or not (default true) */
    signed: true,
    /** (boolean) signed or not (default true) */
    rolling: false,
    /** (boolean) Force a session identifier cookie to be set on every response. The expiration is reset to the original maxAge, resetting the expiration countdown. default is false **/
};

app.use(session(CONFIG, app));
// or if you prefer all default config, just use => app.use(session(app));


const controller = require('./controllers');

app.use(bodyParser());


const templating = require('./templating');
const isProduction = process.env.NODE_ENV === 'production';

// log request URL:
app.use(async (ctx, next) => {
    console.log(`Process ${ctx.request.method} ${ctx.request.url}...`);
    var
        start = new Date().getTime(),
        execTime;
    await next();
    execTime = new Date().getTime() - start;
    ctx.response.set('X-Response-Time', `${execTime}ms`);
});

//static file support:
if (!isProduction) {
    let staticFiles = require('./static-files');
    app.use(staticFiles('/static/', __dirname + '/static'));
}

// add nunjucks as view:
app.use(templating('views', {
    noCache: !isProduction,
    watch: !isProduction
}));

app.use(controller());


app.listen(3000);
console.log('app started at port 3000');

//do some initialize work about three data files

const schedule = require('node-schedule');
let work23_59 = require('./work23_59');
const scheduleCronstyle = () => {
    //每分钟的第30秒定时执行一次:
    schedule.scheduleJob('00 27 18 * * *', () => {
        console.log('perform 23:59 work');
        work23_59();
    });
}

scheduleCronstyle();