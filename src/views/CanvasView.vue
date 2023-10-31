<template>
    <div>
        <canvas ref="myCanvas" width="400" height="600" globalCompositeOperation="source-over"></canvas>
        <img ref="myImage" src="http://120.55.63.197:3000/images/6.jpeg" alt="Image">
        <div id="rect"></div>
    </div>
    
</template>
<script>
export default {
    data() {
        return {
            rect: [

            ],
            isDrawing: false,
            canvas: "",
            ctx: "",
            image: ""
        }
    },
    mounted() {
        this.canvas = this.$refs.myCanvas;
        this.ctx = this.canvas.getContext("2d");
        this.image = this.$refs.myImage;
        this.image.onload = () => {
            this.canvas.width = 650;
            this.canvas.height = 500;
            this.ctx.drawImage(this.image, 0, 0);
        };
        // 添加事件监听器
        this.canvas.addEventListener('mousedown', this.startDrawing);
        this.canvas.addEventListener('mousemove', this.drawRectangle);
        this.canvas.addEventListener('mouseup', this.stopDrawing);
    },
    methods: {
        startDrawing(e) {
            this.rect.push({ x: 0, y: 0, width: 0, height: 0 })
            this.rect[this.rect.length - 1].x = e.offsetX;
            this.rect[this.rect.length - 1].y = e.offsetY;
            this.isDrawing = true;
        },
        drawRectangle(e) {
            // ...
            if (!this.isDrawing) return;
            this.rect[this.rect.length - 1].width = e.offsetX - this.rect[this.rect.length - 1].x;
            this.rect[this.rect.length - 1].height = e.offsetY - this.rect[this.rect.length - 1].y;
            //this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            //this.ctx.drawImage(this.image, 0, 0);
            this.ctx.strokeStyle = "red";
            this.ctx.lineWidth = 2;
            this.ctx.beginPath();
            this.ctx.rect(this.rect[this.rect.length - 1].x, this.rect[this.rect.length - 1].y, this.rect[this.rect.length - 1].width, this.rect[this.rect.length - 1].height);
            this.ctx.stroke();
            this.ctx.closePath();
        },
        stopDrawing() {
            // ...

            this.isDrawing = false;
        },
        linestartDrawing(e) {
            console.log(e);
            // ...
            this.rect.x = e.offsetX;
            this.rect.y = e.offsetY;
            this.isDrawing = true;
        },
        linedrawRectangle(e) {
            // ...
            if (!this.isDrawing) return;
            this.rect.width = e.offsetX - this.rect.x;
            this.rect.height = e.offsetY - this.rect.y;
            console.log(this.rect.width, this.rect.height);
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
            this.ctx.drawImage(this.image, 0, 0);
            this.ctx.strokeStyle = "red";
            this.ctx.lineWidth = 2;
            this.ctx.beginPath();
            this.ctx.rect(this.rect.x, this.rect.y, this.rect.width, this.rect.height);
            this.ctx.stroke();
        },
        linestopDrawing() {
            // ...
            this.isDrawing = false;
        }
    }
}
</script>
<style scoped>
#rect {
    position: absolute;
    box-shadow: 0 0 0 1999px rgba(0, 0, 0, .4);
    left: -9999px;
    top: 0;
    width: 0;
    height: 0;
    border: 1px solid #fa9120;
    cursor: move;
}
</style>