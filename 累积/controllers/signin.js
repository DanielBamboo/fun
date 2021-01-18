// sign in:

module.exports = {
    'POST /signin': async (ctx, next) => {
        console.log('/signin')
        var name = ctx.request.body.name;
        if(name == "阿洁" || name == "恒炜") {
            ctx.session.name=name;
            ctx.response.redirect('/accumulate')
        } else {
            ctx.body = 'shit';
        }
        
    }
};