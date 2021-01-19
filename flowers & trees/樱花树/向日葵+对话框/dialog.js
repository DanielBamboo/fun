let context = document.getElementById('dialog').getContext('2d');
let ctx = context;
context.lineWidth = 3;
//context.fillStyle = 'rgba(255, 255, 255, 0.7)';
context.strokeStyle = 'rgba(0, 0, 0, 0.7)';

function draw(text) {
    context.font = "25px serif";
    let length = context.measureText(text).width;
    console.log(length)
    let delta = (length - 80) > 0 ? (length - 80) : 0;
    if (125 + delta > 290) {
        // 扩大canvas面积
        document.getElementById('dialog').width = `${125+delta+10}`;
    }
    context.font = "25px serif";
    let ctx = document.getElementById('dialog').getContext('2d');
    context.lineWidth = 3;
    //context.fillStyle = 'rgba(255, 255, 255, 0.7)';
    context.strokeStyle = 'rgba(0, 0, 0, 0.7)';

    ctx.beginPath();
    ctx.moveTo(75, 25);
    ctx.quadraticCurveTo(25, 25, 25, 62.5);
    ctx.quadraticCurveTo(25, 100, 50, 100);
    // 对话框的小勾
    ctx.quadraticCurveTo(50, 120, 30, 125);
    ctx.quadraticCurveTo(60, 120, 65, 100);
    // 小勾 end
    ctx.lineTo(65 + delta, 100);
    ctx.quadraticCurveTo(125 + delta, 100, 125 + delta, 62.5);
    ctx.quadraticCurveTo(125 + delta, 25, 75 + delta, 25);
    ctx.lineTo(75, 25);
    ctx.fillText(text, 35, 72)
    ctx.stroke();
}