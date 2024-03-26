<template>
    <el-card>
        <div slot="header" style="display: flex;justify-content: flex-start;align-items: center;">
            <el-page-header @back="goBack">
            </el-page-header>
            <span>编辑配置</span>
        </div>
        <div class="main">
            <el-card class="teachcard">
                <div slot="header" style="text-align: right">
                    <span @click="gotogenerate"
                        style="color: rgb(36,104,242);text-decoration: underline;cursor: pointer;">前往生成图片区-></span>
                </div>
                <div id="map"></div>
            </el-card>
            <el-card class="teachcard">
                <div slot="header" style="text-align: center;">
                    <i class="el-icon-top toparrow" @click="together(nowselect - 1)"></i>
                </div>
                <div
                    style="display: flex;flex-direction: column;justify-content: flex-start;height: 540px;padding-left: 20px;padding-right: 20px;padding-top: 0;padding-bottom: 0;">
                    <div style="width: 120px;height: 120px;margin-top: 15px;padding: 5px;"
                        v-for="(item, index) in showlist" :key="item.url">
                        <img @click="together(index)" :src="item.ossPath" :class="{ select: index === nowselect % 5 }"
                            style="width: 120px;height: 75px;cursor: pointer;">
                    </div>
                </div>
                <el-divider style="padding: 0;margin: 0;"></el-divider>
                <div style="text-align: center;">
                    <i class="el-icon-bottom toparrow" @click="together(nowselect + 1)"></i>
                </div>
            </el-card>
            <el-collapse v-model="colitem">
                <el-collapse-item name="results">
                    <template slot="title">
                        <div style="color: #666;font-size: 20px;padding: 5px;font-weight: 600;width: 195px;">
                            <span>标注结果</span>
                        </div>
                    </template>
                    <el-card class="teachcard">
                        <div
                            style="height:450px;overflow-y: auto;padding-left: 20px;padding-right: 20px;padding-top: 0;padding-bottom: 0;">
                            <div v-for="(item, index) in nowpicdata" :key="item.id" class="resultlist">
                                <el-card>
                                    <div slot="header" style="display: flex;justify-content: space-between;">
                                        <span style="font-size: 20px;">
                                            <i style="cursor: pointer;font-size: 20px;" class="el-icon-view"
                                                v-if="item.vis" @click="hidefeature(item, index)"></i>
                                            <i style="cursor: pointer;font-size: 20px;" class="el-icon-hide" v-else
                                                @click="appearfeature(item, index)"></i>
                                            <span>{{ item.textInfo.text }}</span>
                                        </span>
                                        <span>
                                            <el-tooltip placement="top-start" content="删除该主体">
                                                <i @click="entity_delete(index)"
                                                    style="cursor: pointer;font-size: 20px;" class="el-icon-minus"></i>
                                            </el-tooltip>
                                            <el-tooltip placement="top-start" content="替换该主体">
                                                <i @click='entity_replace(index)'
                                                    style="cursor: pointer;font-size: 20px;"
                                                    class="el-icon-refresh"></i>
                                            </el-tooltip>
                                        </span>
                                    </div>
                                    <img style="width: 160px;height: 120px;" v-if="item.base64str"
                                        :src="'data:image/gif;base64,' + item.base64str">
                                </el-card>
                            </div>
                        </div>
                    </el-card>
                </el-collapse-item>
            </el-collapse>
        </div>
        <el-dialog title="替换配置" :visible.sync="replacevis" width="24%" top="15%">
            <span>替换生成图像数量</span>
            <el-input-number :step-strictly="true" :min="1" size="small"
                v-model="replaceform.generate"></el-input-number>
            <el-input v-model="replaceform.prompt" size="small" placeholder="请输入替换描述"></el-input>
            <div slot="footer">
                <div style="width: 100%;display: flex;justify-content: space-around;">
                    <el-button :disabled="!replaceform.prompt" type="primary" @click="replace_ok">确定</el-button>
                    <el-button @click="replace_cancel">取消</el-button>
                </div>
            </div>
        </el-dialog>
    </el-card>
</template>
<script>
import AILabel from "ailabel";
import axios from "axios";
//import time from '../util/time'
//import io from 'socket.io-client'
//import FileSaver from "file-saver";
export default {
    data() {
        return {
            colitem: [],
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
            showlist: [],
            Recognizetextcontent: "",
            nowselect: 0,
            page: 1,
            markfilter: "",
            marktype: [{ value: "POLYGON", label: "多边形" }, { value: "POLYLINE", label: "多段线" }, { value: "RECT", label: "矩形" }, { value: "CIRCLE", label: "圆" }, { value: "LINE", label: "线" }, { value: "POINT", label: "点" }],
            project: { projectid: "fdsafd", projectname: "dsa", version: "v1", marktype: "图像文本标注" },
            //处理分割
            rightclick: false,
            segvis: false,
            rect: [],
            pointlist: [],
            seglabels: [],
            newlabel: "",
            segpop: [],
            storage: "",
            nowpicdata: [],
            textprompt: "",
            textpromptdisable: false,
            socket: null,
            replacevis: false,
            replaceform: {
                prompt: "",
                generate: 0,
                number: 0,
                id: 0
            }
        };
    },
    watch: {
        mode: {
            handler(mode) {
                this.gMap.setMode(mode);
                this.setDrawingStyle(mode);
            },
            deep: true
        },
    },
    computed: {
    },
    methods: {
        gotogenerate() {
            console.log(1);
            this.$router.push({
                path: "/RemainPic",
                query: { versionId: this.project.versionId }
            })
        },
        replace_ok() {
            axios.post("http://10.99.212.243:8000/update", this.replaceform)
                .then(res => {
                    if (res.data.code == 200) {
                        this.$message.success('替换成功，生成图像已缓存于图像暂存区，请及时前往筛选')
                    }
                })
                .catch(e => {
                    console.log(e);
                })
            this.replace_cancel()
        },
        replace_cancel() {
            this.replacevis = false
            this.replaceform = {
                prompt: "",
                generate: 0,
                number: 0,
                id: 0
            }
        },
        entity_replace(index) {
            this.replacevis = true
            this.replaceform.id = this.showlist[this.nowselect].id
            this.replaceform.number = index
        },
        entity_delete(index) {
            axios.post("http://10.99.212.243:8000/remove", { id: this.showlist[this.nowselect].id, number: index })
                .then(res => {
                    if (res.data.code === 200) {
                        this.changepic(this.showlist[this.nowselect])
                    }
                })
        },
        /*text_to_segment(url) {
            if (this.textprompt) {
                this.socket.emit("textprompt_to_segment", { url: url, text: this.textprompt, label: this.seglabels })
                this.textpromptdisable = true
            } else {
                this.$message.error("请填写分割信息")
            }
        },
        changelabel(item, index) {
            let a = this.seglabels.find(ele => item.text == ele.label)
            if (a !== undefined) {
                this.gFirstFeatureLayer.removeFeatureById(item.id)
                this.addFeature(item.shape, item.type, item.id, a.color, item.rlecode, item.textInfo, true)
            }
            this.tagtextLayer.removeTextById(item.textid)
            const polygontext = new AILabel.Text(item.textid, { text: item.textInfo.text, position: item.textInfo.position, offset: item.textInfo.offset })
            this.tagtextLayer.addText(polygontext)
            this.nowpicdata[index].edit = false
        },*/
        appearfeature(item, index) {
            this.addFeature(item.shape, item.type, item.id, item.color, item.rlecode, item.textInfo, true)
            const polygontext = new AILabel.Text(item.textid, item.textInfo)
            this.tagtextLayer.addText(polygontext)
            this.nowpicdata[index].vis = true
        },
        hidefeature(item, index) {
            this.gFirstFeatureLayer.removeFeatureById(item.id)
            this.tagtextLayer.removeTextById(item.textid)
            this.nowpicdata[index].vis = false
        },
        /*delmask(mask) {
            this.gFirstFeatureLayer.removeFeatureById(mask.id)
            this.tagtextLayer.removeTextById(mask.textid)
            this.nowpicdata = this.nowpicdata.filter(item => {
                return item.id !== mask.id
            })
        },*/
        /*addlabel() {
            if (this.seglabels.includes(this.newlabel) || this.newlabel === "") {
                this.$notify.error({
                    title: '添加失败',
                    message: this.seglabels.includes(this.newlabel) ? "标签重复" : "标签为空",
                    duration: 3000
                });
            } else {
                this.$notify.success({
                    title: '',
                    message: '添加成功',
                    duration: 3000
                });
                this.seglabels.push({ label: this.newlabel, color: 'rgb(' + Math.floor(Math.random() * (255 - 0)) + ',' + Math.floor(Math.random() * (255 - 0)) + ',' + Math.floor(Math.random() * (255 - 0)) + ')' })
            }
            this.newlabel = ""
        },*/
        /*pointok() {
            if (this.pointlist.length === 0) {
                this.$notify.error({
                    title: '请添加至少一个点',
                    message: this.seglabels.includes(this.newlabel) ? "标签重复" : "标签为空",
                    duration: 3000
                });
                return
            }
            if (!this.vis) {
                const popover = this.$refs.popover;
                let timer = setTimeout(() => {
                    const clientX = this.segpop[0]
                    const clientY = this.segpop[1]
                    this.segpop.splice(0)
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
            this.pointlist.forEach(point => { this.gFirstFeatureLayer.removeFeatureById(point.id) })
            this.pointlist.splice(0)
        },*/
        /*segok() {
            axios.post('http://localhost:5000/api/segment_manual', { point: this.pointlist, box: this.rect, url: this.gMap.layers[0].imageInfo.src })
                .then(res => {
                    let id = Date.now() + ""
                    if (!this.segvis) {
                        if (this.pointlist.length > 1) {
                            this.gFirstFeatureLayer.removeFeatureById(this.storage.id)
                        }
                    }
                    this.addFeature(res.data.point, "POLYGON", id)
                    this.storage = { point: res.data.point, id: id, rlecode: res.data.rle }
                    if (this.rect.length > 0) {
                        this.gFirstFeatureLayer.removeFeatureById(this.rect[4])
                    }
                    this.rect.splice(0)
                    if (!this.segvis) {
                        return
                    }
                    this.pointlist.forEach(point => { this.gFirstFeatureLayer.removeFeatureById(point.id) })
                    this.pointlist.splice(0)
                    if (!this.vis) {
                        const popover = this.$refs.popover;
                        let timer = setTimeout(() => {
                            const clientX = this.segpop[0]
                            const clientY = this.segpop[1]
                            this.segpop.splice(0)
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
                })
                .catch(e => {
                    console.log(e);
                })
        },*/
        /*切图片时把已标注数据标上 */
        keepdraw(markdata, url) {
            let mattinglist = []
            markdata.forEach((item) => {
                if (item.vis) {
                    this.addFeature(item.shape, item.type, item.id, item.color, item.rlecode)
                    let text = new AILabel.Text(item.textid, item.textInfo)
                    this.tagtextLayer.addText(text)
                }
                if (!Object.prototype.hasOwnProperty.call(item, 'base64str')) {
                    mattinglist.push({ code: item.rlecode, id: item.id })
                }
            })
            if (mattinglist.length > 0) {
                axios.post("http://localhost:5000/api/matting", { url: url, mattinglist: mattinglist })
                    .then(res => {
                        console.log(this.nowpicdata);
                        res.data.forEach(item => {
                            this.nowpicdata[this.nowpicdata.findIndex(item2 => item2.id == item.id)].base64str = item.code
                        })
                    })
                    .catch(e => {
                        console.log(e);
                    })
            }
        },
        //汇总框选向后台提交//
        together(num) {
            /*let jsondata = JSON.stringify(this.nowpicdata)
            let file = new FormData()
            const blob = new Blob([jsondata]);
            file.set("file", blob, "data.json")
            file.set("id", this.showlist[this.nowselect].id)*/
            if (this.page === 1 && num === -1) {
                this.$message.warning("已经是第一张了")
                return
            } else if (num === this.showlist.length || num == -1) {
                this.gMap.destroy()
                this.page = num == -1 ? this.page - 1 : this.page + 1
                this.getdata(this.page, num == -1 ? 0 : 1)
            } else {
                this.gMap.destroy()
                this.changepic(this.showlist[num])
                this.nowselect = num
            }
            /*axios.put("http://120.26.142.114:10010/dataset/call", file, { headers: { "Content-Type": "multipart/form-data;charset=utf-8" } }).then((res) => {
                if (res.data.code === 200) {
                    console.log(res.data.data);
                    this.showlist[this.nowselect].mark = res.data.data
                    let a = (this.colitem.findIndex(item => item === 'results'))
                    this.colitem.splice(a, 1)
                    
                } else {
                    this.$message.error("保存失败")
                }

            })*/
        },
        /*ok() {
            this.power = false
            if (this.Recognizetextcontent === "") {
                return
            }
            if (this.type === "RECT") {
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const recttext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2.x, y: this.data2.y }, offset: { x: 1, y: this.data2.y < 19 ? -this.data2.y - this.data2.height - 25 : 0 } })
                this.tagtextLayer.addText(recttext)
                this.Recognizetextcontent = ""
                //this.showlist[this.nowselect].mark.push({ type: "RECT", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "POLYGON") {
                let sum_x = this.data2.reduce((acc, current) => acc + current.x, 0);
                let sum_y = this.data2.reduce((acc, current) => acc + current.y, 0);
                sum_x = sum_x / this.data2.length
                sum_y = sum_y / this.data2.length
                let id = Date.now() + ""
                this.gFirstFeatureLayer.removeFeatureById(this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id)
                axios.post("http://localhost:5000/api/getmask", { point: this.data2, url: this.showlist[this.nowselect].url, type: "POLYGON" })
                    .then(res => {
                        this.addFeature(this.data2, "POLYGON", id, this.seglabels[this.Recognizetextcontent].color, res.data, { text: this.seglabels[this.Recognizetextcontent].label, position: { x: sum_x, y: sum_y }, offset: { x: 1, y: 0 } })
                        let textid = id + "-" + 0
                        const polygontext = new AILabel.Text(textid, { text: this.seglabels[this.Recognizetextcontent].label, position: { x: sum_x, y: sum_y }, offset: { x: 1, y: 0 } })
                        this.tagtextLayer.addText(polygontext)
                        this.Recognizetextcontent = ""
                    })
                    .catch(e => {
                        console.log(e);
                    })
                //this.showlist[this.nowselect].mark.push({ type: "POLYGON", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
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
                this.Recognizetextcontent = ""
                //this.showlist[this.nowselect].mark.push({ type: "POLYLINE", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "CIRCLE") {
                let id = Date.now() + ""
                this.gFirstFeatureLayer.removeFeatureById(this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id)
                axios.post("http://localhost:5000/api/getmask", { point: this.data2, url: this.showlist[this.nowselect].url, type: "CIRCLE" })
                    .then(res => {
                        this.addFeature(this.data2, "CIRCLE", id, this.seglabels[this.Recognizetextcontent].color, res.data, { text: this.seglabels[this.Recognizetextcontent].label, position: { x: this.data2.cx, y: this.data2.cy }, offset: { x: 0, y: 0 } })
                        let textid = id + "-" + 0
                        const polygontext = new AILabel.Text(textid, { text: this.seglabels[this.Recognizetextcontent].label, position: { x: this.data2.cx, y: this.data2.cy }, offset: { x: 0, y: 0 } })
                        this.tagtextLayer.addText(polygontext)
                        this.Recognizetextcontent = ""
                    })
                    .catch(e => {
                        console.log(e);
                    })

                //this.showlist[this.nowselect].mark.push({ type: "CIRCLE", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "POINT") {
                this.gFirstFeatureLayer.removeFeatureById(this.storage.id)
                let sum_x = this.storage.point.reduce((acc, current) => acc + current.x, 0);
                let sum_y = this.storage.point.reduce((acc, current) => acc + current.y, 0);
                sum_x = sum_x / this.storage.point.length
                sum_y = sum_y / this.storage.point.length
                this.addFeature(this.storage.point, 'POLYGON', Date.now() + "", this.seglabels[this.Recognizetextcontent].color, this.storage.rlecode, { text: this.seglabels[this.Recognizetextcontent].label, position: { x: sum_x, y: sum_y }, offset: { x: 1, y: 0 } })
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.seglabels[this.Recognizetextcontent].label, position: { x: sum_x, y: sum_y }, offset: { x: 1, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                if (this.segvis) {
                    this.segvis = false
                    this.setMode("RECT")
                }
                this.Recognizetextcontent = ""
                //this.showlist[this.nowselect].mark.push({ type: "POINT", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            } else if (this.type === "LINE") {
                let textid = this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id + "-" + 0
                const polygontext = new AILabel.Text(textid, { text: this.Recognizetextcontent, position: { x: this.data2.start.x, y: this.data2.start.y }, offset: { x: 1, y: 0 } })
                this.tagtextLayer.addText(polygontext)
                this.Recognizetextcontent = ""
                //this.showlist[this.nowselect].mark.push({ type: "LINE", id: this.gFirstFeatureLayer.getAllFeatures()[this.gFirstFeatureLayer.getAllFeatures().length - 1].id, shape: this.data2, text: { text: this.Recognizetextcontent, id: textid } })
            }
            this.vis = false
        },*/
        /*la(e) {
            if (this.type === "POINT") {
                this.segpop.push(e.clientX)
                this.segpop.push(e.clientY)
                let a = setTimeout(() => {
                    if (this.selected || !this.power) {
                        return
                    }
                    if (this.type === "LINE") {
                        this.linenumber += 1
                    }
                    if (this.type === "CIRCLE" || (this.type === "LINE" && this.linenumber % 2 === 0)) {
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
            if (this.selected || !this.power) {
                return
            }
            if ((this.type === "POLYGON" || this.type === "POLYLINE") && this.data2) {
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
        },*/
        /*zoomIn() {
            this.gMap.zoomIn();
        },
        zoomOut() {
            this.gMap.zoomOut();
        },
        setMode(mode) {
            if (!this.segvis) {
                let features = this.gFirstFeatureLayer.getAllFeatures()
                features.forEach(item => {
                    if (!Object.prototype.hasOwnProperty.call(item.props, 'rlecode')) {
                        this.gFirstFeatureLayer.removeFeatureById(item.id)
                        this.vis = false
                    }
                })
            }
            if (this.segvis && mode !== 'POINT') {
                return
            }
            this.pointlist.splice(0)
            this.mode = mode;
            this.linenumber = 0
            this.type = mode
        },*/
        // 获取所有features
        getFeatures() {
            this.allFeatures = this.gFirstFeatureLayer.getAllFeatures();
        },
        getText() {
            this.allText = this.tagtextLayer.texts;
        },
        // 初始样式
        /*setDrawingStyle(mode) {
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
                    this.drawingStyle = { fillStyle: "rgb(255,0,0)" };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //圆
                case "CIRCLE": {
                    this.drawingStyle = {
                        fillStyle: "#ff0000",
                        strokeStyle: "#ff0000",
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
                        strokeStyle: "rgb(255,0,0)",
                        lineJoin: "round",
                        lineCap: "round",
                        lineWidth: 8,
                        arrow: false,
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //多线段
                case "POLYLINE": {
                    this.drawingStyle = {
                        strokeStyle: "rgb(255,0,0)",
                        lineJoin: "round",
                        lineCap: "round",
                        lineWidth: 8,
                        stroke: true
                    };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //矩形
                case "RECT": {
                    this.drawingStyle = { strokeStyle: "rgb(255,0,0)", lineWidth: 2, stroke: true };
                    this.gMap.setDrawingStyle(drawingStyle);
                    break;
                }
                //多边形
                case "POLYGON": {
                    this.drawingStyle = {
                        strokeStyle: "rgb(255,0,0)", //边框颜色
                        fill: true, //是否填充
                        //fillStyle: "rgb(145,172,218)", //填充色
                        globalAlpha: 0.3,
                        lineWidth: 12,
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
        },*/

        // 添加图形
        addFeature(data, type, id, color = null, rlecode = null, textInfo = null, isappear = false, base64str = null) {
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
                this.segvis = true
                this.rect.push(data.x)
                this.rect.push(data.y)
                this.rect.push(data.x + data.width)
                this.rect.push(data.y + data.height)
                this.rect.push(id)
                this.setMode("POINT")
                this.segpop.push(window.event.clientX)
                this.segpop.push(window.event.clientY)
            }
            //多边形
            else if (type === "POLYGON") {
                const polygonFeature = new AILabel.Feature.Polygon(
                    id, // id
                    { points: data }, // shape
                    rlecode !== null ? { rlecode } : { name }, // props
                    {
                        strokeStyle: color === null ? "rgb(36,104,242)" : color, //边框颜色
                        fill: true, //是否填充
                        fillStyle: color === null ? "rgb(145,172,218)" : color, //填充色
                        globalAlpha: 0.5,
                        lineWidth: 3,
                        stroke: false,
                    } // style
                );
                that.gFirstFeatureLayer.addFeature(polygonFeature);
            }
            //点
            else if (type == "POINT") {
                const gFirstFeaturePoint = new AILabel.Feature.Point(
                    id, // id
                    { x: data.x, y: data.y, r: 5 }, // shape
                    { name }, // props
                    { fillStyle: this.rightclick ? "rgb(255,0,0)" : "rgb(0,255,0)", zIndex: 5, lineWidth: 255 } // style
                );
                that.gFirstFeatureLayer.addFeature(gFirstFeaturePoint);
                if (!this.segvis) {
                    this.segok()
                }
                this.rightclick = false
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
                    rlecode !== null ? { rlecode } : { name }, // props
                    {
                        fill: true, //是否填充
                        fillStyle: color === null ? "rgb(145,172,218)" : color, //填充色
                        strokeStyle: color === null ? "rgb(145,172,218)" : color,
                        stroke: false,
                        globalAlpha: 0.5,
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
            if (rlecode !== null && textInfo !== null && !isappear & base64str == null) {
                axios.post("http://localhost:5000/api/matting", { url: this.showlist[this.nowselect].url, mattinglist: [{ code: rlecode, id: id }] })
                    .then(res => {
                        this.nowpicdata.push({
                            base64str: res.data[0].code,
                            color: color,
                            id: res.data[0].id,
                            shape: data,
                            rlecode: rlecode,
                            type: type,
                            textid: res.data[0].id + "-0",
                            textInfo: textInfo,
                            vis: true,
                            edit: false
                        })
                    })
                    .catch(e => {
                        console.log(e);
                    })
            }
            this.getFeatures();
        },
        /* 增加删除图标
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
                    src: "../../delete.png",
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
                this.nowpicdata = this.nowpicdata.filter(item => {
                    return item.id !== feature.id
                })
                this.getText(feature.id)
                this.tagtextLayer.removeTextById(feature.id + "-0")
                this.selected = false
                this.power = false
            });
            gMap.markerLayer.addMarker(gFirstMarker);
 
            // that.gFirstFeatureLayer
        },
        // 删除 删除按钮
        deIcon() {
            this.gMap.markerLayer.removeAllMarkers();
        },*/
        // 增加事件
        addEvent() {
            let that = this;
            let gMap = this.gMap;
            gMap.events.on("drawDone", (type, data) => {
                this.data2 = data
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
                        let id = Date.now() + ""
                        this.power = true
                        data.label = this.rightclick ? 0 : 1
                        data.id = id
                        this.pointlist.push(data)
                        if (!this.segvis || (data.x > this.rect[0] && data.x < this.rect[2] && data.y > this.rect[1] && data.y < this.rect[3]))
                            that.addFeature(data, type, id);
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
                let id = feature.id;
                this.getText()
                this.allText.forEach(item => {
                    if (item.id.split("-")[0] === id) {
                        switch (feature.type) {
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
        /*getPoints(feature) {
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
            this.segvis = false
        },*/
        changepic(item) {
            let that = this
            const gMap = new AILabel.Map("map", {
                center: { x: 250, y: 187 },  // 确定中心点
                zoom: 500,
                mode: "BAN", // 绘制线段
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
                    src: item.ossPath,
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
            this.nowpicdata = []
            if (item.calloutPath) {
                axios.get(item.calloutPath)
                    .then(res => {
                        res.data.map(ele => {
                            ele.edit = false
                        })
                        this.nowpicdata = res.data
                        this.keepdraw(res.data, item.ossPath)
                    }).catch(e => {
                        console.log(e);
                    })
            }
            this.rect.splice(0)
            this.segvis = false
            this.rightclick = false
            this.pointlist.splice(0)
            this.segpop.splice(0)
            this.storage = ""
            window.onresize = function () {
                this.gMap && this.gMap.resize();
            };
            /*if (item.data) {
                axios.get(item.data).then(res => {
                    item.mark = res.data
                    this.keepdraw(res.data)
                })
            }*/
        },
        goBack() {
            this.$router.push("/ProjectList")
        },
        getdata(page, num) {
            console.log();
            axios.post("http://120.26.142.114:10010/dataset/admin/select", { version: this.project.versionId, current: page, pageSize: 5 })
                .then(res => {
                    if (res.data.data.length === 0) {
                        this.$message.warning("已经是最后一张了")
                        return
                    }
                    this.showlist.splice(0)
                    this.showlist = res.data.data.datasetCallNewVOS;
                    this.changepic(this.showlist[num == 1 ? 0 : 4])
                    this.nowselect = num == 1 ? 0 : 4
                })
                .catch(e => {
                    console.log(e);
                })
        }
    },
    connect: function (data) {
        console.log(data)
    },
    mounted() {
        this.project = this.$route.query
        this.project.verisonId -= 0
        this.getdata(1, 1)
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
    align-items: flex-start;
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
    align-items: center;
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
    cursor: pointer;
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

.segment {
    font-size: 12px;
    cursor: pointer;
}

.segment:hover {
    color: rgb(36, 104, 242);
    text-decoration: underline;
}

.labelblock {
    border: 1px solid rgb(221, 221, 221);
    display: flex;
    justify-content: flex-start;
    align-items: center;
    height: 65px;
    width: 190px;
    padding-left: 5px;
    cursor: pointer;
    margin-bottom: 15px;
}

.labelblock:hover {
    border: 1px solid rgb(36, 104, 242);
}

.resultlist {
    padding: 8px;
}
</style>