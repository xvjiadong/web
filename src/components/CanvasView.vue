<template>
    <div>
        <canvas ref="canvas" :width="width" :height="height" @mousedown="startDrawing" @mousemove="draw"
            @mouseup="stopDrawing" @touchstart="startDrawingTouch" @touchmove="drawTouch" @touchend="stopDrawing">
            Your browser does not support the HTML5 canvas tag.
        </canvas>
        <button @click="clearCanvas">Clear</button>
        <button @click="toggleEraser">{{ eraserMode ? 'Brush' : 'Eraser' }}</button>
        <button @click="exportCanvas">Export</button>
    </div>
</template>

<script>
export default {
    data() {
        return {
            canvas: null,
            ctx: null,
            drawing: false,
            eraserMode: false,
            width: 500,
            height: 300
        };
    },
    mounted() {
        this.canvas = this.$refs.canvas;
        this.ctx = this.canvas.getContext('2d');
    },
    methods: {
        startDrawing(e) {
            this.drawing = true;
            this.ctx.beginPath();
            this.ctx.moveTo(e.offsetX, e.offsetY);
        },
        draw(e) {
            if (this.drawing) {
                if (!this.eraserMode) {
                    this.ctx.lineTo(e.offsetX, e.offsetY);
                    this.ctx.stroke();
                } else {
                    this.ctx.clearRect(e.offsetX, e.offsetY, 10, 10);
                }
            }
        },
        stopDrawing() {
            this.drawing = false;
        },
        startDrawingTouch(e) {
            this.drawing = true;
            this.ctx.beginPath();
            this.ctx.moveTo(e.touches[0].offsetX, e.touches[0].offsetY);
        },
        drawTouch(e) {
            if (this.drawing) {
                e.preventDefault();
                if (!this.eraserMode) {
                    this.ctx.lineTo(e.touches[0].offsetX, e.touches[0].offsetY);
                    this.ctx.stroke();
                } else {
                    this.ctx.clearRect(e.touches[0].offsetX, e.touches[0].offsetY, 10, 10);
                }
            }
        },
        clearCanvas() {
            this.ctx.clearRect(0, 0, this.width, this.height);
        },
        toggleEraser() {
            this.eraserMode = !this.eraserMode;
        },
        exportCanvas() {
            const dataUrl = this.canvas.toDataURL();
            console.log(dataUrl);
            // 这里你可以将 dataUrl 发送到服务器端进行保存或者进行其他处理
        }
    }
};
</script>

<style scoped>
canvas {
    border: 1px solid black;
}

button {
    margin: 5px;
}
</style>