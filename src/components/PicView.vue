<template>
    <el-card>
        <div slot="header" style="display: flex;justify-content: left;align-items: center;">
            <el-page-header @back="goBack" :content="project.name">
            </el-page-header>
            <span>{{ project.projectName }}->{{ project.version }}->{{ project.callType }}</span>
        </div>
        <div class="main">
            <!--<div class="operation">
            <div class="button-wrap">
                <el-button type="text" class="el-icon-thumb" @click="setMode('PAN')">平移</el-button>
                <el-button type="text" class="el-icon-more-outline" @click="setMode('POINT')">点</el-button>
                <el-button type="text" class="el-icon-minus" @click="setMode('LINE')">线段</el-button>
                <el-button type="text" class="el-icon-share" @click="setMode('POLYLINE')">多段线</el-button>
                <el-button type="text" class="el-icon-orange" @click="setMode('CIRCLE')">圆</el-button>
                <el-button type="text" class="el-icon-full-screen" @click="setMode('RECT')">矩形</el-button>
                <el-button type="text" class="el-icon-house" @click="setMode('POLYGON')">多边形</el-button>
                <el-button type="text" class="el-icon-magic-stick" @click="Fill()">填充</el-button>
                <el-button type="text" class="el-icon-refresh-left" @click="Revoke()">撤销</el-button>
                <el-button type="text" class="el-icon-plus" @click="zoomIn">放大</el-button>
                <el-button type="text" class="el-icon-minus" @click="zoomOut">缩小</el-button>
                <el-button type="text" class="el-icon-suitcase" @click="together">汇总</el-button>
                <el-button type="text" class="el-icon-location-outline" @click="setMode('MARKER')">注记</el-button>
                <button class="btn btn-default" @click="setMode('DRAWMASK')">
                        涂抹
                    </button>
                
                <button class="btn btn-default" @click="setMode('CLEARMASK')">
                        擦除
                    </button> 
                
                 <button class="btn btn-default" @click="getRle()">获取rle数据</button>
            </div>
            
            <div class="zoom-icon-wrapper">
                <div class="zoom-icon-plus" @click="zoomIn">+</div>
                <div class="zoom-icon-minus" @click="zoomOut">-</div>
            </div> 
            
        </div>-->
            <el-card class="teachcard">
                <div slot="header" class="operation">
                    <div class="button-wrap">
                        <!---->
                        <el-tooltip content="平移" placement="top-start">
                            <div class="toolblock" :class="{ modeing: mode === 'PAN' }">
                                <el-button type="text" class="el-icon-thumb" @click="setMode('PAN')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="点标注" placement="top-start">
                            <div class="toolblock" :class="{ modeing: mode === 'POINT' }">
                                <el-button type="text" class="el-icon-more-outline" @click="setMode('POINT')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="线标注" placement="top-start">
                            <div class="toolblock" :class="{ modeing: mode === 'LINE' }">
                                <el-button type="text" class="el-icon-minus button" @click="setMode('LINE')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="多段线标注" placement="top-start">
                            <div class="toolblock" :class="{ modeing: mode === 'POLYLINE' }">
                                <el-button type="text" class="el-icon-share button"
                                    @click="setMode('POLYLINE')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="圆标注" placement="top-start">
                            <div class="toolblock" :class="{ modeing: mode === 'CIRCLE' }">
                                <el-button type="text" class="el-icon-orange button" @click="setMode('CIRCLE')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="矩形标注" placement="top-start">
                            <div class="toolblock" :class="{ modeing: mode === 'RECT' }">
                                <el-button type="text" class="el-icon-full-screen button"
                                    @click="setMode('RECT')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="多边形标注" placement="top-end">
                            <div class="toolblock" :class="{ modeing: mode === 'POLYGON' }">
                                <el-button type="text" class="el-icon-house button" @click="setMode('POLYGON')"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="填充" placement="top-end">
                            <div class="toolblock" :class="{ modeing: mode === 'FILL' }">
                                <el-button type="text" class="el-icon-magic-stick button" @click="Fill()"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="撤销" placement="top-end">
                            <div class="toolblock">
                                <el-button type="text" class="el-icon-refresh-left button" @click="Revoke()"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="放大" placement="top-end">
                            <div class="toolblock">
                                <el-button type="text" class="el-icon-plus button" @click="zoomIn"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="缩小" placement="top-end">
                            <div class="toolblock">
                                <el-button type="text" class="el-icon-minus button" @click="zoomOut"></el-button>
                            </div>
                        </el-tooltip>
                        <el-tooltip content="保存" placement="top-end">
                            <div class="toolblock">
                                <el-button type="text" class="el-icon-suitcase button"
                                    @click="together(nowselect)"></el-button>
                            </div>
                        </el-tooltip>
                        <!--<el-button type="text" class="el-icon-location-outline" @click="setMode('MARKER')">注记</el-button>-->
                        <!--<button class="btn btn-default" @click="setMode('DRAWMASK')">
                        涂抹
                    </button>
                -->
                        <!--<button class="btn btn-default" @click="setMode('CLEARMASK')">
                        擦除
                    </button> 
                -->
                        <!-- <button class="btn btn-default" @click="getRle()">获取rle数据</button> -->
                    </div>
                    <div style="display: flex;align-items: center;margin-right: 8px;">
                        <i style="cursor: pointer;font-size: 12px;" class="el-icon-arrow-left toparrow"
                            @click="together(nowselect - 1)"></i>
                        <span style="font-size: 12px;">第{{ nowselect + 1 }}张/一共30张</span>
                        <i style="cursor: pointer;font-size: 12px;" class="el-icon-arrow-right toparrow"
                            @click="together(nowselect + 1)"></i>
                    </div>
                </div>
                <el-popover trigger="manual" v-model="vis" ref="popover" popper-class="pop">
                    <el-input v-model="Recognizetextcontent" style="width: 100%;" size="mini"
                        placeholder="请输入识别内容"></el-input>
                    <div style="display: flex;justify-content: center;margin-top: 5px;">
                        <el-button size="mini" type="primary" @click="ok">
                            确定
                        </el-button>
                        <el-button size="mini" @click="Revoke">
                            取消
                        </el-button>
                    </div>
                    <div id="map" slot="reference" @click="la" @dblclick="la2"></div>
                </el-popover>
            </el-card>
            <el-card class="teachcard">
                <div slot="header" style="text-align: center;">
                    <i class="el-icon-top toparrow" @click="together(nowselect - 1)"></i>
                </div>
                <div
                    style="display: flex;flex-direction: column;justify-content: space-between;height: 540px;padding-left: 20px;padding-right: 20px;padding-top: 0;padding-bottom: 0;">
                    <div style="width: 120px;height: 120px;margin-top: 15px;padding: 5px;"
                        v-for="(item, index) in imagelist1.slice((page - 1) * 5, page * 5)" :key="item.url">
                        <img @click="together((page - 1) * 5 + index)" :src="item.url"
                            :class="{ select: index === nowselect % 5 }" style="width: 120px;height: 75px;cursor: pointer;">
                    </div>
                </div>
                <el-divider style="padding: 0;margin: 0;"></el-divider>
                <div style="text-align: center;">
                    <i class="el-icon-bottom toparrow" @click="together(nowselect + 1)"></i>
                </div>
            </el-card>
            <el-card class="teachcard">
                <div slot="header" class="resultheader">
                    <div style="color: #666;font-size: 20px;padding: 5px;font-weight: 600;">标注结果</div>
                    <el-select clearable size="mini" filterable v-model="markfilter">
                        <el-option v-for="item in marktype" :key="item.value" :value="item.value"
                            :label="item.label"></el-option>
                    </el-select>
                </div>
                <div
                    style="overflow-y: scroll;height: 507px;padding-left: 20px;padding-right: 20px;padding-top: 0;padding-bottom: 0;">
                    <div class="result" v-for="item in imagelist1[nowselect].mark" :key="item.id">
                        <span>id:{{ item.id }}</span>
                        <span>标注类型:{{ item.type === "RECT" ? "矩形" : (item.type === "POLYGON" ? "多边形" : (item.type
                            === "CIRCLE" ? "圆" : (item.type === "POLYLINE" ? "多段线" : (item.type === "LINE" ? "线" : "点"))))
                        }}</span>
                        <span>标注文本:{{ item.text.text }}</span>
                    </div>
                </div>
            </el-card>
        </div>
    </el-card>
</template>
<script>
import AILabel from "ailabel";
//import FileSaver from "file-saver";
import axios from 'axios'

//import PicDoc from '../../public/PicDoc.json'
//import data from '../../public/data (1).json'
//import example from "../../public/示例.json"
//import * as cv from 'opencv.js'
export default {
    data() {
        return {
            imglist: [],
            imgUrl: "http://120.55.63.197:3000/images/test3.jpg",
            drawingStyle: {},
            mode: "",
            itemName: "",
            editId: "", //待填充图形id
            deleteIconId: "delete01",
            gMap: null, //AILabel实例
            gFirstFeatureLayer: null, //矢量图层实例(矩形，多边形等矢量)
            allFeatures: null, //所有features,
            tagtextLayer: null,
            allText: null,
            labelcontent: null,
            vis: false,
            height: 0,
            list: [],
            data2: null,
            type: "",
            selected: false,
            power: false,
            shapelist: [],
            imagelist1: [
                {
                    url: "/图像标注/4.webp.jpg",
                    data: "/图像标注/1.json",
                    mark: []
                },
                {
                    url: "/图像标注/10.webp.jpg", data: "/图像标注/2.json", mark: []
                },
                {
                    url: "/图像标注/11.png", data: "/图像标注/3.json", mark: []
                },
                {
                    url: "/图像标注/12.webp.jpg", data: "/图像标注/4.json", mark: []
                },
                {
                    url: "/图像标注/13.webp.jpg", data: "/图像标注/5.json", mark: []
                },
            ],
            imagelist2: [
                {
                    url: "/图像标注/14.webp.jpg", data: "", mark: []
                },
                {
                    url: "/图像标注/15.webp (1).jpg", data: "", mark: []
                },
                {
                    url: "/图像标注/15.webp.jpg", data: "", mark: []
                },
                {
                    url: "/图像标注/16.webp.jpg", data: "", mark: []
                },
                {
                    url: "/图像标注/17.jpg", data: "", mark: []
                }
            ],
            imagelist3: [
                {
                    url: "http://120.55.63.197:3000/images/中国节日.jpg", mark: [{
                        "id": "1699412607806",
                        "type": "RECT",
                        "shape": { "x": 53.75, "y": 190.125, "width": 35.625, "height": 27.5 },
                        "text": { "id": "1699412607806-0", "text": "人脸" }
                    }]
                },
                {
                    url: "http://120.55.63.197:3000/images/中秋.jpg", mark: [{
                        "id": "65756",
                        "type": "POINT",
                        "shape": { "x": 111.25, "y": 80.125, "r": 3 },
                        "text": { id: "65756-0", text: "4545" }
                    }]
                },
                {
                    url: "http://120.55.63.197:3000/images/重阳节.jpg", mark: [{
                        "id": "1699375246644",
                        "type": "LINE",
                        "shape": {
                            "start": { "x": 138.125, "y": 92.625 },
                            "end": { "x": 283.75, "y": 71.375 },
                            "width": 3.125
                        },
                        "text": { "id": "1699375246644-0", "text": "人脸" }
                    }]
                },
                {
                    url: "http://120.55.63.197:3000/images/总.jpg", mark: [{
                        "id": "1699375117322",
                        "type": "POLYLINE",
                        "shape": [
                            { "x": 240.625, "y": 142.625 },
                            { "x": 350, "y": 91.375 },
                            { "x": 355.625, "y": 276.375 },
                            { "x": 419.375, "y": 190.125 }
                        ],
                        "text": { "id": "1699375117322-0", "text": "人脸" }
                    }]
                },
                {
                    url: "http://120.55.63.197:3000/images/中国.webp.jpg", mark: [{
                        "id": "1699374713865",
                        "type": "CIRCLE",
                        "shape": { "cx": 370.625, "cy": 63.25, "r": 45.573601185335356 },
                        "text": { "id": "1699374713865-0", "text": "人脸" }
                    }]
                }
            ],
            Recognizetextcontent: "",
            nowselect: 0,
            page: 1,
            markfilter: "",
            marktype: [{ value: "POLYGON", label: "多边形" }, { value: "POLYLINE", label: "多段线" }, { value: "RECT", label: "矩形" }, { value: "CIRCLE", label: "圆" }, { value: "LINE", label: "线" }, { value: "POINT", label: "点" }],
            project: { projectid: "fdsafd", projectname: "dsa", version: "v1", marktype: "图像文本标注" }
        };
    },
    watch: {
        mode: {
            handler(mode) {
                this.gMap.setMode(mode);
                this.setDrawingStyle(mode);
            },
            deep: true
        }
    },
    computed: {
    },
    methods: {
        /*切图片时把已标注数据标上 */
        keepdraw(markdata) {
            markdata.forEach((item) => {
                this.setDrawingStyle(item.type)
                this.addFeature(item.shape, item.type, item.id)
                if (item.type === "RECT") {
                    const recttext = new AILabel.Text(item.text.id, { text: item.text.text, position: { x: item.shape.x, y: item.shape.y }, offset: { x: 1, y: item.shape.y < 19 ? -item.shape.y - item.shape.height - 25 : 0 } })
                    this.tagtextLayer.addText(recttext)
                } else if (item.type === "POLYGON") {
                    let maxx = 9999
                    let maxy = 9999
                    let num
                    item.shape.forEach((item3, index) => {
                        if (item3.x < maxx || item3.x < maxx && item3.y < maxy) {
                            maxx = item3.x
                            maxy = item3.y
                            num = index
                        }
                    })
                    const polygontext = new AILabel.Text(item.text.id, { text: item.text.text, position: { x: item.shape[num].x, y: item.shape[num].y }, offset: { x: 1, y: 0 } })
                    this.tagtextLayer.addText(polygontext)
                } else if (item.type === "CIRCLE") {
                    const circletext = new AILabel.Text(item.text.id, { text: item.text.text, position: { x: item.shape.cx, y: item.shape.cy }, offset: { x: 0, y: 19 } })
                    this.tagtextLayer.addText(circletext)
                } else if (item.type === "POLYLINE") {
                    let maxx = 9999
                    let maxy = 9999
                    let num
                    item.shape.forEach((item3, index) => {
                        if (item3.x < maxx || item3.x < maxx && item3.y < maxy) {
                            maxx = item3.x
                            maxy = item3.y
                            num = index
                        }
                    })
                    const polygontext = new AILabel.Text(item.text.id, { text: item.text.text, position: { x: item.shape[num].x, y: item.shape[num].y }, offset: { x: 1, y: 0 } })
                    this.tagtextLayer.addText(polygontext)
                } else if (item.type === "LINE") {
                    const recttext = new AILabel.Text(item.text.id, { text: item.text.text, position: { x: item.shape.start.x, y: item.shape.start.y }, offset: { x: 1, y: 0 } })
                    this.tagtextLayer.addText(recttext)
                } else if (item.type === "POINT") {
                    const recttext = new AILabel.Text(item.text.id, { text: item.text.text, position: { x: item.shape.x, y: item.shape.y }, offset: { x: 1, y: 0 } })
                    this.tagtextLayer.addText(recttext)
                }
            })
            this.setMode("RECT")
        },
        //汇总框选向后台提交//
        together(index) {
            let a = this.gFirstFeatureLayer.getAllFeatures();
            let b = this.tagtextLayer.texts
            a.forEach(item => {
                let feature = { id: "", type: "", shape: "", text: [] }
                feature.id = item.id
                feature.type = item.type
                b.forEach(item2 => {
                    if (item2.id && item2.id.split("-")[0] === item.id) {
                        feature.text = { id: item2.id, text: item2.textInfo.text }
                    }
                })
                feature.shape = item.shape
                if (item.type === "POLYGON" || item.type === "POLYLINE") {
                    feature.shape = item.shape.points
                } else {
                    feature.shape = item.shape
                }
                this.shapelist.push(feature);
            })
            this.imagelist1[this.nowselect].mark = this.shapelist
            this.shapelist = []
            let data = JSON.stringify(this.imagelist1[this.nowselect].mark)
            let file = new FormData()
            const blob = new Blob([data]);
            file.set("file", blob, "data.json")
            file.set("id", this.imagelist1[this.nowselect].id)
            axios.put("http://192.168.224.150:10010/dataset/call", file, { headers: { "Content-Type": "multipart/form-data;charset=utf-8" } }).then((res) => {
                console.log(res.data);
            })
            if (index === -1) {
                this.$message.warning("已经是第一张图片了")
                return
            } else if (index === this.imagelist1.length) {
                if (this.imagelist1.length === 10) {
                    this.$message.warning("已经是最后一张图片了")
                    return
                } else {
                    this.imagelist2.map(item => {
                        this.imagelist1.push(item)
                    })

                }
            }
            /*let data = JSON.stringify(this.imagelist1[this.nowselect].mark)
            let file = new FormData()
            const blob = new Blob([data]);
            file.set("file", blob, "data.json")
            file.set("id", this.imagelist1[this.nowselect].id)
            axios.put("http://192.168.224.150:10010/dataset/call", file, { headers: { "Content-Type": "multipart/form-data;charset=utf-8" } }).then((res) => {
                console.log(res.data);
            })
            if (index === -1) {
                this.$message.warning("已经是第一张图片了")
                return
            } else if (index === this.imagelist1.length) {
                axios.post("http://192.168.224.150:10010/dataset/task", { version: this.project.versionId, page: Math.floor(index/5)+1, number: 5 }).then(res => {
                    console.log(res.data);
                    res.data.data.map(item => {
                        this.imagelist1.push(item)
                    })
                })
            }*/
            /* const json = JSON.stringify(this.imagelist1[this.nowselect].mark)
             const blob = new Blob([json], { type: 'application/json' });
             FileSaver.saveAs(blob, (this.nowselect + 1) + ".json");*/
            this.gMap.destroy()
            this.allText = null
            this.allFeatures = null
            this.vis = false
            //this.imgUrl = this.imagelist1[index].url
            this.changepic(this.imagelist1[index])
            this.nowselect = index
            this.page = Math.floor(this.nowselect / 5 + 1)
        },
        ok() {
            this.power = false
            if (this.Recognizetextcontent === "") {
                return
            }
            if (this.type === "RECT") {
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const recttext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2.x, y: this.data2.y }, offset: { x: 1, y: this.data2.y < 19 ? -this.data2.y - this.data2.height - 25 : 0 } })
                this.tagtextLayer.addText(recttext)
                this.imagelist1[this.nowselect].mark.push({ type: "RECT", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "POLYGON") {
                let maxx = 9999
                let maxy = 9999
                let num
                this.data2.forEach((item, index) => {
                    if (item.x < maxx || item.x < maxx && item.y < maxy) {
                        maxx = item.x
                        maxy = item.y
                        num = index
                    }
                })
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2[num].x, y: this.data2[num].y }, offset: { x: 1, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                this.imagelist1[this.nowselect].mark.push({ type: "POLYGON", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "POLYLINE") {
                let maxx = 9999
                let maxy = 9999
                let num
                this.data2.forEach((item, index) => {
                    if (item.x < maxx || item.x < maxx && item.y < maxy) {
                        maxx = item.x
                        maxy = item.y
                        num = index
                    }
                })
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2[num].x, y: this.data2[num].y }, offset: { x: 1, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                this.imagelist1[this.nowselect].mark.push({ type: "POLYLINE", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "CIRCLE") {
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2.cx, y: this.data2.cy }, offset: { x: 0, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                this.imagelist1[this.nowselect].mark.push({ type: "CIRCLE", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "POINT") {
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2.x, y: this.data2.y }, offset: { x: 1, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                this.imagelist1[this.nowselect].mark.push({ type: "POINT", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "LINE") {
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2.start.x, y: this.data2.start.y }, offset: { x: 1, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                this.imagelist1[this.nowselect].mark.push({ type: "LINE", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            }
            this.vis = false
            this.Recognizetextcontent = ""
        },
        la(e) {
            if (this.type === "POINT") {
                let a = setTimeout(() => {
                    if (this.selected || !this.power) {
                        return
                    }
                    if (this.type === "LINE") {
                        this.linenumber += 1
                    }
                    if (this.type === "POINT" || this.type === "RECT" || this.type === "CIRCLE" || (this.type === "LINE" && this.linenumber % 2 === 0)) {
                        if (!this.vis) {
                            const popover = this.$refs.popover;
                            let timer = setTimeout(() => {
                                const { clientX, clientY } = e;
                                const bodyWidth = document.body.clientWidth;
                                const { popperElm } = popover;
                                let disX = clientX + popperElm.offsetWidth < bodyWidth
                                    ? clientX
                                    : bodyWidth - popperElm.offsetWidth;
                                let disY = clientY - this.height
                                popover.popperElm.style.left = disX + "px";
                                popover.popperElm.style.top = disY + "px";
                                popover.popperElm.style.zIndex = '99';
                                clearTimeout(timer);
                            }, 5);
                            this.vis = true
                        }
                    }
                    clearTimeout(a)
                }, 200)
            } else {
                if (this.selected || !this.power) {
                    return
                }
                if (this.type === "POINT" || this.type === "RECT" || this.type === "CIRCLE" || (this.type === "LINE")) {
                    //if (!this.vis) {
                    const popover = this.$refs.popover;
                    let timer = setTimeout(() => {
                        const { clientX, clientY } = e;
                        const bodyWidth = document.body.clientWidth;
                        const { popperElm } = popover;
                        let disX = clientX + popperElm.offsetWidth < bodyWidth
                            ? clientX
                            : bodyWidth - popperElm.offsetWidth;
                        let disY = clientY - this.height
                        popover.popperElm.style.left = disX + "px";
                        popover.popperElm.style.top = disY + "px";
                        popover.popperElm.style.zIndex = '99';
                        clearTimeout(timer);
                    }, 5);
                    this.vis = true
                    //}
                }
            }
        },
        la2(e) {
            console.log(2);
            if (this.selected || !this.power) {
                return
            }
            if ((this.type === "POLYGON" || this.type === "POLYLINE") && this.data2) {
                //if (!this.vis) {
                console.log(0);
                const popover = this.$refs.popover;
                let timer = setTimeout(() => {
                    const { clientX, clientY } = e;
                    const bodyWidth = document.body.clientWidth;
                    const { popperElm } = popover;
                    let disX = clientX + popperElm.offsetWidth < bodyWidth
                        ? clientX
                        : bodyWidth - popperElm.offsetWidth;
                    let disY = clientY - this.height
                    popover.popperElm.style.left = disX + "px";
                    popover.popperElm.style.top = disY + "px";
                    popover.popperElm.style.zIndex = '99';
                    clearTimeout(timer);
                }, 5);
                this.vis = true
                //}
            }
        },
        zoomIn() {
            this.gMap.zoomIn();
        },
        zoomOut() {
            this.gMap.zoomOut();
        },
        setMode(mode) {
            //console.log(mode);
            this.mode = mode;
            this.linenumber = 0
            this.type = mode
        },
        // 获取所有features
        getFeatures() {
            this.allFeatures = this.gFirstFeatureLayer.getAllFeatures();
        },
        getText() {
            this.allText = this.tagtextLayer.texts;
        },
        // 初始样式
        setDrawingStyle(mode) {
            let drawingStyle = {};
            switch (mode) {
                //平移
                case "PAN": {
                    break;
                }
                //注记
                case "MARKER": {
                    // 忽略
                    break;
                }
                //点
                case "POINT": {
                    this.drawingStyle = { fillStyle: "rgb(36,104,242)" };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //圆
                case "CIRCLE": {
                    this.drawingStyle = {
                        fillStyle: "#8856FF",
                        strokeStyle: "#87CEFF",
                        lineWidth: 5,
                        stroke: true,
                        fill: true,
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //线段
                case "LINE": {
                    this.drawingStyle = {
                        strokeStyle: "rgb(145,172,218)",
                        lineJoin: "round",
                        lineCap: "round",
                        lineWidth: 5,
                        arrow: false,
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //多线段
                case "POLYLINE": {
                    this.drawingStyle = {
                        strokeStyle: "rgb(145,172,218)",
                        lineJoin: "round",
                        lineCap: "round",
                        lineWidth: 5,
                        stroke: true
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //矩形
                case "RECT": {
                    this.drawingStyle = { strokeStyle: "rgb(36,104,242)", lineWidth: 4, stroke: true };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //多边形
                case "POLYGON": {
                    this.drawingStyle = {
                        strokeStyle: "rgb(36,104,242)", //边框颜色
                        fill: true, //是否填充
                        //fillStyle: "rgb(145,172,218)", //填充色
                        globalAlpha: 0.3,
                        lineWidth: 3,
                        stroke: true,
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //涂抹
                case "DRAWMASK": {
                    this.drawingStyle = {
                        strokeStyle: "rgba(255, 0, 0, .5)",
                        fillStyle: "#00f",
                        lineWidth: 50,
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //擦除
                case "CLEARMASK": {
                    this.drawingStyle = { fillStyle: "#00f", lineWidth: 30 };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                default:
                    break;
            }
        },

        // 添加图形
        addFeature(data, type, id) {
            let that = this;
            let drawingStyle = this.drawingStyle;
            //线
            if (type === "LINE") {
                const scale = that.gMap.getScale();
                const width = drawingStyle.lineWidth / scale;
                const lineFeature = new AILabel.Feature.Line(
                    id, // id
                    { ...data, width }, // shape
                    { name }, // props
                    drawingStyle // style
                );
                that.gFirstFeatureLayer.addFeature(lineFeature);
            }
            //线段
            else if (type === "POLYLINE") {
                const scale = that.gMap.getScale();
                const width = drawingStyle.lineWidth / scale;
                const polylineFeature = new AILabel.Feature.Polyline(
                    id, // id
                    { points: data, width }, // shape
                    { name }, // props
                    drawingStyle // style
                );
                that.gFirstFeatureLayer.addFeature(polylineFeature);
            }
            //矩形
            else if (type === "RECT") {
                const rectFeature = new AILabel.Feature.Rect(
                    id, // id
                    data, // shape
                    { name }, // props
                    drawingStyle // style
                );
                that.gFirstFeatureLayer.addFeature(rectFeature);
            }
            //多边形
            else if (type === "POLYGON") {
                const polygonFeature = new AILabel.Feature.Polygon(
                    id, // id
                    { points: data }, // shape
                    { name }, // props
                    drawingStyle // style
                );
                that.gFirstFeatureLayer.addFeature(polygonFeature);
            }
            //点
            else if (type == "POINT") {
                const gFirstFeaturePoint = new AILabel.Feature.Point(
                    id, // id
                    { x: data.x, y: data.y, r: 3 }, // shape
                    { name }, // props
                    { fillStyle: "rgb(36,102,242)", zIndex: 5, lineWidth: 2 } // style
                );
                that.gFirstFeatureLayer.addFeature(gFirstFeaturePoint);
            }
            //注记
            else if (type == "MARKER") {
                const gFirstMarker = new AILabel.Marker(
                    id, // id
                    {
                        src: "http://ailabel.com.cn/public/ailabel/demo/marker.png",
                        position: {
                            // marker坐标位置
                            x: data.x,
                            y: data.y,
                        },
                        offset: {
                            x: -16,
                            y: 32,
                        },
                    }, // markerInfo
                    { name: "第一个marker注记" } // props
                );
                that.gFirstFeatureLayer.addFeature(gFirstMarker);
            }
            //圆
            else if (type == "CIRCLE") {
                const gFirstFeatureCircle = new AILabel.Feature.Circle(
                    id, // id
                    { cx: data.cx, cy: data.cy, r: data.r }, // shape
                    { name: "第一个矢量图层" }, // props
                    {
                        fillStyle: "#87CEFF",
                        strokeStyle: "rgb(36,104,242)",
                        globalAlpha: 1,
                        lineWidth: 2,
                    } // style
                );
                that.gFirstFeatureLayer.addFeature(gFirstFeatureCircle);
            }
            //涂抹
            else if (type == "DRAWMASK") {
                const drawMaskAction = new AILabel.Mask.Draw(
                    `${+new Date()}`, // id
                    "铅笔",
                    { points: data, width: 5 }, // shape
                    { name: "港币", price: "1元" }, // props
                    { strokeStyle: "#FF0000" } // style
                );
                that.gFirstFeatureLayer.addAction(drawMaskAction);
            }
            //擦除
            else if (type == "CLEARMASK") {
                const clearMaskAction = new AILabel.Mask.Clear(
                    "first-action-clear", // id
                    { points: data, width: 5 } // shape
                );
                that.gFirstMaskLayer.addAction(clearMaskAction);
            }
            this.getFeatures();
        },
        // 增加删除图标
        addDeleteIcon(feature, shape) {
            let gMap = this.gMap;
            let that = this;
            // 添加delete-icon
            // let points = that.getPoints(feature);
            console.log(shape, "shape");
            this.vis = false
            let position = {}
            if (feature.type === "RECT") {
                position.x = shape.x + shape.width
                position.y = shape.y - 15
            } else if (feature.type === "CIRCLE") {
                position.x = shape.cx
                position.y = shape.cy
            } else if (feature.type === "POLYGON") {
                position.x = shape.points[shape.points.length - 1].x
                position.y = shape.points[shape.points.length - 1].y
            } else if (feature.type === "POINT") {
                position.x = shape.x
                position.y = shape.y
            } else if (feature.type === "POLYLINE") {
                position.x = shape.points[shape.points.length - 1].x
                position.y = shape.points[shape.points.length - 1].y
            } else if (feature.type === "LINE") {
                position.x = shape.end.x
                position.y = shape.end.y
            }
            const gFirstMarker = new AILabel.Marker(
                that.deleteIconId, // id
                {
                    src: "https://s1.aigei.com/src/img/png/45/45aabfc232a34e5b9bfaf75412973c08.png?|watermark/3/image/aHR0cHM6Ly9zMS5haWdlaS5jb20vd2F0ZXJtYXJrLzUwMC0xLnBuZz9lPTE3MzU0ODgwMDAmdG9rZW49UDdTMlhwemZ6MTF2QWtBU0xUa2ZITjdGdy1vT1pCZWNxZUpheHlwTDpjYWQ1NHVoRlhGUUViSGR3Vm02aXctVTJoWVE9/dissolve/40/gravity/NorthWest/dx/18/dy/21/ws/0.0/wst/0&e=1735488000&token=P7S2Xpzfz11vAkASLTkfHN7Fw-oOZBecqeJaxypL:C11LKqsRLbAqQo2uVPETYDya0QU=",
                    position: position, // 矩形右上角 根据图形动态调整
                    offset: {
                        x: -20,
                        y: -4,
                    },
                }, // markerInfo
                { name: "delete" } // props
            );
            gFirstMarker.events.on("click", (marker) => {
                // 首先删除当前marker
                gMap.markerLayer.removeMarkerById(marker.id);
                // 删除对应text
                // gFirstTextLayer.removeTextById(textId);
                // 删除对应feature
                that.gFirstFeatureLayer.removeFeatureById(feature.id);
                this.imagelist1[this.nowselect].mark = this.imagelist1[this.nowselect].mark.filter(item => {
                    return item.id !== feature.id
                })
                this.getText(feature.id)
                let a = []
                console.log();
                for (let i = 0; i < this.allText.length; i++) {
                    if (this.allText[i].id.split("-")[0] === feature.id) {
                        a.push(this.allText[i].id)
                    }
                }
                a.map(item => {
                    this.tagtextLayer.removeTextById(item)
                })
                this.selected = false
                this.power = false
            });
            gMap.markerLayer.addMarker(gFirstMarker);

            // that.gFirstFeatureLayer
        },
        // 删除 删除按钮
        deIcon() {
            this.gMap.markerLayer.removeAllMarkers();
        },
        // 增加事件
        addEvent() {
            let that = this;
            let gMap = this.gMap;
            gMap.events.on("drawDone", (type, data) => {
                this.data2 = data
                console.log(data);
                // that.addFeature(data, type);
                if (type == "CLEARMASK" || type == "DRAWMASK") {
                    that.addFeature(data, type);
                } else {
                    if (type === "RECT" && data.width > 10 && data.height > 10 && 500 - data.x - data.width > 0 && data.y + data.height < 375 && data.x > 0 && data.y > 0) {
                        this.power = true
                        that.addFeature(data, type, Date.now() + "");
                    } else if (type === "POLYGON") {
                        let c = true
                        data.forEach(item => {
                            if (item.x < 0 || item.y < 0) {
                                c = false
                            }
                        })
                        if (!c) {
                            return
                        }
                        this.power = true
                        that.addFeature(data, type, Date.now() + "");
                    } else if (type === "LINE" && data.start.x > 0 && data.start.y > 0 && data.end.x > 0 && data.end.y > 0) {
                        this.power = true
                        that.addFeature(data, type, Date.now() + "");
                    }
                    else if (type === "POINT" && data.x > 0 && data.y > 0) {
                        this.power = true
                        that.addFeature(data, type, Date.now() + "");
                    } else if (type === "POLYLINE") {
                        let c = true
                        data.forEach(item => {
                            if (item.x < 0 || item.y < 0) {
                                c = false
                            }
                        })
                        if (!c) {
                            return
                        }
                        this.power = true
                        that.addFeature(data, type, Date.now() + "");
                    } else if (type === "CIRCLE" && data.r > 10 && data.r + data.cx < 500 && data.r + data.cy < 375 && data.cx - data.r > 0 && data.cy - data.r > 0) {
                        this.power = true
                        that.addFeature(data, type, Date.now() + "");
                    }
                }
            });
            gMap.events.on("boundsChanged", (data) => {
                console.log("--map boundsChanged--", data);
                return "";
            });
            // 双击编辑 在绘制模式下双击feature触发选中
            gMap.events.on("featureSelected", (feature) => {
                console.log(1);
                this.editId = feature.id;
                this.selected = true
                console.log("--map featureSelected--", feature, "双击编辑");
                //设置编辑feature
                gMap.setActiveFeature(feature);
                if (feature.type != "POINT") {
                    // 增加删除按钮
                    that.addDeleteIcon(feature, feature.shape);
                }
                this.vis = false
            });
            //右键 目前只针对点双击选中右键触发
            gMap.events.on("featureDeleted", (feature) => {
                if (feature.type == "POINT") {
                    // 根据id删除对应feature
                    that.gFirstFeatureLayer.removeFeatureById(feature.id);
                }
            });
            // 单机空白取消编辑
            gMap.events.on("featureUnselected", () => {
                console.log("unselected");
                // 取消featureSelected
                that.editId = "";
                that.deIcon();
                gMap.setActiveFeature(null);
                let a = setTimeout(() => {
                    this.selected = false
                    clearTimeout(a)
                }, 500)
            });
            // 更新完
            gMap.events.on("featureUpdated", (feature, shape) => {
                this.vis = false
                console.log();
                let id = feature.id;
                this.getText()
                console.log(feature.type);
                this.allText.forEach(item => {
                    if (item.id.split("-")[0] === id) {
                        switch (feature.type) {
                            case "RECT": {
                                let position = { x: shape.x, y: shape.y }
                                item.updatePosition(position)
                                break;
                            }
                            case "CIRCLE": {
                                console.log(shape);
                                let position = { x: shape.cx, y: shape.cy }
                                item.updatePosition(position)
                                break;
                            }
                            case "POLYGON": {
                                let maxx = 9999;
                                let maxy = 9999
                                let num
                                console.log(shape);
                                shape.points.forEach((item, index) => {
                                    if (item.x < maxx || item.x < maxx && item.y < maxy) {
                                        maxx = item.x
                                        maxy = item.y
                                        num = index
                                    }
                                })
                                let position = { x: shape.points[num].x, y: shape.points[num].y }
                                item.updatePosition(position)
                                break;
                            }
                            case "POLYLINE": {
                                let maxx = 9999;
                                let maxy = 9999
                                let num
                                shape.points.forEach((item, index) => {
                                    if (item.x < maxx || item.x < maxx && item.y < maxy) {
                                        maxx = item.x
                                        maxy = item.y
                                        num = index
                                    }
                                })
                                let position = { x: shape.points[num].x, y: shape.points[num].y }
                                item.updatePosition(position)
                                break;
                            }
                            case "LINE": {
                                let position = { x: shape.start.x, y: shape.start.y }
                                item.updatePosition(position)
                                break;
                            }
                            case "POINT": {
                                let position = { x: shape.x, y: shape.y }
                                item.updatePosition(position)
                                break;
                            }
                            default:
                                break;
                        }

                    }
                })
                this.getText()
                // 更新或者移动需要重新设置删除图标
                that.deIcon();

                feature.updateShape(shape);
                that.addDeleteIcon(feature, shape);

            });

            // 删除
            gMap.events.on("FeatureDeleted", () => {
                console.log(2222222);
                // that.gFirstFeatureLayer.removeFeatureById(that.editId);
            });
        },
        // 获取坐标 需要自行添加
        getPoints(feature) {
            switch (feature.type) {
                case "RECT":
                    return feature.getPoints();
                case "LINE":
                    return [feature.shape.start, feature.shape.end];
                case "POLYLINE":
                    return feature.shape.points;
                case "POLYGON":
                    return feature.shape.points;
                default:
                    return [];
            }
        },
        //填充事件
        Fill() {
            console.log("填充事件");
            let fill = this.gFirstFeatureLayer.getFeatureById(this.editId);
            console.log("--填充对象--", fill);
            fill.style.fillStyle = "#FFDAB9";
            fill.style.fill = true;
            //刷新map
            this.gMap.refresh();
        },
        //撤销
        Revoke() {
            if (this.allFeatures.length === 0) {
                this.$message("页面无标注")
            }
            console.log("撤销");
            this.getFeatures();
            this.getText()
            for (let i = this.allText.length - 1; i >= 0; i--) {
                if (this.allText[i].id.split("-")[0] !== this.allFeatures[this.allFeatures.length - 1].id) {
                    break;
                } else {
                    this.allText.pop()
                }
            }
            this.allFeatures.pop();
            //this.gMap.removeTextById(this.editId);
            //刷新map
            this.gMap.refresh();
            this.vis = false
        },
        changepic(item) {
            let that = this
            const gMap = new AILabel.Map("map", {
                center: { x: 250, y: 187 },  // 确定中心点
                zoom: 500,
                mode: "POINT", // 绘制线段
                //refreshDelayWhenZooming: false, // 缩放时是否允许刷新延时，性能更优
                zoomWhenDrawing: true,
                panWhenDrawing: true,
                // 控制滑轮缩放缩率[0, 10), 值越小，则缩放越快，反之越慢
                withHotKeys: false, // 关闭快捷键,
                autoFeatureSelect: true,
                //drawZoom: false,
                //autoPan: false,
            });
            that.gMap = gMap;
            this.addEvent();
            // 图片层添加
            const gFirstImageLayer = new AILabel.Layer.Image(
                "first-layer-image", // id
                {
                    id: "image",
                    src: item.url,
                    width: 500,
                    height: 374,
                    crossOrigin: true, // 如果跨域图片，需要设置为true
                    position: {
                        // 左上角相对中心点偏移量
                        x: 0,
                        y: 0,
                    },
                    // 网格
                    grid: false
                }, // imageInfo
                { name: "第一个图片图层" }, // props
                { zIndex: 5 } // style
            );
            // 添加到gMap对象
            gMap.addLayer(gFirstImageLayer);
            // 添加矢量图层
            const gFirstFeatureLayer = new AILabel.Layer.Feature(
                "first-layer-feature", // id
                { name: "第一个矢量图层" }, // props
                { zIndex: 10 } // style
            );
            this.gFirstFeatureLayer = gFirstFeatureLayer;
            const tagtextLayer = new AILabel.Layer.Text("tagtext-layer", { name: "as" }, { zIndex: 10, opacity: 1 })
            this.tagtextLayer = tagtextLayer;
            gMap.addLayer(gFirstFeatureLayer);
            gMap.addLayer(tagtextLayer)
            window.onresize = function () {
                this.gMap && this.gMap.resize();
            };
            /*"https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2023-11-24/1094cb6a6f964e0eae2990477b9ec5c0-图像文本标注/V1/4.webp.jpg"*/

            if (item.data) {
                axios.get(item.data).then(res => {
                    item.mark = res.data
                    this.keepdraw(res.data)
                })
            }
        },
        goBack() {
            this.$router.push("/MakeMark")
        },
        getdata(page) {
            axios.post("http://192.168.224.150:10010/dataset/task", { version: this.$route.query.versionId, page: page, number: 5 }).then(res => {
                //this.imagelist1 = res.data.data;
                console.log(res.data.data);
            })
        }
    },
    mounted() {
        /*axios.post("http://home.itzyc.com:12349/img/", { url: "http://120.55.63.197:3000/images/92ECD77B012246391BBE80247F874F10.jpg" }, { timeout: 5000000000 }).then(res => {
            console.log(res.data);
        }).catch(e => {
            console.log(e);
        })*/
        this.project = this.$route.query
        this.getdata(this.page)
        /*axios.post("http://localhost:3000/imagelist").then((res) => {
            console.log(res.data);
            this.imagelist=res.data
        })*/
        setTimeout(() => {
            this.changepic(this.imagelist1[0])
        }, 1000)

        /*let file = new FormData()
        let a = JSON.stringify(data)
        const blob = new Blob([a]);
        file.set("file", blob, "data.json")
        console.log(file.getAll("file"));
        file.append("id", 15)
        axios.put("http://10.99.254.235:10010/dataset/call", file, { headers: { "Content-Type": "multipart/form-data;charset=utf-8" } }).then((res) => {
            console.log(res.data);
        })*/
    },
    beforeDestroy() {
        this.gMap.destroy();
    },
};
</script>
   
  <!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.main {
    display: flex;
    justify-content: center;
    align-items: center;
}

.container {
    width: 100%;
    height: 643px;
}

.operation {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.teachcard {
    text-align: left;
    margin-top: 25px;
}

/deep/.el-card__header {
    padding: 0px;
}

/deep/.el-card__body {
    padding: 0px;
}

.button-wrap {
    display: flex;
    padding-bottom: 5px;
    justify-content: left;
    position: relative;
    z-index: 99;
}

#map {
    /* margin: 0 auto; */
    overflow: hidden;
    position: relative;
    height: 540px;
    width: 720px;
    margin-top: 15px;
    border: 1px dashed #ccc;
}

.zoom-icon-wrapper {
    position: absolute;
    /* left: 20px; */
    /* top: 20px; */
    z-index: 1000;
}

.zoom-icon-plus {
    width: 30px;
    height: 30px;
    line-height: 20px;
    text-align: center;
    border: 3px solid #6495ed;
    font-size: 20px;
    border-top-left-radius: 6px;
    border-top-right-radius: 6px;
    color: #ff8c00;
    cursor: pointer;
}

.zoom-icon-plus:hover {
    border-color: #4169e1;
}

.zoom-icon-minus {
    margin-top: 6px;
    width: 30px;
    height: 30px;
    line-height: 20px;
    text-align: center;
    border: 3px solid #6495ed;
    font-size: 25px;
    border-bottom-left-radius: 6px;
    border-bottom-right-radius: 6px;
    color: #ff8c00;
    cursor: pointer;
}

.zoom-icon-minus:hover {
    border-color: #4169e1;
}

/* 删除图标 */
#delete01 {
    width: 20px;
    height: 20px;
}

.el-button {
    margin-left: 0px;
}

.pop .popper__arrow::after {
    border-bottom-color: transparent !important;
}

.pop .popper__arrow {
    border-bottom-color: transparent !important;
}

.el-menu-vertical-demo:not(.el-menu--collapse) {
    width: 100%;
    height: 5000px;
    padding: 0;
}

.el-menu-vertical-demo {
    width: 100%;
    height: 500px;
    padding: 0;
}

.toolblock {
    width: 30px;
    margin-left: 8px;
    height: 30px;
    display: flex;
    align-items: center;
    justify-content: center;
}

.toolblock:hover {
    background-color: rgb(209, 227, 250);
}

.modeing {
    background-color: rgb(209, 227, 250);
}

.select {
    border: 3px solid rgb(36, 104, 242);
    border-radius: 3px;
}

.toparrow {
    cursor: pointer;
    font-size: 25px;
}

.toparrow:hover {
    color: rgb(36, 104, 240);
}

/deep/.el-divider--horizontal {
    display: block;
    height: 0.5px;
    width: 100%;
    margin: 0px 0px;
}

.result {
    border: 2px solid rgb(36, 104, 240);
    border-radius: 5px;
    display: flex;
    flex-direction: column;
    justify-content: flex-start;
    align-items: flex-start;
    width: 150px;
    margin-top: 10px;
    cursor: pointer;
    background-color: rgb(209, 227, 250);
    padding: 8px;
}

.resultheader {
    padding: 10px;
}
</style>