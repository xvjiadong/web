<template>
    <div id="main">
        <el-upload action="" :before-upload="doc" accept=" .xlsx, .pdf, .doc, .docx, .xls, .rar, .zip, .png , .jpg, .jepg">
            <el-button slot="trigger" draggable="">上传测试数据</el-button>
        </el-upload>
        <div>
            <el-button @click="turn">导出</el-button>
        </div>

        <el-popover title="" trigger="manual" v-model="vis" ref="popover">
            <el-form :model="choosecss" label-width="80px">

                <el-form-item>
                    <el-button @click="ok" size="mini">确认</el-button>
                    <el-button @click="vis = !vis" size="mini">取消</el-button>
                </el-form-item>
            </el-form>
            <div slot="reference" class="con">
                <div id="container" ref="container" @mouseup="la"></div>
            </div>
        </el-popover>
    </div>
</template>
<script>
//import Mark from "mark"
import FileSaver from "file-saver";
import htmlDocx from "html-docx-js/dist/html-docx";
import { renderAsync } from "docx-preview";
require('@/util/jquery.wordexport.js')
export default {
    mounted() {
        //console.log(VueOfficePdf);
    },
    data() {
        return {
            pdfData: null,
            blob: "",
            option: {
                className: "docx", // 默认和文档样式类的类名/前缀
                inWrapper: true, // 启用围绕文档内容渲染包装器
                ignoreWidth: false, // 禁止页面渲染宽度
                ignoreHeight: false, // 禁止页面渲染高度
                ignoreFonts: false, // 禁止字体渲染
                breakPages: true, // 在分页符上启用分页
                ignoreLastRenderedPageBreak: true, //禁用lastRenderedPageBreak元素的分页
                experimental: false, //启用实验性功能（制表符停止计算）
                trimXmlDeclaration: true, //如果为真，xml声明将在解析之前从xml文档中删除
                debug: false, // 启用额外的日志记录
            },
            vis: false,
            choose: "",
            choosecss: {
                fontcolor: "#000000",
                backcolor: "#ffffff",
                weight: 400,
                border: {
                    width: 0,
                    type: "",
                    color: "0px",
                    radius: "0"
                }
            }

        }
    },
    methods: {
        prf() {
            console.log(1);
        },
        dis() {
        },
        doc(file) {
            console.log(file);
            this.fileToBlob(file)
            //FileSaver.saveAs(file, "导出" + ".docx");
            /*const markInstance = new Mark(document.getElementById("a"));
            markInstance.mark("text", {
                "element": "span",
                "className": "highlight"
            });*/
            return false
        },
        async render(buffer) {

            await renderAsync(buffer, document.getElementById("container"), null, this.option);
            this.$refs.container.style.overflowY = "scroll"

            //window.print()
        },
        turn() {
            //console.log(document.getElementById("container").getElementsByTagName("style"));
            let a = document.getElementsByTagName("style")
            let b = document.createElement("style")
            for (let i = 0; i < a.length; i++) {
                b.innerHTML += a[i].innerHTML
            }
            let c = document.getElementsByTagName("img")
            for (let i = 0; i < c.length; i++) {
                let Img = new Image()
                Img.src = c[i].src;
                Img.setAttribute("crossOrigin", 'Anonymous')
                //console.log(Img.src);
                Img.onload = () => { //要先确保图片完整获取到，这是个异步事件
                    let canvas = document.createElement("canvas") //创建canvas元素
                    //width = Img.width, //确保canvas的尺寸和图片一样
                    //height = Img.height;
                    //console.log(c[i].style.width, c[i].style.height);    
                    canvas.width = parseFloat(c[i].style.width.slice(0, -2)) * 1.33;
                    canvas.height = parseFloat(c[i].style.height.slice(0, -2)) * 1.33;
                    //console.log(width,height);
                    canvas.getContext("2d").drawImage(Img, 0, 0, canvas.width, canvas.height); //将图片绘制到canvas中
                    let dataURL = canvas.toDataURL('image/png'); //转换图片为dataURL
                    c[i].setAttribute('src', dataURL);
                };
            }
            setTimeout(() => {
                let contenthtml = document.getElementsByClassName("docx-wrapper")[0].innerHTML
                document.getElementsByClassName("docx-wrapper")[0].setAttribute("id","doc")
                let content = `
              Content-Type: text/html; charset="utf-8"
              <!DOCTYPE html><html>
                <head>
                    <meta charset="utf-8">
                    <meta http-equiv="X-UA-Compatible" content="IE=edge">
                    <meta name="viewport" content="width=device-width,initial-scale=1.0">
                    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
                    <style>
                        ${b}
                    </style>
                </head>
                <body>
                    ${contenthtml}
                </body>
            </html>`;
                //let blob = new Blob([content], { type: "application/msword;charset=utf-8" });
                let converted = htmlDocx.asBlob(contenthtml, "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
                console.log(converted);
                console.log(content);
                console.log(FileSaver);
                //$("#doc").wordExport("测试");
                FileSaver.saveAs(converted, "导出.docx");
            }, 5000)
        },
        getBase64(url, charImg) {
            var Img = new Image();
            Img.crossOrigin = "Anonymous";//跨域必须使用，且后台也得设置允许跨域
            let dataURL = '';
            Img.src = url;

            Img.onload = () => { //要先确保图片完整获取到，这是个异步事件
                let canvas = document.createElement("canvas"), //创建canvas元素
                    width = Img.width, //确保canvas的尺寸和图片一样
                    height = Img.height;
                canvas.width = width;
                canvas.height = height;
                canvas.getContext("2d").drawImage(Img, 0, 0, width, height); //将图片绘制到canvas中
                dataURL = canvas.toDataURL('image/jpg'); //转换图片为dataURL
                this.condataurl(dataURL, charImg) //调用回调函数

            };
        },
        condataurl(dataURL, charImg) {
            charImg.src = dataURL;
            //console.log(charImg);
        },
        fileToBlob(file) {
            let fr = new FileReader();
            fr.readAsArrayBuffer(file);
            fr.addEventListener("loadend", (e) => {
                let buffer = e.target.result;

                this.render(buffer);
            }, false);
        },

        blobToBuffer(blob) {
            return new Promise((resolve, reject) => {
                const reader = new FileReader();
                reader.onloadend = () => {
                    resolve(reader.result);
                };
                reader.onerror = reject;
                reader.readAsArrayBuffer(blob);
            });
        },
        scroll(e) {
            this.x = e.pageX
            this.y = e.pageY
            this.x1 = e.clientX
            this.y1 = e.clientY
        },
        la(e) {
            if (window.getSelection().toString().split(" ").join("").split("\n").join("")) {
                const popover = this.$refs.popover;
                let timer = setTimeout(() => {
                    const { clientX, pageY } = e;
                    const bodyWidth = document.body.clientWidth;
                    const { popperElm } = popover;
                    let disX =
                        clientX + popperElm.offsetWidth < bodyWidth
                            ? clientX
                            : bodyWidth - popperElm.offsetWidth;
                    let disY = pageY
                    popover.popperElm.style.left = disX + "px";
                    popover.popperElm.style.top = disY + "px";
                    clearTimeout(timer);
                }, 5);
                this.vis = true
                console.log(window.getSelection(), window.getSelection().anchorNode, window.getSelection().focusNode);
                console.log(window.getSelection().getRangeAt(0).toString());
                this.choose = window.getSelection()
                //console.log(this.choose);
            } else {
                this.vis = false
            }
        },
        async ok() {
            let newSpan = document.createElement("span");
            newSpan.style.backgroundColor = "red";
            newSpan.style.color = "green";
            newSpan.innerHTML = this.choose.toString();
            //let regex = /[\r\n]/g; // 匹配所有回车符(\r)和换行符(\n)
            //let matches = this.choose.toString().match(regex);
            //console.log(matches ? matches.length : 0);
            //console.log(this.choose.getRangeAt(0).extractContents());
            //this.choose.getRangeAt(0).selectNode(document.querySelectorAll("article")[1])
            console.log();
            this.choose.getRangeAt(0).deleteContents();
            this.choose.getRangeAt(0).insertNode(newSpan);
            this.vis = !this.vis
        }
    }
}
</script>
<style scoped>
#main {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: flex-start;
}

:deep(.docx-wrapper) {
    background-color: #fff;
}

#container {
    height: 450px;
}
</style>