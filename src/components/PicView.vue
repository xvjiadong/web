<template>
    <div class="main">
        <div class="operation">
            <div class="button-wrap">
                <!---->
                <el-button type="text" class="el-icon-thumb" @click="setMode('PAN')">平移</el-button>
                <el-button type="text" class="el-icon-location-outline" @click="setMode('MARKER')">注记</el-button>
                <el-button type="text" class="el-icon-more-outline" @click="setMode('POINT')">点</el-button>
                <el-button type="text" class="el-icon-minus" @click="setMode('LINE')">线段</el-button>
                <el-button type="text" class="el-icon-share" @click="setMode('POLYLINE')">多段线</el-button>
                <el-button type="text" class="el-icon-orange" @click="setMode('CIRCLE')">圆</el-button>
                <el-button type="text" class="el-icon-full-screen" @click="setMode('RECT')">矩形</el-button>
                <el-button type="text" class="el-icon-house" @click="setMode('POLYGON')">多边形</el-button>
                <el-button type="text" class="el-icon-magic-stick" @click="Fill()">填充</el-button>
                <el-button type="text" class="el-icon-refresh-left" @click="Revoke()">撤销</el-button>
                <el-button type="text" @click="getFeatures()">获取标注数据</el-button>
                <el-button @click="together">汇总</el-button>
                <!-- <button class="btn btn-default" @click="setMode('DRAWMASK')">
            涂抹
          </button> -->
                <!-- <button class="btn btn-default" @click="setMode('CLEARMASK')">
            擦除
          </button> -->
                <!-- <button class="btn btn-default" @click="getRle()">获取rle数据</button> -->
            </div>
            <div class="zoom-icon-wrapper">
                <div class="zoom-icon-plus" @click="zoomIn">+</div>
                <div class="zoom-icon-minus" @click="zoomOut">-</div>
            </div>
        </div>
        <el-popover trigger="manual" v-model="vis" ref="popover" popper-class="pop">
            <el-checkbox-group v-model="list">
                <el-checkbox label="原批"></el-checkbox>
                <el-checkbox label="铁皮"></el-checkbox>
                <el-checkbox label="撸狗"></el-checkbox>
                <el-checkbox label="魂w"></el-checkbox>
            </el-checkbox-group>
            <el-button @click="ok">
                确定
            </el-button>
            <el-button @click="Revoke">
                取消
            </el-button>
            <div id="map" slot="reference" @click="la" @dblclick="la2"></div>
        </el-popover>
    </div>
</template>
   
<script>
import AILabel from "ailabel";
import axios from 'axios'
//import * as cv from 'opencv.js'
export default {
    data() {
        return {
            imglist:[],
            imgUrl: "http://120.55.63.197:3000/images/33.jpg",
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
            imagelist:[]
        };
    },
    watch: {
        mode(mode) {
            this.gMap.setMode(mode);
            this.setDrawingStyle(mode);
        },
    },
    methods: {
        change() {
            
        },
        //汇总框选向后台提交//
        together() {
            let a = this.gFirstFeatureLayer.getAllFeatures();
            let b = this.tagtextLayer.texts
            console.log(a);
            console.log(b);
            a.forEach(item => {
                let feature = { id: "", type: "", shape: "", text: [] }
                feature.id = item.id
                feature.type = item.type
                b.forEach(item2 => {
                    if (item2.id.substring(0, 1) === item.id) {
                        feature.text.push({id:item2.id,text:item2.textInfo.text})
                    }
                })
                feature.shape=item.shape
                this.shapelist.push(feature);
            })
            console.log(this.shapelist);
            //this.imgUrl = "http://120.55.63.197:3000/images/虎戏.jpg"
        },
        ok() {
            console.log(this.type);
            this.power = false
            if (this.type === "RECT") {
                this.list.forEach((item, index) => {
                    let textid = this.gFirstFeatureLayer.getAllFeatures().length + "." + index
                    const recttext = new AILabel.Text(textid, { text: item, position: { x: this.data2.x, y: this.data2.y }, offset: { x: 1, y: index * 19 } })
                    this.tagtextLayer.addText(recttext)
                })
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
                this.list.forEach((item, index) => {
                    let textid = this.gFirstFeatureLayer.getAllFeatures().length + "." + index
                    const polygontext = new AILabel.Text(textid, { text: item, position: { x: this.data2[num].x, y: this.data2[num].y }, offset: { x: 1, y: index * 19 } })
                    this.tagtextLayer.addText(polygontext)
                })
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
                this.list.forEach((item, index) => {
                    let textid = this.gFirstFeatureLayer.getAllFeatures().length + "." + index
                    const polygontext = new AILabel.Text(textid, { text: item, position: { x: this.data2[num].x, y: this.data2[num].y }, offset: { x: 1, y: index * 19 } })
                    this.tagtextLayer.addText(polygontext)
                })
            } else if (this.type === "CIRCLE") {
                this.list.forEach((item, index) => {
                    let textid = this.gFirstFeatureLayer.getAllFeatures().length + "." + index
                    const polygontext = new AILabel.Text(textid, { text: item, position: { x: this.data2.cx, y: this.data2.cy }, offset: { x: 0, y: index * 19 } })
                    this.tagtextLayer.addText(polygontext)
                })
            } else if (this.type === "POINT") {
                this.list.forEach((item, index) => {
                    let textid = this.gFirstFeatureLayer.getAllFeatures().length + "." + index
                    const polygontext = new AILabel.Text(textid, { text: item, position: { x: this.data2.x, y: this.data2.y }, offset: { x: 1, y: index * 19 } })
                    this.tagtextLayer.addText(polygontext)
                })
            } else if (this.type === "LINE") {
                this.list.forEach((item, index) => {
                    let textid = this.gFirstFeatureLayer.getAllFeatures().length + "." + index
                    const polygontext = new AILabel.Text(textid, { text: item, position: { x: this.data2.start.x, y: this.data2.start.y }, offset: { x: 1, y: index * 19 } })
                    this.tagtextLayer.addText(polygontext)
                })
            }
            this.vis = !this.vis
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
                    this.drawingStyle = { fillStyle: "#FF8C00" };
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
                        strokeStyle: "#BA55D3",
                        lineJoin: "round",
                        lineCap: "round",
                        lineWidth: 10,
                        arrow: false,
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //多线段
                case "POLYLINE": {
                    this.drawingStyle = {
                        strokeStyle: "#FF1493",
                        lineJoin: "round",
                        lineCap: "round",
                        lineWidth: 10,
                        stroke: true
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //矩形
                case "RECT": {
                    this.drawingStyle = { strokeStyle: "#0f0", lineWidth: 1, stroke: true };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //多边形
                case "POLYGON": {
                    this.drawingStyle = {
                        strokeStyle: "#0099CC", //边框颜色
                        fill: true, //是否填充
                        fillStyle: "#FF6666", //填充色
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
                    { x: data.x, y: data.y, r: 5 }, // shape
                    { name }, // props
                    { fillStyle: "#FF8C00", zIndex: 5, lineWidth: 2 } // style
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
                        strokeStyle: "#3CB371",
                        globalAlpha: 1,
                        lineWidth: 5,
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
        // 画完取名
        /*getName() {
            return this.$prompt("请输入填写名字", {
                confirmButtonText: "确定",
                showCancelButton: true,
            }).then(({ value }) => {
                this.itemName = value;
                this.labelcontent = value
                return value;
            })
                .catch(() => {
                    return null;
                });
        },*/
        // 增加删除图标
        addDeleteIcon(feature, shape) {
            let gMap = this.gMap;
            let that = this;
            // 添加delete-icon
            // let points = that.getPoints(feature);
            console.log(shape, "shape");
            this.vis = false
            const gFirstMarker = new AILabel.Marker(
                that.deleteIconId, // id
                {
                    src: "https://s1.aigei.com/src/img/png/45/45aabfc232a34e5b9bfaf75412973c08.png?|watermark/3/image/aHR0cHM6Ly9zMS5haWdlaS5jb20vd2F0ZXJtYXJrLzUwMC0xLnBuZz9lPTE3MzU0ODgwMDAmdG9rZW49UDdTMlhwemZ6MTF2QWtBU0xUa2ZITjdGdy1vT1pCZWNxZUpheHlwTDpjYWQ1NHVoRlhGUUViSGR3Vm02aXctVTJoWVE9/dissolve/40/gravity/NorthWest/dx/18/dy/21/ws/0.0/wst/0&e=1735488000&token=P7S2Xpzfz11vAkASLTkfHN7Fw-oOZBecqeJaxypL:C11LKqsRLbAqQo2uVPETYDya0QU=",
                    position: { x: shape.x + shape.width, y: shape.y - 15 }, // 矩形右上角 根据图形动态调整
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
                        that.addFeature(data, type, (this.gFirstFeatureLayer.getAllFeatures().length + 1) + "");
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
                        that.addFeature(data, type, (this.gFirstFeatureLayer.getAllFeatures().length + 1) + "");
                    } else if (type === "LINE" && data.start.x > 0 && data.start.y > 0 && data.end.x > 0 && data.end.y > 0) {
                        this.power = true
                        that.addFeature(data, type, (this.gFirstFeatureLayer.getAllFeatures().length + 1) + "");
                    }
                    else if (type === "POINT" && data.x > 0 && data.y > 0) {
                        this.power = true
                        that.addFeature(data, type, (this.gFirstFeatureLayer.getAllFeatures().length + 1) + "");
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
                        that.addFeature(data, type, (this.gFirstFeatureLayer.getAllFeatures().length + 1) + "");
                    } else if (type === "CIRCLE" && data.r > 10 && data.r + data.cx < 500 && data.r + data.cy < 375 && data.cx - data.r > 0 && data.cy - data.r > 0) {
                        this.power = true
                        that.addFeature(data, type, (this.gFirstFeatureLayer.getAllFeatures().length + 1) + "");
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
                console.log("update");
                let id = feature.id;
                this.getText()
                this.allText.forEach(item => {
                    if (item.id.substring(0, 1) === id) {
                        switch (this.type) {
                            case "RECT": {
                                let position = { x: shape.x, y: shape.y }
                                item.updatePosition(position)
                                break;
                            }
                            case "CIRCLE": {
                                let position = { x: shape.cx, y: shape.cy }
                                item.updatePosition(position)
                                break;
                            }
                            case "POLYGON": {
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
                console.log(this.allText);
                // 更新或者移动需要重新设置删除图标
                that.deIcon();

                feature.updateShape(shape);
                if (feature.type != "POINT") {
                    that.addDeleteIcon(feature, shape);
                }
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
                if (this.allText[i].id.substring(0, 1) !== this.allFeatures[this.allFeatures.length - 1].id) {
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
    },
    mounted() {
        axios.post("http://localhost:3000/imagelist").then((res) => {
            console.log(res.data);
            this.imagelist=res.data
        })
        let that = this;
        //------------------------AILabel创建------------------------------//
        const gMap = new AILabel.Map("map", {
            center: { x: 250, y: 187 },  // 确定中心点
            zoom: 500,
            mode: "RECT", // 绘制线段
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
                src: that.imgUrl,
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
        //---------------------opencv实验-------------------------//
        /*console.log(cv);
        try {
            const classifier = new cv.CascadeClassifier();
            const faceCascadeFile = "../views/haarcascade_frontalface_default.xml";
            console.log(classifier.load(faceCascadeFile));
            console.log(classifier);
            classifier.load(faceCascadeFile);
            console.log("8910");
            const src = cv.imread("1"); // 假设imageElement是一个图像元素，可以是<img>或<canvas>
            const gray = new cv.Mat();
            cv.cvtColor(src, gray, cv.COLOR_RGBA2GRAY);
            cv.equalizeHist(gray, gray); // 对图像进行直方图均衡化（可选）
            const faces = new cv.RectVector();
            const minSize = new cv.Size(30, 30);
            const maxSize = new cv.Size(200, 200); // 可以根据需要调整最小和最大人脸大小
            classifier.detectMultiScale(gray, faces, 1.1, 3, 0, minSize, maxSize);
    
            for (let i = 0; i < faces.size(); ++i) {
                const faceRect = faces.get(i);
                const point1 = new cv.Point(faceRect.x, faceRect.y);
                const point2 = new cv.Point(faceRect.x + faceRect.width, faceRect.y + faceRect.height);
                const faceColor = new cv.Scalar(255, 0, 0);
                cv.rectangle(src, point1, point2, faceColor, 2);
            }
            cv.imshow('canvasoutput', src);
            src.delete()
            gray.delete();
            faces.delete();
        } catch (ex) {
            console.log("error is " + ex);
        }*/


    },
    beforeDestroy() {
        this.gMap.destroy();
    },
};
</script>
   
  <!-- Add "scoped" attribute to limit CSS to this component only -->
<style>
.main {
    display: flex;
    justify-content: center;
    align-items: center;
}

.button-wrap {
    display: flex;
    flex-direction: column;
    padding-bottom: 10px;
    position: relative;
    z-index: 99;
}

#map {
    /* margin: 0 auto; */
    overflow: hidden;
    position: relative;
    height: 600px;
    width: 800px;
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
</style>